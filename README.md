# MAVLink UDP Server & Client in C++ for Linux  

This project implements a MAVLink UDP server and client using POSIX sockets for network communication on Linux.  

## Components  

- **UDP Server (GCS)** – Listens on a specified UDP port, receives MAVLink messages, and decodes them.  
- **UDP Client (Drone)** – Sends MAVLink heartbeat messages to the server.  

## Build Instructions  

### 1. Install MAVLink and Generate Headers  
Follow the instructions in the official MAVLink repository: [MAVLink GitHub](https://github.com/mavlink/mavlink).  

### 2. Configure the Build  
Navigate to the project's root directory and execute the following CMake command. Ensure `CMAKE_PREFIX_PATH` is set to the location of `mavlink.h`:  

```sh
cmake -B build -H. -DCMAKE_PREFIX_PATH=$(pwd)/../../mavlink/install
```

### 3. Compile the Project
```sh
cmake --build build
```
