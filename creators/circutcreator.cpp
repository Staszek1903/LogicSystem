#include "circutcreator.h"

CircutCreator::CircutCreator(entityx::EntityX &enX, ContainersContainer &container)
    :enX(enX), container(container)
{

}

entityx::Entity CircutCreator::operator()(entityx::EntityManager &entities, int index, sf::Vector2f pos)
{
    auto en = entities.create();

    en.assign<PartID>(index);
    en.assign<CircuitTypeIndex>(index);
    en.assign<Position>(pos);
    en.assign<VertexArray>(container.draw.get_gate(index));
    int ports_index = container.ports.create(index,en);
    en.assign<Ports>(ports_index, container.draw.get_port(index), container.ports.ports_in[ports_index].second.size() );
    en.assign<ConfigWindow>(container.win_create.creates[index]);

    ports_index = container.memory.create(en, index);
    en.assign<Memory>(ports_index);
    //std::cout<<"dodaje memory index: "<<ports_index<<std::endl;

    for(int additional :container.additional.additional[index])
    {
        switch(additional)
        {
        case AdditionalContainer::BUTTON:
            en.assign<CircuitButton>();
            break;
        case AdditionalContainer::LED:
            en.assign<Led>(sf::Color::Red);
            break;
        case AdditionalContainer::ALGORITHM:
            en.assign<Algorithm>(container.instruction.inst[index]);
            break;
        case AdditionalContainer::LATCH:
            en.assign<Latch>("255",sf::Vector2f(-10,-10));
            break;
        case AdditionalContainer::PROBE:
            en.assign<Probe>("00000000",sf::Vector2f(-24,-10));
            break;
        case AdditionalContainer::LABEL:
            en.assign<Label>(container.names.get_name(index), sf::Vector2f(-18,-12));
            break;
        case AdditionalContainer::PIN:
            container.ports.get_ports_out(ports_index)[0].data = 1;
            en.assign<Constant>();
            break;
        case AdditionalContainer::DISP_7_SEG:
            en.assign<Disp7Seg>(container.ports.get_ports_in(ports_index)[0]);
            break;
        case AdditionalContainer::START_POINT:
            en.assign<StartPoint>();
            break;
        default:
            break;
        }
    }
    return en;
}

void CircutCreator::destroy(entityx::Entity circuit)
{
    Ports::Handle ports = circuit.component<Ports>();
    Memory::Handle memory = circuit.component<Memory>();
    auto & ports_out = container.ports.ports_out[ports->index];
    auto & ports_in = container.ports.ports_in[ports->index];

    for(auto & port : ports_out.second)
    {
        if(port.joined)
        {
            Wire::Handle wH = port.wire.component<Wire>();
            Ports::Handle ports_another = wH->entity_in.component<Ports>();
            ports_another->joined_in_count--;
            wH->port_in->joined = false;
            //wH->port_out->data = 0;
            port.wire.destroy();
        }
    }

    for(auto & port : ports_in.second)
    {
        if(port.joined)
        {
            Wire::Handle wH = port.wire.component<Wire>();
            wH->port_out->joined = false;
            //wH->port_out->data = 0;
            port.wire.destroy();
        }
    }

    container.ports.destroy(ports->index);
    container.memory.destroy(memory->index);

    circuit.destroy();

    enX.events.emit<ResetSequence>();
}
