#ifndef KEYPUSHEVENT_H
#define KEYPUSHEVENT_H

#include <SFML/Graphics.hpp>

struct KeyPushEvent
{
    KeyPushEvent(sf::Keyboard::Key key)
        :key(key){}
    sf::Keyboard::Key key;
};

#endif // KEYPUSHEVENT_H
