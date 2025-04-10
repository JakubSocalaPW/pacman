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

    // Delete copy constructor and assignment to prevent issues with pointer ownership
    Level(const Level&) = delete;
    Level& operator=(const Level&) = delete;

    // Implement move semantics
    Level(Level&& other) noexcept;
    Level& operator=(Level&& other) noexcept;

    bool isWallAt(const sf::Vector2f& position) const;
    std::list<sf::Vector2<int>> getWallPositions() const;
    int getLevelNumber() const;
    int getSize() const { return getWallPositionsAsVector().size(); }

    // Serialization methods
    sf::Packet serialize() const;
    static Level deserialize(sf::Packet& packet);

    // Operators for SFML packet serialization
    friend sf::Packet& operator<<(sf::Packet& packet, const Level& level);
    friend sf::Packet& operator>>(sf::Packet& packet, Level& level);

    // Getter methods needed for serialization
    const std::list<Wall>& getWalls() const { return gameMap; }
    std::vector<PlayerCharacter*>& getPlayerCharacters() { return players; }
    void setPlayerCharacters(std::vector<PlayerCharacter*> players); // Will be implemented with proper memory management
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

    std::vector<Ghost*> getGhosts();
    std::vector<std::vector<int>> getWallPositionsAsVector() const;
    void addPlayer(PlayerCharacter* player);
};

#endif //LEVEL_H