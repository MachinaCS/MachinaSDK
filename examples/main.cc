#include <string>
#include <iostream>

#include <stdint.h>
#include <stddef.h>

#include "udp_server.h"

typedef struct example_data {
    float_t c;
    uint32_t a;
    std::string b;
} example_data_t;

int32_t main() {
    machinasdk::udp_server_t* server = machinasdk::udp_server_create(54000);

    if (!server) {
        std::cout << "Error: Could not create UDP server\n" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Server started on port 54000\n";

    machinasdk::udp_server_sender sender = {};
    char buffer[1024];

    while (true) {
        ZeroMemory(buffer, 1024);

        int32_t received = udp_server_receive(server, &sender, buffer, 1024);

        if (received == SOCKET_ERROR) {
            std::cout << "Error: Can't receive message from client!" << std::endl;
            continue;
        }

        std::cout << "Received " << received << " bytes\n";

        if (received == sizeof(example_data_t)) {
            example_data_t data = {};
            memcpy(&data, buffer, sizeof(example_data_t));
        }
        else {
            std::cout << "Received data is not of expected size!\n";
        }
    }

    udp_server_destroy(server);
    return EXIT_SUCCESS;
}