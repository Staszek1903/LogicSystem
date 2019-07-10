#ifndef GATESPROCESSINGSYSTEM_H
#define GATESPROCESSINGSYSTEM_H

#include <entityx/entityx.h>
#include <sstream>
#include <deque>

#include <components/led.h>
#include <components/port.h>
#include <components/algorithm.h>
#include <components/latch.h>
#include <components/probe.h>
#include <components/circuittypeindex.h>
#include <components/startpoint.h>
#include <components/wire.h>

#include <events/resetsequence.h>

#include <containers/containerscontainer.h>

class GatesProcessingSystem : public entityx::System<GatesProcessingSystem> , public entityx::Receiver<GatesProcessingSystem>
{
    entityx::EntityX & enX;
    ContainersContainer & container;
    std::vector <entityx::Entity> sequence;
    int result_size;

public:
    GatesProcessingSystem(entityx::EntityX & enX, ContainersContainer & container);
    void update(entityx::EntityManager &entities, entityx::EventManager &events, double dt);

    static int get_sequence(std::vector<entityx::Entity> &v, entityx::EntityManager &manager, ContainersContainer & cont);

    void receive( const ResetSequence & ev);
};

#endif // GATESPROCESSINGSYSTEM_H
