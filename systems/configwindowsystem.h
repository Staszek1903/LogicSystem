#ifndef CONFIGWINDOWSYSTEM_H
#define CONFIGWINDOWSYSTEM_H

#include <entityx/entityx.h>

#include <oopgui/configwindow.h>

#include <events/configwindowcreateevent.h>
#include <events/newdirevent.h>
#include <events/namechangeevent.h>

#include <components/circuitbutton.h>
#include <components/constant.h>
#include <components/port.h>
#include <components/yesnowindow.h>
#include <components/savedata.h>
#include <components/loaddata.h>
#include <components/label.h>

#include <containers/containerscontainer.h>

#include <creators/listcreator.h>

#include <vector>
#include <utility>

class ConfigWindowSystem: public entityx::System<ConfigWindowSystem>, public entityx::Receiver<ConfigWindowSystem>
{
    std::vector<std::pair <entityx::Entity, ConfigWindowBase *> > windows;
    entityx::EntityX & enX;
    ContainersContainer & container;
public:
    ConfigWindowSystem(entityx::EntityX &enX, ContainersContainer & container);
    virtual ~ConfigWindowSystem();
    void update(entityx::EntityManager &entities, entityx::EventManager &events, double dt);
    void receive(const ConfigWindowCreateEvent &event);
};

#endif // CONFIGWINDOWSYSTEM_H
