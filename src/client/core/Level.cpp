
#include "Level.h"

#include "Objective.h"


Level::Level() {
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
                    PowerUp p{rowCounter, colCounter, PowerUpType::Invincibility};
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