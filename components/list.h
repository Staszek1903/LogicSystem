#ifndef LIST_H
#define LIST_H

#include <entityx/entityx.h>

struct List :public entityx::Component<List>
{
    List(bool open, entityx::Entity myself)
        :open(open), size(0), last(myself){}
    bool open;
    int size;
    entityx::Entity last;
};

#endif // LIST_H
