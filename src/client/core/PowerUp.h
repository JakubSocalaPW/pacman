#ifndef POWERUP_H
#define POWERUP_H


#include <cstdint>

#include "abstract/Drawable.h"

enum class PowerUpType {
    SpeedBoost,
    GhostKiller,
    Invincibility,
    ExtraPoints
};

class PowerUp: public Drawable {
    PowerUpType m_type;
    int m_powerUpDurationSec;

public:
    PowerUp(int x, int y, PowerUpType type);
    void activate();
    PowerUpType getType() const;
    int getDuration() const;
};

#endif //POWERUP_H
