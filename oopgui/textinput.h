#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include <SFML/Graphics.hpp>
#include <iostream>

class TextInput : public sf::Drawable
{
    sf::VertexArray box;
    sf::Transform box_pos;
    sf::Clock clock;
    sf::Time time;
    sf::Text text;
    sf::String string_text;
    sf::FloatRect bounds;
    int width;
    int size;
    bool active;
    bool marker;
    bool upper_case;


public:
    TextInput();
    void init(sf::Vector2f pos, int max_size, sf::String init_text, sf::Font & font);
    void update_ev(sf::Event& ev);
    void update_time();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void set_text_color(sf::Color color);
    sf::String get_text();
    void set_text(std::string text);
};

#endif // TEXTINPUT_H
