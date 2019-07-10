#ifndef BINDBUTTONWINDOW_H
#define BINDBUTTONWINDOW_H

#include "oopgui/configwindow.h"
#include <oopgui/button.h>
#include <sstream>
#include <iostream>

class BindButtonWindow : public ConfigWindowBase
{
    sf::Font font;
    Button ok_button, set_button;
    sf::Keyboard::Key key= sf::Keyboard::A;
    sf::Text key_text;
    bool read;

public:
    BindButtonWindow();
    bool update();
    Configs get_configs();
    void load_config(Configs & conf);
};

ConfigWindowBase * createBindButtonWindow();

#endif // BINDBUTTONWINDOW_H
