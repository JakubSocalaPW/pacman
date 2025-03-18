//
// Created by jakub on 18.03.2025.
//

#ifndef PICKABLE_H
#define PICKABLE_H



class Pickable {

public:
    virtual ~Pickable() = default;
    virtual void onPickup();
};



#endif //PICKABLE_H
