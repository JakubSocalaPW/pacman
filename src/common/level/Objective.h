#ifndef OBJECTIVE_H
#define OBJECTIVE_H


#include "../abstract/Pickable.h"
#include "../abstract/PlayerCharacter.h"


class Objective: public Pickable {
    int m_value;

public:
    Objective(int x, int y);
    void getCollisionEffect(PlayerCharacter& player) override;
    ~Objective();
    int getValue() const;
};

#endif //OBJECTIVE_H
