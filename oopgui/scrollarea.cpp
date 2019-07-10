#include "scrollarea.h"

ScrollArea::ScrollArea()
    :pos(sf::Vector2f(0,0)), dim(sf::Vector2f(0,0)), scroll_span(0), current_pos(0), has_mouse(false)
{

}

void ScrollArea::init(sf::Vector2f pos, sf::Vector2f dim, sf::FloatRect ratio, float span)
{
    this->pos = pos;
    this->dim = dim;
    scroll_span = (dim.y/2) + span;
    current_pos = dim.y/2;

    camera.setViewport(ratio);
    camera.setCenter(sf::Vector2f(dim.x/2, current_pos));
    camera.setSize(dim);
    camera.setRotation(0);

    rect.setFillColor(sf::Color::Black);
    rect.setPosition(pos);
    rect.setSize(dim);
    rect.setOutlineColor(sf::Color(128,128,128));
    rect.setOutlineThickness(3);
}

void ScrollArea::update(sf::Event ev)
{
    if(ev.type == sf::Event::MouseMoved)
    {
        int x = ev.mouseMove.x,
                y = ev.mouseMove.y;
        has_mouse = ((x>=pos.x) && (y>=pos.y) && (x<=(pos.x+dim.x)) && (y<=(pos.y+dim.y)));
        //std::cout<<"x: "<<x<<"  y: "<<y<<"  pos.x: "<<pos.x<<"  pos.y: "<<pos.y<<"  has_mouse: "<<has_mouse<<std::endl;
    }
    if(has_mouse && ev.type == sf::Event::MouseWheelScrolled)
    {
        const float scroll_speed = 5.0f;
        float prev_pos = current_pos;
        current_pos -= ev.mouseWheelScroll.delta * scroll_speed;
        current_pos = ((current_pos>(dim.y/2)- scroll_speed) && (current_pos<((dim.y/2)+scroll_span+ scroll_speed)))?
                    current_pos : prev_pos;
        camera.setCenter(sf::Vector2f(dim.x/2,current_pos));
    }
}

void ScrollArea::draw(sf::RenderTarget &win) const
{
    win.draw(rect);
}

void ScrollArea::setCamera(sf::RenderTarget &target) const
{
    target.setView(camera);
}

void ScrollArea::unsetCamera(sf::RenderTarget &target) const
{
    target.setView(target.getDefaultView());
}
