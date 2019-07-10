#include "loadwindow.h"

LoadWindow::LoadWindow()
    :ConfigWindowBase(sf::VideoMode(300,100), "LOAD")
{
    win.setPosition(sf::Vector2i(400,400));
    font.loadFromFile(std::string("LS-resources/system.ttf"));
    text.setFont(font);
    text.setCharacterSize(18);
    text.setPosition(sf::Vector2f(20,20));
    text.setString("Load? Unsaved data will be lost");

    button_ok.init(sf::Vector2f(120,70), sf::Vector2f(50,20), "OK", font);
    button_cancel.init(sf::Vector2f(220,70), sf::Vector2f(50,20), "CANCEl", font);

    conf.result = false;
}

bool LoadWindow::update()
{
    sf::Event ev;
    while(win.pollEvent(ev))
    {
        if( ev.type == sf::Event::Closed)
        {
            win.close();
            return false;
        }
        if(button_ok.update(ev))
        {
            conf.result = true;
            win.close();
            return false;
        }
        if(button_cancel.update(ev))
        {
            conf.result = false;
            win.close();
            return false;
        }
    }

    win.clear(sf::Color(5,5,5));

    win.draw(text);
    win.draw(button_ok);
    win.draw(button_cancel);

    win.display();
    return true;
}

Configs LoadWindow::get_configs()
{
    return conf;
}

void LoadWindow::load_config(Configs &conf)
{

}

ConfigWindowBase *loadWindowCreate()
{
    return new LoadWindow;
}
