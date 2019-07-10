#include "listcreator.h"

ListCreator::ListCreator()
{

}

entityx::Entity ListCreator::operator()(entityx::EntityManager &es, sf::Vector2f pos, sf::Vector2f dim, std::string text, entityx::Entity ancestor, bool open)
{
    ButtonCreator button;
    auto en = button(es,pos,dim,text,ancestor,-1);

    en.assign<List>(open, en);

    return en;
}

entityx::Entity ListCreator::addList(entityx::EntityManager &es, entityx::Entity list, std::string text)
{
    ListCreator listcreator;
    Position::Handle pos = list.component<Position>();
    Rect::Handle rect = list.component<Rect>();
    List::Handle listcomp = list.component<List>();
    Button::Handle button;

    listcomp->size++;
    sf::Vector2f newpos = pos->pos;
    newpos.x +=10;
    newpos.y += listcomp->size * rect->dim.y;
    int newbuttonId = listcomp->size - 1;
    auto en = listcreator(es,newpos,rect->dim,text, list, listcomp->open);

    button = en.component<Button>();
    button->id =newbuttonId;
    button->upper = listcomp->last;
    listcomp->last = en;

    return en;
}

int ListCreator::addButton(entityx::EntityManager &es, entityx::Entity list, std::string text)
{

    ButtonCreator button;

    Position::Handle pos = list.component<Position>();
    Rect::Handle rect = list.component<Rect>();
    List::Handle listcomp = list.component<List>();
    Button::Handle buttoncomp;
    Active::Handle activebutton;

    listcomp->size++;
    sf::Vector2f newpos = pos->pos;
    newpos.x +=10;
    newpos.y += listcomp->size * rect->dim.y;
    int newbuttonId = listcomp->size - 1;
    auto en = button(es,newpos,rect->dim,text, list, newbuttonId);

    buttoncomp = en.component<Button>();
    activebutton = en.component<Active>();
    activebutton->visible = listcomp->open;
    buttoncomp->upper = listcomp->last;
    listcomp->last = en;

    return buttoncomp->id;
}
