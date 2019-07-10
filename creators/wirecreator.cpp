#include "wirecreator.h"

WireCreator::WireCreator(entityx::EntityX & manager, ContainersContainer & container)
    : enX(manager), container(container), started(false)
{

}

bool WireCreator::isStarted()
{
    return started;
}

void WireCreator::start(entityx::Entity en, int ports_index , int port_index, sf::Vector2f en_pos)
{
    if(started)
        return;
    started = true;

    PortOUT & port_out = container.ports.get_ports_out(ports_index)[port_index];

    wire = enX.entities.create();
    auto deblH =wire.assign<Line>(port_out.pos + en_pos, port_out.pos + en_pos, sf::Color::White);



    wire.assign<Wire>(&port_out ,en, port_index);
    port_out.wire = wire;
    port_origin = &port_out;
    std::cout<<"wire started"<<std::endl;


    // DEBUG
     //   float test = deblH->line.getThickness();
    //DEBUG END
}

void WireCreator::abort()
{
    if(!started)
        return;

    port_origin->joined = false;
    wire.destroy();
    started = false;
}

void WireCreator::setType(int type, float break_point)
{
     Line::Handle lH= wire.component<Line>();
     lH->line.setType(type);
     lH->line.setBreakPoint(break_point);
}

void WireCreator::moveBreakPoint(bool add)
{
    Line::Handle lH= wire.component<Line>();
    float bp = lH->line.getBreakPoint();
    if(add && bp <0.9f)
        bp += 0.1f;
    else if (!add && bp > 0.1f)
        bp -= 0.1f;
    lH->line.setBreakPoint(bp);
}

void WireCreator::end(entityx::Entity en, Ports::Handle ports, int port_index)
{
    std::cout<<ports->index<<" "<<port_index<<std::endl;

    PortIN & port_in = container.ports.get_ports_in(ports->index).at(port_index);

    std::cout<<ports->index<<" "<<port_index<<std::endl;
    if(!started)
        return;
    started = false;

    Position::Handle pos = en.component<Position>();
    Line::Handle lH= wire.component<Line>();
    Wire::Handle wH= wire.component<Wire>();
    std::cout<<port_in.pos.x<<std::endl;

    //auto & debugl = lH->line;

    lH->line.setEnd(port_in.pos + pos->pos);
    wH->port_in = &port_in;
    wH->entity_in = en;
    wH->in_index = port_index;
    port_in.joined = true;
    port_origin->joined = true;
    port_in.wire = wire;
    port_in.source = port_origin;
    std::cout<<"wire ended3"<<std::endl;
    ports->joined_in_count++;

    std::cout<<"wire ended"<<std::endl;
    enX.events.emit<ResetSequence>();
}

entityx::Entity WireCreator::detach(PortIN &port, Ports::Handle ports)
{
    started = true;
    wire = port.wire;
    port_origin = port.source;
    port.joined = false;
    port_origin->joined = false;
    Wire::Handle wc = wire.component<Wire>();
    port.source = NULL;
    ports->joined_in_count--;
    enX.events.emit<ResetSequence>();
    return (wc->entity_out);
}

entityx::Entity WireCreator::get_wire()
{
    return wire;
}
