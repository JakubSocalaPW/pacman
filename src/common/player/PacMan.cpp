#include "PacMan.h"

PacMan::PacMan(int x, int y, Player* player) : PlayerCharacter(x, y, player) {
    if (player) {
        player->setIsPacMan(true);
    }
}

PacMan::PacMan(Player* player) : PlayerCharacter(player) {
    if (player) {
        player->setIsPacMan(true);
    }
}

PacMan::PacMan() : PlayerCharacter() {
    _player = new Player();
    _player->setIsPacMan(true) ;
}

bool PacMan::isPacman() {
    return true;
}