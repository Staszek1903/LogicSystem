#ifndef CONFIGWINDOWB_H
#define CONFIGWINDOWB_H

#include <SFML/Graphics.hpp>

struct Configs
{
    sf::Keyboard::Key key;
    int universal;
    std::string text;
    bool result;
    std::vector <uint8_t> * memory;
};

class ConfigWindowBase
{
protected:
    sf::RenderWindow win;
public:
    ConfigWindowBase(sf::VideoMode vm, std::string title);
    virtual ~ConfigWindowBase(){}
    virtual bool update();
    virtual Configs get_configs();
    virtual void load_config(Configs &conf);
};


ConfigWindowBase* createNoneWindow();
#endif // CONFIGWINDOWB_H
