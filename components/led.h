#ifndef LED_H
#define LED_H

#include <entityx/entityx.h>
#include <SFML/Graphics.hpp>

struct Led : public entityx::Component<Led>
{
    Led(sf::Color color)
        :color(color), on(false){}
    sf::Color color;
    bool on;
};

#endif // LED_H
