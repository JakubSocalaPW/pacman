
#include "PowerUp.h"

PowerUp::PowerUp(int x, int y, PowerUpType type) {
    m_position = {x,y};
    m_type = type;
}


PowerUpType PowerUp::getType() const {
    return m_type;
}

void PowerUp::getCollisionEffect(Player& player) {
    if (!player.getIsPacman()) return;

    switch (m_type) {
        case PowerUpType::SpeedBoost:
            // Increase player's speed
            break;
        case PowerUpType::GhostKiller:
            // Make player invincible to ghosts

            break;
        case PowerUpType::Invincibility: {
            const int invincibilityDurationSec = 5;
            break;
        }

        case PowerUpType::ExtraPoints: {
            const int extraPoints = 10;
            player.addScore(extraPoints);
            break;
        }

    }
}