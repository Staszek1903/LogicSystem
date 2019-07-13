#ifndef TEXTWINDOW_H
#define TEXTWINDOW_H

#include "configwindow.h"
#include "textinput.h"
#include "button.h"

class TextWindow : public ConfigWindowBase
{
    sf::Font font;
    TextInput input;
    Button ok_button;


public:
    TextWindow();

    virtual bool update() override;
    virtual Configs get_configs() override;
    virtual void load_config(Configs &conf) override;

private:
    void render();
};

ConfigWindowBase * createTextWindow();

#endif // TEXTWINDOW_H
