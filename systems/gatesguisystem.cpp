#include "gatesguisystem.h"

GatesGuiSystem::GatesGuiSystem(entityx::EntityX& entX, MouseHandler & mouse, ContainersContainer &container)
    :mouse(mouse), container(container), entX(entX), latch(false), block(false), is_selecting_area(false), is_selected_area(false),
      select_area_catch(false), ctrl_pushed(false), wire_create(entX, container), to_create(-1)
{
    entX.events.subscribe<ButtonPushEvent>(*this);
    entX.events.subscribe<KeyPushEvent>(*this);
    entX.events.subscribe<KeyReleasedEvent>(*this);
}

void GatesGuiSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, double dt)
{
    ConfigWindow::Handle cfgwin;
    VertexArray::Handle v_array;
    Ports::Handle ports;
    Position::Handle pos;
    PartID::Handle part_id;

    //TWORZENIE BRAMKI
    if(select_area.valid())
        to_create = -1;
    if(to_create >= 0 && to_create < container.ports.meta_data.size())
    {
        CircutCreator cc(entX, container);
        mouse_latch = cc(entities, to_create, mouse.pos);
        latch = true;
        to_create = -1;
        block = true;

        VertexArray::Handle mlv = mouse_latch.component<VertexArray>();
        Position::Handle pos = mouse_latch.component<Position>();

        select_area = entities.create();
        sf::FloatRect rect = mlv->ref.getBounds();
        s_area_origin = sf::Vector2f(rect.left, rect.top);
        rect.left += pos->pos.x;
        rect.top += pos->pos.y;
        select_area.assign<SelectArea>(rect);
    }

    //ZŁAPANA BRAMKA
    if(latch)
    {
        sf::Vector2 <int> ipos;
        sf::Vector2f fpos;
        ipos.x = mouse.viewPos().x;
        ipos.y = mouse.viewPos().y;
        ipos.x = (ipos.x/10)*10;
        ipos.y = (ipos.y/10)*10;
        fpos.x = ipos.x;
        fpos.y = ipos.y;

        set_circ_pos(mouse_latch, fpos);

        Position::Handle pos = mouse_latch.component<Position>();
        SelectArea::Handle s_a =  select_area.component<SelectArea>();
        s_a->rect.setPosition(s_area_origin + pos->pos);
    }

    //PUSZCZONY PRZYCISK
    if(!mouse.Lbutton)
    {
        block = false;
        if(is_selected_area)
        {
            SelectArea::Handle s_a = select_area.component<SelectArea>();
            sf::Vector2f s_size = s_a->rect.getSize();
            sf::Vector2f s_pos = s_a->rect.getPosition();

            if(s_size.x < 0)
            {
                s_pos.x += s_size.x;
                s_size.x = -s_size.x;
            }

            if(s_size.y < 0)
            {
                s_pos.y += s_size.y;
                s_size.y = -s_size.y;
            }
            s_a->rect.setPosition(s_pos);
            s_a->rect.setSize(s_size);

            if(s_size.x < 10 || s_size.y < 10)
            {
                is_selected_area = false;
                select_area.destroy();
            }
        }
        is_selecting_area = false;
        select_area_catch = false;
    }

    //POSTAWIENIE BRAMIKI
    if(latch && mouse.Lbutton && !block)
    {
        latch = false;
        block = true;
        if(select_area.valid())
            select_area.destroy();
        is_selected_area = false;
    }

    //PRZECIĄGANIE KABLA
    if(wire_create.isStarted())
    {
        static bool prev_rmb =false;
        Line::Handle line = wire_create.get_wire().component<Line>();
        line->line.setEnd(mouse.viewPos());

        if(!prev_rmb && mouse.Rbutton) line->line.nextType();
        prev_rmb = mouse.Rbutton;


        /*
        // DEBUG
            float test = line->line.getThickness();

            test *=2;
            test /=2;
        //DEBUG END


        // DEBUG
            test = line->line.getThickness();

            test *=2;
            test /=2;
        //DEBUG END
        */
    }

    //PRZENIESIENIE OBSZARU ZAZNACZENIA
    if(select_area_catch)
    {
        SelectArea::Handle s_a = select_area.component<SelectArea>();
        sf::Vector2f s_pos = s_a->rect.getPosition();
        sf::Vector2f mouse_v_pos = mouse.viewPos();
        sf::Vector2 <int> ipos;
        sf::Vector2f fpos;
        ipos.x = mouse_v_pos.x;
        ipos.y = mouse_v_pos.y;
        ipos.x = (ipos.x/10)*10;
        ipos.y = (ipos.y/10)*10;
        fpos.x = ipos.x;
        fpos.y = ipos.y;

        for(auto en : s_a_catched)
        {
            Position::Handle pos = en.component<Position>();
            sf::Vector2f target = pos->pos +(fpos - s_area_catch_pos);
            //std::cout<<target.x<< " "<< target.y<<std::endl;
            set_circ_pos(en, target);
        }
        s_pos += (fpos - s_area_catch_pos);
        s_a->rect.setPosition(s_pos);
        s_area_catch_pos = fpos;
    }

    //ZŁAPANIE OBSZARU ZAZNACZENIA
    if(!block && mouse.Lbutton && is_selected_area)
    {
        sf::Vector2f mouse_v_pos = mouse.viewPos();
        SelectArea::Handle s_a = select_area.component<SelectArea>();
        sf::Vector2f s_pos = s_a->rect.getPosition();
        sf::Vector2f s_size = s_a->rect.getSize();

        s_a_catched.clear();

        if( mouse_v_pos.x > s_pos.x && mouse_v_pos.x < s_pos.x+ s_size.x &&
                mouse_v_pos.y > s_pos.y && mouse_v_pos.y < s_pos.y + s_size.y)
        {
            block = true;
            select_area_catch = true;
            s_area_catch_pos = mouse_v_pos;

            for(auto en : entX.entities.entities_with_components(v_array,pos))
            {
                if(pos->pos.x > s_pos.x && pos->pos.x < s_pos.x + s_size.x &&
                        pos->pos.y > s_pos.y && pos->pos.y < s_pos.y + s_size.y)
                {
                    s_a_catched.push_back(en);
                }
            }
        }
    }

    //NACISNIECIE PORTU
    if(!latch && mouse.Lbutton && !block)
    {
        for( auto en : entities.entities_with_components(ports, pos))
        {
            if(wire_create.isStarted() && (en == wire_origin))
                continue;

            auto & ports_in = container.ports.get_ports_in(ports->index);
            auto & ports_out = container.ports.get_ports_out(ports->index);

            int port_index = 0;
            for(auto & port_in: ports_in)
            {
                sf::FloatRect rect(port_in.pos + pos->pos -sf::Vector2f(5,5), sf::Vector2f(10,10));
                if(has_mouse(rect))
                {
                    std::cout<<"port in clicked"<<std::endl;
                    block = true;
                    if(wire_create.isStarted() && !port_in.joined)
                    {
                        wire_create.end(en, ports,  port_index);
                        std::cout<< port_index<<std::endl;
                    }
                    else if(!wire_create.isStarted() && port_in.joined)
                    {
                        wire_origin = wire_create.detach(port_in, ports);
                        std::cout<<"detached"<<std::endl;
                    }
                    break;
                }

                ++port_index;
            }

            if(!wire_create.isStarted())
            {
                int port_index =0;

                for(auto & port_out: ports_out)
                {
                    sf::FloatRect rect(port_out.pos + pos->pos -sf::Vector2f(5,5), sf::Vector2f(10,10));
                    if(has_mouse(rect) && !port_out.joined)
                    {
                        std::cout<<"port out clicked"<<std::endl;
                        block = true;
                        wire_origin = en;
                        wire_create.start(en, ports->index , port_index, pos->pos);
                        break;
                    }
                    ++port_index;
                }
            }
        }
    }

    //WYSWIETLANIE NAZWY PORTU

    static auto port_hint = entities.create();
    if(!port_hint.has_component<Label>()) port_hint.assign<Label>("Port: ", sf::Vector2f(10,10));
    if(!port_hint.has_component<Position>()) port_hint.assign<Position>(sf::Vector2f(100,100));

    bool found = false;
    for( auto en : entities.entities_with_components(ports, pos, part_id))
    {

        auto & ports_in = container.ports.get_ports_in(ports->index);
        auto & ports_out = container.ports.get_ports_out(ports->index);
        //auto & ports_info = container.names.

        int port_index = 0;
        for(auto & port_in: ports_in)
        {
            sf::FloatRect rect(port_in.pos + pos->pos -sf::Vector2f(5,5), sf::Vector2f(10,10));
            if(has_mouse(rect))
            {
                //ODNALEZC ID KOMPONENTU
                int p_id = part_id->id;
                std::string name = container.port_names.get_name(p_id,port_index,PortNamesContainer::IN);
                port_hint.component<Label>()->text = "Port: IN "+name;
                port_hint.component<Position>()->pos = mouse.viewPos();
                found = true;
            }

            ++port_index;
        }

        port_index =0;
        for(auto & port_out: ports_out)
        {
            sf::FloatRect rect(port_out.pos + pos->pos -sf::Vector2f(5,5), sf::Vector2f(10,10));
            if(has_mouse(rect) && !port_out.joined)
            {
                int p_id = part_id->id;
                std::string name = container.port_names.get_name(p_id,port_index, PortNamesContainer::OUT);
                port_hint.component<Label>()->text = "Port: OUT "+name;
                port_hint.component<Position>()->pos = mouse.viewPos();
                found = true;
            }
            ++port_index;
        }

    }
    if(!found) port_hint.component<Label>()->text = " ";

    //POSTAWIENIE SPLITTERA
    if(wire_create.isStarted() && mouse.Lbutton && !block)
    {
        CircutCreator cc(entX, container);
        std::string name("junction");
        int index = container.names.get_index(name);
        sf::Vector2i ipos(mouse.viewPos().x,mouse.viewPos().y);
        sf::Vector2f new_pos((ipos.x/10)*10, (ipos.y/10)*10);
        auto en = cc(entities, index, new_pos);
        ports = en.component<Ports>();
        pos = en.component<Position>();

        wire_create.end(en, ports, 0);
        wire_create.start(en, ports->index,0, pos->pos);
        block = true;
    }

    //ŁAPANIE BRAMKI
    if(!latch && mouse.Lbutton && !block)
    {

        for( auto en : entities.entities_with_components(v_array, pos))
        {
            sf::FloatRect rect = v_array->ref.getBounds();
            sf::FloatRect rect_ori = rect;
            rect.left += pos->pos.x;
            rect.top  += pos->pos.y;
            if(has_mouse(rect))
            {
                latch = true;
                mouse_latch = en;
                block = true;
                if(select_area.valid())
                    select_area.destroy();
                select_area = entities.create();
                select_area.assign<SelectArea>(rect);
                s_area_origin = sf::Vector2f(rect_ori.left, rect_ori.top);
            }
        }
    }

    //ODZNACZENIE OBSZARU ZAZNACZENIA
    if(mouse.Lbutton && is_selected_area && !block)
    {
        is_selected_area = false;
        block = true;
        select_area.destroy();
    }

    //PRZECIĄGANIE OBSZARU ZAZNACZENIA
    if(is_selecting_area)
    {
        SelectArea::Handle s_a = select_area.component<SelectArea>();
        sf::Vector2f origin = s_a->rect.getPosition();
        s_a->rect.setSize(mouse.viewPos() - origin);
    }

    //ROZPOCZECIE OBSZARU ZAZNACZENIA
    if(!latch && mouse.Lbutton && !block)
    {
        sf::FloatRect rect;

        rect.left = mouse.viewPos().x;
        rect.top = mouse.viewPos().y;
        rect.width = 0;
        rect.height = 0;
        select_area = entities.create();
        select_area.assign<SelectArea>(rect);
        is_selecting_area = true;
        is_selected_area = true;
        block = true;
    }

    if(mouse.Rbutton && !wire_create.isStarted())
    {
        for( auto en : entities.entities_with_components(cfgwin,v_array, pos))
        {
            sf::FloatRect rect = v_array->ref.getBounds();
            rect.left += pos->pos.x;
            rect.top  += pos->pos.y;
            if(has_mouse(rect))
                        events.emit<ConfigWindowCreateEvent>(en,cfgwin->create);

        }
    }
}

