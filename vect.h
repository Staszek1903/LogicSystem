#ifndef VECT_H
#define VECT_H

#include <SFML/Graphics.hpp>
#include <cmath>

namespace stuff {
class Vect
{
public:
    Vect();

    template<class T>
    static float len_sq(const sf::Vector2<T>& v);

    template<class T>
    static float lenght(const sf::Vector2<T>& v);

    template<class T>
    static void normalize(sf::Vector2<T> & v);

    template<class T>
    static float dot(const sf::Vector2<T> & a, const sf::Vector2<T> &b);

    template<class T>
    static double getRotationRandians(const sf::Vector2<T> &v);

    template<class T>
    static double getRotationDegrees(const sf::Vector2<T> &v);
};


}

template<class T>
double stuff::Vect::getRotationDegrees(const sf::Vector2<T> &v)
{
    double rad = getRotationRandians(v);
    double q = rad/(M_PI*2);
    double deg = q * 360;
    return deg;
}

template<class T>
double stuff::Vect::getRotationRandians(const sf::Vector2<T> &v)
{
    auto temp = v;
    normalize(temp);
    return std::atan2(temp.y,temp.x);
}

template<class T>
float stuff::Vect::dot(const sf::Vector2<T> &a, const sf::Vector2<T> &b)
{
    return (a.x*b.x + a.y*b.y);
}

template<class T>
float stuff::Vect::len_sq(const sf::Vector2<T> &v)
{
    return(v.x*v.x + v.y*v.y);
}

template<class T>
float stuff::Vect::lenght(const sf::Vector2<T> &v)
{
    return(std::sqrt(len_sq(v)));
}

template<class T>
void stuff::Vect::normalize(sf::Vector2<T> &v)
{
    float l = lenght(v);
    v.x /= l;
    v.y /= l;
}


#endif // VECT_H
