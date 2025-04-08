#include "Ghost.h"

Ghost::Ghost(Player* player): PlayerCharacter(player) {
}

Ghost::Ghost() {
}

Ghost::Ghost(int x, int y, Player* player): PlayerCharacter(x, y, player) {
}

bool Ghost::isPacman() {
    return false;
}