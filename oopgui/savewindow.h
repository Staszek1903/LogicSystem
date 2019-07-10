#ifndef SAVEWINDOW_H
#define SAVEWINDOW_H

#include <oopgui/configwindow.h>
#include <oopgui/textinput.h>
#include <oopgui/button.h>

class SaveWindow : public ConfigWindowBase
{
    sf::Font font;
    sf::Text label;
    sf::Text error;
    TextInput filename;
    Button save,  cancel;
    Configs conf;

    bool check_save();

public:
    SaveWindow();

    bool update();
    Configs get_configs();
    void load_config(Configs &conf);
};

ConfigWindowBase * saveWindowCreate();

#endif // SAVEWINDOW_H
