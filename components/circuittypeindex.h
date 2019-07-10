#ifndef CIRCUITTYPEINDEX_H
#define CIRCUITTYPEINDEX_H

#include <entityx/entityx.h>

struct CircuitTypeIndex: public entityx::Component<CircuitTypeIndex>
{
    CircuitTypeIndex(int index)
        :index(index){}
    int index;
};
#endif // CIRCUITTYPEINDEX_H
