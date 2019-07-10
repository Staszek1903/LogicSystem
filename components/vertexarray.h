#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <entityx/entityx.h>
#include <SFML/Graphics.hpp>

struct VertexArray : public entityx::Component<VertexArray>
{
    VertexArray(sf::VertexArray & ref)
        :ref(ref){}
    sf::VertexArray &ref;
};

#endif // VERTEXARRAY_H
