
#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include <string>


class NetworkClient {
    std::string m_serverIP;
    int m_serverPort;
    int m_clientId;

public:
    bool connectToServer(const std::string& serverIP, int port);
    void sendPacketToServer(const std::string& packet);
    void registerPacketListener();
    void disconnectFromServer();
};

#endif //NETWORKCLIENT_H
