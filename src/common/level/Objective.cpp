#include "Objective.h"
#include "../../common/player/Player.h"

Objective::Objective(int x, int y) {
    _position = {x, y};
    _value = 1;
}

Objective::~Objective() {}

int Objective::getValue() const {
    return _value;
}

void Objective::getCollisionEffect(PlayerCharacter& pc) {
    if (pc.isPacman()) {
        pc.getPlayer().addScore(_value);
    }
}