# webserv — Concepts & Study Guide (42)

*This project has been created as part of the 42 curriculum by ppaula-s.*

> **Status.** This repository currently contains only the subject (`webserv.pdf`).
> This document is the **concept guide** you read *before* writing the server: it
> explains every mechanism the project forces you to build, and — because the
> engineering is transferable — how the same ideas apply to *any* project with
> similar requirements (event-driven servers, protocol implementations, parsers,
> process-based CGI). The **Instructions** section will be completed with the real
> config paths and run commands once the code exists.

---

## Description

Write an **HTTP server in C++ 98** that you can point a real browser at. It must be
**fully non-blocking**, driven by **a single `poll()`** (or `select`/`epoll`/`kqueue`)
covering *all* socket and pipe I/O including the listening socket, and it must never
call `read`/`write` on an I/O descriptor outside that readiness check. It has to:

- speak HTTP well enough to serve a **static website** to a standard browser;
- implement at least **GET, POST and DELETE**;
- accept **file uploads**;
- execute **CGI** (fork is allowed *only* for this);
- listen on **multiple ports** serving different content;
- read an **NGINX-style configuration file** (routes, roots, redirects, upload dirs,
  error pages, body-size limit, autoindex, CGI-by-extension);
- **never crash, never hang**, and never leak descriptors or memory.

Reading **RFC 7230–7233** (or the current **RFC 9110–9112**) and poking at a real
NGINX with `telnet`/`curl` before coding is part of the assignment, not optional
background.

---

## What you are building, in one picture

A **single-process, event-driven server**. One thread of control, one event loop,
many simultaneous connections, each a small state machine.

```
                          ┌──────────────────────────────────────────┐
                          │              webserv (1 process)          │
                          │                                           │
   browser ──TCP:8080──►  │   listen_fd ─┐                            │
   browser ──TCP:8081──►  │   listen_fd ─┼─►  ┌──────────────────┐     │
   curl    ──TCP:8080──►  │   conn_fd  ──┼─►  │  poll()  (ONE)   │     │
                          │   cgi_pipe ──┘    └────────┬─────────┘     │
                          │                          │ readiness     │
                          │              ┌───────────▼───────────┐     │
                          │              │  per-connection state  │     │
                          │              │  read buf / write buf  │     │
                          │              │  parse state / target  │     │
                          │              └───────────┬───────────┘     │
                          │                          │                 │
                          │        HTTP parse ─► route (config) ─► act │
                          │         static · upload · delete · CGI     │
                          └──────────────────────────────────────────┘
```

Three ideas carry the whole project:

1. **Readiness, not blocking** — ask the kernel who is ready, then act.
2. **Byte streams, not messages** — TCP gives you bytes; *you* reassemble requests.
3. **State per connection** — the server's only long-lived context is a table of
   connection objects, each in a known state.

---

## Instructions

### Build

```sh
make          # builds ./webserv
make re       # clean rebuild
make clean    # remove object files
make fclean   # remove object files + binary
```

The Makefile must contain `$(NAME)`, `all`, `clean`, `fclean`, `re`, compile with
`c++ -Wall -Wextra -Werror -std=c++98`, and **must not relink unnecessarily**.

### Run

```sh
./webserv [configuration file]     # config is optional only if a default path exists
```

### Test (once implemented)

```sh
curl -v http://127.0.0.1:8080/                       # request + response headers
curl -i -X DELETE http://127.0.0.1:8080/file.txt
printf 'GET / HTTP/1.0\r\n\r\n' | nc 127.0.0.1 8080  # raw request, no browser magic
```

> This section will gain concrete paths (default config location, sample routes,
> CGI interpreter used) as the implementation lands. Treat it as the contract the
> README must eventually fulfil, not as finished instructions.

---

## Concept map

