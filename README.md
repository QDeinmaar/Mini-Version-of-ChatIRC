# ChatIRC

A lightweight IRC client written in C that implements the core features of the Internet Relay Chat (IRC) protocol. This project was built to improve my understanding of low-level networking, socket programming, multithreading, and network protocol implementation.

---

## Features

- Connect to an IRC server
- Register a nickname and user
- Join IRC channels
- Send messages to channels
- Receive messages asynchronously
- Graceful client shutdown
- Command-line configuration

---

## Technologies

- C
- POSIX Sockets
- POSIX Threads (`pthread`)
- TCP/IP Networking
- Linux

---

## Project Structure

```
chatirc/
├── src/
│   ├── main.c
│   ├── connect.c
│   ├── irc.c
│   ├── utils.c
│   └── cleanup.c
│
├── include/
│   ├── connect.h
│   ├── includes.h
│   ├── irc.h
│   └── utils.h
│
├── assets/
├── docs/
├── tests/
│
├── Makefile
├── README.md
├── LICENSE
└── .gitignore
```

---

## Requirements

- Linux
- GCC
- POSIX Threads

---

## Build

Compile the project with:

```bash
make
```

Clean object files:

```bash
make clean
```

Rebuild everything:

```bash
make re
```

---

## Usage

Start the client using:

```bash
./irc_client -s <server> -n <nickname> -c "#<channel>"
```

Example:

```bash
./irc_client -s 127.0.0.1 -n alice -c "#general"
```

---

## Example

```
$ ./irc_client -s 127.0.0.1 -n alice -c "#general"

Connecting to 127.0.0.1...
Connected.

JOIN #general

<alice> Hello everyone!
<bob> Hi Alice!
```

---

## Commands

| Command | Description |
|---------|-------------|
| `/JOIN #channel` | Join a channel |
| `/QUIT` | Disconnect from the server |

---

## Skills Demonstrated

- TCP socket programming
- Network protocol implementation
- IRC protocol fundamentals
- Concurrent programming with POSIX threads
- Command parsing
- Linux systems programming
- Memory and resource management

---

## Future Improvements

- [ ] Private messaging
- [ ] Channel switching
- [ ] Channel list support
- [ ] User list command
- [ ] Message history
- [ ] TLS/SSL support
- [ ] IRCv3 compatibility
- [ ] SASL authentication
- [ ] Better terminal interface

---

## Learning Objectives

This project was created to gain practical experience with:

- Socket programming
- Multithreaded applications
- Client-server communication
- IRC protocol internals
- Systems programming in C

---

## License

This project is licensed under the MIT License.

---

## Author

**Tudor**

GitHub: https://github.com/YOUR_USERNAME