void GatesGuiSystem::receive(const ButtonPushEvent &ev)
{
    std::cout<<"received button: "<<ev.id<<std::endl;
    to_create = ev.id;
}

void GatesGuiSystem::receive(const KeyPushEvent &ev)
{
    Position::Handle pos;
    CircuitButton::Handle circ_button;
    VertexArray::Handle v_array;
    Ports::Handle ports;
    CircuitTypeIndex::Handle circ_type;
    Wire::Handle wire_c;

    if(ev.key == sf::Keyboard::Delete)
    {
        if(latch)
        {
            CircutCreator cc(entX,container);
            cc.destroy(mouse_latch);
            latch = false;
            select_area.destroy();
            std::cout<<"delete circuit"<<std::endl;
        }
        else if(is_selected_area)
        {
            SelectArea::Handle s_a = select_area.component<SelectArea>();
            sf::Vector2f s_pos = s_a->rect.getPosition();
            sf::Vector2f s_size = s_a->rect.getSize();
            for(auto en : entX.entities.entities_with_components(v_array,pos))
            {
                CircutCreator cc(entX, container);
                if(pos->pos.x > s_pos.x && pos->pos.x < s_pos.x + s_size.x &&
                        pos->pos.y > s_pos.y && pos->pos.y < s_pos.y + s_size.y)
                    cc.destroy(en);
            }
        }
        else if(wire_create.isStarted())
        {
            wire_create.abort();
            std::cout<<"delete wire"<<std::endl;
        }
    }
    else if(ev.key == sf::Keyboard::LControl)
        ctrl_pushed = true;
    else if(is_selected_area && ctrl_pushed && ev.key == sf::Keyboard::C)
    {
        SelectArea::Handle s_a = select_area.component<SelectArea>();
        sf::Vector2f s_pos = s_a->rect.getPosition();
        sf::Vector2f s_size = s_a->rect.getSize();
        selected_save_size = s_size;
        saved_circ.clear();
        saved_wires.clear();
        for(auto en : entX.entities.entities_with_components(circ_type,pos))
        {
            if(pos->pos.x > s_pos.x && pos->pos.x < s_pos.x + s_size.x &&
                    pos->pos.y > s_pos.y && pos->pos.y < s_pos.y + s_size.y)
               saved_circ.push_back({en,circ_type->index, (pos->pos - s_pos)});

            //std::cout<<"czo jesz kuwełe"<<std::endl;
        }

        for(auto en: entX.entities.entities_with_components(wire_c))
        {
            bool is_in = false, is_out = false;
            int in_index, out_index;
            for(unsigned int i=0; i<saved_circ.size(); ++i)
            {
                if(saved_circ[i].en == wire_c->entity_in)
                {
                    is_in = true;
                    in_index= i;
                }
                if(saved_circ[i].en == wire_c->entity_out)
                {
                    is_out = true;
                    out_index = i;
                }
            }

            if(is_in && is_out)
                saved_wires.push_back({in_index, out_index, wire_c->in_index, wire_c->out_index});
        }
    }
    else if(!is_selected_area && ctrl_pushed && ev.key == sf::Keyboard::V)
    {
        std::cout<<"ctrl+V : "<<saved_circ.size()<<" "<<saved_wires.size()<<std::endl;
        is_selected_area = true;
        sf::FloatRect rect;
        sf::Vector2f mouse_v_pos = mouse.viewPos();
        rect.left = mouse_v_pos.x;
        rect.top = mouse_v_pos.y;
        rect.width = selected_save_size.x;
        rect.height = selected_save_size.y;
        select_area = entX.entities.create();
        select_area.assign<SelectArea>(rect);

        CircutCreator cc(entX, container);
        std::vector <entityx::Entity> ens;
        for(auto p : saved_circ)
            ens.push_back(cc(entX.entities, p.index, p.pos + mouse_v_pos));
        for(auto w : saved_wires)
        {
            Ports::Handle ports_out = ens[w.en_out].component<Ports>();
            Position::Handle pos_out = ens[w.en_out].component<Position>();
            Ports::Handle ports_in = ens[w.en_in].component<Ports>();
            wire_create.start(ens[w.en_out],ports_out->index,w.port_out,pos_out->pos);
            wire_create.end(ens[w.en_in],ports_in,w.port_in);
        }

    }
    else if(ev.key == sf::Keyboard::Comma)
    {
        if(wire_create.isStarted())
        {
            wire_create.moveBreakPoint(true);
        }
    }
    else if (ev.key == sf::Keyboard::Period)
    {
        if(wire_create.isStarted())
        {
            wire_create.moveBreakPoint(false);
        }
    }

    for( auto en : entX.entities.entities_with_components(circ_button, v_array, ports))
    {
        if(circ_button->key == ev.key)
        {
            circ_button->state = !(circ_button->state);
            container.ports.ports_out.at(ports->index).second.at(0).data = -(circ_button->state);
        }
    }
}

