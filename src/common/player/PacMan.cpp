#include "PacMan.h"


PacMan::PacMan(Player* player): PlayerCharacter(player) {
}

PacMan::PacMan() {
}

PacMan::PacMan(int x, int y, Player* player): PlayerCharacter(x, y, player) {
}

bool PacMan::isPacman() {
    return true;
}
