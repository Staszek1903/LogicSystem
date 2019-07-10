#include "guisystem.h"

GuiSystem::GuiSystem(MouseHandler &m, entityx::EntityX &ex)
    :mouse(m),resizescale(0,0), ex(ex)
{
    ex.events.subscribe<ResizeEvent>(*this);
    ex.events.subscribe<MouseScrollEvent>(*this);
}

void GuiSystem::update(entityx::EntityManager &es, entityx::EventManager &ev, double dt)
{
    Position::Handle pos;
    MouseBox::Handle mouseb;
    Rect::Handle rect;
    Button::Handle button;
    Active::Handle active;
    Slider::Handle slider;
    ScreenResize::Handle s_resize;

    if(resized)
    {
        for(auto entity : es.entities_with_components(pos, slider))
        {
            if(slider->horizontal)
            {
                slider->lenght = resizescale.width -100;
                slider->initPos.y = resizescale.height -20;
                pos->pos.y = resizescale.height -20;
            }
            else
            {
                slider->lenght = resizescale.height -100;
                //std::cout<<"v: "<<slider->lenght<<std::endl;
            }

        }
        resized = false;
    }

    // | OBSLUGA SLDERÓW
    // V


    for(auto entity : es.entities_with_components(pos, mouseb, rect, slider))
    {
        sf::Vector2f box(mouseb->dim + pos->pos);
        bool in = mouse.pos.x > pos->pos.x && mouse.pos.y > pos->pos.y &&
                        mouse.pos.x < box.x && mouse.pos.y < box.y;

        rect->color =(in)? rect->color = sf::Color(10,10,20) : sf::Color(30,30,40);
        slider->active = (slider->active || in) && mouse.Lbutton;
        slider->active = slider->active * mouse.Lbutton;

        float &sliderPos = (slider->horizontal)? (pos->pos.x) : (pos->pos.y),
                &mousePos = (slider->horizontal)? (mouse.pos.x) : (mouse.pos.y),
                &rectDim = (slider->horizontal)? (rect->dim.x) : (rect->dim.y),
                &initPos = (slider->horizontal)? (slider->initPos.x) : (slider->initPos.y);


        if(mousePos < initPos + rectDim/2 && slider->active)
        {
            slider->position = 0;
            sliderPos = initPos;
        }
        else if(mousePos > initPos + slider->lenght + rectDim/2 && slider->active)
        {
            slider->position = 1;
            sliderPos = initPos + slider->lenght;
        }
        else if(slider->active)
        {
            sliderPos = mousePos - rectDim/2;
            slider->position = (sliderPos - initPos)/slider->lenght;
            ev.emit<ScrollEvent>(slider->horizontal, slider->position);
        }
    }

    for(auto entity : es.entities_with_components(pos, mouseb,rect, button, active))
    {

        // |
        // V OBSUGA WIDZIALNOSCI PRZYCISKU I POWYZCJI -- W RAZIE POTRZEBY DO OPTYMALIZACJI

        if(button->id != -1)        //id == -1 button jest nadrzedny i nie ma ancestora ani uppera
        {
            List::Handle anclist = button->ancestor.component<List>();
            Position::Handle prevpos = button->upper.component<Position>();
            Rect::Handle prevrect = button->upper.component<Rect>();
            //Button::Handle prevbutton = button->upper.component<Button>();
            active->visible = anclist->open;

            if(entity.has_component<List>() && !active->visible)                    //Sprawdzanie widzialnosci listy
            {
                List::Handle list= entity.component<List>();
                list->open = false;
                //std::cout<<"Lista: "<<list->open<<std::endl;
            }

            if(button->upper.has_component<List>() && button->upper != button->ancestor)    //pozycjonowanie w zaleznosci od
            {                                                                               //widzialnosci
                List::Handle list= button->upper.component<List>();
                if(list->open)
                    pos->pos.y = prevpos->pos.y + (prevrect->dim.y * (list->size + 1));
                else
                    pos->pos.y = prevpos->pos.y + prevrect->dim.y;
            }
            else
                pos->pos.y = prevpos->pos.y + prevrect->dim.y;
        }


        // |
        // V  OBSLUGA NACISNIECA

        sf::Vector2f box(mouseb->dim + pos->pos);

        rect->color = sf::Color(30,30,40);
        if(mouse.pos.x > pos->pos.x && mouse.pos.y > pos->pos.y &&
                mouse.pos.x < box.x && mouse.pos.y < box.y && active->visible)
        {
            rect->color = sf::Color(10,10,20);

            if(mouse.Lbutton && (!button->clicked))
            {
                button->clicked = true;
                if(entity.has_component<List>())
                {
                    List::Handle list= entity.component<List>();
                    list->open = !(list->open);
                    std::cout<<"Lista: "<<list->open<<std::endl;
                }
                else
                    ev.emit<ButtonPushEvent>(button->id);                  // TUTAJ MA GENEROWAC EVENT
            }
            else if(!mouse.Lbutton)
                button->clicked = false;
        }
    }
}

void GuiSystem::receive(const ResizeEvent &event)
{
    resized = true;
    resizescale = event;
}

void GuiSystem::receive(const MouseScrollEvent &event)
{
    Position::Handle pos;
    Rect::Handle rect;
    Slider::Handle slider;

    for(auto entity : ex.entities.entities_with_components(pos, rect, slider))
    {
        if((slider->horizontal && event.wheel == 0) || (!slider->horizontal && event.wheel == 1))
            continue;

        float &sliderPos = (slider->horizontal)? (pos->pos.x) : (pos->pos.y),
              //&rectDim = (slider->horizontal)? (rect->dim.x) : (rect->dim.y),
              &initPos = (slider->horizontal)? (slider->initPos.x) : (slider->initPos.y);

        sliderPos -= 5 *event.delta;
        slider->position = (sliderPos - initPos)/slider->lenght;

        if(sliderPos < initPos )//+ rectDim/2 )
        {
            slider->position = 0;
            sliderPos = initPos;
        }
        else if(sliderPos > initPos + slider->lenght)// + rectDim/2)
        {
            slider->position = 1;
            sliderPos = initPos + slider->lenght;
        }

        ex.events.emit<ScrollEvent>(slider->horizontal, slider->position);

    }
}
