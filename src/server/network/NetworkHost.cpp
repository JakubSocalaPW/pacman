//
// Created by jakub on 17.03.2025.
//

#include "NetworkHost.h"

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
    sf::TcpSocket* clientSocket = new sf::TcpSocket();
    clientSocket->setBlocking(false);

    if (listener.accept(*clientSocket) == sf::Socket::Status::Done) {
        // log new client

        //add new player and init

        // Add new player to the game


        // Send initial game data to the new player
        sf::Packet initialPacket;
        initialPacket << "Hello buddy";
        clientSocket->send(initialPacket);
    } else {
        delete clientSocket;
    }
}
