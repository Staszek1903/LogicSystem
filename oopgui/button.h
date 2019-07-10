#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Button : public sf::Drawable
{
    sf::RectangleShape rect;
    sf::Text text;
    sf::Vector2f mouse;
    sf::View * camera;
    sf::RenderWindow * win;
public:
    Button();
    void init(sf::Vector2f pos, sf::Vector2f dim, std::string t, sf::Font &font);
    void setCamera(sf::View * c, sf::RenderWindow * win);
    void set_text(std::string s);
    std::string get_text();
    const sf::Vector2f &getPosition();
    bool update(sf::Event &ev);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // BUTTON_H
