# Minitalk

A client-server communication program using UNIX signals for data transmission.

## About

Minitalk is a small data exchange program that uses UNIX signals (SIGUSR1 and SIGUSR2) for character-by-character communication between processes.

### Features
- Reliable communication using only SIGUSR1 and SIGUSR2 signals
- Server displays its PID on startup
- Client can send messages to server using PID
- Server acknowledges received messages
- Handles multiple clients simultaneously
- Buffer-based output for efficiency

## Usage

1. Start the server:
```bash
./server
```
The server will display its PID.

2. Send messages using the client:
```bash
./client <server_pid> "Your message here"
```

### Example
```bash
# Terminal 1
> ./server
The server is ready [PID: 12345]

# Terminal 2
> ./client 12345 "Hello World!"
```

## Technical Details

- Signal handling using `sigaction`
- Bit-by-bit data transmission
- Buffer-based output management
- Error handling for process communication
- Client acknowledgment system
