#include <thread>
#include "SimpleClient.h"
#include "SimpleNetworkExceptions.h"

#pragma comment (lib, "ws2_32.lib")

std::map<int, std::string> errorCodes{
    {10054, "The remote host stopped working"},
    {10061, "Failed to reach remote host"},
    {10053, "Software on remote host caused connection abort"},
    {10057, "Socket is not connected"}
};


SimpleClient::SimpleClient(Config config) : 
    config { config }
{
    WSADATA data;
    WORD ver = MAKEWORD(config.winSockVersion.first, config.winSockVersion.second);

    int status = WSAStartup(ver, &data);
    if (status != 0) throw WinSockException{ "Failed to initialze winsock" };
}


SimpleClient::~SimpleClient()
{
    WSACleanup();
}


std::string SimpleClient::transmit(const std::string& packet) {

    if (connection == INVALID_SOCKET) {

        connection = socket(AF_INET, SOCK_STREAM, 0);
        if (connection == INVALID_SOCKET) throw SocketException{ connection, "Failed to create socket" };

        sockaddr_in addr;
        addr.sin_family = AF_INET;
        inet_pton(AF_INET, config.host.c_str(), &addr.sin_addr);

        addr.sin_port = htons(config.port);
        int status = connect(connection, (sockaddr*)&addr, sizeof(addr));
        if (status == SOCKET_ERROR) return handleSocketError(status);
    }

    char buf[4096];
    int status = send(connection, packet.c_str(), packet.size() + 1, 0);
    if (status == SOCKET_ERROR) return handleSocketError(status);

    ZeroMemory(buf, 4096);
    int len = recv(connection, buf, 4096, 0);
    if (len == SOCKET_ERROR) return handleSocketError(len);

    return buf;
}


SOCKET SimpleClient::createConnection(const std::string& host, int port) 
{
    SOCKET connection = socket(AF_INET, SOCK_STREAM, 0);
    if (connection == INVALID_SOCKET) throw SocketException{connection, "Failed to create socket" };

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, host.c_str(), &addr.sin_addr);

    addr.sin_port = htons(port);
    int status = connect(connection, (sockaddr*)&addr, sizeof(addr));

    if (status == SOCKET_ERROR) {
        std::string reason = handleSocketError(status);
        logger.outnl(reason);
    } 

    return connection;
}


std::tuple<std::string, std::string> SimpleClient::getSocketInfo(SOCKET socket) 
{
    sockaddr_in addr;
    socklen_t len = sizeof(sockaddr_in);
    getpeername(socket, (sockaddr*)&addr, &len);

    char host[NI_MAXHOST];
    char service[NI_MAXHOST];

    ZeroMemory(host, NI_MAXHOST);
    ZeroMemory(service, NI_MAXHOST);

    if (getnameinfo((sockaddr*)&addr, sizeof(addr), host, NI_MAXHOST, service, NI_MAXSERV, 0) != 0) {
        inet_ntop(AF_INET, &addr.sin_addr, host, NI_MAXHOST);
        std::string port = std::to_string(ntohs(addr.sin_port));
        strncpy_s(service, &port[0], port.size());
    }

    return std::make_tuple(host, service);
}


std::string SimpleClient::handleSocketError(int status) {

    if (status != SOCKET_ERROR) return "";

    int code = WSAGetLastError();
    connection = INVALID_SOCKET;

    if (errorCodes.count(code)) {
        return errorCodes[code] + " (" + std::to_string(code) + ")";
    }

    throw SocketException(connection, "Unkown");
}

void SimpleClient::logsock(SOCKET socket, const std::string& msg)
{
    const auto [host, port] = getSocketInfo(socket);
    logger.outnl("[", host, ":", port, "] ", msg);
}