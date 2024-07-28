#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

using namespace std;

int main()
{
    WSADATA wsaData;
    int wsaerr;

    WORD wVersionRequested = MAKEWORD(2, 2);

// Initialising the winsock dll
    wsaerr = WSAStartup(wVersionRequested, &wsaData);
    if (wsaerr != 0)
    {
        cout << "The Winsock dll not found." << endl;
        return 0;
    }
    else
    {
        cout << "The Winsock dll found." << endl;
        cout << "The status : " << wsaData.szSystemStatus << endl;
    }

// Checking if the reuired version of winsock dll is found
    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
    {
        cout << "Version 2.2 of Winsock is not available" << endl;

        WSACleanup();
        return 0;
    }
    cout << "Version 2.2 of Winsock is available" << endl;

// Creating a socket
    SOCKET serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(serverSocket == INVALID_SOCKET)
    {
        cout << "Error at socket() : " << WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    }
    else
    {
        cout << "socket() is OK!" << endl;
    }
    
// Binding the local ip address and port number with socket
    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr("127.0.0.1");
    service.sin_port = htons(55555);
    // Bind socket
    if (bind (serverSocket, (SOCKADDR*) &service, sizeof(service)) == SOCKET_ERROR) {
        cout << "bind() failed : " << WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    }
    else
    {
        cout << "bind() is OK!" << endl;
    }
    
// Listening on socket
    if (listen(serverSocket, 1) == SOCKET_ERROR) {
        cout << "listen():Error listening on socket " << WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    }
    else
    {
        cout << "listen() is OK, I'm waiiting for connections" << endl;
    }

// Accepting connection
    SOCKET acceptSocket;
    acceptSocket = accept(serverSocket, NULL, NULL);
    if(acceptSocket == INVALID_SOCKET) {
        cout << "Accept failed : " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    }
    else{
        cout << "Connection Recieved" << endl;
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
