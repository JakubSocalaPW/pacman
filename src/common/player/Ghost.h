
#ifndef GHOST_H
#define GHOST_H
#include "../abstract/PlayerCharacter.h"

class Ghost : public PlayerCharacter {

public:
    Ghost(int x, int y, Player* player);
    Ghost(Player* player);
    Ghost();
    bool isPacman() override;
};
#endif //GHOST_H
