
#include "PowerUp.h"

PowerUp::PowerUp(int x, int y, PowerUpType type) {
    m_position = {x,y};
    m_type = type;
}


PowerUpType PowerUp::getType() const {
    return m_type;
}
