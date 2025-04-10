#include "PowerUp.h"

#include <random>

#include "../../common/player/Player.h"

PowerUp::PowerUp(int x, int y, PowerUpType type) {
    _position = {x,y};
    _type = type;
}


PowerUpType PowerUp::getType() const {
    return _type;
}

void PowerUp::getCollisionEffect(PlayerCharacter& playerCharacter) {
    if (!playerCharacter.isPacman()) return;

    switch (_type) {
        case PowerUpType::SpeedBoost: {
            playerCharacter.setSpeedBoosted(true);
            playerCharacter.setInvincible(false);
            playerCharacter.setIsGhostKiller(false);
            playerCharacter.setPowerUpDurationLeft(300);
            break;
        }
        case PowerUpType::GhostKiller: {
            playerCharacter.setIsGhostKiller(true);
            playerCharacter.setInvincible(false);
            playerCharacter.setSpeedBoosted(false);
            playerCharacter.setPowerUpDurationLeft(300);
            break;
        }

        case PowerUpType::Invincibility: {
            playerCharacter.setSpeedBoosted(false);
            playerCharacter.setIsGhostKiller(false);
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