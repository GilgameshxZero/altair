#include <bits/stdc++.h>

// #define ONLINEJUDGE

#ifdef ONLINEJUDGE

// Non-Windows networking is supported via POSIX-style sockets.
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#else
// Rain utilizes ANSI Windows functions internally.
#ifdef UNICODE
#undef UNICODE
#endif

// Prevents Windows.h from automatically include Winsock 1.1; Rain uses
// Winsock 2.
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

// Prevents double declarations of min/max functions.
#ifndef NOMINMAX
#define NOMINMAX
#endif

#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Shell32.lib")

#include <Windows.h>
#include <shellapi.h>

// Links ws2_32.dll which includes implementation for Winsock 2. Not necessarily
// x86 as the name suggests.
#pragma comment(lib, "Ws2_32.lib")

#include <iphlpapi.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

using namespace std;

int main() {
#if !defined(ONLINEJUDGE)
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

	int nativeSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (nativeSocket == -1) {
		return 0;
	}

	addrinfo hints;
	memset(&hints, 0, sizeof(addrinfo));
	hints.ai_flags = AI_ALL | AI_ADDRCONFIG | AI_V4MAPPED;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	addrinfo *addresses = nullptr;
	int result = getaddrinfo("127.0.0.1", "80", &hints, &addresses);
	addrinfo address;
	address.ai_addrlen = 16;
	address.ai_addr = new sockaddr();
	address.ai_addr->sa_family = 2;
	address.ai_addr->sa_data[1] = 80;
	address.ai_addr->sa_data[2] = 127;
	address.ai_addr->sa_data[3] = 0;
	address.ai_addr->sa_data[4] = 0;
	address.ai_addr->sa_data[5] = 1;

	int res = connect(nativeSocket, address.ai_addr, address.ai_addrlen);
	if (res == -1) {
		return 0;
	}

	cout << "alf" << '\n';
	return 0;
}
