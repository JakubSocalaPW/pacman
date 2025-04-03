#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include <vector>

#include <SFML/System.hpp>


class PlayerCharacter {
protected:
    int m_immunityTime;
    int m_movementDirection;
    float m_speed;
    sf::Vector2<int> position;

public:
    PlayerCharacter(float speed = 1.0f);
    virtual void updatePosition(const sf::Vector2<int>& position) = 0;
    virtual bool isAlive() const;

    sf::Vector2<int> getPosition() const;
    float getSpeed() const;
    void setImmunityTime(int time);
};

#endif //PLAYERCHARACTER_H
