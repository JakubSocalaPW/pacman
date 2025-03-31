#ifndef POWERUP_H
#define POWERUP_H


#include <cstdint>

#include "Player.h"
#include "abstract/Pickable.h"

enum class PowerUpType {
    SpeedBoost,
    GhostKiller,
    Invincibility,
    ExtraPoints
};

class PowerUp: public Pickable {
    PowerUpType m_type;

public:
    PowerUp(int x, int y, PowerUpType type);
    void activate();
    PowerUpType getType() const;
    void getCollisionEffect(Player& player) override;
};

#endif //POWERUP_H
