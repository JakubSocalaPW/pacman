#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include <vector>
#include <SFML/Network.hpp>
#include "../player/Player.h"

/**
 * @brief An abstract base class representing a player-controlled character in the game.
 *
 * This class provides the fundamental properties and behaviors of a player character,
 * such as movement, direction and interaction with power-ups. It is
 * designed to be inherited by concrete player character types (Pac-Man, Ghosts).
 */
class PlayerCharacter {
protected:
    /**
     * @brief The current movement speed of the character.
     *
     * Unit is index per game tick.
     * Normal speed is 0.05f, but can be boosted by power-ups.
     */
    float _speed = 0.05f;

    /**
     * @brief The current facing direction of the character.
     */
    int _direction = -1; // -1 indicates no direction

    /**
     * @brief Flag indicating whether the character is currently alive.
     */
    bool _isAlive = true;

    /**
     * @brief Flag indicating whether the character is currently invincible.
     */
    bool _isInvincible = false;

    /**
     * @brief Flag indicating whether the character has the ability to kill ghosts.
     */
    bool _isGhostKiller = false;

    /**
     * @brief The remaining duration (in game ticks) of the current power-up effect.
     */
    int _powerUpDurationLeft = 0;

    /**
     * @brief The direction the player has requested to move in next crossover.
     */
    int _requestedDirection = -1; // -1 indicates no requested direction

    /**
     * @brief Flag indicating whether the character's speed is currently boosted.
     */
    bool _isSpeedBoosted = false;

    /**
     * @brief The current floating-point position of the character in the game world (for sub-tile movement).
     */
    sf::Vector2f _position;

    /**
     * @brief A pointer to the Player object associated with this character (holds player-specific data like score).
     */
    Player* _player = nullptr;

public:
    /**
     * @brief Default constructor for the PlayerCharacter.
     *
     * Initializes the player pointer to nullptr.
     * It is discouraged to use this constructor directly.
     */
    PlayerCharacter();

    /**
     * @brief Constructor for the PlayerCharacter with initial position and associated Player object.
     * @param x The initial x-coordinate of the character.
     * @param y The initial y-coordinate of the character.
     * @param player A pointer to the Player object associated with this character.
     */
    PlayerCharacter(int x, int y, Player* player);

    /**
     * @brief Constructor for the PlayerCharacter with only the associated Player object.
     * @param player A pointer to the Player object associated with this character.
     */
    PlayerCharacter(Player* player);

    /**
     * @brief Virtual destructor to ensure proper cleanup in derived classes.
     */
    virtual ~PlayerCharacter();


    // Prevent copy construction and assignment to avoid potential resource management issues.
    PlayerCharacter(const PlayerCharacter&) = delete;
    PlayerCharacter& operator=(const PlayerCharacter&) = delete;

    /**
     * @brief Move constructor for efficient transfer of object state.
     * @param other The PlayerCharacter object to move from.
     */
    PlayerCharacter(PlayerCharacter&& other) noexcept;


    /**
     * @brief Move assignment operator for efficient transfer of object state.
     * @param other The PlayerCharacter object to move from.
     * @return A reference to the modified PlayerCharacter object.
     */
    PlayerCharacter& operator=(PlayerCharacter&& other) noexcept;

    /**
     * @brief Pure virtual function to identify if this character is the main player (Pac-Man).
     * @return True if the character is Pac-Man, false otherwise.
     */
    virtual bool isPacman() = 0;

    /**
     * @brief Gets the current floating-point position of the character.
     * @return An sf::Vector2<float> representing the character's position.
     */
    sf::Vector2<float> getPosition() const;

    /**
     * @brief Gets the current movement speed of the character.
     * @return The speed of the character.
     */
    float getSpeed() const;

    /**
     * @brief Checks if the character's floating-point position aligns with a grid point (integer coordinates).
     * @return True if the character is at a grid point, false otherwise.
     */
    bool isAtGridPoint();

    /**
     * @brief Moves the character to desired x and y coords.
     * @param x The x coord.
     * @param y The y coord.
     */
    void move(float x, float y);

