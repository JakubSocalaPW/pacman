
#ifndef PICKABLE_H
#define PICKABLE_H
#include "Drawable.h"
#include "../../common/player//Player.h"

class Pickable: public Drawable {
public:
    virtual void getCollisionEffect(Player& player) = 0;
};


#endif //PICKABLE_H