| # | Concept | Why it is required | Where to study |
|---|---------|--------------------|----------------|
| 1 | **HTTP/1.x message format** | You are implementing the protocol | RFC 9110–9112 (or 7230–7233) |
| 2 | **TCP sockets** (`socket`/`bind`/`listen`/`accept`) | Every connection starts here | `man 2 socket`, Beej's Guide |
| 3 | **Byte order & addressing** (`htons`, `getaddrinfo`) | Ports/IPs live in network order | Beej's Guide ch. 3–5 |
| 4 | **Non-blocking I/O** (`O_NONBLOCK`) | Required: no call may stall the loop | `man 2 fcntl`, `man 2 poll` |
| 5 | **I/O multiplexing** (`poll`/`select`/`epoll`/`kqueue`) | The core of the architecture | `man 2 poll`, `man 7 epoll` |
| 6 | **Reactor / event loop** | Ties readiness to state machines | "Reactor pattern" |
| 7 | **Request state machine** | TCP has no message boundaries | this doc §5 |
| 8 | **Chunked transfer coding** | Required to un-chunk CGI bodies | RFC 9112 §7 |
| 9 | **Response construction** | Correct status codes + framing | RFC 9110 §15 |
| 10 | **MIME types** | Browsers need `Content-Type` | IANA media-type registry |
| 11 | **Config grammar + parser** | The subject mandates a config file | NGINX `server` blocks |
| 12 | **Routing / prefix matching** | Decide *what* a URL maps to | NGINX `location` docs |
| 13 | **Path safety** | `..` traversal must never escape root | CWE-22 |
| 14 | **Uploads & multipart** | POST file upload is mandatory | RFC 7578 (`multipart/form-data`) |
| 15 | **CGI (RFC 3875)** | Required; the only legal `fork` | RFC 3875, `man 2 fork/execve` |
| 16 | **Signals & zombies** | `SIGPIPE`, `waitpid` after CGI | `man 7 signal`, `man 2 waitpid` |
| 17 | **Robustness under stress** | "Never crash, never hang" | `ab`, `siege`, `wrk` |
| 18 | **C++98 discipline** | Hard build constraint | `man` on `<cstring>` etc. |

---

## 1. HTTP — the protocol you are implementing

### Message shape

A request is a **start line**, zero or more **header fields**, an empty line, then an
optional **body**:

```
GET /index.html?lang=en HTTP/1.1\r\n
Host: localhost:8080\r\n
User-Agent: curl/8\r\n
Accept: */*\r\n
\r\n
<body bytes, length defined by Content-Length or Transfer-Encoding>
```

A response mirrors it:

```
HTTP/1.1 200 OK\r\n
Date: Thu, 24 Sep 2026 12:00:00 GMT\r\n
Server: webserv/1.0\r\n
Content-Length: 1234\r\n
Content-Type: text/html\r\n
Connection: keep-alive\r\n
\r\n
<html>...
```

Line endings are **CRLF** (`\r\n`), the header/body separator is a **bare CRLF**, and
field names are case-insensitive while field *values* are mostly not.

### Methods

| Method | Semantics | Must handle |
|--------|-----------|-------------|
| `GET` | retrieve a resource | yes |
| `POST` | send data (form, upload) | yes |
| `DELETE` | remove a resource | yes |
| `HEAD` | like GET without body | optional (nice, tests can be lenient) |
| `OPTIONS` | capabilities | optional |

Unknown/unsupported method → **501 Not Implemented**; known but disallowed on a route
→ **405 Method Not Allowed** with an `Allow:` header.

### Status codes you will actually use

| Code | Meaning | When |
|------|---------|------|
| 200 | OK | success |
| 201 | Created | POST that creates a resource |
| 204 | No Content | success with empty body (optional) |
| 301 / 302 | Moved Permanently / Found | configured redirect |
| 400 | Bad Request | malformed request line/headers |
| 403 | Forbidden | path exists, access denied |
| 404 | Not Found | no such resource |
| 405 | Method Not Allowed | method not allowed on route (`Allow`) |
| 408 | Request Timeout | idle client |
| 411 | Length Required | body without framing header |
| 413 | Payload Too Large | exceeds `client_max_body_size` |
| 414 | URI Too Long | request target absurdly long |
| 500 | Internal Server Error | unexpected failure (must not crash) |
| 501 | Not Implemented | unknown method |
| 502 | Bad Gateway | CGI produced garbage / died |
| 505 | HTTP Version Not Supported | not HTTP/1.x |

### HTTP/1.0 vs HTTP/1.1

| Aspect | 1.0 | 1.1 |
|--------|-----|-----|
| `Host` header | optional | **required** (400 without it) |
| Persistent connection | opt-in via `Connection: keep-alive` | **default** |
| `Transfer-Encoding: chunked` | not defined | defined, bodies can be streamed |

