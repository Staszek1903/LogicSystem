#ifndef WIRECREATOR_H
#define WIRECREATOR_H

#include <entityx/entityx.h>

#include <containers/containerscontainer.h>

#include <components/port.h>
#include <components/wire.h>
#include <components/line.h>
#include <components/position.h>

#include <events/resetsequence.h>

#include <iostream>

class WireCreator
{
    entityx::EntityX & enX;
    ContainersContainer & container;

    bool started;
    entityx::Entity wire;
    PortOUT * port_origin;

public:
    WireCreator(entityx::EntityX & manager, ContainersContainer & container);
    bool isStarted();
    void start(entityx::Entity en, int ports_index, int port_index, sf::Vector2f en_pos);
    void abort();
    void setType(int type, float break_point);
    void moveBreakPoint(bool add);
    void end(entityx::Entity en, Ports::Handle ports, int port_index);
    entityx::Entity detach(PortIN & port, Ports::Handle ports);
    entityx::Entity get_wire();
};

#endif // WIRECREATOR_H
