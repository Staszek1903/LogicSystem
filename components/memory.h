#ifndef MEMORY_H
#define MEMORY_H

#include <entityx/entityx.h>

struct Memory: public entityx::Component<Memory>
{
    Memory(int index)
        :index(index){}
    int index;
};

#endif // MEMORY_H
