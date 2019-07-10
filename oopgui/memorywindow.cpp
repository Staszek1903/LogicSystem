#include "memorywindow.h"

MemoryWindow::MemoryWindow()
    :ConfigWindowBase(sf::VideoMode(350,400), "Memory"), scroll_area(font, win),load(false), save(false)
{
    font.loadFromFile(std::string("LS-resources/system.ttf"));
    size_text.setFont(font);
    size_text.setCharacterSize(18);
    size_text.setFillColor(sf::Color::White);
    size_text.setPosition(sf::Vector2f(10,10));
    size_text.setString("Size: ");

    size_num.setFont(font);
    size_num.setCharacterSize(18);
    size_num.setFillColor(sf::Color::White);
    size_num.setPosition(sf::Vector2f(50,10));
    size_num.setString("0");

    current_cell.init(sf::Vector2f(100, 370), font);

    load_button.init(sf::Vector2f(280,50),sf::Vector2f(60,20),"Load",font);
    save_button.init(sf::Vector2f(280,80), sf::Vector2f(60,20),"Save", font);
}

bool MemoryWindow::update()
{
    sf::Event ev;
    while(win.pollEvent(ev))
    {
        if(ev.type == sf::Event::Closed)
        {
            win.close();
            return false;
        }

        scroll_area.update(ev);
        current_cell.update(ev);
        if(load_button.update(ev))
        {
            load = true;
            file_select = std::make_unique<FileSelectWindow>();
        }

        if(save_button.update(ev) )
        {
            save = true;
            file_select = std::make_unique<FileSelectWindow>();
        }


    }

    if(file_select.get())
        if(!file_select->update())
        {
            auto conf = file_select->get_configs();
            if(conf.result)
            {
                if(load) load_content(conf.text);
                if(save) save_content(conf.text);
            }
            load = save = false;
            file_select.reset();
        }

    current_cell.update_source();
    scroll_area.update_mem();

    current_cell.set_source(scroll_area.get_source());
    render();
    return true;
}

Configs MemoryWindow::get_configs()
{
    return Configs();
}

void MemoryWindow::load_config(Configs &conf)
{
    memory = conf.memory;

    std::stringstream ss;
    ss << (memory->size()-4);
    size_num.setString(ss.str());

    scroll_area.init(memory, sf::Vector2f(20,50), sf::Vector2f(250,300),
                     sf::FloatRect(20.f/350.f, 50.0f/400.f, 250.0f/350.0f, 300.0f/400.f));
}

void MemoryWindow::render()
{

    win.clear(sf::Color(5,5,5));

    win.draw(scroll_area);
    win.draw(current_cell);
    win.draw(size_text);
    win.draw(size_num);
    win.draw(load_button);
    win.draw(save_button);

    win.display();
}

void MemoryWindow::save_content(std::string dir)
{
    std::cout<<"save dir: "<<dir<<std::endl;
    std::vector <std::vector <std::string> >section;
    std::vector <std::string> line;

    int i=0;
    int omi = 0;
    for(auto cell : *memory)
    {
        if(omi < 4)
        {
            ++omi;
            continue;
        }
        ++i;
        std::stringstream ss;
        ss<<static_cast<int>(cell);
        line.push_back(ss.str());
        if(i==8)
        { i=0; section.push_back(line);  line.clear();}
    }

    ConfigCreator creator;
    creator.setDir("./LS-resources/memory_saves/" + dir);
    creator.addSection("memory", section);
    creator.create();

    std::cout<<"save done"<<std::endl;
}

void MemoryWindow::load_content(std::string dir)
{
    std::cout<<"load dir: "<<dir<<std::endl;

    ConfigParser parser;
    parser.load("./LS-resources/memory_saves/" + dir);
    parser.setSection("memory");
    for(unsigned int i = 4; i < memory->size(); ++i)
    {
        if(parser.EndOfSection())
            break;

        memory->at(i) = parser.getFloat();
    }
    std::cout<<"load done"<<std::endl;
}

ConfigWindowBase *create_memory_window()
{
    return new MemoryWindow;
}
