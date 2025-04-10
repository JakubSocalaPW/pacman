#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <list>

#include "Objective.h"
#include "PowerUp.h"
#include "Wall.h"
#include "../abstract/PlayerCharacter.h"
#include "../player/Ghost.h"

/**
 * @class Level
 * @brief Represents a level in the game, containing the game map, players, objectives, and power-ups.
 *
 * This class manages the static elements of the level (walls, objectives, power-ups)
 * and the dynamic elements (players). It provides methods to access and modify
 * these elements, as well as to serialize and deserialize the level state for
 * network communication.
 */
class Level {
private:
    std::list<Wall> _gameMap;
    std::vector<PlayerCharacter*> _playersCharacters;
    std::list<PowerUp> _powerups;
    std::list<Objective> _objectives;

public:
    /**
     * @brief Default constructor for the Level class.
     *
     * Initializes an empty level.
     */
    Level();

    /**
     * @brief Constructor for the Level class that initializes the level based on a 2D integer map.
     * @param map A 2D vector of integers representing the level layout, where different integers
     * represent different types of tiles (0 - empty, 1 - wall, 2- objective, 3 - powerup).
     */
    Level(std::vector<std::vector<int>> map);

    /**
     * @brief Virtual destructor for the Level class to ensure proper cleanup of dynamically allocated memory,
     * especially for the player characters.
     */
    ~Level();

    // Prevent copy construction and assignment to avoid issues with pointer ownership.
    Level(const Level&) = delete;
    Level& operator=(const Level&) = delete;

    /**
     * @brief Move constructor for efficient transfer of Level object state.
     * @param other The Level object to move from.
     */
    Level(Level&& other) noexcept;

    /**
     * @brief Move assignment operator for efficient transfer of Level object state.
     * @param other The Level object to move from.
     * @return A reference to the modified Level object.
     */
    Level& operator=(Level&& other) noexcept;

    /**
     * @brief Gets the list of wall positions in the level.
     * @return A list of sf::Vector2<int> representing the positions of the walls.
     */
    std::list<sf::Vector2<int>> getWallPositions() const;


    /**
     * @brief Gets the total number of wall tiles in the level row.
     * @return The size of the wall positions list.
     */
    int getSize() const;

    /**
     * @brief Serializes the current state of the level into an SFML packet.
     * @return An sf::Packet containing the serialized level data.
     */
    sf::Packet serialize() const;

    /**
     * @brief Deserializes a Level object from an SFML packet.
     * @param packet The SFML packet containing the level data.
     * @return A new Level object deserialized from the packet.
     */
    static Level deserialize(sf::Packet& packet);

    /**
     * @brief Overloads the SFML packet insertion operator to serialize a Level object.
     * @param packet The SFML packet to insert the Level data into.
     * @param level The Level object to serialize.
     * @return A reference to the modified SFML packet.
     */
    friend sf::Packet& operator<<(sf::Packet& packet, const Level& level);

    /**
     * @brief Overloads the SFML packet extraction operator to deserialize a Level object.
     * @param packet The SFML packet to extract the Level data from.
     * @param level The Level object to populate with the deserialized data.
     * @return A reference to the modified SFML packet.
     */
    friend sf::Packet& operator>>(sf::Packet& packet, Level& level);

    /**
     * @brief Gets a constant reference to the list of Wall objects.
     * @return A constant reference to the gameMap list.
     */
    const std::list<Wall>& getWalls() const;

    /**
     * @brief Gets a reference to the vector of PlayerCharacter pointers.
     * @return A reference to the players vector.
     */
    std::vector<PlayerCharacter*>& getPlayerCharacters();

    /**
     * @brief Sets the vector of PlayerCharacter pointers. This function is responsible for
     * managing the memory of the old players.
     * @param players The new vector of PlayerCharacter pointers.
     */
    void setPlayerCharacters(std::vector<PlayerCharacter*> players);

    /**
     * @brief Gets a reference to the list of PowerUp objects.
     * @return A reference to the powerups list.
     */
    std::list<PowerUp>& getPowerUps();

    /**
     * @brief Gets a reference to the list of Objective objects.
     * @return A reference to the objectives list.
     */
    std::list<Objective>& getObjectives();

    /**
     * @brief Removes a specific PowerUp object from the level.
     * @param powerUp A reference to the PowerUp object to remove.
     */
    void removePowerUp(PowerUp& powerUp);

    /**
     * @brief Removes a specific Objective object from the level.
     * @param objective A reference to the Objective object to remove.
     */
    void removeObjective(Objective& objective);

    /**
     * @brief Gets a vector of pointers to all Ghost characters currently in the level.
     * @return A vector of Ghost pointers.
     */
    std::vector<Ghost*> getGhosts();

    /**
     * @brief Gets the positions of all wall tiles as a vector of integer vectors.
     * @return A vector of sf::Vector2<int> representing the positions of the walls.
     */
    std::vector<std::vector<int>> getWallPositionsAsVector() const;

    /**
     * @brief Adds a player character to the level.
     * @param player A pointer to the PlayerCharacter object to add.
     */
    void addPlayer(PlayerCharacter* player);
};


#endif // LEVEL_H