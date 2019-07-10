#include "wireline.h"

stuff::WireLine::WireLine(const sf::Vector2f &begining, const sf::Vector2f &end)
    :type(STR_ANG_VER), lines_count(0), begining(begining), end(end),
      break_place(0.5f),  thickness(3.0f), color(sf::Color::Magenta)
{
    update_shape();
}

stuff::WireLine::WireLine(const stuff::WireLine &other)
{
    this->begining = other.begining;
    this->end = other.end;
    this->type = other.type;
    this->lines_count = other.lines_count;
    this->thickness = other.thickness;
    this->color = other.color;

    update_shape();
}

void stuff::WireLine::setBegining(const sf::Vector2f &v)
{
    begining = v;
    update_shape();
}

void stuff::WireLine::setEnd(const sf::Vector2f &v)
{
    end = v;
    update_shape();
}

void stuff::WireLine::setType(int type)
{
    this->type = type;
}

int stuff::WireLine::getType()
{
    return this->type;
}

void stuff::WireLine::nextType()
{
    ++type;
    type %= (DIRECT+1);
}

void stuff::WireLine::setColor(const sf::Color &c)
{
    color = c;
    for(size_t i=0; i<lines_count; ++i){
        lines[i].setFillColor(c);
    }
}

sf::Color stuff::WireLine::getColor()
{
    return color;
}

void stuff::WireLine::setThickness(float t)
{
    thickness = t;
    for(size_t i=0; i<lines_count; ++i){
        lines[i].setThickness(t);
    }
}

float stuff::WireLine::getThickness()
{
    if(lines_count == 0)
        return 0;
    return lines[0].getThickness();
}

void stuff::WireLine::setBreakPoint(float bp)
{
    break_place = bp;
    update_shape();
}

float stuff::WireLine::getBreakPoint()
{
    return break_place;
}

void stuff::WireLine::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for(size_t i=0; i<lines_count; ++i){
        target.draw(lines[i]);
    }
}

void stuff::WireLine::update_shape()
{
    switch (type) {
        case STR_ANG_HOR: gen_angle(false); break;
        case STR_ANG_VER: gen_angle(true); break;
        case DIRECT:
        default: gen_dir(); break;
    }

    for(size_t i=0; i<lines_count; ++i){
        lines[i].setFillColor(color);
    }

    for(size_t i=0; i<lines_count; ++i){
        lines[i].setThickness(thickness);
    }
}

void stuff::WireLine::gen_angle(bool up)
{
    lines.reset();
    lines_count =3;
    lines = std::make_unique<Liner[]> (3);

    float interstage_x = std::min(begining.x, end.x) +
            std::abs(begining.x - end.x) * break_place;


    float interstage_y = std::min(begining.y, end.y) +
            std::abs(begining.y - end.y) * break_place;

    sf::Vector2f p1_x(interstage_x, begining.y),
                p2_x(interstage_x, end.y),
                p1_y(begining.x, interstage_y),
                p2_y(end.x, interstage_y),

            p1 = (up)? p1_y : p1_x,
            p2 = (up)? p2_y : p2_x;

    lines[0].setBegining(begining);
    lines[0].setEnd(p1);

    lines[1].setBegining(p1);
    lines[1].setEnd(p2);

    lines[2].setBegining(p2);
    lines[2].setEnd(end);
}

void stuff::WireLine::gen_dir()
{
    lines.reset();
    lines_count = 1;
    lines = std::make_unique<Liner[]>(1);
    lines[0].setBegining(begining);
    lines[0].setEnd(end);
}

