#include <iostream>

#include "SFML/Network/IpAddress.hpp"
#include "SFML/Network/Packet.hpp"
#include "SFML/Network/TcpSocket.hpp"

int main () {
    sf::TcpSocket socket;
    sf::Packet packet;

    std::cout << "Starting game client.\n";

    if (socket.connect(sf::IpAddress(127,0,0,1), 5555) != sf::Socket::Status::Done) {
        std::cerr << "Failed to connect to server";
    }

    else std::cout << "Connected.\n";

    while (true) {
        if (socket.receive(packet) == sf::Socket::Status::Done) {
            std::string msg;
            packet >> msg;
            std::cout << msg;
        }
    }
    return 0;
}
