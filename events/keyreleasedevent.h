#ifndef KEYRELEASEDEVENT_H
#define KEYRELEASEDEVENT_H

#include <SFML/Graphics.hpp>

struct KeyReleasedEvent
{
    KeyReleasedEvent(sf::Keyboard::Key key)
        :key(key){}
    sf::Keyboard::Key key;
};

#endif // KEYRELEASEDEVENT_H
