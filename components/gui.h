#ifndef GUI_H
#define GUI_H

#include <entityx/entityx.h>

struct Gui: public entityx::Component<Gui>
{
    bool a;
};
#endif // GUI_H
