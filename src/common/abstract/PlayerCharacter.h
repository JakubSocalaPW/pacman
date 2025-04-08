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
    Player* player;



public:
    // virtual void updatePosition(const sf::Vector2<int>& position) = 0;
    PlayerCharacter(){}
    PlayerCharacter(int x, int y, Player* player):
        position(x, y),
        player(player) {
    };
    PlayerCharacter(Player* player) : player(player) {};
    virtual bool isPacman() = 0;
    sf::Vector2<float> getPosition() const;
    float getSpeed() const;
    void setImmunityTime(int time);
    bool isAtGridPoint();
    void move(float x, float y);
    Player& getPlayer() { return *player; }
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

    // todo
    friend sf::Packet& operator<<(sf::Packet& packet, const PlayerCharacter& player);
    friend sf::Packet& operator>>(sf::Packet& packet, PlayerCharacter& player);
};

#endif //PLAYERCHARACTER_H
