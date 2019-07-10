#ifndef CIRCUITBUTTON_H
#define CIRCUITBUTTON_H

#include <entityx/entityx.h>
#include <SFML/Graphics.hpp>

struct CircuitButton: public entityx::Component<CircuitButton>
{
    CircuitButton()
        :key(sf::Keyboard::A), state(false){}
    sf::Keyboard::Key key;
    bool state;
};

#endif // CIRCUITBUTTON_H
