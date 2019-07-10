#include "drawcontainer.h"

DrawContainer::DrawContainer()
{
}

sf::VertexArray &DrawContainer::get_gate(int index)
{
    return gates.at(index);
}

sf::VertexArray &DrawContainer::get_port(int index)
{
    return ports.at(index);
}

int DrawContainer::add_gate(sf::VertexArray &array)
{
    gates.push_back(array);
    return (gates.size()-1);
}

int DrawContainer::add_port(sf::VertexArray &array)
{
   // ports.push_back(v);
    //TO_DO
    ports.push_back(array);
    return (ports.size()-1);
}
