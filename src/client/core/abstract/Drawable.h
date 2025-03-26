
#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <string>
#include "SFML/Graphics.hpp"

class Drawable {
protected:
    std::string m_textureUI;
    sf::Vector2<int> m_position;

public:
    std::string getTexture() const;
    sf::Vector2<int> getPosition() const;
};



#endif //DRAWABLE_H
