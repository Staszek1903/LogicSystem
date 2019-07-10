#ifndef LINE_H
#define LINE_H

#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

#include "../../LogicSystem/wireline.h"

struct Line : public entityx::Component<Line>
{
    Line(sf::Vector2f begin, sf::Vector2f end, sf::Color color)
        :line(begin, end)
    {
        //line[0].position = begin;
        //line[1].position = end;
        //line[0].color = color;
        //line[1].color = color;
        line.setThickness(3.0f);
        line.setColor(color);
    }

    //sf::VertexArray line;
    stuff::WireLine line;

};

#endif // LINE_H
