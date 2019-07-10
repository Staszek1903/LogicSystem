#ifndef WIRE_H
#define WIRE_H

#include <containers/portscontainer.h>
#include <entityx/entityx.h>

struct Wire: public entityx::Component<Wire>
{
    Wire(PortOUT * port, entityx::Entity entity_out, int index_out)
        :out_index(index_out), port_out(port), entity_out(entity_out){}

    int in_index;
    int out_index;
    PortIN * port_in;
    PortOUT * port_out;
    entityx::Entity entity_in, entity_out;
};

#endif // WIRE_H
