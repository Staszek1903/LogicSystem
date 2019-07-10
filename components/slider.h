#ifndef SLIDER_H
#define SLIDER_H

#include <entityx/entityx.h>
#include <SFML/Graphics.hpp>
struct Slider :public entityx::Component<Slider>
{
    Slider(sf::Vector2f initpos, float pos,int l,bool horizontal)
        :initPos(initpos), position(pos),lenght(l),horizontal(horizontal), active(false){}
    sf::Vector2f initPos;
    float position; // 0..1
    int lenght;     // w pikselach
    bool horizontal; // albo vertical;
    bool active;    //czy nacisniety;
};

#endif // SLIDER_H
