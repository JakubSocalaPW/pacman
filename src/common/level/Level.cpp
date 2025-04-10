#include "Level.h"
#include <iostream>
#include "../player/PacMan.h"
#include "Objective.h"

Level::Level() {
}

Level::~Level() {
    // Clean up allocated player memory
    for (auto* player : _playersCharacters) {
        delete player;
    }
    _playersCharacters.clear();
}

Level::Level(Level&& other) noexcept :
    _gameMap(std::move(other._gameMap)),
    _playersCharacters(std::move(other._playersCharacters)),
    _powerups(std::move(other._powerups)),
    _objectives(std::move(other._objectives)) {

    other._playersCharacters.clear();
}

Level& Level::operator=(Level&& other) noexcept {
    if (this != &other) {
        for (auto* player : _playersCharacters) {
            delete player;
        }
        _playersCharacters.clear();

        _gameMap = std::move(other._gameMap);
        _playersCharacters = std::move(other._playersCharacters);
        _powerups = std::move(other._powerups);
        _objectives = std::move(other._objectives);

        other._playersCharacters.clear();
    }
    return *this;
}

Level::Level(std::vector<std::vector<int>> map) {
    int rowCounter = 0;
    for (const auto& row : map) {
        int colCounter = 0;
        for (const auto& col : row) {
            switch (col) {
                case 0:
                    break;
                case 1: {
                    Wall w{rowCounter, colCounter};
                    _gameMap.push_back(w);
                    break;
                }
                case 2: {
                    Objective o{rowCounter, colCounter};
                    _objectives.push_back(o);
                    break;
                }
                case 3: {
                    PowerUp p{rowCounter, colCounter, PowerUp::getRandomPowerUp()};
                    _powerups.push_back(p);
                    break;
                }
                default:
                    break;
            }
            colCounter++;
        }
        rowCounter++;
    }
}

std::list<sf::Vector2<int>> Level::getWallPositions() const {
    std::list<sf::Vector2<int>> wallPositions;

    for (const auto& wall : _gameMap) {
        wallPositions.push_back(wall.getPosition());
    }

    return wallPositions;
}

void Level::setPlayerCharacters(std::vector<PlayerCharacter*> newPlayers) {
    for (auto* player : _playersCharacters) {
        delete player;
    }
    _playersCharacters.clear();

    _playersCharacters = std::move(newPlayers);
}

int Level::getSize() const {
    return getWallPositionsAsVector().size();
}


const std::list<Wall>& Level::getWalls() const {
    return _gameMap;
}


std::list<PowerUp>& Level::getPowerUps() {
    return _powerups;
}

std::list<Objective>& Level::getObjectives() {
    return _objectives;
}


std::vector<PlayerCharacter*>& Level::getPlayerCharacters() {
    return _playersCharacters;
}


