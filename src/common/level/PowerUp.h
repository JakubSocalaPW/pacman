#ifndef POWERUP_H
#define POWERUP_H

#include "../abstract/Pickable.h"

/**
 * @enum PowerUpType
 * @brief Enumerates the different types of power-ups available in the game.
 */
enum class PowerUpType {
    /**
     * @brief Temporarily increases the player's movement speed.
     */
    SpeedBoost,
    /**
     * @brief Temporarily allows the player to defeat ghost enemies.
     */
    GhostKiller,
    /**
     * @brief Temporarily makes the player immune to damage from ghosts.
     */
    Invincibility,
    /**
     * @brief Awards the player with extra points upon collection.
     */
    ExtraPoints
};

/**
 * @class PowerUp
 * @brief Represents a power-up item in the game that grants special abilities or bonuses to the player.
 *
 * This class inherits from Pickable and defines different types of temporary enhancements
 * that a player can acquire during gameplay.
 */
class PowerUp : public Pickable {
private:
    PowerUpType _type;

public:
    /**
     * @brief Constructor for the PowerUp class.
     * @param x The initial x-coordinate of the power-up.
     * @param y The initial y-coordinate of the power-up.
     * @param type The type of power-up this item provides.
     */
    PowerUp(int x, int y, PowerUpType type);

    /**
     * @brief Gets the type of this power-up.
     * @return The PowerUpType enum value representing the power-up's effect.
     */
    PowerUpType getType() const;

    /**
     * @brief Defines the effect that occurs when a player collides with and collects this power-up.
     * @param playerCharacter A reference to the PlayerCharacter that collected the power-up.
     * @override
     */
    void getCollisionEffect(PlayerCharacter& playerCharacter) override;

    /**
     * @brief Generates a random PowerUpType.
     * @return A randomly selected PowerUpType enum value.
     */
    static PowerUpType getRandomPowerUp();
};

#endif //POWERUP_H