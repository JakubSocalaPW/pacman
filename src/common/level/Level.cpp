#include "Level.h"
#include <iostream>
#include "../player/PacMan.h"
#include "Objective.h"

Level::Level() {
}

Level::~Level() {
    // Clean up allocated player memory
    for (auto* player : players) {
        delete player;
    }
    players.clear();
}

Level::Level(const Level& other) :
    gameMap(other.gameMap),
    powerups(other.powerups),
    objectives(other.objectives),
    players(other.players)
{ }

Level& Level::operator=(const Level& other) {
    if (this != &other) {
        // for (auto* player : players) {
        //     delete player;
        // }
        // players.clear();

        // Copy resources
        gameMap = other.gameMap;
        powerups = other.powerups;
        objectives = other.objectives;
        players = other.players;

        // for (const auto* player : other.players) {
        //     PlayerCharacter* newPlayer = new PlayerCharacter(*player);
        //     players.push_back(newPlayer);
        // }
    }
    return *this;
}

// Move constructor
Level::Level(Level&& other) noexcept :
    gameMap(std::move(other.gameMap)),
    players(std::move(other.players)),
    powerups(std::move(other.powerups)),
    objectives(std::move(other.objectives)) {

    // Ensure other doesn't delete our pointers
    other.players.clear();
}

// Move assignment operator
Level& Level::operator=(Level&& other) noexcept {
    if (this != &other) {
        // Clean up existing resources
        for (auto* player : players) {
            delete player;
        }

        // Move resources
        gameMap = std::move(other.gameMap);
        players = std::move(other.players);
        powerups = std::move(other.powerups);
        objectives = std::move(other.objectives);

        // Ensure other doesn't delete our pointers
        other.players.clear();
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
                    gameMap.push_back(w);
                    break;
                }
                case 2: {
                    Objective o{rowCounter, colCounter};
                    objectives.push_back(o);
                    break;
                }
                case 3: {
                    PowerUp p{rowCounter, colCounter, PowerUp::getRandomPowerUp()};
                    powerups.push_back(p);
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

    for (const auto& wall : gameMap) {
        wallPositions.push_back(wall.getPosition());
    }

    return wallPositions;
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
    packet << static_cast<int>(level.gameMap.size());
    for (const auto& wall : level.gameMap) {
        const sf::Vector2<int>& pos = wall.getPosition();
        packet << pos.x << pos.y;
    }

    // Serialize players
    packet << static_cast<int>(level.players.size());
    for (auto* player : level.players) {
        // Write player type identifier
        packet << player->isPacman();

        // Serialize player data
        packet << *player;
    }

    // Serialize powerups
    packet << static_cast<int>(level.powerups.size());
    for (const auto& powerup : level.powerups) {
        const sf::Vector2<int>& pos = powerup.getPosition();
        packet << pos.x << pos.y << static_cast<int>(powerup.getType());
    }

    // Serialize objectives
    packet << static_cast<int>(level.objectives.size());
    for (const auto& objective : level.objectives) {
        const sf::Vector2<int>& pos = objective.getPosition();
        packet << pos.x << pos.y;
    }

    return packet;
}


sf::Packet& operator>>(sf::Packet& packet, Level& level) {
    // Clean up existing player data
    for (auto& player : level.players) {
        delete player;
        player = nullptr;
    }

    // Clear existing data
    level.gameMap.clear();
    level.players.clear();
    level.powerups.clear();
    level.objectives.clear();

    // Deserialize walls
    int wallCount;
    packet >> wallCount;
    for (int i = 0; i < wallCount; ++i) {
        int x, y;
        packet >> x >> y;
        Wall wall(x, y);
        level.gameMap.push_back(wall);
    }

    // Deserialize players
    int playerCount;
    packet >> playerCount;
    for (int i = 0; i < playerCount; ++i) {
        // Read player type identifier
        bool isPacman;
        packet >> isPacman;

        // Create appropriate player type
        PlayerCharacter* player;
        if (isPacman) {
            player = new PacMan();
        } else {
            player = new Ghost();
        }

        // Deserialize player data
        packet >> *player;
        level.players.push_back(player);
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
        level.powerups.push_back(powerup);
    }

    // Deserialize objectives
    int objectiveCount;
    packet >> objectiveCount;
    for (int i = 0; i < objectiveCount; ++i) {
        int x, y;
        packet >> x >> y;
        Objective objective(x, y);
        level.objectives.push_back(objective);
    }

    return packet;
}