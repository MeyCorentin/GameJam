# R-Type Game Protocol (RTGP) - Version 1.0

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

## Command Codes

| Code | Description |
|------|-------------|
| `100` | Client connection request |
| `200` | Move up |
| `210` | Move left |
| `220` | Move down |
| `230` | Move right |
| `300` | Shoot action |

## Communication Examples

1. **Client Connection**:

Client: `100\n`

Server: `101 [ID_CLIENT]\n` (where `[ID_CLIENT]` is a unique ID assigned to the client)

2. **Move Up**:

Client: `200\n`

3. **Shoot**:

Client: `300\n`

## Conclusion

This protocol is designed to be straightforward and direct. The command codes allow for quick identification of the desired action.
