#include "udp_server.h"

machinasdk::udp_server* machinasdk::udp_server_create(uint16_t port) {
#if defined(WIN32)
    WSADATA data;
    if (WSAStartup(MAKEWORD(2, 2), &data) != 0) 
        return nullptr;
#endif

    machinasdk::udp_server* server = (machinasdk::udp_server*)malloc(sizeof(machinasdk::udp_server));
    if (!server) 
        return nullptr;

    server->socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server->socket == INVALID_SOCKET) {
        free(server);
        return nullptr;
    }

    memset(&server->server_addr, 0, sizeof(server->server_addr));

    server->server_addr.sin_family = AF_INET;
    server->server_addr.sin_port = htons(port);
    server->server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server->socket, (const sockaddr*)&server->server_addr, sizeof(server->server_addr)) == SOCKET_ERROR) {
        closesocket(server->socket);
        free(server);
        return nullptr;
    }

    return server;
}

void machinasdk::udp_server_destroy(udp_server* server) {
    if (!server)
        return;

    closesocket(server->socket);
    free(server);
    WSACleanup();
}

int32_t machinasdk::udp_server_receive(udp_server* server, udp_server_sender* sender, char* buffer, int16_t buffer_size) {
    int32_t sender_length = sizeof(*sender);
    memset(sender, 0, sender_length);

    int32_t received = recvfrom(server->socket, buffer, buffer_size, 0, (sockaddr*)sender, &sender_length);

    if (received > 0)
        buffer[received] = '\0';

    return received;
}

int32_t machinasdk::udp_server_send(udp_server* server, udp_server_sender* sender, const char* data) {
    return sendto(server->socket, data, strlen(data), 0, (sockaddr*)sender, sizeof(*sender));
}
