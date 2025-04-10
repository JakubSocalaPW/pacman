#ifndef PICKABLE_H
#define PICKABLE_H

#include "Drawable.h"
#include "PlayerCharacter.h"

/**
 * @brief An abstract base class for objects that can be picked up or interacted with by a player.
 *
 * This class inherits from Drawable and defines the interface for what happens when
 * a Pickable object collides with a PlayerCharacter. Concrete pickable items (like
 * objectives or power-ups) will inherit from this and implement their specific
 * collision effects.
 */
class Pickable : public Drawable {
public:
    /**
     * @brief Pure virtual function defining the effect of collision with a player.
     * @param player A reference to the PlayerCharacter that collided with this object.
     *
     * Subclasses must implement this function to define what happens when a player
     * picks up or interacts with this Pickable object (e.g., increasing score,
     * granting a power-up).
     */
    virtual void getCollisionEffect(PlayerCharacter& player) = 0;
};

#endif //PICKABLE_H