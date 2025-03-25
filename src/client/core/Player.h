
#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <SFML/Graphics.hpp>


class Player {
    std::string name;
    sf::Vector2f position;
    int direction;
    bool isPacman;
    int score;
    bool isAlive;

    public:
    Player(int x, int y);

    void move(int x, int y);

public:
    Player(const std::string& nickname);
    std::string getNickname() const;
    int getScore() const;
    void updateScore(int points);
};



#endif //PLAYER_H