The subject suggests **HTTP/1.0 as a reference, not enforced** — so a pragmatic
target is *1.0 semantics with 1.1 niceties*: always send a valid status line,
honour `Host`, support `Connection: close`/`keep-alive`, and un-chunk whatever you
receive. Whatever version you advertise, the framing must be exact.

### The framing rules that matter

- `Content-Length: N` — read exactly `N` body bytes. Reject two conflicting lengths.
- `Transfer-Encoding: chunked` — body arrives as `size CRLF data CRLF`, terminated by
  `0 CRLF` (plus optional trailers). If both headers are present, chunked wins (and
  per RFC a 400 is defensible).
- No framing header on a request that has a body → **411**.
- `Expect: 100-continue` — an edge case; you may answer `100 Continue` or reject.
- Percent-encoding (`%20`, `%2F`) applies to the **path**; `+` means space only in
  query strings / form bodies, **not** in the path.

---

## 2. TCP sockets

HTTP sits on TCP, a **reliable byte stream with no message boundaries**. A single
`recv` may return half a header, exactly one request, or three requests glued
together — your parser must tolerate all three.

Server lifecycle:

```cpp
int listen_fd = socket(AF_INET, SOCK_STREAM, 0);

int yes = 1;
setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)); // avoid TIME_WAIT rebind pain

struct sockaddr_in addr;
std::memset(&addr, 0, sizeof(addr));
addr.sin_family      = AF_INET;
addr.sin_addr.s_addr = htonl(INADDR_ANY);   // host byte order -> network byte order
addr.sin_port        = htons(port);         // port is 16-bit

bind(listen_fd, (struct sockaddr *)&addr, sizeof(addr));
listen(listen_fd, SOMAXCONN);               // backlog: pending-connection queue

// accept() is only called when poll() says listen_fd is readable
int conn_fd = accept(listen_fd, NULL, NULL);
fcntl(conn_fd, F_SETFL, O_NONBLOCK);        // never block on a client
```

Facts worth internalising:

- **Network byte order.** `sin_port`/`sin_addr` are big-endian; use `htons`/`htonl`
  on the way out and `ntohs`/`ntohl` on the way in.
- **`INADDR_ANY` (`0.0.0.0`)** binds every interface; a specific address binds one.
- **`SO_REUSEADDR`** lets you restart the server while old sockets are in `TIME_WAIT`.
- **`accept` may fail** transiently under load (`EMFILE`, or no pending connection);
  the server must continue, not abort.
- **`getaddrinfo`** turns host/service into a list of candidate `sockaddr`s — use it
  to resolve `listen host:port` from the config, and free with `freeaddrinfo`.
- **Closing**: `close(fd)` releases the descriptor; `shutdown(fd, SHUT_WR)` sends FIN
  while still reading. A half-closed connection is a normal HTTP event (`recv` → 0).
- On macOS, non-blocking writes behave differently, which is why the subject allows
  `fcntl` — **only** with `F_SETFL`, `O_NONBLOCK`, `FD_CLOEXEC`.

---

## 3. Non-blocking I/O and the single `poll()`

This is the heart of the project and the strictest rule in the subject:

> I/O that can wait (sockets, pipes/FIFOs) must be non-blocking and driven by a
> single `poll()`. Calling `read`/`recv` or `write`/`send` on those descriptors
> without prior readiness gets a **grade of 0**. Regular disk files are exempt.

### Why one `poll()`

With blocking sockets you would need one thread/process per connection. With
readiness notification you multiplex thousands of sockets on one thread: the kernel
tells you *which* descriptor can make progress without blocking.

| Mechanism | Portability | Notes |
|-----------|-------------|-------|
| `poll` | POSIX, everywhere | no `FD_SETSIZE` limit; level-triggered |
| `select` | oldest, everywhere | `FD_SETSIZE` cap, rebuilds fd sets |
| `epoll` | Linux | scalable; supports edge-triggered |
| `kqueue` | BSD/macOS | scalable |

**`poll()` is level-triggered**: as long as data is unread, it keeps reporting
readable. That makes partial handling safe — read what you can, stay in the loop.

### The loop

```cpp
struct pollfd fds[MAX_FDS];
// 1. fill fds[] from listen_fds + open connections + CGI pipes
//    events: POLLIN always; POLLOUT only when we have bytes queued to send
// 2. block until something is ready (or a timeout, for housekeeping)
int n = poll(fds, nfds, timeout_ms);
// 3. dispatch each entry with revents != 0
```

