#ifndef CONFIGWINDOWCREATEEVENT_H
#define CONFIGWINDOWCREATEEVENT_H

#include <entityx/entityx.h>

#include <oopgui/configwindow.h>

struct ConfigWindowCreateEvent
{
    ConfigWindowCreateEvent(entityx::Entity en, ConfigWindowBase * (*win)())
        :en(en), win(win){}
    entityx::Entity en;
    ConfigWindowBase * (*win)();
};

#endif // CONFIGWINDOWCREATEEVENT_H
