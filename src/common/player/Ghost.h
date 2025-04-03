
#ifndef GHOST_H
#define GHOST_H
#include "../abstract/PlayerCharacter.h"

class Ghost : public PlayerCharacter {

public:
    Ghost();
    void updatePosition(const sf::Vector2<int>& position) override;
};
#endif //GHOST_H
