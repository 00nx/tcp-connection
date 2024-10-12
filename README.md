# TCP Server in C

This project is a simple implementation of a TCP server in C using the `sockets`

## How It Works
- The server creates a socket using the `socket()` function
- Sets socket options like `SO_REUSEADDR` and `SO_REUSEPORT` using `setsockopt()` to allow reuse of the address
- Binds the socket to an IP address (`INADDR_ANY` for any available interface) and a specified port (8080 in this case)
- Listens for incoming client connections using `listen()`
- Accepts incoming connections using `accept()` and prints any data sent by the client
