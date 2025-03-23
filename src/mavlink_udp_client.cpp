#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <mavlink/common/mavlink.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[MAVLINK_MAX_PACKET_LEN];

    // Create socket
    if ((clientSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        std::cerr << "Socket creation failed.\n";
        return 1;
    }

    // Setup server address structure
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    socklen_t serverLen = sizeof(serverAddr);

    while (true) {
        // Create a MAVLink heartbeat message
        mavlink_message_t msg;
        uint8_t mavlink_buffer[MAVLINK_MAX_PACKET_LEN];
        mavlink_msg_heartbeat_pack(
            1, 200, &msg, MAV_TYPE_QUADROTOR, MAV_AUTOPILOT_ARDUPILOTMEGA,
            MAV_MODE_GUIDED_ARMED, 0, MAV_STATE_ACTIVE
        );

        // Serialize MAVLink message
        uint16_t len = mavlink_msg_to_send_buffer(mavlink_buffer, &msg);

        // Send heartbeat message
        if (sendto(clientSocket, (char*)mavlink_buffer, len, 0, (struct sockaddr*)&serverAddr, serverLen) < 0) {
            std::cerr << "Send failed.\n";
            continue;
        }

        std::cout << "Sent MAVLink Heartbeat\n";
        sleep(1);  // Send every 1 second
    }

    close(clientSocket);
    return 0;
}
