#ifndef LATCH_H
#define LATCH_H

#include <components/text.h>

struct Latch: public entityx::Component<Latch>
{
    Latch(std::string text, sf::Vector2f offset)
        :text(text), offset(offset){}

    std::string text;
    int char_size= 18;
    sf::Vector2f offset;
};

#endif // LATCH_H
