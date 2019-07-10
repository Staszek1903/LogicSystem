#ifndef BYTEGUI_H
#define BYTEGUI_H

#include <oopgui/button.h>

class ByteGUI : public sf::Drawable
{
    Button bits_button[8];
    uint8_t * source;
    sf::Vector2f pos;
public:
    ByteGUI();
    void init(sf::Vector2f pos, sf::Font &font);
    void set_source(uint8_t * s);
    void update(sf::Event & ev);
    void update_source();
    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};

#endif // BYTEGUI_H
