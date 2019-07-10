#ifndef MEMORYCONTENTGUI_H
#define MEMORYCONTENTGUI_H

#include <oopgui/scrollarea.h>
#include <oopgui/button.h>
#include <sstream>

class MemoryContentGUI : public ScrollArea, public sf::Drawable
{
    std::vector <uint8_t> * memory;
    int memory_size;
    std::vector <Button> cells;
    std::vector <sf::Text> lines;
    sf::Font & font;
    sf::RenderWindow & win;
    sf::RectangleShape active_rect;
    int in_row;
    int active;


public:
    MemoryContentGUI(sf::Font &font, sf::RenderWindow & win);

    //int  selected_cell();

    void init(std::vector <uint8_t> *memory, sf::Vector2f pos, sf::Vector2f dim, sf::FloatRect ratio);
    void update(sf::Event ev);
    void update_mem();
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    uint8_t * get_source();

private:
    void update_active();

};

#endif // MEMORYCONTENTGUI_H
