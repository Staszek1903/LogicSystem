#ifndef CIRCUTCREATOR_H
#define CIRCUTCREATOR_H

#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

#include <containers/containerscontainer.h>

#include <components/position.h>
#include <components/vertexarray.h>
#include <components/port.h>
#include <components/configwindow.h>
#include <components/circuitbutton.h>
#include <components/led.h>
#include <components/wire.h>
#include <components/algorithm.h>
#include <components/latch.h>
#include <components/probe.h>
#include <components/label.h>
#include <components/constant.h>
#include <components/circuittypeindex.h>
#include <components/disp7seg.h>
#include <components/startpoint.h>
#include <components/partid.h>

#include <events/resetsequence.h>

#include <oopgui/bindbuttonwindow.h>

class CircutCreator
{
    entityx::EntityX & enX;
    ContainersContainer & container;

public:
    CircutCreator(entityx::EntityX & enX, ContainersContainer & container);
    entityx::Entity operator()(entityx::EntityManager & entities,int index, sf::Vector2f pos);
    void destroy(entityx::Entity circuit);
};

#endif // CIRCUTCREATOR_H
