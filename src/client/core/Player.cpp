//
// Created by jakub on 17.03.2025.
//

#include "Player.h"

Player::Player(int x, int y) {
    this->x = x;
    this->y = y;
}

void Player:: move(int x, int y) {

    //todo implement world boundaries
    //
    this->x = x;
    this->y = y;
}