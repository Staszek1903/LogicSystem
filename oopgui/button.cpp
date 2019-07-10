#include "button.h"

Button::Button()
    :camera(nullptr)
{

}

void Button::init(sf::Vector2f pos, sf::Vector2f dim, std::string t, sf::Font &font)
{
    rect.setPosition(pos);
    rect.setSize(dim);
    rect.setFillColor(sf::Color(30,30,40));

    text.setFont(font);
    text.setString(t);
    text.setCharacterSize(16);
    text.setPosition(pos+(dim/2.0f)- sf::Vector2f(5,0));
    text.setOrigin(sf::Vector2f((text.getString().getSize()*8)/2,8));
}

void Button::setCamera(sf::View *c, sf::RenderWindow *win)
{
    camera = c;
    this->win = win;
}

void Button::set_text(std::string s)
{
    text.setString(s);
}

std::string Button::get_text()
{
    return text.getString();
}

const sf::Vector2f &Button::getPosition()
{
    return rect.getPosition();
}

bool Button::update(sf::Event &ev)
{
    sf::Vector2i mouse_i;
    switch (ev.type) {
    case sf::Event::MouseButtonPressed:
        return (mouse.x > rect.getPosition().x && mouse.x < (rect.getPosition().x+ rect.getSize().x) &&
                mouse.y > rect.getPosition().y && mouse.y < (rect.getPosition().y+ rect.getSize().y));
        break;
    case sf::Event::MouseMoved:
         mouse_i = sf::Vector2i(ev.mouseMove.x,ev.mouseMove.y);
         mouse = (camera)? win->mapPixelToCoords(mouse_i,*camera) : sf::Vector2f(mouse_i.x, mouse_i.y);
         rect.setFillColor((mouse.x > rect.getPosition().x && mouse.x < (rect.getPosition().x+ rect.getSize().x) &&
                            mouse.y > rect.getPosition().y && mouse.y < (rect.getPosition().y+ rect.getSize().y))?
                               sf::Color(10,10,20) : sf::Color(30,30,40));
        break;
    default:
        break;
    }

    return false;
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(rect);
    target.draw(text);
}