std::vector<Ghost*> Level::getGhosts() {
    std::vector<Ghost*> ghosts;

    for (auto* player : _playersCharacters) {
        if (player == nullptr) {
            continue;
        }

        try {
            if (!player->isPacman()) {
                auto* ghost = dynamic_cast<Ghost*>(player);
                if (ghost) {
                    ghosts.push_back(ghost);
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Exception in getGhosts: " << e.what() << std::endl;
        }
    }
    return ghosts;
}

std::vector<std::vector<int>> Level::getWallPositionsAsVector() const {
    int width = 0;
    int height = 0;

    for (const auto& element : getWalls()) {
        auto pos = element.getPosition();
        if (pos.x > width) width = pos.x;
        if (pos.y > height) height = pos.y;
    }

    width++;
    height++;

    std::vector<std::vector<int>> grid(height, std::vector<int>(width, 0));

    for (const auto& wall : getWalls()) {
        int gridX = static_cast<int>(wall.getPosition().x);
        int gridY = static_cast<int>(wall.getPosition().y);

        if (gridX >= 0 && gridX < width && gridY >= 0 && gridY < height) {
            grid[gridY][gridX] = 1;
        }
    }

    return grid;
}

void Level::addPlayer(PlayerCharacter* player) {
    if (player == nullptr) {
        std::cerr << "Attempted to add null player!" << std::endl;
        return;
    }
    _playersCharacters.push_back(player);
}

void Level::removePowerUp(PowerUp& powerUp) {
    _powerups.remove_if([&](const PowerUp& p) {
        return &p == &powerUp;  // Compare memory addresses
    });
}

void Level::removeObjective(Objective& objective) {
    _objectives.remove_if([&](const Objective& o) {
        return &o == &objective;  // Compare memory addresses
    });
}

sf::Packet Level::serialize() const {
    sf::Packet packet;
    packet << *this;
    return packet;
}

Level Level::deserialize(sf::Packet& packet) {
    Level level;
    packet >> level;
    return level;
}

sf::Packet& operator<<(sf::Packet& packet, const Level& level) {
    // Serialize walls
    packet << static_cast<int>(level._gameMap.size());
    for (const auto& wall : level._gameMap) {
        const sf::Vector2<int>& pos = wall.getPosition();
        packet << pos.x << pos.y;
    }

    // Serialize players
    packet << static_cast<int>(level._playersCharacters.size());
    for (auto* playerCharacter : level._playersCharacters) {
        if (playerCharacter == nullptr) {
            // Handle null player pointer
            packet << false; // Flag: not valid player
            continue;
        }

        // Valid player
        packet << true; // Flag: valid player

        // Write player type identifier
        packet << playerCharacter->isPacman();

        // Serialize player data
        packet << *playerCharacter;
    }

    // Serialize powerups
    packet << static_cast<int>(level._powerups.size());
    for (const auto& powerup : level._powerups) {
        const sf::Vector2<int>& pos = powerup.getPosition();
        packet << pos.x << pos.y << static_cast<int>(powerup.getType());
    }

    // Serialize objectives
    packet << static_cast<int>(level._objectives.size());
    for (const auto& objective : level._objectives) {
        const sf::Vector2<int>& pos = objective.getPosition();
        packet << pos.x << pos.y;
    }

    return packet;
}

sf::Packet& operator>>(sf::Packet& packet, Level& level) {
    try {
        // Clean up existing player data
        for (auto& player : level._playersCharacters) {
            delete player;
            player = nullptr;
        }
        level._playersCharacters.clear();

        // Clear existing data
        level._gameMap.clear();
        level._powerups.clear();
        level._objectives.clear();

        // Deserialize walls
        int wallCount;
        packet >> wallCount;
        for (int i = 0; i < wallCount; ++i) {
            int x, y;
            packet >> x >> y;
            Wall wall(x, y);
            level._gameMap.push_back(wall);
        }

        // Deserialize players
        int playerCount;
        packet >> playerCount;

        for (int i = 0; i < playerCount; ++i) {
            bool isValidPlayer;
            packet >> isValidPlayer;

            if (!isValidPlayer) {
                continue;
            }

            // Read player type identifier
            bool isPacman;
            packet >> isPacman;

            // Create appropriate player type
            PlayerCharacter* player = nullptr;
            try {
                if (isPacman) {
                    player = new PacMan();
                } else {
                    player = new Ghost();
                }

                // Deserialize player data
                packet >> *player;
                level._playersCharacters.push_back(player);
            } catch (const std::exception& e) {
                std::cerr << "Exception during player deserialization: " << e.what() << std::endl;
                delete player; // Clean up on error
            }
        }

        // Deserialize powerups
        int powerupCount;
        packet >> powerupCount;
        for (int i = 0; i < powerupCount; ++i) {
            int x, y;
            int typeInt;
            packet >> x >> y >> typeInt;
            PowerUpType type = static_cast<PowerUpType>(typeInt);
            PowerUp powerup(x, y, type);
            level._powerups.push_back(powerup);
        }

        // Deserialize objectives
        int objectiveCount;
        packet >> objectiveCount;
        for (int i = 0; i < objectiveCount; ++i) {
            int x, y;
            packet >> x >> y;
            Objective objective(x, y);
            level._objectives.push_back(objective);
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception during Level deserialization: " << e.what() << std::endl;
        // Clean up any partially constructed objects
        for (auto* player : level._playersCharacters) {
            delete player;
        }
        level._playersCharacters.clear();
    }

    return packet;
}

