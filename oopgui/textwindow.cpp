#include "textwindow.h"

TextWindow::TextWindow()
    :ConfigWindowBase(sf::VideoMode(400,100), "text config")
{
    font.loadFromFile("LS-resources/system.ttf");
    input.init(sf::Vector2f(10,10),380,"", font);
    ok_button.init(sf::Vector2f(50,50),sf::Vector2f(50,20),"OK",font);
}

bool TextWindow::update()
{
    sf::Event ev;
    while(win.pollEvent(ev))
    {
        if(ev.type == sf::Event::Closed || ok_button.update(ev))
        {
            win.close();
            return false;
        }

        input.update_ev(ev);
        input.update_time();

    }
    render();
    return true;
}

Configs TextWindow::get_configs()
{
    Configs c;
    c.text = "TEXT:" + input.get_text();
    return c;
}

void TextWindow::load_config(Configs &conf)
{
    input.set_text(conf.text);
}

void TextWindow::render()
{
    win.clear();
    win.draw(input);
    win.draw(ok_button);
    win.display();
}

ConfigWindowBase *createTextWindow()
{
    return new TextWindow;
}
