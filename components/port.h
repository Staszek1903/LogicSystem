#ifndef PORT_H
#define PORT_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

struct Ports : public entityx::Component<Ports>
{
    Ports(int index, sf::VertexArray & vertex, int ports_in_count)
        :index(index), ref(vertex), ports_in_count(ports_in_count), joined_in_count(0) {}

    int index;
    sf::VertexArray & ref;
    const int ports_in_count;
    int joined_in_count;
};

#endif // PORT_H
