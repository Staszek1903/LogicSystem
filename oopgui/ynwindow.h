#ifndef YNWINDOW_H
#define YNWINDOW_H

#include <oopgui/configwindow.h>
#include <oopgui/button.h>

class YNWindow : public ConfigWindowBase
{
    sf::Text text;
    sf::Font font;

    Button yes_button,
    no_button;

    Configs conf;

public:
    YNWindow();
    bool update();
    Configs get_configs();
    void load_config(Configs &conf);
};

ConfigWindowBase * YNWindowCreate();

#endif // YNWINDOW_H
