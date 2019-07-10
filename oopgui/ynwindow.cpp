#include "ynwindow.h"

YNWindow::YNWindow()
    :ConfigWindowBase(sf::VideoMode(400,100), "Alert")
{
    win.setPosition(sf::Vector2i(300,300));

    font.loadFromFile("LS-resources/system.ttf");
    text.setCharacterSize(18);
    text.setFont(font);
    text.setPosition(sf::Vector2f(20,20));
    text.setString(" ");

    yes_button.init(sf::Vector2f(200,70), sf::Vector2f(50,20), "YES", font);
    no_button.init(sf::Vector2f(300,70), sf::Vector2f(50,20), "NO", font);
}

bool YNWindow::update()
{
    sf::Event ev;
    while(win.pollEvent(ev))
    {
        if(yes_button.update(ev))
        {
            conf.result = true;
            win.close();
            return false;
        }

        if(no_button.update(ev))
        {
            conf.result = false;
            win.close();
            return false;
        }
    }

    win.clear(sf::Color(5,5,5));
    win.draw(text);
    win.draw(yes_button);
    win.draw(no_button);
    win.display();
    return true;
}

Configs YNWindow::get_configs()
{
    return conf;
}

void YNWindow::load_config(Configs &conf)
{
    text.setString(conf.text);
}

ConfigWindowBase *YNWindowCreate()
{
    return new YNWindow;
}
