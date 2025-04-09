#ifndef LEVEL_H
#define LEVEL_H
#include <iostream>
#include <vector>
#include <SFML/Network.hpp>
#include <list>

#include "Objective.h"
#include "PowerUp.h"
#include "Wall.h"
#include "../abstract/PlayerCharacter.h"
#include "../player/Ghost.h"
#include "../player/PacMan.h"

class Level {
    std::list<Wall> gameMap;
    std::vector<PlayerCharacter*> players;
    std::list<PowerUp> powerups;
    std::list<Objective> objectives;

public:
    Level();
    Level(std::vector<std::vector<int>> map);
    ~Level();  // Destructor to clean up memory
    
    // Copy constructor and assignment operator to handle deep copying
    Level(const Level& other);
    Level& operator=(const Level& other);
    
    // Move constructor and assignment operator for efficient transfers
    Level(Level&& other) noexcept;
    Level& operator=(Level&& other) noexcept;
    
    bool isWallAt(const sf::Vector2f& position) const;
    std::list<sf::Vector2<int>> getWallPositions() const;
    int getLevelNumber() const;
    
    // Serialization methods
    sf::Packet serialize() const;
    static Level deserialize(sf::Packet& packet);

    // Operators for SFML packet serialization
    friend sf::Packet& operator<<(sf::Packet& packet, const Level& level);
    friend sf::Packet& operator>>(sf::Packet& packet, Level& level);

    // Getter methods needed for serialization
    const std::list<Wall>& getWalls() const { return gameMap; }
    std::vector<PlayerCharacter*>& getPlayerCharacters() { return players; }
    void setPlayerCharacters(std::vector<PlayerCharacter*> players) { this->players = players; }
    std::list<PowerUp>& getPowerUps() { return powerups; }
    std::list<Objective>& getObjectives() { return objectives; }
    
    void removePowerUp(PowerUp& powerUp) {
        powerups.remove_if([&](const PowerUp& p) {
            return &p == &powerUp;  // Compare memory addresses
        });
    }
    
    void removeObjective(Objective& objective) {
        objectives.remove_if([&](const Objective& o) {
            return &o == &objective;  // Compare memory addresses
        });
    }

    std::vector<Ghost*> getGhosts() {
        std::vector<Ghost*> ghosts;

        for (auto* player : players) {
            if (player == nullptr) {
                std::cout << "nulpointer z getGhosts" << std::endl;
            }
            if (!player->isPacman()) {
                auto* ghost = dynamic_cast<Ghost*>(player);
                if (ghost) {
                    ghosts.push_back(ghost);
                }
            }
        }
        return ghosts;
    }

    std::vector<std::vector<int>> getWallPositionsAsVector() const {
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
    
    void addPlayer(PlayerCharacter* player) {
        std::cout << "addPlayer" << std::endl;
        players.push_back(player); 
    }
};

#endif //LEVEL_H