void GatesGuiSystem::receive(const KeyReleasedEvent &ev)
{
    if(ev.key == sf::Keyboard::LControl)
        ctrl_pushed = false;
}

bool GatesGuiSystem::has_mouse(sf::FloatRect rect)
{
    return (mouse.viewPos().x > rect.left && mouse.viewPos().x < rect.left + rect.width &&
            mouse.viewPos().y > rect.top && mouse.viewPos().y < rect.top + rect.height);
}

void GatesGuiSystem::set_circ_pos(entityx::Entity en, sf::Vector2f pos)
{
    sf::Vector2 <int> ipos;
    sf::Vector2f fpos;
    ipos.x = pos.x;
    ipos.y = pos.y;
    ipos.x = (ipos.x/10)*10;
    ipos.y = (ipos.y/10)*10;
    fpos.x = ipos.x;
    fpos.y = ipos.y;

    Position::Handle pos_c = en.component<Position>();
    Ports::Handle ports = en.component<Ports>();
    auto & ports_in = container.ports.ports_in[ports->index];
    auto & ports_out = container.ports.ports_out[ports->index];

    pos_c->pos = fpos;

    for(auto &port_in: ports_in.second)
    {
        if(port_in.joined)
        {
            Line::Handle line = port_in.wire.component<Line>();
            line->line.setEnd(port_in.pos + pos_c->pos);
        }
    }

    for(auto &port_out: ports_out.second)
    {
        if(port_out.joined)
        {
            Line::Handle line = port_out.wire.component<Line>();
            line->line.setBegining(port_out.pos + pos_c->pos);
        }
    }
}
