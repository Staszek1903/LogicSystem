#include "bytegui.h"

ByteGUI::ByteGUI()
    :source(nullptr)
{

}

void ByteGUI::init(sf::Vector2f pos, sf::Font &font)
{
    pos = pos;
    for(int i=0; i<8; ++i)
        bits_button[i].init(sf::Vector2f(pos.x+160-(i*25),pos.y),sf::Vector2f(20,20),"0",font);
}

void ByteGUI::set_source(uint8_t *s)
{
    source = s;
    update_source();
}

void ByteGUI::update(sf::Event &ev)
{
    if(ev.type == sf::Event::KeyPressed && ev.key.code > 26 && ev.key.code < 35)
    {
        int bit_num = ev.key.code - 27;
        std::cout<<bit_num<<std::endl;
        bit_num = -bit_num + 7;
        bool high = (bits_button[bit_num].get_text() == "1");
        bits_button[bit_num].set_text((high)? "0" : "1");
        *source &= ~(1<<bit_num);
        *source |=  high<<bit_num;
    }


    if(!source)
        return;
    for(int i=0; i<8; ++i)
    {
        bool a = bits_button[i].update(ev);
        bool b = (bits_button[i].get_text() == "1");
        bits_button[i].set_text((a ^ b)? "1" : "0");
        *source &= ~(1<<i);
        *source |= (a^b)<<i;
    }
}

void ByteGUI::update_source()
{
    if(!source)
        return;
    for(unsigned int i=0; i<8; ++i)
    {
        uint8_t temp = (*source)&(1<<i);
        bits_button[i].set_text((temp>0)? "1" : "0");
    }
}

void ByteGUI::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if(!source)
        return;

    for(auto &b : bits_button)
        target.draw(b);
}
