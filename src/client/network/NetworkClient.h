
#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include <string>

#include "SFML/Network/TcpSocket.hpp"
#include "../../common/level/Level.h"

class NetworkClient {
    sf::TcpSocket _socket;

public:
    bool connectToServer(const sf::IpAddress& ip, int port);
    void sendUserName(const std::string& name);
    std::optional<sf::Packet> getStateUpdate();
    void sendMoveCommand(int direction);
    void disconnectFromServer();
};

#endif //NETWORKCLIENT_H
