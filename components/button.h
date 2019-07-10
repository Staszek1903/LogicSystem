#ifndef BUTTON_H
#define BUTTON_H

#include <entityx/entityx.h>

struct Button :public entityx::Component<Button>
{
    Button(entityx::Entity anc,int id)
        :ancestor(anc), clicked(false), id(id){}

    entityx::Entity ancestor, upper;
    bool clicked;
    int id;
};
#endif // BUTTON_H
