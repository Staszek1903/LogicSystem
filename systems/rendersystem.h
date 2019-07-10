#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>
#include <components/circcomponent.h>
#include <components/position.h>
#include <components/rectcomponent.h>
#include <components/text.h>
#include <components/active.h>
#include <components/gui.h>
#include <components/vertexarray.h>
#include <components/port.h>
#include <components/circuitbutton.h>
#include <components/line.h>
#include <components/led.h>
#include <components/latch.h>
#include <components/probe.h>
#include <components/label.h>
#include <components/selectarea.h>
#include <components/disp7seg.h>

#include <events/resizeevent.h>
#include <events/scrollevent.h>
#include <events/namechangeevent.h>

#include <containers/containerscontainer.h>

#include <iostream>
#include <fstream>
#include <sstream>

class RenderSystem: public entityx::System<RenderSystem> , public entityx::Receiver<RenderSystem>
{
    sf::RenderWindow &win;
    sf::Font font;
    sf::Font fontLCD;
    sf::View &view;
    sf::Vector2f &view_range, view_origin;
    ContainersContainer &container;


public:
    RenderSystem(sf::RenderWindow & win, entityx::EventManager &ev, sf::View &view, sf::Vector2f &view_range,
                 sf::Vector2f &origin, ContainersContainer &container);
    void update(entityx::EntityManager &es, entityx::EventManager &events, double dt);
    void receive(const ResizeEvent &ev);
    void receive(const ScrollEvent &ev);
    void receive(const NameChangeEvent & ev);

};

#endif // RENDERSYSTEM_H
