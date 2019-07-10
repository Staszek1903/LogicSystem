#define BOXCOLOR sf::Color(30,30,50)
#include "textinput.h"

TextInput::TextInput()
    :box(sf::LineStrip, 5), time(sf::Time::Zero),
     size(0), active(true), marker(false),upper_case(false)

{}

void TextInput::init(sf::Vector2f pos, int width, sf::String init_text, sf::Font &font)
{
    string_text = init_text;
    string_text += " ";
    text.setFont(font);
    text.setCharacterSize(18);
    text.setPosition(pos);
    text.setString(string_text);

    size = string_text.getSize()-1;

    this->width = width;

    box_pos.translate(sf::Vector2f(pos.x-2, pos.y+3));

    box[0].color = BOXCOLOR;
    box[1].color = BOXCOLOR;
    box[2].color = BOXCOLOR;
    box[3].color = BOXCOLOR;
    box[4].color = BOXCOLOR;

    box[0].position = sf::Vector2f(0,0);
    box[1].position = sf::Vector2f(width, 0);
    box[2].position = sf::Vector2f(width, 20);
    box[3].position = sf::Vector2f(0,20);
    box[4].position = sf::Vector2f(0,0);

    bounds = box.getBounds();
    bounds.left += pos.x;
    bounds.top += pos.y;
}

void TextInput::update_ev(sf::Event &ev)
{


    switch (ev.type) {
    case sf::Event::MouseButtonPressed:
        if(ev.mouseButton.x > bounds.left && ev.mouseButton.y > bounds.top &&
               ev.mouseButton.x < bounds.left + bounds.width && ev.mouseButton.y < bounds.top + bounds.height)
        {
            //std::cout<<ev.mouseButton.x<<" "<<ev.mouseButton.y<<"    "<<bounds.left<<" "<<bounds.top<<"   true"<<std::endl;
            active = true;
        }
        else
        {
            //std::cout<<"false"<<std::endl;
            active = false;
        }
        break;

    case sf::Event::KeyPressed:

        if(!active)
            break;

        //std::cout<<"keycode: "<<ev.key.code<<std::endl;
        if( ev.key.code == 59 && size != 0 )
        {
            --size;
            string_text = string_text.substring(0, size+1);
        }
        else if(ev.key.code == 38)
        {
            upper_case = true;
        }
        else if(ev.key.code < 26)
        {
            if(text.getLocalBounds().width+10 >= width)
                break;

            string_text[size] = static_cast<char>(ev.key.code)+ 97 - ((upper_case)? 32 : 0);
            string_text += ' ';
            ++size;
        }
        else if(ev.key.code < 36 && size != 0)
        {
            if(text.getLocalBounds().width+10 >= width)
                break;

            string_text[size] = static_cast<char>(ev.key.code) +22;
            string_text += ' ';
            ++size;
        }
        else if( ev.key.code == 56)
        {
            if(text.getLocalBounds().width+10 >= width)
                break;

            string_text[size] = (upper_case)? '_' : '-';
            string_text += ' ';
            ++size;
        }

        break;

    case sf::Event::KeyReleased:
        if(ev.key.code == 38)
            upper_case = false;
        break;

    default:
        break;
    }

    text.setString(string_text);
}

void TextInput::update_time()
{
    //std::cout<<active<<" "<<marker<<std::endl;
    if(active)
    {
        time += clock.restart();
        if(time.asSeconds() > 0.5f)
        {
            marker = !marker;
            string_text[size] = (marker)? '_':' ';
            text.setString(string_text);
            time = sf::Time::Zero;
        }
    }
    else
    {
        string_text[size] = ' ';
        text.setString(string_text);
    }
}

void TextInput::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(text);
    target.draw(box, box_pos);
}

void TextInput::set_text_color(sf::Color color)
{
    text.setFillColor(color);
}

sf::String TextInput::get_text()
{
    sf::String ret = string_text.substring(0,size);
    return ret;
}

void TextInput::set_text(std::string text)
{
    this->text.setString(text+" ");
    this->string_text = text+" ";
    size = text.size();
}
