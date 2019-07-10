#ifndef LABEL_H
#define LABEL_H

#include <entityx/entityx.h>

struct Label: public entityx::Component<Label>
{
    Label(std::string text, sf::Vector2f offset)
        :text(text), offset(offset){}

    std::string text;
    int char_size= 18;
    sf::Vector2f offset;
};


#endif // LABEL_H
