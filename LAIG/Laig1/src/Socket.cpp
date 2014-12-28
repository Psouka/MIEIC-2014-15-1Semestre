#include "Socket.h"
#define IPADDRESS "127.0.0.1"
#define PORT 60070


Socket::Socket() {
	 WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != NO_ERROR)
		printf("Client: Error at WSAStartup().\n");
    else
        printf("Client: WSAStartup() is OK.\n");

	// Create a socket.
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_socket == INVALID_SOCKET) {
        printf("Client: socket() - Error at socket(): %ld\n", WSAGetLastError());
        WSACleanup();
    }
	else
       printf("Client: socket() is OK.\n");

    // Connect to a server.
    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    // Just test using the localhost, you can try other IP address
    clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientService.sin_port = htons(60070);

    if (connect(m_socket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
        printf("Client: connect() - Failed to connect.\n");
		active = false;
        WSACleanup();
    }
    else {
       printf("Client: connect() is OK.\n");
       printf("Client: Can start sending and receiving data...\n");
	   active = true;
    }

    // Send and receive data.
	printf("Connected\n");
}

string Socket::sendMessage(string message) {
	message += ".\n";

	unsigned int len = message.length();
	const char* s = message.c_str();

	int bytesSent = send(m_socket, s, len, 0);
	if(bytesSent == SOCKET_ERROR) {
		throw exception();
	}

	string answer = "";

	char buffer = '_';
	while (buffer != '\n') {
		recv(m_socket, &buffer, 1, 0);
		answer += buffer;
	}
	return answer;
}

Socket::~Socket() {
	sendMessage("quit");
}

bool Socket::isActive(){
	return active;
}