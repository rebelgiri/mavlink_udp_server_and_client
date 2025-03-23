# MAVLink UDP Server &amp; Client in C++ for Linux

The Linux version of the MAVLink UDP server and client using POSIX sockets for network communication.

- UDP Server (GCS) - Receives MAVLink Messages
This server will listen on a specified UDP port, receive MAVLink messages, and decode them.

- UDP Client (Drone) - Sends MAVLink Heartbeats
The client will send a heartbeat message to the server using the MAVLink protocol.

## Build Steps

1. Install MAVLink follow steps here https://github.com/mavlink/mavlink

2. Go top directory and execute below cmake command make sure CMAKE_PREFIX_PATH is given

```cmake -Bbuild -H. -DCMAKE_PREFIX_PATH=$(pwd)/../../mavlink/install```

3. Build

```cmake --build build```
