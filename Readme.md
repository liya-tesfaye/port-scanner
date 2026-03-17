# Network Port Scanner (C)

A TCP port scanner built in C using low-level socket programming to detect open ports on target hosts.

## Features
- TCP connect scanning
- Configurable IP and port range
- Timeout handling for faster scans
- Lightweight and efficient

## Usage

``bash
./scanner <IP> <start_port> <end_port>

## How It Works

- Uses BSD sockets (socket, connect)
- Attempts TCP handshake on each port
- Reports open ports based on successful connections

## Tech Stack
- C
- POSIX sockets
- Linux

## Future Improvements

- Multithreading (pthread)
- SYN scan (raw sockets)
- Service detection
