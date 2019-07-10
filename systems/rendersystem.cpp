#include "rendersystem.h"

RenderSystem::RenderSystem(sf::RenderWindow &win, entityx::EventManager &ev, sf::View &view, sf::Vector2f &view_range,
                           sf::Vector2f &origin, ContainersContainer &container)
    :win(win), view(view), view_range(view_range), view_origin(origin), container(container)
{
    font.loadFromFile("./LS-resources/system.ttf");
    fontLCD.loadFromFile("./LS-resources/LCD.ttf");
    ev.subscribe<ResizeEvent>(*this);
    ev.subscribe<ScrollEvent>(*this);
    ev.subscribe<NameChangeEvent>(*this);
    view_range = sf::Vector2f(1000,1000);
    view.setViewport(sf::FloatRect(0.02,0.02,0.96,0.96));
}

void RenderSystem::update(entityx::EntityManager &es, entityx::EventManager &events, double dt)
{
    Position::Handle pos;
    Circ::Handle circ;
    Rect::Handle rect;
    Text::Handle text;
    Active::Handle active;
    Gui::Handle gui;
    VertexArray::Handle v_array;
    Ports::Handle ports;
    CircuitButton::Handle circ_button;
    Line::Handle line;
    Led::Handle led;
    Latch::Handle latch;
    Memory::Handle memory;
    Probe::Handle probe;

    sf::CircleShape circle;
    sf::RectangleShape rectangle;
    sf::Text sfText;
    sf::Vector2u winsize = win.getSize();
    sf::Vector2f view_pos = view.getCenter();
    view_pos.x -= winsize.x/2;
    view_pos.y -= winsize.y/2;

    win.clear(sf::Color::Black);


    // |
    // V  bramki render

    win.setView(view);

    //RENDEROWANIE SIATKI
    int pointcount = ((winsize.x/10)+2) * ((winsize.y/10)+2);
    sf::VertexArray vert(sf::PrimitiveType::Points,pointcount);
    //std::cout<<"pc= "<<pointcount<<std::endl;
    int i=0;
    for(int x = view_pos.x - static_cast<int>(view_pos.x)%10 ; x < view_pos.x+winsize.x ; x+= 10)
    {
        for(int y = view_pos.y - static_cast<int>(view_pos.y)%10 ; y < view_pos.y+winsize.y ; y+= 10)
        {
            vert[i].position = sf::Vector2f(x+1,y+1);
            vert[i].color = sf::Color(100,100,100);
            ++i;
        }
    }
    //std::cout<<"i= "<<i<<std::endl;
    win.draw(vert);

    //BUTTON
    for(auto entity : es.entities_with_components(pos, v_array, circ_button))
    {
        sf::Transform trans;
        v_array->ref[0].color = (circ_button->state)? sf::Color::Green : v_array->ref[1].color;
        win.draw(v_array->ref, trans.translate(pos->pos));

        char c[2] = {static_cast<char>(circ_button->key+65), '\0'};
        sf::FloatRect bounds(v_array->ref.getBounds());
        sf::Vector2f offset(bounds.width/2, bounds.height/2);

        sfText.setFillColor(sf::Color(200,200,200));
        sfText.setPosition(pos->pos - offset);
        sfText.setFont(font);
        sfText.setString(c);
        sfText.setCharacterSize(18);
        win.draw(sfText);
    }

    //LED
    for(auto entity : es.entities_with_components(pos, ports, v_array,led))
    {
        auto & led_port = container.ports.get_ports_in(ports->index)[0];

        uint8_t data = (led_port.joined)? led_port.source->data : 0;

        v_array->ref[0].color = (data > 0)? led->color : v_array->ref[1].color;

        sf::Transform trans;
        win.draw(v_array->ref, trans.translate(pos->pos));
    }

    // RESZTA V_ARRAYOW
    for(auto entity : es.entities_with_components(pos,v_array))
    {
        if(entity.has_component<CircuitButton>() || entity.has_component<Led>())
            continue;

        sf::Transform trans;
        win.draw(v_array->ref, trans.translate(pos->pos)); 
    }

    //PORTY
    for(auto entity : es.entities_with_components(pos, ports))
    {
        size_t portsCount = ports->ref.getVertexCount();
        for(size_t i=0; i< portsCount; ++i)
        {
            sf::Vector2f port_pos= ports->ref[i].position + pos->pos;
            sf::CircleShape c_shape;
            c_shape.setPosition(port_pos);
            c_shape.setFillColor(ports->ref[i].color);
            c_shape.setRadius(5);
            c_shape.setOrigin(sf::Vector2f(5,5));
            win.draw(c_shape);
        }
    }

    // WIRE
    for(auto entity : es.entities_with_components(line))
    {
        win.draw(line->line);
    }

    //LATCHE
    for(auto entity: es.entities_with_components(latch,memory, pos))
    {
        std::stringstream ss;
        ss <<std::hex<< (int)container.memory.get_mem(memory->index)[0];
        latch->text = ss.str();

        sf::Text t;
        t.setFont(font);
        t.setCharacterSize(latch->char_size);
        t.setPosition(pos->pos+ latch->offset);
        t.setString(latch->text);
        win.draw(t);
        //std::cout<<latch->text<<"  -  "<<pos->pos.x<<"   "<<pos->pos.y<<std::endl;
    }

    //PROBE
    for(auto entity: es.entities_with_components(probe,ports, pos))
    {
        PortIN & port = container.ports.get_ports_in(ports->index)[0];



        uint8_t data = (port.joined) ? port.source->data : 0;
        char out [8] = {'0','0','0','0','0','0','0','0'};
        for(int i=0; i<8; ++i)
            out[-(i-7)] = ((data>>i)&1)+48;
        probe->text = out;

        sf::Text t;
        t.setFont(font);
        t.setCharacterSize(probe->char_size);
        t.setPosition(pos->pos+ probe->offset);
        t.setString(probe->text);
        win.draw(t);
        //std::cout<<probe->text<<"  -  "<<pos->pos.x<<"   "<<pos->pos.y<<std::endl;
    }

    Label::Handle label;

    //LABELE
    for(auto entity: es.entities_with_components(label, pos))
    {
        sf::Text t;
        t.setFont(font);
        t.setCharacterSize(label->char_size);
        t.setPosition(pos->pos+ label->offset);
        t.setString(label->text);
        win.draw(t);
        //std::cout<<probe->text<<"  -  "<<pos->pos.x<<"   "<<pos->pos.y<<std::endl;
    }

    Disp7Seg::Handle disp7;

    //DISP7
    for(auto entity: es.entities_with_components(disp7, pos))
    {
        std::stringstream ss;
        int data = (disp7->port.joined)? disp7->port.source->data : 0;
        ss << data;
        std::string s = ss.str();
        while(s.size() < 3) s = '0' + s;
        sf::Text t;
        t.setFont(fontLCD);
        t.setCharacterSize(64);
        t.setPosition(pos->pos - sf::Vector2f(30,45));
        t.setFillColor(sf::Color::Red);
        t.setString(s);
        win.draw(t);
    }

    SelectArea::Handle s_a;

    //SELECT AREA
    for(auto entity : es.entities_with_components(s_a))
        win.draw(s_a->rect);

    // |
    // V GUI RENDER

    win.setView(sf::View(sf::FloatRect(0,0,winsize.x,winsize.y)));

    for(auto entity : es.entities_with_components(gui,pos,circ,active))
    {
        if(!(active->visible))
            continue;
        circle.setFillColor(sf::Color::Green);
        circle.setPosition(pos->pos);
        circle.setRadius(circ->r);
        circle.setPointCount(circ->v);
        win.draw(circle);
    }

    for(auto entity : es.entities_with_components(gui,pos,rect,active))
    {
        if(!(active->visible))
            continue;
        rectangle.setFillColor(rect->color);
        rectangle.setOutlineColor(sf::Color(10,10,20));
        rectangle.setOutlineThickness(2);
        rectangle.setSize(rect->dim);
        rectangle.setPosition(pos->pos);
        win.draw(rectangle);
    }

    for(auto entity : es.entities_with_components(gui, pos,text,active))
    {
        if(!(active->visible))
            continue;
        sfText.setFillColor(sf::Color(200,200,200));
        sfText.setPosition(pos->pos+ text->offset);
        sfText.setFont(font);
        sfText.setString(text->text);
        sfText.setCharacterSize(text->CharSize);
        win.draw(sfText);
    }

   win.display();
}

void RenderSystem::receive(const ResizeEvent &ev)
{
    std::cout<<"viev resize"<<std::endl;
    view_origin = sf::Vector2f(ev.width/2,ev.height/2);
    view.setCenter(view_origin);
    view.setSize(sf::Vector2f(ev.width,ev.height));
}

void RenderSystem::receive(const ScrollEvent &ev)
{
    //std::cout<<"scroll: "<<ev.new_pos<<std::endl;

    if(ev.horizontal)
    {
        view.setCenter(sf::Vector2f(view_origin.x, view.getCenter().y));
        view.move(view_range.x * ev.new_pos, 0);
    }
    else
    {
        view.setCenter(sf::Vector2f(view.getCenter().x, view_origin.y));
        view.move(0, view_range.y * ev.new_pos);
    }
}

void RenderSystem::receive(const NameChangeEvent &ev)
{
    win.setTitle(std::string("LogicSystem - "+ ev.name));
}
