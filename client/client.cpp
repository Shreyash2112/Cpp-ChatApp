#include <winsock2.h>
#include <ws2tcpip.h>
#include<iostream>
using namespace std;

int main () {
    
    WSAData wsaData;
    int wsaerr;

    WORD wVersionRequested = MAKEWORD(2, 2);

// Initialising the winsock dll
    wsaerr = WSAStartup(wVersionRequested, &wsaData);
    if(wsaerr != 0) {
        cout << "The winsock dll not found" << endl;
        return 0;
    }
    else{
        cout << "The winsock dll found" << endl;
        cout << "The status : " << wsaData.szSystemStatus << endl;
    }

// Checking if the required version version of dll is found
    if(LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        cout << "Version 2.2 of winsock is not available." << endl;

        WSACleanup();
        return 0;
    }  
    else{
        cout << "Version 2.2 of winsock dll is found" << endl;
    }

// Creating a socket
    SOCKET clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(clientSocket == INVALID_SOCKET){
        cout << "Error at socket() : " << WSAGetLastError() << endl;

        WSACleanup();
        return 0; 
    }
    else{
        cout << "Socket() is ok " << endl;
    }

// Connecting to server 
    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientService.sin_port = htons(55555);
    if(connect(clientSocket, (SOCKADDR*) &clientService, sizeof(clientService)) == SOCKET_ERROR){
        cout << "Client Failed to connect : " << WSAGetLastError() << endl;

        WSACleanup();
        return 0;
    }
    else{
        cout << "Client is ok" << endl;
        cout << "Client can start sending & recieving data" << endl;
    }

    closesocket(clientSocket);
    WSACleanup();
    return 0;

    return 0;
} 