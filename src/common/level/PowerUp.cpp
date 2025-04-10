#include "PowerUp.h"

#include <random>

#include "../../common/player/Player.h"

PowerUp::PowerUp(int x, int y, PowerUpType type) {
    _position = {x,y};
    m_type = type;
}


PowerUpType PowerUp::getType() const {
    return m_type;
}

void PowerUp::getCollisionEffect(PlayerCharacter& playerCharacter) {
    if (!playerCharacter.isPacman()) return;

    switch (m_type) {
        case PowerUpType::SpeedBoost: {
            playerCharacter.setSpeedBoosted(true);
            playerCharacter.setPowerUpDurationLeft(300);
            break;
        }
        case PowerUpType::GhostKiller: {
            playerCharacter.setInvincible(true);
            playerCharacter.setPowerUpDurationLeft(300);
            break;
        }

        case PowerUpType::Invincibility: {
            playerCharacter.setInvincible(true);
            playerCharacter.setPowerUpDurationLeft(300);
            break;
        }

        case PowerUpType::ExtraPoints: {
            const int extraPoints = 10;
            playerCharacter.getPlayer().addScore(extraPoints);
            break;
        }

    }
}


PowerUpType PowerUp::getRandomPowerUp() {
    static std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));

    std::uniform_int_distribution<int> distribution(0, 3);

    int randomValue = distribution(rng);
    return static_cast<PowerUpType>(randomValue);
}