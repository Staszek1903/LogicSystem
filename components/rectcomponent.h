#ifndef RECTCOMPONENT_H
#define RECTCOMPONENT_H

#include <entityx/entityx.h>
#include <SFML/Graphics.hpp>

struct Rect: public entityx::Component<Rect>
{
    Rect(sf::Vector2f dim, sf::Color col)
        :dim(dim),color(col){}
    sf::Vector2f dim;
    sf::Color color;

};
#endif // RECTCOMPONENT_H
