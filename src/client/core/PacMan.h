
#ifndef PACMAN_H
#define PACMAN_H



#include "PlayerCharacter.h"

class PacMan : public PlayerCharacter {
    bool m_isPowerUpActive;
    int m_livesLeft;

public:
    PacMan();
    void updatePosition(const sf::Vector2<int>& position) override;
    void activatePowerUp(float duration);
    bool isPowerUpActive() const;
    int getLivesLeft() const;
    void decreaseLife();
    void collectPoint();
};

#endif //PACMAN_H
