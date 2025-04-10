#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <SFML/Graphics.hpp>
#include "SFML/Network/Packet.hpp"

/**
 * @class Player
 * @brief Represents a player in the game, storing their nickname, score, and role.
 */
class Player {
private:
    std::string _name;
    bool _isPacman = false;
    int _score = 0;

public:
    /**
     * @brief Constructor for the Player class, initializing the player with a nickname.
     * @param nickname The desired nickname for the player.
     */
    Player(const std::string& nickname);

    /**
     * @brief Default constructor for the Player class. Nickname is empty string.
     */
    Player();

    /**
     * @brief Gets the player's nickname.
     * @return The player's nickname as a string.
     */
    std::string getNickname() const;

    /**
     * @brief Gets the player's current score.
     * @return The player's score as an integer.
     */
    int getScore() const;

    /**
     * @brief Adds points to the player's current score.
     * @param points The number of points to add.
     */
    void addScore(int points);

    /**
     * @brief Checks if the player is currently Pac-Man.
     * @return True if the player is Pac-Man, false otherwise.
     */
    bool getIsPacman() const;

    /**
     * @brief Sets whether the player is Pac-Man.
     * @param isPacman True if the player should be Pac-Man, false otherwise.
     */
    void setIsPacMan(bool isPacman);

    /**
     * @brief Overloads the SFML packet insertion operator to serialize Player data.
     * @param packet The SFML packet to insert data into.
     * @param player A reference to the Player object to serialize.
     * @return A reference to the modified SFML packet.
     */
    friend sf::Packet& operator<<(sf::Packet& packet, const Player& player);

    /**
     * @brief Overloads the SFML packet extraction operator to deserialize Player data.
     * @param packet The SFML packet to extract data from.
     * @param player A reference to the Player object to populate with deserialized data.
     * @return A reference to the modified SFML packet.
     */
    friend sf::Packet& operator>>(sf::Packet& packet, Player& player);
};

#endif //PLAYER_H