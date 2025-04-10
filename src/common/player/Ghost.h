#ifndef GHOST_H
#define GHOST_H
#include "../abstract/PlayerCharacter.h"

/**
 * @brief Represents a ghost character in the game, an enemy to the main player.
 *
 * This class inherits from PlayerCharacter and implements the specific
 * behaviors and properties of a ghost, such as its movement patterns and
 * interactions with the main player (Pac-Man).
 */
class Ghost : public PlayerCharacter {

public:
    /**
     * @brief Constructor for the Ghost class with initial position and associated Player object.
     * @param x The initial x-coordinate of the ghost.
     * @param y The initial y-coordinate of the ghost.
     * @param player A pointer to the Player object associated with this ghost (can be null if not needed).
     */
    Ghost(int x, int y, Player* player);

    /**
     * @brief Constructor for the Ghost class with only the associated Player object.
     * @param player A pointer to the Player object associated with this ghost (can be null if not needed).
     */
    Ghost(Player* player);

    /**
     * @brief Default constructor for the Ghost class.
     */
    Ghost();

    /**
     * @brief Overrides the isPacman function from PlayerCharacter to identify this character type.
     * @return Always returns false, as this is a Ghost.
     * @override
     */
    bool isPacman() override;

};
#endif //GHOST_H