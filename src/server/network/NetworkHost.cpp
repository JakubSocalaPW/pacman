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
            // Update each player's movement independently
            auto& players = levelGenerator.getCurrentLevel().getPlayers();
            for (auto& player : players) {
                player.updateMovement(levelGenerator.getCurrentLevel().getWallPositionsAsVector());
            }

            //check for collisions
            for (auto& player : players) {
                if (player.getIsPacman()) {
                    // Check for collision with ghosts
                    for (auto& ghost : levelGenerator.getCurrentLevel().getGhosts()) {
                        if ((int) player.getPosition().x == (int)ghost.get().getPosition().x && (int) player.getPosition().y == (int)ghost.get().getPosition().y) {
                            std::cout << "Pacman collided with a ghost!" << std::endl;
                            player.setIsAlive(false);
                        }
                    }
                    // Check for collision with power-ups
                    std::vector<PowerUp*> powerUpsToRemove;

                    for (auto& powerUp : levelGenerator.getCurrentLevel().getPowerUps()) {
                        if ((int)player.getPosition().x == powerUp.getPosition().x && (int)player.getPosition().y == powerUp.getPosition().y) {
                            std::cout << "Pacman collected a power-up!" << std::endl;
                            powerUp.getCollisionEffect(player);
                            powerUpsToRemove.push_back(&powerUp);  // Collect for later removal
                        }
                    }

                    // Now remove the collected power-ups outside the loop
                    for (auto* powerUp : powerUpsToRemove) {
                        levelGenerator.getCurrentLevel().removePowerUp(*powerUp);
                    }
                    // Check for collision with objectives
                    std::vector<Objective*> objectivesToRemove;

                    for (auto& objective : levelGenerator.getCurrentLevel().getObjectives()) {
                        if ((int)player.getPosition().x == objective.getPosition().x && (int)player.getPosition().y == objective.getPosition().y) {
                            std::cout << "Pacman collected an objective!" << std::endl;
                            player.addScore(objective.getValue());
                            objectivesToRemove.push_back(&objective);  // Collect the objective to remove
                        }
                    }

                    // Now remove the collected objectives outside the loop
                    for (auto* objective : objectivesToRemove) {
                        levelGenerator.getCurrentLevel().removeObjective(*objective);
                    }

                }
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
            std::cout << "Received message: " << msgType << std::endl;

            if (msgType == "NAME") {
                std::string name;
                packet >> name;

                // Give each player a different starting position
                int playerCount = levelGenerator.getCurrentLevel().getPlayers().size();
                // Create player with different starting coordinates
                Player newPlayer(1 + (playerCount * 2), 1, name);

                // Only make first player Pacman if that's your game design
                newPlayer.setIsPacman(playerCount == 0);

                Level& lvl = levelGenerator.getCurrentLevel();
                lvl.addPlayer(newPlayer);

                sf::Packet responsePacket;
                responsePacket << "WELCOME";
                responsePacket << lvl;
                clientSocket->send(responsePacket);

                playersNames.insert({name, clientSocket});
                std::cout << "Player named: " << name << " joined as player #" << playerCount + 1 << std::endl;
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

                // Find and update the player's direction
                auto& allPlayers = levelGenerator.getCurrentLevel().getPlayers();
                bool playerFound = false;

                for (auto& player : allPlayers) {
                    if (player.getNickname() == playerName) {
                        std::cout << "Processing move for player: " << playerName
                                  << ", direction: " << direction << std::endl;
                        player.changeDirection(direction, levelGenerator.getCurrentLevel().getWallPositionsAsVector());
                        playerFound = true;
                        break;
                    }
                }

                if (!playerFound) {
                    std::cerr << "Could not find player with name: " << playerName << std::endl;
                }
            }

            ++it;
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
                // Remove player from the game
                auto& players = levelGenerator.getCurrentLevel().getPlayers();
                for (auto playerIt = players.begin(); playerIt != players.end(); ++playerIt) {
                    if (playerIt->getNickname() == disconnectedPlayer) {
                        players.erase(playerIt);
                        std::cout << "Removed player: " << disconnectedPlayer << std::endl;
                        break;
                    }
                }

                playersNames.erase(disconnectedPlayer);

                // Notify remaining clients that a player left
                sf::Packet leavePacket;
                leavePacket << "PLAYER_LEFT";
                leavePacket << disconnectedPlayer;
                broadcastGameState();
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
