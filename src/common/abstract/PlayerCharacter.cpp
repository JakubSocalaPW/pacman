#include "PlayerCharacter.h"
#include <cmath>
#include <iostream>

void PlayerCharacter:: move(float x, float y) {
    position = sf::Vector2f(x, y);
}

sf::Vector2<float> PlayerCharacter::getPosition() const {
    return position;
}

void PlayerCharacter::changeDirection(int dir, const std::vector<std::vector<int>>& gameMap) {
    requestedDirection = dir;

    if (isAtGridPoint()) {
        if (canMoveInDirection(requestedDirection, gameMap)) {
            direction = requestedDirection;
        }
    }
}

void PlayerCharacter::updateMovement(const std::vector<std::vector<int>>& gameMap) {
    if (direction < 0) {
        return;
    }

    // Check direction changes and wall collisions
    if (isAtGridPoint()) {
        if (canMoveInDirection(requestedDirection, gameMap)) {
            direction = requestedDirection;
        } else if (!canMoveInDirection(direction, gameMap)) {
            return; // Can't move in current direction
        }
    }

    // Calculate new position
    float newX = position.x;
    float newY = position.y;
    const float MOVE_SPEED_DEFAULT = 0.10f; //default 0.05f
    const float MOVE_SPEED = isSpeedBoosted ? MOVE_SPEED_DEFAULT * 2 : MOVE_SPEED_DEFAULT;

    if (direction == 0) // Up
        newY -= MOVE_SPEED;
    else if (direction == 2) // Down
        newY += MOVE_SPEED;
    else if (direction == 1) // Right
        newX += MOVE_SPEED;
    else if (direction == 3) // Left
        newX -= MOVE_SPEED;

    // Snap to grid when very close to integer positions
    const float SNAP_THRESHOLD = 0.01f;
    if (std::abs(newX - std::round(newX)) < SNAP_THRESHOLD)
        newX = std::round(newX);
    if (std::abs(newY - std::round(newY)) < SNAP_THRESHOLD)
        newY = std::round(newY);

    // Move to new position
    move(newX, newY);
}

bool PlayerCharacter::canMoveInDirection(int dir, const std::vector<std::vector<int>>& gameMap) {
    int currentIndexX = static_cast<int>(position.x);
    int currentIndexY = static_cast<int>(position.y);

    int newIndexX = currentIndexX + (dir == 1 ? 1 : (dir == 3 ? -1 : 0));
    int newIndexY = currentIndexY + (dir == 2 ? 1 : (dir == 0 ? -1 : 0));

    if (newIndexY < 0 || newIndexY >= gameMap.size() ||
        newIndexX < 0 || newIndexX >= gameMap[0].size()) {
        return false;  // Out of bounds
    }

    bool isWallAtNewPosition = gameMap[newIndexY][newIndexX] == 1;

    return !isWallAtNewPosition;
}

bool PlayerCharacter::isAtGridPoint() {
    return (std::fmod(position.x, 1.0) < 0.01 && fmod(position.y, 1.0) < 0.01);
}

// Serialization operator - fixed to handle null player pointers
sf::Packet& operator<<(sf::Packet& packet, const PlayerCharacter& player) {
    packet << player.position.x << player.position.y;
    packet << player.direction;
    packet << player.isAlive;
    packet << player.isInvincible;
    packet << player.isGhostKiller;
    packet << player.powerUpDurationLeft;
    packet << player.requestedDirection;
    packet << player.isSpeedBoosted;


    std::cout << "  test" << std::endl;
    packet << *(player.player);

    std::cout << "  test23" << std::endl;

    return packet;
}

// Deserialization operator - fixed to handle null player pointers
sf::Packet& operator>>(sf::Packet& packet, PlayerCharacter& player) {
    packet >> player.position.x >> player.position.y;
    packet >> player.direction;
    packet >> player.isAlive;
    packet >> player.isInvincible;
    packet >> player.isGhostKiller;
    packet >> player.powerUpDurationLeft;
    packet >> player.requestedDirection;
    packet >> player.isSpeedBoosted;

    std::cout << "  desagfa" << std::endl;
    // Clean up existing player if any
    delete player.player;
    std::cout << "dejetesd" << std::endl;

    player.player = nullptr;

    player.player = new Player();
    packet >> *(player.player);


    return packet;
}