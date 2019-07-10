#ifndef SCROLLAREA_H
#define SCROLLAREA_H

#include <SFML/Graphics.hpp>
#include <iostream>

class ScrollArea
{
    sf::Vector2f pos, dim;
    sf::RectangleShape rect;
    float scroll_span, current_pos;
    bool has_mouse;

public:
    ScrollArea();

protected:
    sf::View camera;

    void init(sf::Vector2f pos, sf::Vector2f dim, sf::FloatRect ratio, float span);
    void update(sf::Event ev);
    void draw(sf::RenderTarget &win) const;

    void setCamera(sf::RenderTarget & target) const;
    void unsetCamera(sf::RenderTarget & target) const;

};

#endif // SCROLLAREA_H
