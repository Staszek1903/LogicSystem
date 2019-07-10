#include "slidercreator.h"

SliderCreator::SliderCreator()
{

}

entityx::Entity SliderCreator::operator()(entityx::EntityManager &es, sf::Vector2f pos, int lenght, bool horizontal, bool resize)
{
    entityx::Entity en = es.create();
    en.assign<Position>(pos);
    en.assign<Slider>(pos , 0, lenght, horizontal);
    en.assign<Rect>((horizontal)? sf::Vector2f(80,20) :sf::Vector2f(20,80) , sf::Color(30,30,40));
    en.assign<MouseBox>((horizontal)? sf::Vector2f(80,20) :sf::Vector2f(20,80));
    en.assign<Active>(true);
    en.assign<Gui>();

    if(resize)
        en.assign<ScreenResize>();

    return en;
}
