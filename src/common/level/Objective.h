
#ifndef OBJECTIVE_H
#define OBJECTIVE_H


#include "../../common/player/Player.h"
#include "../abstract/Pickable.h"


class Objective: public Pickable {
    int m_value;

public:
    Objective(int x, int y);
    void getCollisionEffect(Player& player) override;
    ~Objective();
    int getValue() const;
};

#endif //OBJECTIVE_H
