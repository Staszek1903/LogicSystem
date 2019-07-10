#ifndef LINER_H
#define LINER_H

#include <SFML/Graphics.hpp>
#include "vect.h"

namespace stuff
{
    class Liner : public sf::RectangleShape
    {
        sf::Vector2f begining, end; // global points of line;
        float thickness;

    public:
        Liner();
        Liner(const Liner & other);
        Liner(const sf::Vector2f & _beggining, const sf::Vector2f & _end);

        Liner & operator= (const Liner & other);

        Liner( Liner && other);
        Liner & operator= (Liner && other);


        sf::Vector2f getBegining() const;
        void setBegining(const sf::Vector2f &value);

        sf::Vector2f getEnd() const;
        void setEnd(const sf::Vector2f &value);

        void setVector(const sf::Vector2f &value);
        float getLenght();

        float getThickness() const;
        void setThickness(float value);

    private:
        void update_shape();
    };
}


#endif // LINER_H
