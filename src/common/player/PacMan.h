#ifndef PACMAN_H
#define PACMAN_H

#include "../abstract/PlayerCharacter.h"

/**
 * @class PacMan
 * @brief Represents the main player character in the game, Pac-Man.
 *
 * This class inherits from PlayerCharacter and adds possibility for performing actions as PacMan
 */
class PacMan : public PlayerCharacter {

public:
    /**
     * @brief Constructor for the PacMan class with initial position and associated Player object.
     * @param x The initial x-coordinate of Pac-Man.
     * @param y The initial y-coordinate of Pac-Man.
     * @param player A pointer to the Player object associated with Pac-Man.
     */
    PacMan(int x, int y, Player* player);

    /**
     * @brief Constructor for the PacMan class with only the associated Player object.
     * @param player A pointer to the Player object associated with Pac-Man.
     */
    PacMan(Player* player);

    /**
     * @brief Default constructor for the PacMan class.
     */
    PacMan();

    /**
     * @brief Overrides the isPacman function from PlayerCharacter to identify this character type.
     * @return Always returns true, as this is Pac-Man.
     * @override
     */
    bool isPacman() override;
};

#endif //PACMAN_H