#ifndef DRAWCONTAINER_H
#define DRAWCONTAINER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class DrawContainer
{
    std::vector<sf::VertexArray> gates;
    std::vector<sf::VertexArray> ports;

public:
    DrawContainer();
    sf::VertexArray & get_gate(int index);
    sf::VertexArray & get_port(int index);
    int add_gate(sf::VertexArray & array);
    int add_port(sf::VertexArray & array);
};

#endif // DRAWCONTAINER_H
