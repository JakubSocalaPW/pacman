
#ifndef PICKABLE_H
#define PICKABLE_H
#include "Drawable.h"
#include "PlayerCharacter.h"

class Pickable: public Drawable {
public:
    virtual void getCollisionEffect(PlayerCharacter& player) = 0;
};


#endif //PICKABLE_H
