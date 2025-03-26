

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
};



#endif //LEVEL_H
