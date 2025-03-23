#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <mavlink/common/mavlink.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int serverSocket;
    struct sockaddr_in serverAddr, clientAddr;
    char buffer[BUFFER_SIZE];

    // Create socket
    if ((serverSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        std::cerr << "Socket creation failed.\n";
        return 1;
    }

    // Setup server address structure
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind socket to address and port
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Bind failed.\n";
        close(serverSocket);
        return 1;
    }

    std::cout << "MAVLink UDP Server listening on port " << PORT << "...\n";

    socklen_t clientLen = sizeof(clientAddr);
    while (true) {
        int bytesReceived = recvfrom(serverSocket, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&clientAddr, &clientLen);
        if (bytesReceived < 0) {
            std::cerr << "Receive failed.\n";
            continue;
        }

        // Decode MAVLink message
        mavlink_message_t msg;
        mavlink_status_t status;
        for (int i = 0; i < bytesReceived; ++i) {
            if (mavlink_parse_char(MAVLINK_COMM_0, buffer[i], &msg, &status)) {
                if (msg.msgid == MAVLINK_MSG_ID_HEARTBEAT) {
                    mavlink_heartbeat_t heartbeat;
                    mavlink_msg_heartbeat_decode(&msg, &heartbeat);
                    std::cout << "Received MAVLink Heartbeat from Drone! System ID: " 
                              << msg.sysid << ", Component ID: " << msg.compid << std::endl;
                }
            }
        }
    }

    close(serverSocket);
    return 0;
}
