
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
        case PowerUpType::SpeedBoost: {
            player.setSpeedBoosted(true);
            player.setPowerUpDurationLeft(300);
            break;
        }
        case PowerUpType::GhostKiller: {
            player.setInvincible(true);
            player.setPowerUpDurationLeft(300);
            break;
        }

        case PowerUpType::Invincibility: {
            player.setInvincible(true);
            player.setPowerUpDurationLeft(300);
            break;
        }

        case PowerUpType::ExtraPoints: {
            const int extraPoints = 10;
            player.addScore(extraPoints);
            break;
        }

    }
}