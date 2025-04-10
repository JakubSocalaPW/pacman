// Player.h - Removed unnecessary pointer operators
#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <SFML/Graphics.hpp>
#include "SFML/Network/Packet.hpp"

class Player {
    std::string _name;
    bool _isPacman = false;
    int _score = 0;

public:
    Player(const std::string& nickname);
    Player();
    std::string getNickname() const;
    int getScore() const;
    void addScore(int points);
    bool getIsPacman() const;
    void setIsPacMan(bool isPacman) {
        _isPacman = isPacman;
    }

    // Only keep reference-based serialization/deserialization
    friend sf::Packet& operator<<(sf::Packet& packet, const Player& player);
    friend sf::Packet& operator>>(sf::Packet& packet, Player& player);
};

#endif //PLAYER_H