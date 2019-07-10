#ifndef PROGRAM_H
#define PROGRAM_H

#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

#include <systems/rendersystem.h>
#include <systems/guisystem.h>
#include <systems/gatesguisystem.h>
#include <systems/configwindowsystem.h>
#include <systems/gatesprocessingsystem.h>

#include <mousehandler.h>
#include <creators/listcreator.h>
#include <creators/slidercreator.h>

#include <events/resizeevent.h>
#include <events/keypushevent.h>
#include <events/keyreleasedevent.h>
#include <events/mousescrollevent.h>

#include <loaders/configparser.h>
#include <loaders/componentsloader.h>
#include <loaders/savesloader.h>

#include <components/vertexarray.h>

#include <containers/containerscontainer.h>

#include <oopgui/bindbuttonwindow.h>
#include <oopgui/configwindow.h>

#include <frequencycontrol.h>

class Program
{
    entityx::EntityX ex;
    SavesLoader sl;
    ComponentsLoader cl;
    FrequencyControl frequency;
    sf::RenderWindow window_main;
    sf::View v;
    MouseHandler mouse;
    sf::Vector2f view_range, view_origin;
    ContainersContainer container;

public:
    Program();
    void run();

private:
    void input();
    void update();
    void render();
    void setSystems();
};

#endif // PROGRAM_H
