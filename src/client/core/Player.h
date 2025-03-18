
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


};



#endif //PLAYER_H
