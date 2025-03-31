

#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include <SFML/Network.hpp>
#include <list>

#include "Objective.h"
#include "Player.h"
#include "PowerUp.h"
#include "Wall.h"

class Level {
    std::list<Wall> gameMap;
    std::vector<Player> players;
    std::list<PowerUp> powerups;
    std::list<Objective> objectives;

public:
    Level();
    Level(std::vector<std::vector<int>> map);
    bool isWallAt(const sf::Vector2f& position) const;
    std::list<sf::Vector2<int>> getWallPositions() const;
    int getLevelNumber() const;
    void resetLevel();
    // Serialization methods
    sf::Packet serialize() const;
    static Level deserialize(sf::Packet& packet);

    // Operators for SFML packet serialization
    friend sf::Packet& operator<<(sf::Packet& packet, const Level& level);
    friend sf::Packet& operator>>(sf::Packet& packet, Level& level);

    // Getter methods needed for serialization
    const std::list<Wall>& getWalls() const { return gameMap; }
    std::vector<Player>& getPlayers()  { return players; }
    const std::list<PowerUp>& getPowerUps() const { return powerups; }
    const std::list<Objective>& getObjectives() const { return objectives; }
    std::vector<std::vector<int>> getWallPositionsAsVector() const {
        // Determine the grid size (assuming you have width and height of the map somewhere)
        // If not available directly, you might need to find max x and y from all walls
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
    // Method to add a player
    void addPlayer(const Player& player) { players.push_back(player); }
};



#endif //LEVEL_H
