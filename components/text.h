#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <entityx/entityx.h>
#include <SFML/Graphics.hpp>

struct Text: public entityx::Component<Text>
{
    Text(std::string s, int size = 16, sf::Vector2f offset = sf::Vector2f(0,0))
        :text(s), CharSize(size), offset(offset){}
    std::string text;
    int CharSize;
    sf::Vector2f offset;

};
#endif // TEXT_H