Readiness means *permitted*, not *mandatory*:

- `POLLIN` → `recv`/`read` until it returns `<= 0`.
  - `> 0`: append to the connection's read buffer.
  - `== 0`: peer closed → finish, flush pending writes, then close.
  - `< 0`: error; close the connection.
- `POLLOUT` → `send`/`write` as much of the write buffer as possible; when it drains,
  **stop requesting `POLLOUT`** or you will busy-spin.
- `POLLERR`/`POLLHUP`/`POLLNVAL` → tear the connection down.

### Consequences you must design for

- **Partial reads and writes.** `send` can accept fewer bytes than you gave it. Keep a
  per-connection **write buffer** and resume at the offset where you stopped.
- **Never dereference past what you read.** Parse against the accumulated buffer, and
  only when a complete unit (request line, all headers, full body) is present.
- **`errno` is off-limits after `read`/`write`.** Judge the outcome by the *return
  value* and by `revents`, never by inspecting `errno` to change behaviour. (Signals
  that interrupt a call are handled by retrying: if `< 0`, just wait for readiness
  again.)
- **Disk files are synchronous.** For `open`/`read`/`write` on regular files you may
  call them directly; only sockets/pipes need readiness.
- **No indefinite hangs.** Track `last_activity` per connection and close idle
  clients (→ 408), which also neutralises slowloris-style attacks.
- **Descriptor budget.** Handle `accept` failing with `EMFILE`; keep the fd table
  bounded; close on every exit path.

Minimal loop skeleton:

```cpp
while (g_running)
{
    build_pollfds(fds, nfds);          // listen sockets + connections (+ CGI pipes)
    if (poll(fds, nfds, 1000) < 0)
        continue;                       // transient; do not abort
    for (each ready fd)
        switch (kind_of(fd))
        {
            case LISTEN: accept_loop(fd);   // accept until EAGAIN
            case CLIENT: on_readable(c) / on_writable(c);
            case CGI:    pump_child(c);
        }
    reap_dead_connections();
    reap_children();                    // waitpid(WNOHANG) — no zombies
}
```

---

## 4. Per-connection state

Everything the server knows about a client lives in one struct. This is what makes a
stateless event loop possible.

```cpp
struct Connection
{
    int                      fd;            // -1 when gone
    std::string              in;            // bytes read, not yet consumed
    std::string              out;           // bytes waiting to be sent
    size_t                   sent;          // how much of `out` left already
    int                      parse_state;   // REQUEST_LINE / HEADERS / BODY / DONE
    Request                  request;       // method, target, version, headers
    const ServerConfig*      server;        // which server block accepted this
    time_t                   last_activity;
    bool                     keep_alive;
};
```

Rules:

- One struct per client, keyed by fd, removed on close. **RAII everywhere** so a
  removal cannot leak.
- `in` and `out` are independent; a request can be fully parsed and answered while an
  earlier response is still being written (pipelining) — or, simpler and acceptable,
  answer strictly one request at a time per connection.
- Keep the write offset, not a copy, to avoid O(n²) buffer churn.

---

## 5. Request parsing as a state machine

Because TCP has no boundaries, parsing must be *incremental*: each readiness event
appends bytes, and the state machine advances as far as the data allows, then waits.

```
STATES:  REQUEST_LINE ──► HEADERS ──► BODY ──► COMPLETE ──► (respond)
                │              │           │
             malformed ──► 400          framing ──► 411/413
```

Steps:

1. **Request line** — `METHOD SP request-target SP HTTP-version CRLF`.
   Split on spaces; validate the method and the version (`HTTP/1.0`/`HTTP/1.1`).
2. **Headers** — read lines until an empty line. `Name: value` (trim optional
   whitespace). Lowercase the name for lookup; reject duplicate `Content-Length`
   with different values; oversized header block → 431/400.
3. **Body** — decided by `Content-Length` (count bytes) or `Transfer-Encoding:
   chunked` (a **sub-state machine**). Enforce `client_max_body_size` while reading →
   413.
4. **Complete** — hand the parsed request to routing; leave any surplus bytes in `in`
   for the next request on the same connection.

Chunked decoding:

