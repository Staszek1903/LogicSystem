#ifndef ACTIVE_H
#define ACTIVE_H

#include <entityx/entityx.h>

struct Active: public entityx::Component<Active>
{
    Active(bool visible)
        :visible(visible){}
    bool visible;
};
#endif // ACTIVE_H
