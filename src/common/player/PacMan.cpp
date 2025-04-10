#include "PacMan.h"

PacMan::PacMan(int x, int y, Player* player) : PlayerCharacter(x, y, player) {
    if (player) {
        player->setIsPacMan(true); // Ensure player knows it's a pacman
    }
}

PacMan::PacMan(Player* player) : PlayerCharacter(player) {
    if (player) {
        player->setIsPacMan(true) ; // Ensure player knows it's a pacman
    }
}

PacMan::PacMan() : PlayerCharacter() {
    // Allocate a default Player for this PacMan
    player = new Player();
    if (player) {
        player->setIsPacMan(true) ;
    }
}

bool PacMan::isPacman() {
    return true;
}