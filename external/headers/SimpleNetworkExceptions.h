#pragma once
#include <string>  
#include <iostream>
#include <WS2tcpip.h>

struct WinSockException : public std::exception
{
public:

    WinSockException(const std::string& msg) : msg{ msg }
    {
        std::cout << descFull() << std::endl;
        WSACleanup();
    }

    const char* what() const throw ()
    {
        return descShort().c_str();
    }

private:

    std::string descShort() const {
        return msg + " ERR #" + std::to_string(WSAGetLastError());
    }

    std::string descFull() const {
        std::string d;
        d += "WinSockException thrown";
        d += '\n';
        d += "\n    Reason: " + msg;
        d += "\n    Error Code: " + std::to_string(WSAGetLastError());
        d += '\n';
        d += "\nSee: https://docs.microsoft.com/en-us/windows/win32/winsock/windows-sockets-error-codes-2";
        d += "\nfor error code reference.";
        return d;
    }

    const std::string msg;
};


struct SocketException : WinSockException
{
public:

    SocketException(SOCKET socket, const std::string& msg) : WinSockException{ msg }
    {
        closesocket(socket);
    }
};