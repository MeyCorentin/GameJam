# R-Type Game Protocol (RTGP) - Version 1.0


## Main Documentation

- [Main Documentation](README.md)

## Table of Contents

- [Introduction](#introduction)
- [General Message Format](#general-message-format)
- [Command Codes](#command-codes)
- [Communication Examples](#communication-examples)
- [Conclusion](#conclusion)

## Introduction

The R-Type Game Protocol (RTGP) is designed to facilitate communication between the client and the server for the R-Type game. This document outlines the various commands and their format.

## General Message Format

Each message sent according to this protocol consists of a command code followed, if necessary, by additional information. Each message ends with a newline character (`\n`).

## Message format

```
struct BinaryMessage {
    uint16_t type; // 0: Player, 1: Other
    uint32_t id; // Id of element
    uint16_t x; // X position
    uint16_t y; // Y position
    uint16_t data; // Data
};
```

| Value | Description |
|------|-------------|
| `type` | 0: Player, 1: Other |
| `id` | Client id |
| `x` | X Position |
| `y` | Y Position |
| `data` | Message codes |



**Exemple for connection:**

```
BinaryProtocole::BinaryMessage initial_msg;
initial_msg = {0, 0, 0, 0, 100};
send(initial_msg);
```

```
void UDPClient::send(BinaryProtocole::BinaryMessage msg)
{
    this->socket_.send_to(boost::asio::buffer(protocole.ValueToBin(msg)), server_endpoint_);
}
```

## Command Codes

**Client to server:**
| Code | Description |
|------|-------------|
| `100` | Client connection request |
| `200` | Press up |
| `210` | Press left |
| `220` | Press down |
| `230` | Press right |
| `300` | Press Shoot |
| `201` | Release up |
| `211` | Release left |
| `221` | Release down |
| `231` | Release right |
| `301` | Release Shoot |

**Server to client:**
| Code | Description |
|------|-------------|
| `100` | Client connection request |
| `200` | Press up |
| `210` | Press left |
| `220` | Press down |
| `230` | Press right |
| `300` | Press Shoot |
| `201` | Release up |
| `211` | Release left |
| `221` | Release down |
| `231` | Release right |
| `301` | Release Shoot |
| `1000` | Client ID |

## Conclusion

This protocol is designed to be straightforward and direct. The command codes allow for quick identification of the desired action.
