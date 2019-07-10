#ifndef BUTTONCREATOR_H
#define BUTTONCREATOR_H

#include <entityx/entityx.h>
#include <SFML/Graphics.hpp>
#include <string>

#include <components/position.h>
#include <components/text.h>
#include <components/rectcomponent.h>
#include <components/mousebox.h>
#include <components/button.h>
#include <components/active.h>
#include <components/gui.h>
#include <components/screenresize.h>

class ButtonCreator
{
public:
    ButtonCreator();
    entityx::Entity operator()(entityx::EntityManager &es, sf::Vector2f pos, sf::Vector2f dim,
                               std::string text, entityx::Entity ancestor, int id);
};

#endif // BUTTONCREATOR_H
