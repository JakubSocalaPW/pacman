
#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <string>
#include "SFML/Graphics.hpp"

class Drawable {
protected:
    std::string m_textureUI;
    sf::Vector2f m_position;

public:
    virtual void draw() = 0;
    virtual void virtual_draw() = 0;
    std::string getTexture() const;
    sf::Vector2f getPosition() const;
};



#endif //DRAWABLE_H