```
read a line -> hex size
  size == 0  -> read trailer lines until CRLF -> DONE
  else       -> consume `size` bytes + trailing CRLF -> append decoded -> repeat
handle a size line split across recv() by keeping partial state
```

Traps:

- A header line can be split across two `recv` calls — never assume a whole line
  arrived.
- Headers are case-insensitive; the request target needs percent-decoding.
- A request with a `Content-Length` body but a `GET` method is legal (rare but real).
- Never `strtol`/parse without bounds; a malicious size must not overflow.

---

## 6. Building the response

```
HTTP/1.1 <status> <reason>\r\n
<Content-Type: …>
<Content-Length: N>            <- exact byte count of the body you will send
<Connection: keep-alive|close>
\r\n
<body>
```

- **Content-Length is a promise.** Compute it before sending; never guess.
- **MIME by extension.** Maintain a table (`.html`→`text/html`, `.css`→`text/css`,
  `.js`→`text/javascript`, `.png`→`image/png`, `.jpg`→`image/jpeg`, `.svg`→
  `image/svg+xml`, `.json`→`application/json`, default `application/octet-stream`).
- **`Connection`**: honour `close`, otherwise keep alive per policy.
- **Default error pages**: generate a small valid HTML body when the config provides
  none, and send it with the right status.
- **Server/Date headers** are polite and expected by comparers like NGINX.
- **HEAD** sends the same headers with an empty body (if implemented).

---

## 7. Configuration file and routing

The config should feel like the NGINX `server` section. A workable grammar:

```nginx
server {
    listen 8080;
    server_name localhost;
    root /var/www/html;
    index index.html;
    error_page 404 /errors/404.html;
    client_max_body_size 10M;

    location / {
        allow_methods GET POST;
        autoindex off;
    }

    location /upload {
        allow_methods POST DELETE;
        upload_store /var/www/uploads;
    }

    location /old {
        return 301 /new;
    }

    location /cgi-bin {
        cgi_extension .py /usr/bin/python3;
    }
}
```

Required capabilities (from the subject):

| Capability | Shape it takes |
|------------|----------------|
| interface:port pairs | one `server` block per site, multiple `listen` |
| default error pages | `error_page <code> <path>` |
| max request body | `client_max_body_size` |
| accepted methods per route | `allow_methods …` |
| HTTP redirection | `return <code> <url>` |
| route root directory | `root <dir>` |
| directory listing on/off | `autoindex on\|off` |
| default file in a directory | `index <file>` |
| upload authorisation + storage | `upload_store <dir>` |
| CGI by extension | `cgi_extension .php /path/to/php-cgi` |

### Parser design (the transferable skill)

1. **Tokenizer** — walk the file character by character/token by token; honour
   `{}` blocks, `;` terminators, `#` comments, quoted strings, whitespace.
2. **Parser** — recursive descent into nested blocks producing an **AST** (a tree of
   directive nodes). Keep it separate from the tokenizer.
3. **Validator** — unknown directive, missing `listen`, bad port, `root` that does not
   exist → clear error to stderr, non-zero exit.
4. **Binder** — turn the AST into runtime structs (`ServerConfig`, `LocationConfig`)
   with defaults applied.

Separating these stages is what lets you add directives without touching the lexer.

### Routing

- Match the **longest** prefix `location` for the decoded path (NGINX prefix rules).
- Apply, in order: allowed methods → redirect → resolve the filesystem target →
  dispatch to static / autoindex / upload / CGI.
- `root` concatenates the path (`/kapouet` rooted at `/tmp/www` → `/tmp/www/pouic/…`);
  distinguish it from `alias` if you implement both.
- Virtual hosts (`server_name`) are **out of scope** — optional.
- Unmatched route → 404; disallowed method → 405 with `Allow`.

---

## 8. Static files, uploads, path safety

**Serving a file**: resolve `root + decoded-path` → `stat` → if directory, try
`index`, else autoindex or 403/404; if regular file, open, fill the write buffer with
headers + body. Use `<sys/stat.h>` (`stat` is in the allowed list).

**Directory listing**: `opendir`/`readdir`/`closedir`, generate an HTML index with
links, honour `autoindex`, and escape names (a filename is user data).

**Path safety (do not skip):**

```cpp
// A path is dangerous if, after canonicalisation, it escapes root.
// Reject or normalise:  /../../etc/passwd, encoded %2e%2e, backslashes on some systems,
// NUL bytes, symlinks that point outside root.
```

