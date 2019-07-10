#include "constwindow.h"

ConstWindow::ConstWindow()
    :ConfigWindowBase(sf::VideoMode(200,100),std::string("costant"))
{
    font.loadFromFile(std::string("LS-resources/system.ttf"));
    ok_button.init(sf::Vector2f(140,70),sf::Vector2f(50,20),std::string("OK"),font);
    configs.universal = 0;

    for(int i=0; i<8; ++i)
        bits_button[i].init(sf::Vector2f(160-(i*20),40),sf::Vector2f(20,20),"0",font);
}

bool ConstWindow::update()
{
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
        default:
            if(ok_button.update(ev))
                win.close();
            for(int i=0; i<8; ++i)
            {
                bool a = bits_button[i].update(ev);
                bool b = (bits_button[i].get_text() == "1");
                bits_button[i].set_text((a ^ b)? "1" : "0");
                configs.universal &= ~(1<<i);
                configs.universal |= (a^b)<<i;
            }
            break;
        }
    }

    win.clear(sf::Color(5,5,5));
    win.draw(ok_button);
    for(auto &b : bits_button)
        win.draw(b);
    win.display();

    return true;
}

Configs ConstWindow::get_configs()
{
    return configs;
}

void ConstWindow::load_config(Configs &conf)
{
    //std::cout<<"universal data: "<<conf.universal<<std::endl;
    for(int i=0; i<8; ++i)
    {
        bits_button[i].set_text(((conf.universal>>i)&1)? "1" : "0");
        //std::cout<<((conf.universal>>i)&1);
    }
    //std::cout<<std::endl;
}

ConfigWindowBase *createConstWindow()
{
    return new ConstWindow;
}
