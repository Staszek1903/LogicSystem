#include "memorycontentgui.h"

MemoryContentGUI::MemoryContentGUI(sf::Font &font, sf::RenderWindow &win)
    :memory(nullptr),memory_size(0), font(font), win(win), in_row(0), active(0)
{

}

void MemoryContentGUI::init(std::vector<uint8_t> *memory, sf::Vector2f pos, sf::Vector2f dim, sf::FloatRect ratio)
{
    this->memory = memory;
    memory_size = memory->size() - 4;
    in_row = dim.x / 25 - 2;
    int span = (memory_size/in_row)*25 + 50;
    ScrollArea::init(pos, dim, ratio, span);

    if(memory_size == 0)
        return;

    cells.resize(memory_size);


    for(unsigned int i=0; i<memory_size; ++i)
    {
        std::stringstream ss;
        ss<<static_cast<int>(this->memory->at(i+4));
        cells[i].init(sf::Vector2f((i%in_row)*25+50, (i/in_row)*25), sf::Vector2f(20,20), ss.str(), font);
        cells[i].setCamera(&camera, &win);
    }

    lines.resize(memory_size/in_row);
    for(unsigned int i=0; i<(memory_size/in_row); ++i)
    {
        std::stringstream ss;
        ss<<std::hex<<(i*in_row);
        lines[i].setFont(font);
        lines[i].setPosition(sf::Vector2f(0, i*25));
        lines[i].setCharacterSize(16);
        lines[i].setString("0x" + ss.str());
    }

    active_rect.setFillColor(sf::Color(255,255,255, 100));
    active_rect.setOutlineColor(sf::Color::White);
    active_rect.setOutlineThickness(2);
    active_rect.setPosition(sf::Vector2f((active%in_row)*25 + 50, (active/in_row)*25));
    active_rect.setSize(sf::Vector2f(20,20));
}

void MemoryContentGUI::update(sf::Event ev)
{
    ScrollArea::update(ev);

    if(ev.type == sf::Event::KeyPressed)
    {
        switch (ev.key.code) {
        case sf::Keyboard::Up:
            active -= in_row;
            break;
        case sf::Keyboard::Down:
            active += in_row;
            break;
        case sf::Keyboard::Left:
            --active;
            break;
        case sf::Keyboard::Right:
            ++active;
            break;
        default:
            break;
        }
        active = (active < 0)? 0 : active;
        active = (active >= memory_size)? memory_size-1 : active;
        update_active();
    }

    sf::Vector2f center = camera.getCenter();
    sf::Vector2f size = camera.getSize();
    float upper = center.y - (size.y/2),
          lower = center.y + (size.y/2);

    int first = (upper*in_row)/25 - in_row;
    first = (first < 0)? 0 :first;
    int last = (lower*in_row)/25 + in_row;
    last = (last >= cells.size())? cells.size()-1 : last;

    for(int i=first; i<last; ++i)
    {
        if(cells[i].update(ev)){
            active = i;
            update_active();
        }
    }
}

void MemoryContentGUI::update_mem()
{
    sf::Vector2f center = camera.getCenter();
    sf::Vector2f size = camera.getSize();
    float upper = center.y - (size.y/2),
          lower = center.y + (size.y/2);

    int first = (upper*in_row)/25 - in_row;
    first = (first < 0)? 0 :first;
    int last = (lower*in_row)/25 + in_row;
    last = (last >= cells.size())? cells.size()-1 : last;

    for(int i=first; i<last; ++i)
    {
        std::stringstream ss;
        ss << static_cast<int>(memory->at(i+4));
        cells[i].set_text(ss.str());
    }
}

void MemoryContentGUI::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    ScrollArea::draw(target);

    sf::Vector2f center = camera.getCenter();
    sf::Vector2f size = camera.getSize();
    float upper = center.y - (size.y/2),
          lower = center.y + (size.y/2);

    int first = (upper*in_row)/25 - in_row;
    first = (first < 0)? 0 :first;
    int last = (lower*in_row)/25 + in_row;
    last = (last >= cells.size())? cells.size()-1 : last;

    setCamera(target);
    for(int i=first; i<last; ++i)
        target.draw(cells[i]);
    for(auto & line: lines)
        target.draw(line);
    win.draw(active_rect);
    unsetCamera(target);
}

uint8_t *MemoryContentGUI::get_source()
{
    return (&(memory->at(active+4)));
}

void MemoryContentGUI::update_active()
{
    active_rect.setPosition(sf::Vector2f((active%in_row)*25 + 50, (active/in_row)*25));
}