Never build a path by string concatenation without checking that the resolved result
is still inside the configured root. This is CWE-22 and the first thing an evaluator
will probe.

**Upload (POST)**: parse `multipart/form-data` (RFC 7578) — split on the boundary,
parse each part's headers, write the payload to `upload_store` with a safe name and
the right permissions; or accept a raw `application/x-www-form-urlencoded` body.
Return 201/200 and never trust the client-supplied filename.

**DELETE**: resolve and `unlink` within root; 200/204 on success, 404 if absent, 403
if outside root.

---

## 9. CGI — running external programs

CGI (RFC 3875) is the one place `fork` is allowed. The server launches the program,
feeds it the request on **stdin**, and reads the response from **stdout**.

```
client ──► server ──fork/exec──► CGI program (php-cgi, python script)
              │  env: REQUEST_METHOD, PATH_INFO, QUERY_STRING,
              │       CONTENT_LENGTH, CONTENT_TYPE, SERVER_PROTOCOL,
              │       SERVER_NAME, SERVER_PORT, REMOTE_ADDR,
              │       GATEWAY_INTERFACE, HTTP_* …
              └─ stdin: request body (chunked must be un-chunked first, EOF = end)
                 stdout: CGI headers + blank line + body (EOF = end if no Content-Length)
```

Skeleton:

```cpp
int in_pipe[2], out_pipe[2];
pipe(in_pipe);  pipe(out_pipe);
pid_t pid = fork();                    // the ONLY legal fork
if (pid == 0)
{
    dup2(in_pipe[0],  STDIN_FILENO);
    dup2(out_pipe[1], STDOUT_FILENO);
    /* close unneeded ends */
    chdir(script_dir);                 // relative file access must work
    execve(interpreter, argv, envp);
    _exit(1);                          // exec failed
}
/* parent: write body to in_pipe[1], close it (EOF),
   register out_pipe[0] in poll(), read output,
   waitpid(pid) to avoid a zombie, kill on timeout. */
```

Details the subject calls out explicitly:

- **Un-chunk before feeding CGI**: CGI expects a body ending at **EOF**, not chunks.
- **CGI output has no `Content-Length` by default** — then **EOF terminates the
  body**. Buffer it fully, then frame it with a correct length (or close the
  connection).
- **Environment must carry the full request and arguments** — query string, method,
  content type/length, and `HTTP_*` versions of headers.
- **Run in the correct working directory** so relative paths inside the script work.
- **Support at least one interpreter** (php-cgi, Python, …). No interpreter is
  guaranteed to be installed — treat the interpreter path as configuration and fail
  visibly if it is missing.
- **Timeouts**: a hung CGI must be killed, not allowed to hang the server.
- CGI is the historical ancestor of FastCGI/application servers — the process
  isolation and env-var contract you learn here is the same contract behind
  PHP-FPM, WSGI, Rack, and containerised app servers.

---

## 10. Robustness: "never crash, never hang"

| Risk | Mitigation |
|------|-----------|
| Client vanishes mid-request | `recv` → 0 / `POLLHUP`; flush or drop, free state |
| `SIGPIPE` on writing to a closed socket | `signal(SIGPIPE, SIG_IGN)` (or `MSG_NOSIGNAL` where available) |
| Zombie CGI children | `waitpid(pid, &status, WNOHANG)` reaped in the loop |
| Slow/idle clients | per-connection timeout → 408/close |
| Huge request body | enforce `client_max_body_size` while streaming → 413 |
| Absurd header/URI | cap sizes → 400/414/431 |
| Malformed input | parse defensively; never index out of range |
| `accept`/`poll` transient failure | log and continue; never `exit` |
| Memory errors | RAII, no leaks, no double-free; ASan during development |
| Fork after threads / descriptors | close inherited fds in the child (`FD_CLOEXEC`) |

Stress it with many concurrent clients (`ab -n 10000 -c 200`, `siege`, or a small
Python asyncio client) and confirm the process still answers and its memory is flat.

---

## 11. C++ 98 build discipline

- Compile with `c++ -Wall -Wextra -Werror -std=c++98`; it must also build with an
  explicit `-std=c++98`.
