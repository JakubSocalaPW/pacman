
#ifndef OBJECTIVE_H
#define OBJECTIVE_H

#include <cstdint>
#include <SFML/System.hpp>


class Objective {
    int m_value;
    sf::Vector2<int> m_position;

public:
    Objective(int32_t value, const sf::Vector2<int>& position);
    int getValue() const;
    sf::Vector2<int> getPosition() const;
    virtual int getReward() const;
};

#endif //OBJECTIVE_H
