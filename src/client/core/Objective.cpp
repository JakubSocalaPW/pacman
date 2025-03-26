
#include "Objective.h"


Objective::Objective(int x, int y) {
    m_position = {x, y};
    m_value = 1;
}

Objective::~Objective() {

}

int Objective::getValue() const {
    return m_value;
}
