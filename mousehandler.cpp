#include "mousehandler.h"

MouseHandler::MouseHandler(sf::RenderWindow &window, sf::View &view)
    :window(window), view(view), pos(sf::Vector2f(0,0)),Lbutton(false), Rbutton(false)
{

}

sf::Vector2f MouseHandler::viewPos()
{
    sf::Vector2i ipos;
    ipos.x = pos.x;
    ipos.y = pos.y;
    return window.mapPixelToCoords(ipos,view);
}
