

#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include <SFML/Network.hpp>
#include <list>
#include "Player.h"

class Level {
    std::vector<std::vector<int>> gameMap;
    std::vector<Player> players;
    std::vector<sf::Vector2f> powerupPositions;

public:
    Level(int number);
    void loadLevel(int levelIndex);
    bool isWallAt(const sf::Vector2f& position) const;
    std::list<sf::Vector2f> getWallPositions() const;
    int getLevelNumber() const;
    void resetLevel();
};



#endif //LEVEL_H
