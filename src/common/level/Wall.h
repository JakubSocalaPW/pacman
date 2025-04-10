#ifndef WALL_H
#define WALL_H
#include "../abstract/Drawable.h"

/**
 * @class Wall
 * @brief Represents an impassable wall tile in the game level.
 *
 * This class inherits from Drawable and signifies a static element that
 * player characters and other entities cannot move through.
 */
class Wall : public Drawable {

public:
    /**
     * @brief Default constructor for the Wall class.
     *
     * Initializes a wall object at a default position (0, 0).
     */
    Wall();

    /**
     * @brief Constructor for the Wall class with specified initial coordinates.
     * @param x The initial x-coordinate of the wall.
     * @param y The initial y-coordinate of the wall.
     */
    Wall(int x, int y);
};

#endif //WALL_H