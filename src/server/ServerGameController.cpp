#include "ServerGameController.h"

#include <iostream>

ServerGameController::ServerGameController() : networkHost(5555, this), m_isGameActive(false) {
}

void ServerGameController::startGame() {
    m_isGameActive = true;
    sf::Clock clock;
    networkHost.startServer();
    while (m_isGameActive) { //move to separate thread todo
        float tickInterval = 1.0f / 60; //tick rate, move to const todo
        if (clock.getElapsedTime().asSeconds() >= tickInterval) {
            // Update each player's movement independently
            auto &players = levelGenerator.getCurrentLevel().getPlayers();
            for (auto &player: players) {
                player.updateMovement(levelGenerator.getCurrentLevel().getWallPositionsAsVector());
            }

            //check for collisions
            for (auto &player: players) {
                if (player.getIsPacman() && player.isAtGridPoint() && player.getIsAlive()) {

                    if (!player.getIsInvincible()) {
                        // Check for collision with ghosts
                        for (auto &ghost: levelGenerator.getCurrentLevel().getGhosts()) {
                            if ((int) player.getPosition().x == (int) ghost.get().getPosition().x && (int) player.
                                getPosition().
                                y == (int) ghost.get().getPosition().y) {
                                std::cout << "Pacman collided with a ghost!" << std::endl;
                                if (player.getIsGhostKiller()) {
                                    ghost.get().setIsAlive(false);
                                    player.addScore(10); //todo move to config
                                }
                                else {
                                    player.setIsAlive(false);
                                    ghost.get().addScore(10); //todo move to config
                                }
                            }
                        }
                    }

                    // Check for collision with power-ups
                    std::vector<PowerUp *> powerUpsToRemove;

                    for (auto &powerUp: levelGenerator.getCurrentLevel().getPowerUps()) {
                        if ((int) player.getPosition().x == powerUp.getPosition().x && (int) player.getPosition().y ==
                            powerUp.getPosition().y) {
                            std::cout << "Pacman collected a power-up!" << std::endl;
                            powerUp.getCollisionEffect(player);
                            powerUpsToRemove.push_back(&powerUp); // Collect for later removal
                        }
                    }

                    // Now remove the collected power-ups outside the loop
                    for (auto *powerUp: powerUpsToRemove) {
                        levelGenerator.getCurrentLevel().removePowerUp(*powerUp);
                    }
                    // Check for collision with objectives
                    std::vector<Objective *> objectivesToRemove;

                    for (auto &objective: levelGenerator.getCurrentLevel().getObjectives()) {
                        if ((int) player.getPosition().x == objective.getPosition().x && (int) player.getPosition().y ==
                            objective.getPosition().y) {
                            std::cout << "Pacman collected an objective!" << std::endl;
                            player.addScore(objective.getValue());
                            objectivesToRemove.push_back(&objective); // Collect the objective to remove
                        }
                    }

                    // Now remove the collected objectives outside the loop
                    for (auto *objective: objectivesToRemove) {
                        levelGenerator.getCurrentLevel().removeObjective(*objective);
                    }
                }
            }

            //check for dead players and respawn
            for (auto &player: players) {
                if (!player.getIsAlive()) {
                    player.setPosition(sf::Vector2f(1, 1));
                    player.setIsAlive(true);
                    player.setInvincible(true);
                    player.changeDirection(-1, levelGenerator.getCurrentLevel().getWallPositionsAsVector());
                    player.setPowerUpDurationLeft(300); //todo move to config
                }
            }

            //check for expired powerups
            for (auto &player: players) {
                if (player.getPowerUpDurationLeft() > 0) {
                    player.setPowerUpDurationLeft(player.getPowerUpDurationLeft() - 1);
                } else {
                    player.setInvincible(false);
                    player.setIsGhostKiller(false);
                    player.setSpeedBoosted(false);
                }
            }

            //check if all objectives are collected
            if (levelGenerator.getCurrentLevel().getObjectives().empty()) {
                std::cout << "All objectives collected! Generating new level..." << std::endl;
                levelGenerator.nextLevel();
            }
            clock.restart();
            networkHost.broadcastGameState(levelGenerator.getCurrentLevel());
        }

    }
}

void ServerGameController::detectCollisions() {
}

void ServerGameController::broadcastUpdatedState() {
}

void ServerGameController::handlePlayerMovement(int playerId, int direction) {
}

Level &ServerGameController::getCurrentLevel() {
    return levelGenerator.getCurrentLevel();
}

void ServerGameController::addPlayer(const std::string &name) {
    // Give each player a different starting position
    int playerCount = levelGenerator.getCurrentLevel().getPlayers().size();
    // Create player with different starting coordinates
    Player newPlayer(1 + (playerCount * 2), 1, name);

    // Only make first player Pacman if that's your game design
    newPlayer.setIsPacman(playerCount == 0);

    Level &lvl = levelGenerator.getCurrentLevel();
    lvl.addPlayer(newPlayer);
}

void ServerGameController::movePlayer(const std::string &name, int direction) {
    auto &allPlayers = levelGenerator.getCurrentLevel().getPlayers();
    bool playerFound = false;

    for (auto &player: allPlayers) {
        if (player.getNickname() == name) {
            std::cout << "Processing move for player: " << name
                    << ", direction: " << direction << std::endl;
            player.changeDirection(direction, levelGenerator.getCurrentLevel().getWallPositionsAsVector());
            playerFound = true;
            break;
        }
    }

    if (!playerFound) {
        std::cerr << "Could not find player with name: " << name << std::endl;
    }
}


void ServerGameController::removePlayer(const std::string &name) {
    // Remove player from the game
    auto &players = levelGenerator.getCurrentLevel().getPlayers();
    for (auto playerIt = players.begin(); playerIt != players.end(); ++playerIt) {
        if (playerIt->getNickname() == name) {
            players.erase(playerIt);
            std::cout << "Removed player: " << name << std::endl;
            break;
        }
    }
    networkHost.broadcastGameState(getCurrentLevel());
}
