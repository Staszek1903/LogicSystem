#include "buttoncreator.h"

ButtonCreator::ButtonCreator()
{

}

entityx::Entity ButtonCreator::operator()(entityx::EntityManager &es, sf::Vector2f pos, sf::Vector2f dim,
                                          std::string text, entityx::Entity ancestor,int id)
{
    static int idc = -1;
    if(id != -1)
    {
        ++idc;
        id = idc;
    }
    entityx::Entity en = es.create();
    en.assign<Position>(pos);
    en.assign<Text>(text, 18, sf::Vector2f(5,0));
    en.assign<Rect>(dim, sf::Color(30,30,40));
    en.assign<MouseBox>(dim);
    en.assign<Button>(ancestor, id);
    en.assign<Active>(true);
    en.assign<Gui>();
    return en;
}
