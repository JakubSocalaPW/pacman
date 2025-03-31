#include <iostream>

#include "SFML/Network/IpAddress.hpp"
#include "SFML/Network/Packet.hpp"
#include "SFML/Network/TcpSocket.hpp"
#include "src/client/view/Window.h"
#include "src/client/core/Level.h"
#include "src/client/core/input/KeyboardController.h"

int main () {
    sf::TcpSocket socket;
    sf::Packet packet;

    std::cout << "Starting game client.\n";


    if (socket.connect(sf::IpAddress(127,0,0,1), 5555) != sf::Socket::Status::Done) {
        std::cerr << "Failed to connect to server";
    }

    else std::cout << "Connected.\n";

    Level level;
    Window window;
    KeyboardController controller;
    socket.setBlocking(false);
    sf::Clock clock;


    if (socket.receive(packet) == sf::Socket::Status::Done) {
        std::string msg;
        packet >> msg;
        std::cout << msg;

        std::string name;


        std::cin >> name;

        sf::Packet packetout;

        packetout << "NAME";
        packetout << name;

        socket.send(packetout);


        //packet >> level;
        //std::cout << level.getPlayers().size();

    }



    while (true) {
        window.pollEvents();



        if (clock.getElapsedTime().asSeconds() >= 0.05f) {
            window.render(level);

            if (window.hasFocus()) {
                if (controller.isArrowDownPressed()) {
                    sf::Packet packet;
                    packet << "MOVE" << 2;
                    socket.send(packet);
                }
                else if (controller.isArrowUpPressed()) {
                    sf::Packet packet;
                    packet << "MOVE" << 0;
                    socket.send(packet);
                }
                else if (controller.isArrowLeftPressed()) {
                    sf::Packet packet;
                    packet << "MOVE" << 3;
                    socket.send(packet);
                }
                else if (controller.isArrowRightPressed()) {
                    sf::Packet packet;
                    packet << "MOVE" << 1;
                    socket.send(packet);
                }
            }

            // 20 updates per second
            //level.update();
            clock.restart();
        }


        if (socket.receive(packet) == sf::Socket::Status::Done) {
            std::string msg;

            packet >> msg;
            std::cout << msg;


            packet >> level;
        }


    }
    return 0;
}
