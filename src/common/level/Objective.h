#ifndef OBJECTIVE_H
#define OBJECTIVE_H

#include "../abstract/Pickable.h"
#include "../abstract/PlayerCharacter.h"

/**
 * @class Objective
 * @brief Represents an objective item in the game that players can collect.
 *
 * This class inherits from Pickable and defines a specific type of collectible
 * item that increases the player's score when collected.
 */
class Objective : public Pickable {
private:
    int _value;

public:
    /**
     * @brief Constructor for the Objective class.
     * @param x The initial x-coordinate of the objective.
     * @param y The initial y-coordinate of the objective.
     */
    Objective(int x, int y);

    /**
     * @brief Defines the effect that occurs when a player collides with and collects this objective.
     * @param player A reference to the PlayerCharacter that collected the objective.
     * @override
     */
    void getCollisionEffect(PlayerCharacter& player) override;

    /**
     * @brief Virtual destructor for the Objective class.
     */
    virtual ~Objective();

    /**
     * @brief Gets the point value of this objective.
     * @return The integer value awarded upon collection.
     */
    int getValue() const;
};

#endif //OBJECTIVE_H