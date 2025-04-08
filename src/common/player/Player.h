#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <SFML/Graphics.hpp>


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
};


#endif //PLAYER_H