#include "NetworkHost.h"

#include <iostream>

#include "../core/LevelGenerator.h"
#include "../ServerGameController.h"

NetworkHost::NetworkHost(const int port, ServerGameController* serverController) : _port(port), _serverController(serverController) {
    _listener.setBlocking(false);
}

bool NetworkHost::startServer() {
    auto status = _listener.listen(_port);

    if (status != sf::Socket::Status::Done) {
        return false;
    }

    _running = true;
    _gameThread = std::thread(&NetworkHost::_waitForConnection, this);
    return true;
}

void NetworkHost::_waitForConnection() {
    while (_running) {
        _acceptNewClients();
        _processClientMessages();

        sf::sleep(sf::milliseconds(1));
    }
}

NetworkHost::~NetworkHost() {
    // Stop the server thread if running
    _running = false;
    if (_gameThread.joinable()) {
        _gameThread.join();
    }

    // Clean up all client sockets
    for (auto& client : _clients) {
        delete client;
    }
    _clients.clear();
}


void NetworkHost::broadcastGameState(const Level& state) {
    sf::Packet packet;

    packet << "GAME_STATE";
    packet << state;

    for (sf::TcpSocket* client : _clients) {
        std::lock_guard<std::mutex> lock(_playersMutex);

        if (client->send(packet) != sf::Socket::Status::Done) {
            std::cerr << "Failed to send game state to client." << std::endl;
        }
    }
}


void NetworkHost::_processClientMessages() {
    std::lock_guard<std::mutex> lock(_playersMutex);

    for (auto it = _clients.begin(); it != _clients.end();) {
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

                _serverController->addPlayer(name);
                sf::Packet responsePacket;
                responsePacket << "WELCOME";
                responsePacket << _serverController->getCurrentLevel();
                clientSocket->send(responsePacket);

                _playersNames.insert({name, clientSocket});
                std::cout << "Player named: " << name << " joined." << std::endl;
            }
            else if (msgType == "MOVE") {
                int direction;
                packet >> direction;

                // Find which player this client controls
                std::string playerName = "";
                for (const auto& pair : _playersNames) {
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

                _serverController->movePlayer(playerName, direction);
                ++it;
            }
        }
        else if (status == sf::Socket::Status::Disconnected) {
            std::cout << "Client disconnected" << std::endl;

            // Find which player disconnected
            std::string disconnectedPlayer = "";
            for (const auto& pair : _playersNames) {
                if (pair.second == clientSocket) {
                    disconnectedPlayer = pair.first;
                    break;
                }
            }

            _serverController->removePlayer(disconnectedPlayer);

            if (!disconnectedPlayer.empty()) {
                _playersNames.erase(disconnectedPlayer);
            }

            it = _clients.erase(it);
            delete clientSocket;
        }

        else {
            ++it;
        }
    }
}

void NetworkHost::_acceptNewClients() {
    // Allocate memory for the new client socket
    sf::TcpSocket* clientSocket = new sf::TcpSocket();
    clientSocket->setBlocking(false);
    if (_listener.accept(*clientSocket) == sf::Socket::Status::Done) {
        std::cout << "New client connected." << std::endl;
        // Store the client socket for future use
        _clients.push_back(clientSocket);

        // Send initial game data to the new player
        sf::Packet initialPacket;
        initialPacket << "Welcome to the game! Please tell me your name or nickname: ";
        clientSocket->send(initialPacket);
    } else {
        // No connection this time, clean up the unused socket
        delete clientSocket;
    }
}
