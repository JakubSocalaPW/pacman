#include "PlayerCharacter.h"
#include <cmath>
#include <iostream>


PlayerCharacter::PlayerCharacter() : _player(nullptr){}

PlayerCharacter::PlayerCharacter(int x, int y, Player* player) :
    _position(static_cast<float>(x), static_cast<float>(y)),
    _player(player) {
}

PlayerCharacter::PlayerCharacter(Player* player) : _player(player) {}

PlayerCharacter::~PlayerCharacter() {}

PlayerCharacter::PlayerCharacter(PlayerCharacter&& other) noexcept :
        _speed(other._speed),
        _direction(other._direction),
        _isAlive(other._isAlive),
        _isInvincible(other._isInvincible),
        _isGhostKiller(other._isGhostKiller),
        _powerUpDurationLeft(other._powerUpDurationLeft),
        _requestedDirection(other._requestedDirection),
        _isSpeedBoosted(other._isSpeedBoosted),
        _position(other._position),
        _player(other._player) {
    other._player = nullptr; // Prevent double deletion
}

PlayerCharacter& PlayerCharacter::operator=(PlayerCharacter&& other) noexcept {
    if (this != &other) {
        _speed = other._speed;
        _direction = other._direction;
        _isAlive = other._isAlive;
        _isInvincible = other._isInvincible;
        _isGhostKiller = other._isGhostKiller;
        _powerUpDurationLeft = other._powerUpDurationLeft;
        _requestedDirection = other._requestedDirection;
        _isSpeedBoosted = other._isSpeedBoosted;
        _position = other._position;
        _player = other._player;

        other._player = nullptr; // Prevent double deletion
    }
    return *this;
}

void PlayerCharacter:: move(float x, float y) {
    _position = sf::Vector2f(x, y);
}

float PlayerCharacter::getSpeed() const {
    return _speed;
}

void PlayerCharacter::setIsGhostKiller(bool ghostKiller) {
    _isGhostKiller = ghostKiller;
}

bool PlayerCharacter::getIsGhostKiller() const {
    return _isGhostKiller;
}

int PlayerCharacter::getPowerUpDurationLeft() const {
    return _powerUpDurationLeft;
}

void PlayerCharacter::setPowerUpDurationLeft(int duration) {
    _powerUpDurationLeft = duration;
}

void PlayerCharacter::setInvincible(bool invincible) {
    _isInvincible = invincible;
}

bool PlayerCharacter::getIsInvincible() const {
    return _isInvincible;
}

void PlayerCharacter::setSpeedBoosted(bool speedBoosted) {
    _isSpeedBoosted = speedBoosted;
}

bool PlayerCharacter::getIsSpeedBoosted() const {
    return _isSpeedBoosted;
}

void PlayerCharacter::setIsAlive(bool alive) {
    _isAlive = alive;
}


void PlayerCharacter::setPlayer(Player* newPlayer) {
    _player = newPlayer;
}

int PlayerCharacter::getDirection() const {
    return _direction;
}

bool PlayerCharacter::getIsAlive() const { return _isAlive; }



Player& PlayerCharacter::getPlayer() {
    if (!_player) {
        throw std::runtime_error("Accessing null player pointer");
    }
    return *_player;
}

sf::Vector2<float> PlayerCharacter::getPosition() const {
    return _position;
}

Player* PlayerCharacter::getPlayerPtr() {
    return _player;
}


void PlayerCharacter::changeDirection(int dir, const std::vector<std::vector<int>>& gameMap) {
    _requestedDirection = dir;

    if (isAtGridPoint()) {
        if (canMoveInDirection(_requestedDirection, gameMap)) {
            _direction = _requestedDirection;
        }
    }
}

void PlayerCharacter::updateMovement(const std::vector<std::vector<int>>& gameMap) {
    if (_direction < 0) {
        return;
    }

    // Check direction changes and wall collisions
    if (isAtGridPoint()) {
        if (canMoveInDirection(_requestedDirection, gameMap)) {
            _direction = _requestedDirection;
        } else if (!canMoveInDirection(_direction, gameMap)) {
            return; // Can't move in current direction
        }
    }

    // Calculate new position
    float newX = _position.x;
    float newY = _position.y;
    const float MOVE_SPEED_DEFAULT = 0.10f; //default 0.05f
    const float MOVE_SPEED = _isSpeedBoosted ? MOVE_SPEED_DEFAULT * 2 : MOVE_SPEED_DEFAULT;

    if (_direction == 0) // Up
        newY -= MOVE_SPEED;
    else if (_direction == 2) // Down
        newY += MOVE_SPEED;
    else if (_direction == 1) // Right
        newX += MOVE_SPEED;
    else if (_direction == 3) // Left
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
    int currentIndexX = static_cast<int>(_position.x);
    int currentIndexY = static_cast<int>(_position.y);

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
    return (std::fmod(_position.x, 1.0) < 0.01 && fmod(_position.y, 1.0) < 0.01);
}

sf::Packet& operator<<(sf::Packet& packet, const PlayerCharacter& player) {
    packet << player._position.x << player._position.y;
    packet << player._direction;
    packet << player._isAlive;
    packet << player._isInvincible;
    packet << player._isGhostKiller;
    packet << player._powerUpDurationLeft;
    packet << player._requestedDirection;
    packet << player._isSpeedBoosted;

    packet << *(player._player);

    return packet;
}

sf::Packet& operator>>(sf::Packet& packet, PlayerCharacter& player) {
    packet >> player._position.x >> player._position.y;
    packet >> player._direction;
    packet >> player._isAlive;
    packet >> player._isInvincible;
    packet >> player._isGhostKiller;
    packet >> player._powerUpDurationLeft;
    packet >> player._requestedDirection;
    packet >> player._isSpeedBoosted;

    // Clean up existing player if any
    delete player._player;

    player._player = nullptr;

    player._player = new Player();
    packet >> *(player._player);


    return packet;
}
