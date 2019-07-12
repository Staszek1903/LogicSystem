#include "configwindow.h"

ConfigWindowBase::ConfigWindowBase(sf::VideoMode vm, std::string title)
{
    win.create(vm,title,sf::Style::Close);
    win.setFramerateLimit(30);
    win.setVerticalSyncEnabled(false);
}

bool ConfigWindowBase::update()
{
    return false;
}

Configs ConfigWindowBase::get_configs()
{
    return Configs();
}

void ConfigWindowBase::load_config(Configs &conf)
{

}

ConfigWindowBase *createNoneWindow()
{
    return nullptr;
}
