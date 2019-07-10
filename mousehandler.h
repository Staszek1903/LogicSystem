#ifndef MOUSEHANDLER_H
#define MOUSEHANDLER_H

#include <SFML/Graphics.hpp>

class MouseHandler
{
    sf::RenderWindow & window;
    sf::View &view;
public:
    MouseHandler(sf::RenderWindow & window, sf::View &view);

    sf::Vector2f pos;
    bool Lbutton,Rbutton;
    sf::Vector2f viewPos();
};

#endif // MOUSEHANDLER_H
