#include "ServerGameController.h"

#include <iostream>
#include "../common/player/PacMan.h"

ServerGameController::ServerGameController() : _networkHost(5555, this), _isGameActive(false) {
}

void ServerGameController::startGame() {
    _isGameActive = true;
    sf::Clock clock;
    std::cout << "Starting Server..." << std::endl;
    _networkHost.startServer();
    std::cout << "Server running." << std::endl;
    while (_isGameActive) {
        const int FPS = 60;
        float tickInterval = 1.0f / FPS;
        if (clock.getElapsedTime().asSeconds() >= tickInterval) {
            auto &playerCharacters = _levelGenerator.getCurrentLevel().getPlayerCharacters();
            for (auto &player: playerCharacters) {
                player->updateMovement(_levelGenerator.getCurrentLevel().getWallPositionsAsVector());
            }

            //check for collisions
            for (auto &player: playerCharacters) {
                if (player->isPacman() && player->isAtGridPoint() && player->getIsAlive()) {

                    if (!player->getIsInvincible()) {
                        // Check for collision with ghosts
                        for (auto &ghost: _levelGenerator.getCurrentLevel().getGhosts()) {
                            if ((int) player->getPosition().x == (int) ghost->getPosition().x && (int) player->getPosition().y == (int) ghost->getPosition().y) {
                                std::cout << "Pacman collided with a ghost!" << std::endl;
                                if (player->getIsGhostKiller()) {
                                    ghost->setIsAlive(false);
                                    player->getPlayer().addScore(10);
                                }
                                else {
                                    player->setIsAlive(false);
                                    ghost->getPlayer().addScore(10);
                                }
                            }
                        }
                    }

                    // Check for collision with power-ups
                    std::vector<PowerUp *> powerUpsToRemove;

                    for (auto &powerUp: _levelGenerator.getCurrentLevel().getPowerUps()) {
                        if ((int) player->getPosition().x == powerUp.getPosition().x && (int) player->getPosition().y == powerUp.getPosition().y) {
                            std::cout << "Pacman collected a power-up!" << std::endl;
                            powerUp.getCollisionEffect(*player);
                            powerUpsToRemove.push_back(&powerUp); // Collect for later removal
                        }
                    }

                    for (auto *powerUp: powerUpsToRemove) {
                        _levelGenerator.getCurrentLevel().removePowerUp(*powerUp);
                    }
                    std::vector<Objective *> objectivesToRemove;

                    for (auto &objective: _levelGenerator.getCurrentLevel().getObjectives()) {
                        if ((int) player->getPosition().x == objective.getPosition().x && (int) player->getPosition().y == objective.getPosition().y) {
                            std::cout << "Pacman collected an objective!" << std::endl;
                            player->getPlayer().addScore(objective.getValue());
                            objectivesToRemove.push_back(&objective); // Collect the objective to remove
                        }
                    }

                    for (auto *objective: objectivesToRemove) {
                        _levelGenerator.getCurrentLevel().removeObjective(*objective);
                    }
                }
            }

            //check for dead players and respawn
            for (auto &player: playerCharacters) {
                if (!player->getIsAlive()) {
                    player->move(1, 1); //todo make starting places interesting and legal and random
                    player->setIsAlive(true);
                    player->setInvincible(true);
                    player->changeDirection(-1, _levelGenerator.getCurrentLevel().getWallPositionsAsVector());
                    player->setPowerUpDurationLeft(200);
                }
            }


            //check for expired powerups
            for (auto &player: playerCharacters) {
                if (player->getPowerUpDurationLeft() > 0) {
                    player->setPowerUpDurationLeft(player->getPowerUpDurationLeft() - 1);
                } else if (player->getPowerUpDurationLeft() == 0) {
                    player->setInvincible(false);
                    player->setIsGhostKiller(false);
                    player->setSpeedBoosted(false);
                    player->setPowerUpDurationLeft(-1);
                }
            }


            //check if all objectives are collected
            if (_levelGenerator.getCurrentLevel().getObjectives().empty()) {
                std::cout << "All objectives collected! Generating new level..." << std::endl;
                _levelGenerator.nextLevel();
            }

            clock.restart();
            _networkHost.broadcastGameState(_levelGenerator.getCurrentLevel());
        }

    }
}

void ServerGameController::_detectCollisions() {
}

void ServerGameController::broadcastUpdatedState() {
}

void ServerGameController::_handlePlayerMovement(int playerId, int direction) {
}

Level &ServerGameController::getCurrentLevel() {
    return _levelGenerator.getCurrentLevel();
}

void ServerGameController::addPlayer(const std::string &name) {
    int playerCount = _levelGenerator.getCurrentLevel().getPlayerCharacters().size();
    Player* newPlayer = new Player(name);

    PlayerCharacter* newPlayerCharacter;
    if (playerCount == 0) {
        newPlayerCharacter = new PacMan(1 + (playerCount * 2), 1, newPlayer);
    }
    else {
        newPlayerCharacter = new Ghost(1 + (playerCount * 2), 1, newPlayer);
    }

    Level &lvl = _levelGenerator.getCurrentLevel();
    lvl.addPlayer(newPlayerCharacter);
    _networkHost.broadcastLogs("Player joined the game: " + name);
}

void ServerGameController::movePlayer(const std::string &name, int direction) {
    auto& allPlayers = _levelGenerator.getCurrentLevel().getPlayerCharacters();

    for (auto& player: allPlayers) {
        if (player->getPlayer().getNickname() == name) {
            std::cout << "Processing move for player: " << name
                    << ", direction: " << direction << std::endl;
            player->changeDirection(direction, _levelGenerator.getCurrentLevel().getWallPositionsAsVector());
            break;
        }
    }
}


void ServerGameController::removePlayer(const std::string &name) {
    auto &players = _levelGenerator.getCurrentLevel().getPlayerCharacters();

    for (auto& player: players) {
        if (player != nullptr && player->getPlayer().getNickname() == name) {
            delete &player->getPlayer();
            delete player;
            player = nullptr;  // Mark as to be deleted
        }
    }

    players.erase(
        std::remove_if(players.begin(), players.end(),
            [](PlayerCharacter* p) { return p == nullptr; }),
        players.end()
    );
}