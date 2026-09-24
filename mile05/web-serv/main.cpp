#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <cstring>
#include <cstdio>
#include <cerrno>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>

int main() {
    // ========================================================================
    // 1. SOCKET INITIALIZATION & SETUP
    // ========================================================================
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Allow port to be reused immediately after server restarts
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("Setsockopt failed");
        close(server_fd);
        return 1;
    }

    // Configure the address structure (IP and Port)
    struct sockaddr_in address;
    std::memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(9501);

    // Bind the socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        return 1;
    }

    // Listen for connections
    if (listen(server_fd, SOMAXCONN) < 0) {
        perror("Listen failed");
        close(server_fd);
        return 1;
    }

    // Make the server listening socket non-blocking
    if (fcntl(server_fd, F_SETFL, O_NONBLOCK) < 0) {
        perror("Fcntl failed on server_fd");
        close(server_fd);
        return 1;
    }

    std::cout << "Asynchronous Server listening on http://localhost:9501" << std::endl;

    // ========================================================================
    // 2. EPOLL INITIALIZATION
    // ========================================================================
    int epoll_fd = epoll_create(10); 
    if (epoll_fd == -1) {
        perror("epoll_create failed");
        close(server_fd);
        return 1;
    }

    // Register the server socket to listen for incoming connections (EPOLLIN)
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = server_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &ev) < 0) {
        perror("epoll_ctl failed for server_fd");
        close(server_fd);
        close(epoll_fd);
        return 1;
    }

    const int MAX_EVENTS = 10;
    struct epoll_event events[MAX_EVENTS];

    // [EFFORT NEEDED 1 - ARCHITECTURE]: This is a primitive map just to hold strings.
    // In your real project, this MUST become a map of `std::map<int, Client>` where 
    // `Client` is a class tracking parse state, write offsets, and timestamps.
    std::map<int, std::string> client_buffers;

    // ========================================================================
    // 3. THE EVENT LOOP
    // ========================================================================
    while (true) {
        // The program ONLY pauses here. Waits until at least one fd is ready.
        int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if (nfds < 0) {
            perror("epoll_wait error");
            break; 
        }
        
        for (int i = 0; i < nfds; i++) {
            int current_fd = events[i].data.fd;

            // SCENARIO A: NEW CONNECTION
            if (current_fd == server_fd) {
                int new_socket = accept(server_fd, NULL, NULL);
                if (new_socket < 0) continue; 

                // Make the new client non-blocking
                fcntl(new_socket, F_SETFL, O_NONBLOCK);

                // Register the new client with epoll to read data (EPOLLIN)
                ev.events = EPOLLIN;
                ev.data.fd = new_socket;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, new_socket, &ev);
                
                client_buffers[new_socket] = ""; // Initialize their buffer
                std::cout << "New client connected: fd " << new_socket << std::endl;
            } 
            
            // SCENARIO B: CLIENT SENT DATA (READY TO READ)
            else if (events[i].events & EPOLLIN) {
                char buffer[1024] = {0};
                int bytes_read = recv(current_fd, buffer, sizeof(buffer) - 1, 0);

                // [EFFORT NEEDED 2 - DISCONNECTS]: bytes_read == 0 means the client 
                // closed the connection. bytes_read < 0 means error. You must handle 
                // both gracefully by cleaning up fd and memory without crashing.
                if (bytes_read <= 0) {
                    std::cout << "Client disconnected: fd " << current_fd << std::endl;
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, current_fd, NULL);
                    close(current_fd);
                    client_buffers.erase(current_fd);
                    continue;
                }

                // Append new bytes to this specific client's buffer
                client_buffers[current_fd].append(buffer, bytes_read);

                // [EFFORT NEEDED 3 - HTTP PARSING]: This simple check only looks for 
                // the end of headers. Your real parser must check Content-Length to 
                // know if a body exists, un-chunk chunked requests, and build an AST.
                if (client_buffers[current_fd].find("\r\n\r\n") != std::string::npos) {
                    std::cout << "Full HTTP headers received on fd " << current_fd << std::endl;
                    
                    // We have the full request. Tell epoll we want to SEND data now.
                    ev.events = EPOLLOUT;
                    ev.data.fd = current_fd;
                    epoll_ctl(epoll_fd, EPOLL_CTL_MOD, current_fd, &ev);
                }
            } 
            
            // SCENARIO C: SOCKET IS CLEAR (READY TO WRITE)
            else if (events[i].events & EPOLLOUT) {
                
                // [EFFORT NEEDED 4 - FILE I/O]: Opening the file synchronously here 
                // on every request is terrible for performance. Your server should 
                // map URIs to files during the parsing phase.
                std::ifstream file("image.png", std::ios::binary | std::ios::ate);
                if (!file) {
                    std::string err = "HTTP/1.1 404 Not Found\r\n\r\nImage not found.";
                    send(current_fd, err.c_str(), err.length(), 0);
                } else {
                    std::streamsize size = file.tellg();
                    file.seekg(0, std::ios::beg);
                    std::vector<char> img_buffer(size);
                    file.read(&img_buffer[0], size);

                    std::ostringstream header;
                    header << "HTTP/1.1 200 OK\r\n"
                           << "Content-Type: image/png\r\n"
                           << "Content-Length: " << size << "\r\n"
                           << "Connection: close\r\n\r\n";
                    
                    std::string header_str = header.str();
                    
                    // [EFFORT NEEDED 5 - PARTIAL SENDS]: send() is NOT guaranteed to 
                    // send all these bytes at once. If it only sends half, your code 
                    // currently drops the rest. You must track `bytes_sent` inside 
                    // your Client class and return here on the next loop to resume sending!
                    send(current_fd, header_str.c_str(), header_str.length(), 0);
                    send(current_fd, &img_buffer[0], size, 0);
                }

                // Cleanup after sending the response
                std::cout << "Response sent, closing fd " << current_fd << std::endl;
                epoll_ctl(epoll_fd, EPOLL_CTL_DEL, current_fd, NULL);
                close(current_fd);
                client_buffers.erase(current_fd);
            }
        }
    }

    close(server_fd);
    close(epoll_fd);
    return 0;
}