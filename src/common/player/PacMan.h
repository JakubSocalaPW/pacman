#ifndef PACMAN_H
#define PACMAN_H


#include "../abstract/PlayerCharacter.h"

class PacMan : public PlayerCharacter {

public:
    PacMan(int x, int y, Player* player);
    PacMan(Player* player);
    PacMan();
    bool isPacman() override;
};

#endif //PACMAN_H
