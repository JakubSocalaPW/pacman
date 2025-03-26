//
// Created by jakub on 17.03.2025.
//

#include "NetworkHost.h"

#include "../../../cmake-build-debug/_deps/freetype-src/include/freetype/internal/fttrace.h"
#include "../core/LevelGenerator.h"

NetworkHost::NetworkHost(const int port) {
    listener.setBlocking(false);
    this->port = port;
}

bool NetworkHost::startServer() {
    auto status = listener.listen(port);

    if (status != sf::Socket::Status::Done) {
        return false;
    }

    running = true;
    gameThread = std::thread(&NetworkHost::waitForConnection, this);


    return true;
}

void NetworkHost::waitForConnection() {
    sf::Clock clock;
    float tickInterval = 1.0f / 60;  //tick rate, move to const todo

    while (running) {
        acceptNewClients();
        processClientMessages();

        if (clock.getElapsedTime().asSeconds() >= tickInterval) {
            // update();
            // broadcastGameState();
            clock.restart();
        }

        sf::sleep(sf::milliseconds(1));
    }
}

void NetworkHost::processClientMessages() {

}

void NetworkHost::acceptNewClients() {
    sf::TcpSocket* clientSocket;
    clientSocket->setBlocking(false);

    if (listener.accept(*clientSocket) == sf::Socket::Status::Done) {
        // log new client

        //add new player and init

        // Add new player to the game

        LevelGenerator lg;
        // Send initial game data to the new player
        sf::Packet initialPacket;
        initialPacket << "Hello buddy";
        initialPacket << lg.getCurrentLevel(); // todo serializable operator
        clientSocket->send(initialPacket);
    } else {
        delete clientSocket;
    }
}

void NetworkHost::sendPacketToClients