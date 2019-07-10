#ifndef PARTID_H
#define PARTID_H

#include <entityx/entityx.h>

struct PartID: public entityx::Component<PartID>
{
    PartID(int id) : id(id) {}
    int id;
};

#endif // PARTID_H
