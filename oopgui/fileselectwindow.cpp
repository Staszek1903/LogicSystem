#include "fileselectwindow.h"

FileSelectWindow::FileSelectWindow()
    :ConfigWindowBase(sf::VideoMode(300,250), "File Select"), list(font, win)
{
    font.loadFromFile(std::string("LS-resources/system.ttf"));
    input.init(sf::Vector2f(50,190),200,"file_name", font);
    ok_button.init(sf::Vector2f(100, 220), sf::Vector2f(70,20), "OK", font);
    cancel_button.init(sf::Vector2f(200, 220), sf::Vector2f(70,20), "CANCEL", font);
    list.init(sf::Vector2f(20,20),sf::Vector2f(260,160),
              sf::FloatRect(20.0f/300.0f, 20.0f/250.0f, 260.0f/300.0f, 160.0f/250.0f), "./LS-resources/memory_saves/");
}

bool FileSelectWindow::update()
{
    sf::Event ev;
    while(win.pollEvent(ev))
    {
        if(ev.type == sf::Event::Closed)
        { conf.result = false; win.close(); return false;}

        input.update_ev(ev);

        if(ok_button.update(ev))
        { conf.result = true; win.close(); return false;}
        if(cancel_button.update(ev))
        { conf.result = false; win.close(); return false;}

        int but_num = list.update(ev);
        if(but_num > -1)
            input.set_text(list.get_button_text(but_num));
    }

    input.update_time();


    win.clear(sf::Color::Black);

    win.draw(list);
    win.draw(input);
    win.draw(ok_button);
    win.draw(cancel_button);

    win.display();

    return true;
}

Configs FileSelectWindow::get_configs()
{
    conf.text = input.get_text();
    return conf;
}

void FileSelectWindow::load_config(Configs &conf)
{

}
