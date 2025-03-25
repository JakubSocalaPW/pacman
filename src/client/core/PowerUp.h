#ifndef POWERUP_H
#define POWERUP_H


#include <cstdint>

enum class PowerUpType {
    SpeedBoost,
    GhostKiller,
    Invincibility,
    ExtraPoints
};

class PowerUp {
    PowerUpType m_type;
    int m_powerUpDurationSec;

public:
    PowerUp(PowerUpType type, int32_t duration);
    void activate();
    PowerUpType getType() const;
    int getDuration() const;
};

#endif //POWERUP_H
