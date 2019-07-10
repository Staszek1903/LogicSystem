#ifndef SLIDERCREATOR_H
#define SLIDERCREATOR_H

#include <entityx/entityx.h>
#include <SFML/Graphics.hpp>
#include <components/position.h>
#include <components/slider.h>
#include <components/active.h>
//include <components/button.h>
#include <components/rectcomponent.h>
#include <components/mousebox.h>
#include <components/gui.h>
#include <components/screenresize.h>

class SliderCreator
{
public:
    SliderCreator();
    entityx::Entity operator()(entityx::EntityManager &es, sf::Vector2f pos, int lenght, bool horizontal, bool resize);
};

#endif // SLIDERCREATOR_H
