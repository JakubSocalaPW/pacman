#include "Drawable.h"

sf::Vector2<int> Drawable::getPosition() const {
    return { m_position.x, m_position.y};
}
