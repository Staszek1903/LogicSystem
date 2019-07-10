#ifndef MOUSEBOX_H
#define MOUSEBOX_H

#include <entityx/entityx.h>
#include <SFML/Graphics.hpp>

struct MouseBox:public entityx::Component<MouseBox>
{
    MouseBox(sf::Vector2f dim)
        :dim(dim){}
    sf::Vector2f dim;
};
#endif // MOUSEBOX_H
