#include <tuple>
#include <string>  
#include <functional>
#include <WS2tcpip.h>
#include "SimpleLogger.h"
#include <map>

struct Config {
    std::string host = "127.0.0.1";
    int port = 54000;
    bool loggingEnabled = true;
    std::pair<int, int> winSockVersion = { 2,2 };
};

class SimpleClient {
public:

    SimpleClient(Config);
    ~SimpleClient();
    std::string transmit(const std::string&);

private:

    Config config;
    SimpleLogger logger;
    SOCKET connection = INVALID_SOCKET;

    SOCKET createConnection(const std::string&, int);
    std::tuple<std::string, std::string> getSocketInfo(SOCKET);
    std::string handleSocketError(int);

    void logsock(SOCKET, const std::string&);
};