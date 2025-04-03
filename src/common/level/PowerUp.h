#ifndef POWERUP_H
#define POWERUP_H


#include <cstdint>
#include <random>
#include <ctime>


#include "../player/Player.h"
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
    void getCollisionEffect(Player& player) override;

    static PowerUpType getRandomPowerUp() {
        // Create a random number generator
        static std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));

        // Define the range (0 to 3 for your enum with 4 values)
        std::uniform_int_distribution<int> distribution(0, 3);

        // Generate random value and cast to enum
        int randomValue = distribution(rng);
        return static_cast<PowerUpType>(randomValue);
    }
};

#endif //POWERUP_H
