#ifndef LISTCREATOR_H
#define LISTCREATOR_H

#include <entityx/entityx.h>
#include <creators/buttoncreator.h>
#include <components/list.h>
#include <components/position.h>
#include <components/rectcomponent.h>
#include <SFML/Graphics.hpp>

class ListCreator
{
public:
    ListCreator();
    entityx::Entity operator()(entityx::EntityManager &es, sf::Vector2f pos, sf::Vector2f dim,
                               std::string text, entityx::Entity ancestor, bool open);
    entityx::Entity addList(entityx::EntityManager &es, entityx::Entity list, std::string text);
    int addButton(entityx::EntityManager &es, entityx::Entity list, std::string text);
};

#endif // LISTCREATOR_H
