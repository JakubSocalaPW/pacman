#include "Drawable.h"

sf::Vector2<int> Drawable::getPosition() const {
    return { _position.x, _position.y};
}
