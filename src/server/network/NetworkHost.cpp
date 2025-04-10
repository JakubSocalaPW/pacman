//
// Created by jakub on 17.03.2025.
//

#include "NetworkHost.h"

#include <iostream>

#include "../core/LevelGenerator.h"
#include "../ServerGameController.h"
NetworkHost::NetworkHost(const int port, ServerGameController* serverController) : port(port), serverController(serverController) {
    listener.setBlocking(false);
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
    while (running) {
        acceptNewClients();
        processClientMessages();

        sf::sleep(sf::milliseconds(1));
    }
}



void NetworkHost::broadcastGameState(const Level& state) {
    sf::Packet packet;

    packet << "GAME_STATE";
    std::cout << "Broadcasting game state to clieasdnts." << std::endl;
    packet << state;
    std::cout << "it is done." << std::endl;

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
            std::cout << "Received message: " << msgType << std::endl;

            if (msgType == "NAME") {
                std::string name;
                packet >> name;

                serverController->addPlayer(name);
                sf::Packet responsePacket;
                responsePacket << "WELCOME";
                responsePacket << serverController->getCurrentLevel();
                clientSocket->send(responsePacket);

                playersNames.insert({name, clientSocket});
                std::cout << "Player named: " << name << " joined." << std::endl;
            }
            else if (msgType == "MOVE") {
                int direction;
                packet >> direction;

                // Find which player this client controls
                std::string playerName = "";
                for (const auto& pair : playersNames) {
                    if (pair.second == clientSocket) {
                        playerName = pair.first;
                        break;
                    }
                }

                if (playerName.empty()) {
                    std::cerr << "Received move command from unidentified client" << std::endl;
                    ++it;
                    continue;
                }

                serverController->movePlayer(playerName, direction);
                ++it;
            }
        }
        else if (status == sf::Socket::Status::Disconnected) {
            std::cout << "Client disconnected" << std::endl;

            // Find which player disconnected
            std::string disconnectedPlayer = "";
            for (const auto& pair : playersNames) {
                if (pair.second == clientSocket) {
                    disconnectedPlayer = pair.first;
                    break;
                }
            }

            if (!disconnectedPlayer.empty()) {
                playersNames.erase(disconnectedPlayer);

                // Notify remaining clients that a player left
                sf::Packet leavePacket;
                leavePacket << "PLAYER_LEFT";
                leavePacket << disconnectedPlayer;
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
