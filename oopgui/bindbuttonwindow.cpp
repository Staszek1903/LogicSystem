#include "bindbuttonwindow.h"

BindButtonWindow::BindButtonWindow()
    :ConfigWindowBase(sf::VideoMode(200,100),std::string("button")) ,key(sf::Keyboard::A), read(false)
{
    font.loadFromFile(std::string("LS-resources/system.ttf"));

    ok_button.init(sf::Vector2f(140,70),sf::Vector2f(50,20),std::string("OK"),font);
    set_button.init(sf::Vector2f(80,70),sf::Vector2f(50,20),std::string("SET"),font);

    key_text.setFont(font);
    key_text.setCharacterSize(18);
    key_text.setPosition(sf::Vector2f(30,30));
    key_text.setString("A");
}

bool BindButtonWindow::update()
{
    char k;
    //std::stringstream ss;
    std::string ks;
    if( !win.isOpen())
        return false;
    sf::Event ev;
    while(win.pollEvent(ev))
    {
        switch(ev.type)
        {
        case sf::Event::Closed:
            win.close();
            break;
        case sf::Event::KeyPressed:
            k = ev.key.code + 65;
            if(read && k > 64 && k < 91)
            {
                key = ev.key.code;
                ks = ks + k;
                key_text.setString(ks);
                read = false;
            }
            else if(ev.key.code == sf::Keyboard::Escape || ev.key.code == sf::Keyboard::Return)
                win.close();
            break;
        default:
            if(ok_button.update(ev)) {win.close();}
            if(set_button.update(ev)) {read = true;}
            break;
        }
    }

    win.clear(sf::Color(5,5,5));
    win.draw(ok_button);
    win.draw(set_button);
    win.draw(key_text);
    win.display();

    return true;
}

Configs BindButtonWindow::get_configs()
{
    Configs conf;
    conf.key = key;
    return conf;
}

void BindButtonWindow::load_config(Configs &conf)
{
    key = conf.key;
    char c[2] = {key+65, '\0'};
    key_text.setString(c);
}

ConfigWindowBase *createBindButtonWindow()
{
    return (new BindButtonWindow);
}
