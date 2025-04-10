#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "SFML/Graphics.hpp";

/**
 * @class Drawable
 * @brief An abstract base class for objects that can be drawn on the screen.
 *
 * This class defines the basic properties that a drawable object should have,
 * for now - position in the game world.
 */
class Drawable {
protected:
    /**
     * @brief The current position of the object in the game world. Please note that this are indexes, not pixels coordinates.
     */
    sf::Vector2<int> _position{0, 0};

public:
    /**
     * @brief Gets the current position of the drawable object.
     * @return An sf::Vector2<int> representing the object's position.
     */
    sf::Vector2<int> getPosition() const;
};

#endif //DRAWABLE_H