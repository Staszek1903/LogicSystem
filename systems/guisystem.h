#ifndef GUISYSTEM_H
#define GUISYSTEM_H

#include <entityx/entityx.h>
#include <SFML/Graphics.hpp>
#include <components/mousebox.h>
#include <components/position.h>
#include <components/rectcomponent.h>
#include <components/button.h>
#include <components/list.h>
#include <components/active.h>
#include <components/slider.h>
#include <components/screenresize.h>

#include <events/resizeevent.h>
#include <events/scrollevent.h>
#include <events/buttonpushevent.h>
#include <events/mousescrollevent.h>

#include <mousehandler.h>
#include <iostream>

class GuiSystem: public entityx::System<GuiSystem>, public entityx::Receiver<GuiSystem>
{
    MouseHandler & mouse;
    bool resized;
    ResizeEvent resizescale;
    entityx::EntityX &ex;

public:
    GuiSystem(MouseHandler &m, entityx::EntityX &ex);
    void update(entityx::EntityManager &es, entityx::EventManager &ev, double dt);
    void receive(const ResizeEvent & event);
    void receive(const MouseScrollEvent & event);
};

#endif // GUISYSTEM_H
