#ifndef POWERUP_H
#define POWERUP_H


#include "../abstract/Pickable.h"

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
    void getCollisionEffect(PlayerCharacter& playerCharacter) override;

    static PowerUpType getRandomPowerUp();
};

#endif //POWERUP_H
