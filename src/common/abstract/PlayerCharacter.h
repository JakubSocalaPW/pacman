#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include <vector>
#include <SFML/Network.hpp>
#include "../player/Player.h"

class PlayerCharacter {
protected:
    int m_immunityTime;
    int m_movementDirection;
    float m_speed;
    int direction;
    bool isAlive = true;
    bool isInvincible = false;
    bool isGhostKiller = false;
    int powerUpDurationLeft = 0;
    int requestedDirection;
    bool isSpeedBoosted = false;
    sf::Vector2f position;
    Player* player = nullptr; // Initialize to nullptr

public:
    // Default constructor
    PlayerCharacter() : player(nullptr) {}

    // Constructor with position and player
    PlayerCharacter(int x, int y, Player* player) :
        position(x, y),
        player(player) {
    }

    // Constructor with just player
    PlayerCharacter(Player* player) : player(player) {}

    // Virtual destructor to ensure proper cleanup in derived classes
    virtual ~PlayerCharacter() {
    }

    // Delete copy constructor and assignment operator to prevent double-free issues
    PlayerCharacter(const PlayerCharacter&) = delete;
    PlayerCharacter& operator=(const PlayerCharacter&) = delete;

    // Implement move semantics
    PlayerCharacter(PlayerCharacter&& other) noexcept :
        m_immunityTime(other.m_immunityTime),
        m_movementDirection(other.m_movementDirection),
        m_speed(other.m_speed),
        direction(other.direction),
        isAlive(other.isAlive),
        isInvincible(other.isInvincible),
        isGhostKiller(other.isGhostKiller),
        powerUpDurationLeft(other.powerUpDurationLeft),
        requestedDirection(other.requestedDirection),
        isSpeedBoosted(other.isSpeedBoosted),
        position(other.position),
        player(other.player) {
        other.player = nullptr; // Prevent double deletion
    }

    PlayerCharacter& operator=(PlayerCharacter&& other) noexcept {
        if (this != &other) {
            delete player; // Delete our current player

            // Move all data
            m_immunityTime = other.m_immunityTime;
            m_movementDirection = other.m_movementDirection;
            m_speed = other.m_speed;
            direction = other.direction;
            isAlive = other.isAlive;
            isInvincible = other.isInvincible;
            isGhostKiller = other.isGhostKiller;
            powerUpDurationLeft = other.powerUpDurationLeft;
            requestedDirection = other.requestedDirection;
            isSpeedBoosted = other.isSpeedBoosted;
            position = other.position;
            player = other.player;

            other.player = nullptr; // Prevent double deletion
        }
        return *this;
    }

    virtual bool isPacman() = 0;
    sf::Vector2<float> getPosition() const;
    float getSpeed() const;
    void setImmunityTime(int time);
    bool isAtGridPoint();
    void move(float x, float y);

    // Safely access player (with null check)
    Player* getPlayerPtr() { return player; }
    Player& getPlayer() {
        if (!player) {
            throw std::runtime_error("Accessing null player pointer");
        }
        return *player;
    }

    void setPlayer(Player* newPlayer) {
        player = newPlayer;
    }

    bool canMoveInDirection(int dir, const std::vector<std::vector<int>>& gameMap);
    int getDirection() const { return direction; }
    void changeDirection(int dir, const std::vector<std::vector<int>>& gameMap);
    bool getIsAlive() const { return isAlive; }
    void setIsAlive(bool alive) { isAlive = alive; }
    void updateMovement(const std::vector<std::vector<int>>& gameMap);
    void setIsGhostKiller(bool ghostKiller) { isGhostKiller = ghostKiller; }
    bool getIsGhostKiller() const { return isGhostKiller; }
    int getPowerUpDurationLeft() const { return powerUpDurationLeft; }
    void setPowerUpDurationLeft(int duration) { powerUpDurationLeft = duration; }
    void setInvincible(bool invincible) { isInvincible = invincible; }
    bool getIsInvincible() const { return isInvincible; }
    void setSpeedBoosted(bool speedBoosted) { isSpeedBoosted = speedBoosted; }
    bool getIsSpeedBoosted() const { return isSpeedBoosted; }

    friend sf::Packet& operator<<(sf::Packet& packet, const PlayerCharacter& player);
    friend sf::Packet& operator>>(sf::Packet& packet, PlayerCharacter& player);
};

#endif //PLAYERCHARACTER_H
