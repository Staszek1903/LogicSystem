#ifndef CIRCCOMPONENT_H
#define CIRCCOMPONENT_H

#include <entityx/entityx.h>

struct Circ: public entityx::Component<Circ>
{
    Circ(int r, int vert)
        :r(r),v(vert){}
    int r, v;
};

#endif // CIRCCOMPONENT_H
