#ifndef LOADWINDOW_H
#define LOADWINDOW_H

#include <oopgui/configwindow.h>
#include <oopgui/button.h>

class LoadWindow : public ConfigWindowBase
{
    sf::Font font;
    sf::Text text;
    Button button_ok, button_cancel;
    Configs conf;
public:
    LoadWindow();

    bool update();
    Configs get_configs();
    void load_config(Configs &conf);
};

ConfigWindowBase * loadWindowCreate();

#endif // LOADWINDOW_H
