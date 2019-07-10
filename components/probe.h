#ifndef PROBE_H
#define PROBE_H

#include <entityx/entityx.h>

struct Probe : public entityx::Component<Probe>
{
    Probe(std::string text, sf::Vector2f offset)
        :text(text), offset(offset), last(0){}

    std::string text;
    int char_size= 18;
    sf::Vector2f offset;
    uint8_t last;
};

#endif // PROBE_H
