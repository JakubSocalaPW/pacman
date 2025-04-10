#include "Ghost.h"

Ghost::Ghost(int x, int y, Player* player) : PlayerCharacter(x, y, player) {
    if (player) {
        player->setIsPacMan(false); // Ensure player knows it's a ghost
    }
}

Ghost::Ghost(Player* player) : PlayerCharacter(player) {
    if (player) {
        player->setIsPacMan(false); // Ensure player knows it's a ghost
    }
}

Ghost::Ghost() : PlayerCharacter() {
    // Allocate a default Player for this Ghost
    player = new Player();
    if (player) {
        player->setIsPacMan(false);
    }
}

bool Ghost::isPacman() {
    return false;
}