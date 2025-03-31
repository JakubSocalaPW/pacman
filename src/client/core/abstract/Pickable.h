
#ifndef PICKABLE_H
#define PICKABLE_H
#include "Drawable.h"


class Pickable: public Drawable {
public:
    virtual void getCollisionEffect() = 0;
};


#endif //PICKABLE_H
