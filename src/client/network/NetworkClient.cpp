#include "NetworkClient.h"
#include <iostream>
#include "SFML/Network.hpp"

bool NetworkClient::connectToServer(const sf::IpAddress& ip, int port) {
    if (_socket.connect(ip, port) != sf::Socket::Status::Done) {
        std::cerr << "Failed to connect to server";
        return false;
    }
    _socket.setBlocking(false);
    std::cout << "Connected to server.\n";

    sf::Packet packet;

    // to avoid race condition with sending message to server
    _socket.setBlocking(true);

    if (_socket.receive(packet) == sf::Socket::Status::Done) {
        std::string msg;
        packet >> msg;
        std::cout << msg;
    }

    _socket.setBlocking(true);

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


std::string NetworkClient::getLastStateType() const {
    return _lastStateType;
}


std::optional<sf::Packet> NetworkClient::getStateUpdate() {
    sf::Packet packet;
    Level level;
    _socket.setBlocking(false);
    if (_socket.receive(packet) == sf::Socket::Status::Done) {
        packet >> _lastStateType;
        std::cout << "[Client] Received packet type: " << _lastStateType << std::endl;
        return packet;
    }
    return {};
}
void NetworkClient::sendMoveCommand(int direction) {
    sf::Packet packet;
    packet << "MOVE" << direction;
    _socket.send(packet);
}