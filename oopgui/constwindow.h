#ifndef CONSTWINDOW_H
#define CONSTWINDOW_H

#include <oopgui/configwindow.h>
#include <oopgui/button.h>

class ConstWindow : public ConfigWindowBase
{
    Button ok_button, bits_button[8];
    sf::Font font;
    Configs configs;
public:
    ConstWindow();
    bool update();
    Configs get_configs();
    void load_config(Configs &conf);
};

ConfigWindowBase * createConstWindow();

#endif // CONSTWINDOW_H
