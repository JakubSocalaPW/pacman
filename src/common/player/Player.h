#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <SFML/Graphics.hpp>

#include "SFML/Network/Packet.hpp"


class Player {
    std::string _name;
    bool _isPacman;
    int _score;

public:
    Player(const std::string& nickname);
    Player();
    std::string getNickname() const;
    int getScore() const;
    void addScore(int points);
    bool getIsPacman() const;

    // Serialization/Deserialization friends
    friend sf::Packet& operator<<(sf::Packet& packet, const Player& player);
    friend sf::Packet& operator>>(sf::Packet& packet, Player& player);
    friend sf::Packet& operator<<(sf::Packet& packet, const Player* player);
    friend sf::Packet& operator>>(sf::Packet& packet, Player* player);
};


#endif //PLAYER_H