- Prefer C++ headers (`<cstring>`, `<cstdlib>`) over C ones; C functions are allowed
  but the C++ equivalents are preferred.
- **No external or Boost libraries.** Implement what you need.
- Allowed system calls include: `execve, pipe, strerror, gai_strerror, errno, dup,
  dup2, fork, socketpair, htons, htonl, ntohs, ntohl, select, poll, epoll_*,
  kqueue/kevent, socket, accept, listen, send, recv, shutdown, chdir, bind, connect,
  getaddrinfo, freeaddrinfo, setsockopt, getsockname, getprotobyname, fcntl, close,
  read, write, waitpid, kill, signal, access, stat, open, opendir, readdir,
  closedir`.
- `fork` **only** for CGI. `fcntl` only with `F_SETFL`, `O_NONBLOCK`, `FD_CLOEXEC`.
- No `errno` inspection after `read`/`write`.
- Makefile: no unnecessary relinking; `all`, `clean`, `fclean`, `re`, `$(NAME)`.

---

## 12. Transferable concepts — for any project with similar requirements

Everything above generalises. If a project requires *concurrent I/O, a wire protocol,
configuration, and external processes*, the same five patterns apply:

| Pattern | webserv instance | Where else it appears |
|---------|------------------|-----------------------|
| **Reactor / event loop** | one `poll()` over all fds | Node.js, Redis, NGINX, HAProxy, game/chat servers |
| **Per-connection state machine** | request parse states | any parser over a stream: WebSocket framing, TLS records, MQTT, Redis RESP |
| **Protocol implementation** | HTTP over TCP | SMTP/IMAP, SSH, DNS (over UDP/TCP), gRPC |
| **Declarative config → AST → runtime** | NGINX-style blocks | nginx/Apache, systemd units, YAML pipelines, router tables |
| **Process isolation via env + pipes** | CGI fork/exec | FastCGI, WSGI, Rack, containerised app servers |
| **Backpressure & buffering** | write buffers, surplus bytes | proxies, load balancers, streaming APIs |
| **Path/input validation** | `..` traversal, size caps | every user-facing service (CWE-22, CWE-400) |
| **Resource lifecycle (RAII)** | fds, connections, children | any long-running daemon |

**Method, not just knowledge:** read the spec → build the smallest thing that obeys
it (`curl` answers) → compare against a reference implementation (NGINX) → add the
hard cases (chunked, CGI, multiple ports) → stress it → only then optimise. This
loop is what the 42 curriculum is training; it is the same loop used to write a
database driver, a message broker, or a browser engine.

---

## 13. Testing strategy

Do **not** test with a single tool (the subject says so explicitly). Use a mix:

| Tool | Use |
|------|-----|
| `curl -v` | real requests, header inspection, uploads (`-F`), DELETE |
| `nc` / `telnet` | raw, malformed, hand-crafted requests; see exact bytes |
| Python (`socket`/`asyncio`) | concurrent load, partial-write/partial-read cases |
| NGINX | compare headers, status codes, redirect and directory behaviour |
| `ab` / `siege` / `wrk` | concurrency and resilience; watch memory |
| Browser | the acceptance test the subject cares about |

Test cases worth writing first: missing `Host`, unknown method, too-large body,
`..` traversal, missing file, directory without index, redirect route, upload then
GET, chunked request into CGI, CGI that returns no `Content-Length`, client that
disconnects mid-body, and many simultaneous connections.

---

## 14. Pitfalls checklist (peer-evaluation style)

I/O and loop:
- [ ] Exactly one `poll()` (or equivalent) governs **all** socket/pipe I/O, listen socket included.
- [ ] No `read`/`recv`/`write`/`send` on a socket/pipe without prior readiness.
- [ ] Both read and write readiness monitored simultaneously.
- [ ] `POLLOUT` disabled when nothing is queued (no busy-spin).
- [ ] `errno` never consulted after `read`/`write`.
- [ ] Disk I/O exempt; sockets/pipes non-blocking.

Protocol:
- [ ] Requests may arrive split or coalesced; parser is incremental.
- [ ] Chunked requests decoded; CGI fed an EOF-terminated body.
- [ ] `Content-Length` exact; framing never ambiguous.
- [ ] Status codes accurate; default error pages exist.
- [ ] `Host` honoured; `Connection` respected.
- [ ] GET/POST/DELETE all work.

