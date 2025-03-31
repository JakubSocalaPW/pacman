//
// Created by jakub on 17.03.2025.
//

#include "Player.h"

#include <cmath>
#include <iostream>

Player::Player(int x, int y, std::string name) {
    position = sf::Vector2f(x, y);
    this->name  = name;
}

void Player:: move(float x, float y) {
    position = sf::Vector2f(x, y);
}

int Player::getScore() const {
    return score;
}

void Player::changeDirection(int dir, const std::vector<std::vector<int>>& gameMap) { //todo move this second argument to more suitable place
    requestedDirection = dir;

    if (fmod(position.x, 1.0) < 0.01 && fmod(position.y, 1.0) < 0.01) {
        if (canMoveInDirection(requestedDirection, gameMap)) {
            direction = requestedDirection;
        }}
}

Player::Player(const std::string& nickname) {
    name = nickname;
}

Player::Player() : name(""), position(0, 0), direction(0), isPacman(false), score(0), isAlive(true) {
}

// Serialization operator
sf::Packet& operator<<(sf::Packet& packet, const Player& player) {
    packet << player.name;
    packet << player.position.x << player.position.y;
    packet << player.direction;
    packet << player.isPacman;
    packet << player.score;
    packet << player.isAlive;
    return packet;
}

// Deserialization operator
sf::Packet& operator>>(sf::Packet& packet, Player& player) {
    packet >> player.name;
    packet >> player.position.x >> player.position.y;
    packet >> player.direction;
    packet >> player.isPacman;
    packet >> player.score;
    packet >> player.isAlive;
    return packet;
}

void Player::updateMovement(const std::vector<std::vector<int>>& gameMap) {
    // Check direction changes and wall collisions
    if (fmod(position.x, 1.0) < 0.01 && fmod(position.y, 1.0) < 0.01) {
        if (canMoveInDirection(requestedDirection, gameMap)) {
            direction = requestedDirection;
        } else if (!canMoveInDirection(direction, gameMap)) {
            return;
        }
    }


    // Calculate new position
    float newX = position.x;
    float newY = position.y;
    const float MOVE_SPEED = 0.05f;

    if (direction == 0) // Up
        newY -= MOVE_SPEED;
    else if (direction == 2) // Down
        newY += MOVE_SPEED;
    else if (direction == 1) // Right
        newX += MOVE_SPEED;
    else if (direction == 3) // Left
        newX -= MOVE_SPEED;

    // Snap to grid when very close to integer positions (optional)
    const float SNAP_THRESHOLD = 0.01f;
    if (std::abs(newX - std::round(newX)) < SNAP_THRESHOLD)
        newX = std::round(newX);
    if (std::abs(newY - std::round(newY)) < SNAP_THRESHOLD)
        newY = std::round(newY);

    // Move to new position
    move(newX, newY);
}
bool Player::canMoveInDirection(int dir, const std::vector<std::vector<int>>& gameMap) {
    int currentIndexX = static_cast<int>(position.x);
    int currentIndexY = static_cast<int>(position.y);

    int newIndexX = currentIndexX + (dir == 1 ? 1 : (dir == 3 ? -1 : 0));
    int newIndexY = currentIndexY + (dir == 2 ? 1 : (dir == 0 ? -1 : 0));

    // Bounds checking
    if (newIndexY < 0 || newIndexY >= gameMap.size() ||
        newIndexX < 0 || newIndexX >= gameMap[0].size()) {
        return false;  // Out of bounds
        }

    // Check for wall - using same indexing as your getter function (y,x)
    bool isWallAtNewPosition = gameMap[newIndexY][newIndexX] == 1;

    // For debugging - make sure you print using the same indexing
    std::cout << "Check position: " << newIndexX << ", " << newIndexY << std::endl;
    std::cout << "Current: " << direction << ", " << position.x << ", " << position.y << std::endl;
    std::cout << "Wall at position? " << isWallAtNewPosition << " (value: " << gameMap[newIndexY][newIndexX] << ")" << std::endl;

    return !isWallAtNewPosition;
}