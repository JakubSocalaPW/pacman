//
// Created by jakub on 17.03.2025.
//

#include "NetworkHost.h"

#include <iostream>

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

            //temporal state update
            auto& players = levelGenerator.getCurrentLevel().getPlayers();
            for (auto& player : players) {
                player.updateMovement(levelGenerator.getCurrentLevel().getWallPositionsAsVector());
            }

            broadcastGameState();
            clock.restart();
        }

        sf::sleep(sf::milliseconds(1));
    }
}


void NetworkHost::broadcastGameState() {
    sf::Packet packet;

    packet << "GAME_STATE";
    packet << levelGenerator.getCurrentLevel();

    for (sf::TcpSocket* client : clients) {
        std::lock_guard<std::mutex> lock(playersMutex);

        if (client->send(packet) != sf::Socket::Status::Done) {
            std::cerr << "Failed to send game state to client." << std::endl;
        }
    }

}



void NetworkHost::processClientMessages() {
    std::lock_guard<std::mutex> lock(playersMutex);

    for (auto it = clients.begin(); it != clients.end();) {
        sf::TcpSocket* clientSocket = *it;
        sf::Packet packet;

        auto status = clientSocket->receive(packet);

        if (status == sf::Socket::Status::Done) {
            std::string msgType;
            packet >> msgType;
            std::cout << msgType << std::endl;
            if (msgType == "NAME") {
                std::string name;
                packet >> name;
                Player newPlayer(1,1, name);
                newPlayer.setIsPacman(true);
                Level& lvl = levelGenerator.getCurrentLevel();
                lvl.addPlayer(newPlayer);
                sf::Packet packet;
                packet << "Transmitting starting level config \n";
                packet << lvl;
                clientSocket->send(packet);
                playersNames.insert({name, clientSocket});
                std::cout << "Player named: " << name << std::endl;
            }
            else if (msgType == "MOVE") {
                int direction;
                packet >> direction;
                std::cout << "Direction: " << direction << std::endl;
                std::string name;
                for (const auto& pair : playersNames) {
                    if (pair.second == clientSocket) {
                        name = pair.first;
                        break;
                    }
                }

                auto& allPlayers = levelGenerator.getCurrentLevel().getPlayers();
                for (auto& player : allPlayers) {
                    if (player.getNickname() == name) {
                        player.changeDirection(direction, levelGenerator.getCurrentLevel().getWallPositionsAsVector());
                        std::cout << "Player " << name << " moved in direction: " << direction << std::endl;
                        break;
                    }
                }
            }

            ++it;
        }
        else if (status == sf::Socket::Status::Disconnected) {
            std::cout << "Client disconnected" << std::endl;
            std::string name;
            for (const auto& pair : playersNames) {
                if (pair.second == clientSocket) {
                    playersNames.erase(pair.first);
                    break;
                }
            }
            it = clients.erase(it);
            delete clientSocket;
        }
        else {
            ++it;
        }
    }
}

void NetworkHost::acceptNewClients() {
    // Allocate memory for the new client socket
    sf::TcpSocket* clientSocket = new sf::TcpSocket();
    clientSocket->setBlocking(false);
    if (listener.accept(*clientSocket) == sf::Socket::Status::Done) {
        std::cout << "New client connected." << std::endl;
        // Store the client socket for future use
        clients.push_back(clientSocket);

        // Send initial game data to the new player
        sf::Packet initialPacket;
        initialPacket << "Welcome to the game! Please tell me your name or nickname: ";
        clientSocket->send(initialPacket);
    } else {
        // No connection this time, clean up the unused socket
        delete clientSocket;
    }
}
