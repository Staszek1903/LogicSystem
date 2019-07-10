#ifndef SELECTAREA_H
#define SELECTAREA_H

#include <entityx/entityx.h>
#include <SFML/Graphics.hpp>

struct SelectArea: public entityx::Component<SelectArea>
{
    SelectArea(sf::FloatRect info)
        :rect(sf::Vector2f(info.width, info.height))
    {
        rect.setPosition(sf::Vector2f(info.left, info.top));
        rect.setFillColor(sf::Color(200,200,200,100));
        rect.setOutlineColor(sf::Color(200,200,200));
        rect.setOutlineThickness(2);
    }
    sf::RectangleShape rect;
};
#endif // SELECTAREA_H
