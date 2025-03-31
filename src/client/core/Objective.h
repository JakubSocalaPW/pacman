
#ifndef OBJECTIVE_H
#define OBJECTIVE_H


#include "abstract/Pickable.h"


class Objective: public Pickable {
    int m_value;

public:
    Objective(int x, int y);
    void getCollisionEffect() override;
    ~Objective();
    int getValue() const;
};

#endif //OBJECTIVE_H
