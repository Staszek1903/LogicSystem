#ifndef FILESELECTWINDOW_H
#define FILESELECTWINDOW_H

#include <oopgui/configwindow.h>
#include <oopgui/textinput.h>
#include <oopgui/button.h>
#include <oopgui/filelist.h>

class FileSelectWindow : public ConfigWindowBase
{
    sf::Font font;
    Configs conf;

    FileList list;
    TextInput input;
    Button ok_button, cancel_button;

public:
    FileSelectWindow();

    bool update();
    Configs get_configs();
    void load_config(Configs &conf);
};

#endif // FILESELECTWINDOW_H