Config and routing:
- [ ] Config parsed with clear errors; multiple ports serve different sites.
- [ ] Longest-prefix location matching; methods/redirect/root/index/autoindex/upload/CGI all supported.
- [ ] Paths cannot escape root.

Processes and robustness:
- [ ] `fork` used only for CGI; child fds closed / `FD_CLOEXEC`.
- [ ] CGI timeout kills; `waitpid` reaps (no zombies).
- [ ] `SIGPIPE` ignored.
- [ ] No crash on malformed input, disconnect, or resource exhaustion.
- [ ] No fd/memory leaks under stress.

Build:
- [ ] `-Wall -Wextra -Werror -std=c++98`; Makefile has all rules; no relinking.

---

## 15. Glossary

| Term | Meaning |
|------|---------|
| **Blocking I/O** | A call that suspends the thread until it can complete. |
| **Non-blocking I/O** | A call that returns immediately (`EAGAIN`) if it cannot progress. |
| **Readiness** | The kernel's signal that an operation *can* proceed without blocking. |
| **`poll`/`select`/`epoll`/`kqueue`** | Kernel interfaces that report readiness for many descriptors. |
| **Level-triggered** | Keeps reporting readiness while unhandled data remains (`poll`, default `epoll`). |
| **Reactor** | Event loop that dispatches readiness events to per-connection handlers. |
| **Backlog** | Queue of connections accepted by the kernel but not yet `accept`ed by you. |
| **Byte stream** | TCP: ordered bytes with no message boundaries. |
| **Chunked transfer coding** | Body framed as hex-size + data chunks ending with `0`. |
| **Keep-alive** | Reusing one connection for several requests. |
| **MIME / media type** | `Content-Type` label telling the client how to interpret bytes. |
| **Autoindex** | Automatically generated directory listing. |
| **CGI** | Common Gateway Interface: run an external program per request via env + pipes. |
| **`PATH_INFO`** | Extra path after the CGI script name, passed to the program. |
| **Zombie** | Exited child not yet reaped by `waitpid`. |
| **FD_CLOEXEC** | Close this fd on `exec`, so the child does not inherit it. |
| **CWE-22** | Path traversal: escaping an intended directory via `..`. |

---

## 16. Resources

**Specifications**
- RFC 9110 — HTTP Semantics; RFC 9111 — HTTP Caching; RFC 9112 — HTTP/1.1.
  (The subject's era used RFC 7230–7233, still readable and cited by many tutors.)
- RFC 3875 — The Common Gateway Interface (CGI) Version 1.1.
- RFC 7578 — Returning Values from Forms: `multipart/form-data`.
- IANA Media Types registry.

**Guides and man pages**
- Beej's Guide to Network Programming (sockets, `getaddrinfo`, byte order).
- `man 2 socket`, `bind`, `listen`, `accept`, `poll`, `recv`, `send`, `fcntl`,
  `fork`, `execve`, `waitpid`, `pipe`, `signal`; `man 7 epoll`, `man 7 signal`.
- NGINX documentation: `server`/`location` blocks, `autoindex`, `return`,
  `error_page`, `client_max_body_size`.
- "The C10K problem" (historical motivation for event-driven I/O) and the
  "Reactor pattern".

**How AI was used in this project**

This README and the learning path were assisted by AI, and the 42 AI policy is
respected: AI was used to **reduce tedium and structure study**, never to replace
understanding.

| Task | AI role | Human responsibility |
|------|---------|----------------------|
| Reading the subject | Summarise requirements, list allowed functions, tabulate status codes | Verify against `webserv.pdf` |
| Concept map | Propose the study order and references | Read the RFCs/guides; discuss with peers |
| Parser / event-loop design | Brainstorm state machines, config grammar | Walk the logic through with a peer before coding |
| Testing plan | Draft test cases and tooling | Actually run them; compare with NGINX |
| This document | Draft and edit prose | Own the content; be able to defend every line |

No AI-generated code is copied into the implementation without being fully
understood and testable; anything that cannot be explained at the defence does not
belong in the repository.

---

## Honest scope note

There is **no implementation in this repository yet**. This file is the study guide
for building one, plus the structural skeleton of the mandatory README. Once the
server exists, update the *Instructions* section with the real build/run/test
commands, add the feature list and technical choices, and keep this guide as the
conceptual reference it is meant to be.
