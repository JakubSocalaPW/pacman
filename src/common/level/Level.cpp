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
        players.clear();

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

void Level::setPlayerCharacters(std::vector<PlayerCharacter*> newPlayers) {
    // Clean up existing players
    for (auto* player : players) {
        delete player;
    }
    players.clear();

    // Take ownership of new players
    players = std::move(newPlayers);
}

std::vector<Ghost*> Level::getGhosts() {
    std::vector<Ghost*> ghosts;

    for (auto* player : players) {
        if (player == nullptr) {
            std::cout << "nullptr in getGhosts" << std::endl;
            continue; // Skip null pointers
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
    // Determine the grid size
    int width = 0;
    int height = 0;

    for (const auto& element : getWalls()) {
        auto pos = element.getPosition();
        if (pos.x > width) width = pos.x;
        if (pos.y > height) height = pos.y;
    }

    width++;
    height++; //to overcome 0-based indexing

    // Initialize grid with all zeros (no walls)
    std::vector<std::vector<int>> grid(height, std::vector<int>(width, 0));

    // Mark walls in the grid with 1
    for (const auto& wall : getWalls()) {
        // Convert wall position to grid coordinates
        int gridX = static_cast<int>(wall.getPosition().x);
        int gridY = static_cast<int>(wall.getPosition().y);

        // Set wall position to 1 in the grid
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
    players.push_back(player);
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
    for (auto* playerCharacter : level.players) {
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
    try {
        // Clean up existing player data
        for (auto& player : level.players) {
            delete player;
            player = nullptr;
        }
        level.players.clear();

        // Clear existing data
        level.gameMap.clear();
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
            // Check if this is a valid player
            bool isValidPlayer;
            packet >> isValidPlayer;

            if (!isValidPlayer) {
                // Skip this invalid player entry
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
                level.players.push_back(player);
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
    } catch (const std::exception& e) {
        std::cerr << "Exception during Level deserialization: " << e.what() << std::endl;
        // Clean up any partially constructed objects
        for (auto* player : level.players) {
            delete player;
        }
        level.players.clear();
    }

    return packet;
}