    /**
     * @brief Retrieves a pointer to the associated Player object.
     * @return A pointer to the Player object, or nullptr if no Player is associated.
     */
    Player* getPlayerPtr();

    /**
     * @brief Retrieves a reference to the associated Player object.
     * @return A reference to the Player object.
     * @throws std::runtime_error if no Player object is associated.
     */
    Player& getPlayer();

    /**
     * @brief Sets the associated Player object for this character.
     * @param newPlayer A pointer to the new Player object.
     */
    void setPlayer(Player* newPlayer);

    /**
     * @brief Checks if the character can move in a given direction based on the game map.
     * @param dir The direction to check (e.g., 0: up, 1: down, 2: left, 3: right).
     * @param gameMap A 2D vector representing the game level layout (0 - empty, 1 - wall).
     * @return True if the character can move in the specified direction, false otherwise (due to a wall).
     */
    bool canMoveInDirection(int dir, const std::vector<std::vector<int>>& gameMap);

    /**
     * @brief Gets the current facing direction of the character.
     * @return The current direction (e.g., 0: up, 1: down, 2: left, 3: right).
     */
    int getDirection() const;

    /**
     * @brief Changes the character's direction of movement, if possible based on the game map.
     *
     * If not at a grid point, the direction will be updated when the character reaches a grid point.
     * @param dir The new direction to move in.
     * @param gameMap A 2D vector representing the game level layout.
     */
    void changeDirection(int dir, const std::vector<std::vector<int>>& gameMap);

    /**
     * @brief Gets the current alive status of the character.
     * @return True if the character is alive, false otherwise.
     */
    bool getIsAlive() const;

    /**
     * @brief Sets the alive status of the character.
     * @param alive The new alive status (true for alive, false for dead).
     */
    void setIsAlive(bool alive);

    /**
     * @brief Updates the character's movement based on its current direction and speed, considering the game map.
     * @param gameMap A 2D vector representing the game level layout.
     */
    virtual void updateMovement(const std::vector<std::vector<int>>& gameMap);

    /**
     * @brief Sets whether the character has the ability to kill ghosts.
     * @param ghostKiller True if the character can kill ghosts, false otherwise.
     */
    void setIsGhostKiller(bool ghostKiller);

    /**
     * @brief Gets whether the character currently has the ability to kill ghosts.
     * @return True if the character can kill ghosts, false otherwise.
     */
    bool getIsGhostKiller() const;

    /**
     * @brief Gets the remaining duration of current power-up.
     * @return The remaining duration in game ticks.
     */
    int getPowerUpDurationLeft() const;

    /**
     * @brief Sets the remaining duration of the current power up.
     * @param duration The new duration in game ticks.
     */
    void setPowerUpDurationLeft(int duration);

    /**
     * @brief Sets whether the character is currently invincible.
     * @param invincible True if the character is invincible, false otherwise.
     */
    void setInvincible(bool invincible);

    /**
     * @brief Gets whether the character is currently invincible.
     * @return True if the character is invincible, false otherwise.
     */
    bool getIsInvincible() const;

    /**
     * @brief Sets whether the character's speed is currently boosted.
     * @param speedBoosted True if the speed is boosted, false otherwise.
     */
    void setSpeedBoosted(bool speedBoosted);

    /**
     * @brief Gets whether the character's speed is currently boosted.
     * @return True if the speed is boosted, false otherwise.
     */
    bool getIsSpeedBoosted() const;

    /**
     * @brief Overloads the SFML packet insertion operator to serialize PlayerCharacter data.
     * @param packet The SFML packet to insert data into.
     * @param player The PlayerCharacter object to serialize.
     * @return A reference to the modified SFML packet.
     */
    friend sf::Packet& operator<<(sf::Packet& packet, const PlayerCharacter& player);

    /**
     * @brief Overloads the SFML packet extraction operator to deserialize PlayerCharacter data.
     * @param packet The SFML packet to extract data from.
     * @param player The PlayerCharacter object to populate with deserialized data.
     * @return A reference to the modified SFML packet.
     */
    friend sf::Packet& operator>>(sf::Packet& packet, PlayerCharacter& player);
};
#endif //PLAYERCHARACTER_H