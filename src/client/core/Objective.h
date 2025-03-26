
#ifndef OBJECTIVE_H
#define OBJECTIVE_H

#include <cstdint>
#include <SFML/System.hpp>

#include "abstract/Drawable.h"


class Objective: public Drawable {
    int m_value;

public:
    Objective(int x, int y);
    ~Objective();
    int getValue() const;
};

#endif //OBJECTIVE_H
