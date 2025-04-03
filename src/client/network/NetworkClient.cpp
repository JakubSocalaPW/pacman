#include "NetworkClient.h"
#include <iostream>
#include "SFML/Network.hpp"

bool NetworkClient::connectToServer(const sf::IpAddress& ip, int port) {
    if (_socket.connect(ip, port) != sf::Socket::Status::Done) {
        std::cerr << "Failed to connect to server";
        return false;
    }
    _socket.setBlocking(false);
    std::cout << "Connected.\n";

    sf::Packet packet;

    _socket.setBlocking(true);

    if (_socket.receive(packet) == sf::Socket::Status::Done) {
        std::string msg;
        packet >> msg;
        std::cout << msg;
    }

    return true;
}

void NetworkClient::sendUserName(const std::string &name) {
    sf::Packet packetOut;

    packetOut << "NAME";
    packetOut << name;
    _socket.send(packetOut);
    _socket.setBlocking(false);
}

void NetworkClient::disconnectFromServer() {
    _socket.disconnect();
}

const Level NetworkClient::getStateUpdate() {
    sf::Packet packet;
    Level level;

    if (_socket.receive(packet) == sf::Socket::Status::Done) {
        std::string msg;

        packet >> msg;
        //std::cout << msg;

        packet >> level;
        std::cout << level.getPlayers().size() << std::endl;
    }

    return level;
}

void NetworkClient::sendMoveCommand(int direction) {
    sf::Packet packet;
    packet << "MOVE" << direction;
    _socket.send(packet);
}