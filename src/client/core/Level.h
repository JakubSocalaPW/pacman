

#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include <SFML/Network.hpp>

#include "Player.h"

class Level {
    std::vector<std::vector<int>> gameMap;
    std::vector<Player> players;
    std::vector<sf::Vector2f> powerupPositions;
};



#endif //LEVEL_H
