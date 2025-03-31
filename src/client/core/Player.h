
#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>


class Player {
    std::string name;
    sf::Vector2f position;
    int direction;
    bool isPacman;
    int score;
    bool isAlive;
    int requestedDirection;
    bool canMoveInDirection(int dir, const std::vector<std::vector<int>>& gameMap);



public:
    Player(int x, int y, std::string name);
    void move(float x, float y);
    Player(const std::string& nickname);
    std::string getNickname() const {return name; }
    int getScore() const;
    void addScore(int points);
    // Getter and setter methods needed for serialization
    sf::Vector2f getPosition() const { return position; }
    void setPosition(const sf::Vector2f& pos) { position = pos; }
    int getDirection() const { return direction; }
    void changeDirection(int dir, const std::vector<std::vector<int>>& gameMap);
    bool getIsPacman() const { return isPacman; }
    void setIsPacman(bool pacman) { isPacman = pacman; }
    bool getIsAlive() const { return isAlive; }
    void setIsAlive(bool alive) { isAlive = alive; }
    void updateMovement(const std::vector<std::vector<int>>& gameMap);


    // Operators for SFML packet serialization
    friend sf::Packet& operator<<(sf::Packet& packet, const Player& player);
    friend sf::Packet& operator>>(sf::Packet& packet, Player& player);

    // Default constructor needed for deserialization
    Player();

};



#endif //PLAYER_H
