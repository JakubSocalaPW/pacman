#include "Player.h"


Player::Player(const std::string& nickname) {
    _name = nickname;
}

Player::Player() : _name(""), _isPacman(false), _score(0) {
}

int Player::getScore() const {
    return _score;
}

void Player::addScore(int points) {
    _score += points;
}

std::string Player::getNickname() const {
    return _name;
}

bool Player::getIsPacman() const {
    return _isPacman;
}

sf::Packet& operator<<(sf::Packet& packet, const Player& player) {
    return packet << player._name << player._score << player._isPacman;
}

sf::Packet& operator>>(sf::Packet& packet, Player& player) {
    return packet >> player._name >> player._score >> player._isPacman;
}

sf::Packet& operator<<(sf::Packet& packet, const Player* player) {
    return packet << player->_name << player->_score << player->_isPacman;
}

sf::Packet& operator>>(sf::Packet& packet, Player* player) {
    return packet >> player->_name >> player->_score >> player->_isPacman;
}