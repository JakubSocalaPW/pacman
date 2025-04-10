#include "Objective.h"
#include "../../common/player/Player.h"

Objective::Objective(int x, int y) {
    _position = {x, y};
    m_value = 1;
}

Objective::~Objective() {

}

int Objective::getValue() const {
    return m_value;
}

void Objective::getCollisionEffect(PlayerCharacter& pc) {
    if (pc.isPacman()) {
        pc.getPlayer().addScore(m_value);
    }
}