cmake_minimum_required(VERSION 3.10)

# Project Name
project(MAVLinkUDPExample)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)

# Define the MAVLink installation directory
#set(MAVLINK_INSTALL_DIR "${CMAKE_SOURCE_DIR}/install")

# Include the directory where MAVLink headers were installed
#include_directories("${MAVLINK_INSTALL_DIR}/include")

find_package(MAVLink REQUIRED)

# Set the source files for client and server
set(SERVER_SRC src/mavlink_udp_server.cpp)
set(CLIENT_SRC src/mavlink_udp_client.cpp)

# Add an executable for the server
add_executable(mavlink_udp_server ${SERVER_SRC})
#target_link_libraries(mavlink_udp_server pthread)
target_link_libraries(mavlink_udp_server PRIVATE MAVLink::mavlink)

# Add an executable for the client
add_executable(mavlink_udp_client ${CLIENT_SRC})
#target_link_libraries(mavlink_udp_client pthread)
target_link_libraries(mavlink_udp_client PRIVATE MAVLink::mavlink)

# Optionally, if MAVLink was installed with additional libraries, you could link against them:
# target_link_libraries(mavlink_udp_server ${MAVLINK_INSTALL_DIR}/lib/libmavlink.a)
# target_link_libraries(mavlink_udp_client ${MAVLINK_INSTALL_DIR}/lib/libmavlink.a)
