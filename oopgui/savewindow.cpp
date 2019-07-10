#include "savewindow.h"

SaveWindow::SaveWindow()
    :ConfigWindowBase(sf::VideoMode(350,150), "SAVE")
{
    font.loadFromFile(std::string("LS-resources/system.ttf"));
    filename.init(sf::Vector2f(120,50),200,"name",font);

    label.setFont(font);
    label.setCharacterSize(18);
    label.setPosition(sf::Vector2f(10,50));
    label.setString("Project name: ");

    error.setFont(font);
    error.setCharacterSize(18);
    error.setPosition(sf::Vector2f(20,80));
    error.setFillColor(sf::Color::Red);
    error.setString("");

    save.init(sf::Vector2f(170,110), sf::Vector2f(70,20), std::string("SAVE"), font);
    cancel.init(sf::Vector2f(260,110), sf::Vector2f(70,20), std::string("CANCEL"), font);
}

bool SaveWindow::update()
{
    sf::Event ev;
    while(win.pollEvent(ev))
    {
        if(ev.type == sf::Event::Closed)
        {
            win.close();
            return false;
        }

        filename.update_ev(ev);

        if(save.update(ev))
            return check_save();

        if(cancel.update(ev))
        {
            conf.result = false;
            win.close();
            return false;
        }
    }

    //filename.set_text_color((filename.get_text().getSize() > 4) ? sf::Color::Red : sf::Color::White);


    filename.update_time();

    win.clear(sf::Color(5,5,5));
    win.draw(filename);
    win.draw(label);
    win.draw(save);
    win.draw(cancel);
    win.draw(error);
    win.display();
    return true;
}

Configs SaveWindow::get_configs()
{
    return conf;
}

void SaveWindow::load_config(Configs &conf)
{

}

bool SaveWindow::check_save()
{
    sf::String project_name = filename.get_text();

    if(project_name.getSize() == 0)
    {
        error.setString("ERROR: file name box empty");
        return true;
    }

    conf.result = true;
    conf.text = project_name.toAnsiString();
    return false;
}

ConfigWindowBase *saveWindowCreate()
{
    return new SaveWindow();
}
