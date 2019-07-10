#include "line.h"

stuff::Liner::Liner()
    :begining(sf::Vector2f(0,0)), end(sf::Vector2f(0,0)),thickness(1.0f)
{
    setFillColor(sf::Color::White);
    update_shape();
}

stuff::Liner::Liner(const stuff::Liner &other)
    :begining(other.begining), end(other.end), thickness(other.thickness)
{
    setFillColor(other.getFillColor());
    update_shape();
}

stuff::Liner::Liner(const sf::Vector2f &_begining, const sf::Vector2f &_end)
    :begining(_begining), end(_end), thickness(1.0f)
{
    setFillColor(sf::Color::White);
    update_shape();
}

stuff::Liner &stuff::Liner::operator=(const stuff::Liner &other)
{
    this->begining = other.begining;
    this->end = other.end;
    this->thickness = other.thickness;
    setFillColor(other.getFillColor());
    update_shape();
    return * this;
}

stuff::Liner::Liner(stuff::Liner &&other)
    :begining(other.begining), end(other.end), thickness(other.thickness)
{
    setFillColor(other.getFillColor());
    update_shape();
}

stuff::Liner &stuff::Liner::operator=(stuff::Liner &&other)
{
    this->begining = other.begining;
    this->end = other.end;
    this->thickness = other.thickness;
    setFillColor(other.getFillColor());
    update_shape();
    return * this;
}

sf::Vector2f stuff::Liner::getBegining() const
{
    return begining;
}

void stuff::Liner::setBegining(const sf::Vector2f &value)
{
    begining = value;
    update_shape();
}

sf::Vector2f stuff::Liner::getEnd() const
{
    return end;
}

void stuff::Liner::setEnd(const sf::Vector2f &value)
{
    end = value;
    update_shape();
}

void stuff::Liner::setVector(const sf::Vector2f &value)
{
    end = begining + value;
    update_shape();
}

float stuff::Liner::getLenght()
{
    auto vect = begining - end;
    float lenght = Vect::lenght(vect);
    return lenght;
}

float stuff::Liner::getThickness() const
{
    return thickness;
}

void stuff::Liner::setThickness(float value)
{
    thickness = value;
    update_shape();
}

void stuff::Liner::update_shape()
{
    float lenght = getLenght();
    sf::Vector2f size(lenght, thickness);
    auto vect = end - begining;
    auto origin = size/2.0f;
    auto pos = begining + (vect/2.0f);
    double rot = Vect::getRotationDegrees(vect);

    setSize(size);
    setOrigin(origin);
    setPosition(pos);
    setRotation(static_cast<float>(rot));
}
