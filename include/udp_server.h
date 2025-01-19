#ifndef _udp_server_h_
#define _udp_server_h_

#include <atomic>
#include <thread>
#include <string>
#include <iostream>

#if defined(_WIN32)
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h>
#include <ws2tcpip.h>
#ifdef MACHINASDK_EXPORT_DLL
#define MACHINASDK_API __declspec(dllexport)
#else
#define MACHINASDK_API __declspec(dllimport)
#endif
#endif

extern "C" {
	namespace machinasdk {
		MACHINASDK_API typedef struct udp_server {
			SOCKET		socket;
			sockaddr_in server_addr;
		} udp_server_t;

		MACHINASDK_API typedef sockaddr_in udp_server_sender;

		MACHINASDK_API udp_server* 	udp_server_create(uint16_t port);
		MACHINASDK_API void		udp_server_destroy(udp_server* server);
		MACHINASDK_API int32_t		udp_server_receive(udp_server* server, udp_server_sender* sender, char* buffer, int16_t buffer_size);
		MACHINASDK_API int32_t		udp_server_send(udp_server* server, udp_server_sender* sender, const char* data);
	}; // namespace machinasdk
}; // extern "C"


#endif // !_udp_server_h_
