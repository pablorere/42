#include <string>
#include <iostream>
#include <cstring>
int main(int ac, char **av)
{
    std::string size;
    size += strlen(av[1]) + '0';

    std::cout << size << std::endl;
    return (0);
}