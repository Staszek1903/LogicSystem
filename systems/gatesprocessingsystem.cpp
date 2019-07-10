#include "gatesprocessingsystem.h"

GatesProcessingSystem::GatesProcessingSystem(entityx::EntityX &enX, ContainersContainer &container)
    :enX(enX), container(container), result_size(0)
{
    enX.events.subscribe<ResetSequence>(*this);
}

void GatesProcessingSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, double dt)
{
    Ports::Handle ports;
    Algorithm::Handle algorithm;
    Memory::Handle memory;
    CircuitTypeIndex::Handle id;


    int i=0;

    for(auto en: sequence) // entities.entities_with_components(ports, algorithm, memory,id))
    {
        if(i>=result_size)
            break;
        ++i;

        ports = en.component<Ports>();
        algorithm = en.component<Algorithm>();
        memory = en.component<Memory>();

        if(ports->joined_in_count != ports->ports_in_count)
            continue;

        int algorithm_size = algorithm->ref.size();

        std::vector <PortIN> &ports_in = container.ports.get_ports_in(ports->index);
        std::vector <PortOUT> &ports_out = container.ports.get_ports_out(ports->index);
        std::vector <uint8_t> &memory_vec = container.memory.get_mem(memory->index);
        uint8_t carry_temp1 = 0, carry_temp2 = 0;
        uint8_t carry = false;
        uint32_t temp32 = 0;
        uint32_t adr32 = 0;

        for(int i=0; i<algorithm_size; ++i)
        {
            uint8_t inst = algorithm->ref[i];
            uint8_t* arg[3];
            uint8_t temp_arg[3] = {0,0,0};
            for(int j=0; j<3; ++j)
            {
                ++i;
                switch (algorithm->ref[i])
                {
                case CONST:
                    temp_arg[j] = algorithm->ref[i+1];
                    arg[j] = &temp_arg[j];
                    break;
                case IN:
                    arg[j] = &(ports_in[algorithm->ref[i+1]].source->data);
                    break;
                case OUT:
                    arg[j] = &(ports_out[algorithm->ref[i+1]].data);
                    break;
                case MEM:
                    arg[j] = &(memory_vec[algorithm->ref[i+1]]);
                    break;

                case MEM_ADR_MEM:
                    temp_arg[j] = memory_vec[algorithm->ref[i+1]];
                    arg[j] = &(memory_vec[temp_arg[j]]);
                    break;
                case MEM_ADR_IN:
                    temp_arg[j] = ports_in[algorithm->ref[i+1]].source->data;
                    arg[j] = &(memory_vec[temp_arg[j]]);
                    break;
                case OUT_ADR_MEM:
                    temp_arg[j] = memory_vec[algorithm->ref[i+1]];
                    arg[j] = &(ports_out[temp_arg[j]].data);
                    break;
                case OUT_ADR_IN:
                    temp_arg[j] = ports_in[algorithm->ref[i+1]].source->data;
                    arg[j] = &(ports_out[temp_arg[j]].data);
                    break;
                case IN_ADR_MEM:
                    temp_arg[j] = memory_vec[algorithm->ref[i+1]];
                    arg[j] = &(ports_in[temp_arg[j]].source->data);
                    break;
                case IN_ADR_IN:
                    temp_arg[j] = ports_in[algorithm->ref[i+1]].source->data;
                    arg[j] = &(ports_in[temp_arg[j]].source->data);
                    break;
                case CARRY_REG:
                    arg[j] = &carry;
                    break;
                case ADR32_MEM:
                    arg[j] = &(memory_vec.at(adr32));
                    //std::cout<<"adr32: "<<memory_vec.at(adr32)<<std::endl;
                    break;
                default:
                    arg[j] = &temp_arg[j];
                    break;
                }
                ++i;
            }

            switch (inst) {
            case NOT:
                *arg[2] = ~(*arg[0]);
                break;
            case OR:
                *arg[2] = *arg[0] | *arg[1];
                break;
            case XOR:
                *arg[2] = *arg[0] ^ *arg[1];
                break;
            case NOR:
                *arg[2] = *arg[0] | *arg[1];
                *arg[2] = ~(*arg[2]);
                break;
            case AND:
                *arg[2] = *arg[0] & *arg[1];
                break;
            case ADD:
                *arg[2] = temp32 = *arg[0] + *arg[1];
                carry = (temp32 > 255)*255;
                break;
            case SUB:
                carry_temp1 =*arg[0];
                carry_temp2 =*arg[1];
                *arg[2] = *arg[0] - *arg[1];
                carry = (carry_temp2 > carry_temp1)*255;
                break;
            case MOV:
                *arg[2] = *arg[0];
                break;
            case EQU:
                *arg[2] = (*arg[0] == *arg[1]);
                *arg[2] *= 255;
                break;
            case LST:
                *arg[2] = (*arg[0] < *arg[1]);
                *arg[2] *= 255;
                break;
            case ADR32:
                temp32 = *arg[2];
                adr32 &= ~(255<<(8*(*arg[0]))); // maskowanie bajtu arg1
                adr32 |= (temp32<<(8*(*arg[0])));   // wpisanie do tego bajtu
                break;
            default:
                break;
            }
        }
    }
}

int GatesProcessingSystem::get_sequence(std::vector<entityx::Entity> &v, entityx::EntityManager &manager, ContainersContainer &cont)
{
    v.resize(manager.size());
    int result_size=0;
    int queue_front =0;

    Ports::Handle ports_handle;
    Wire::Handle wire_handle;

    std::vector <entityx::Entity> entity_queue;
    int occurence_priority = 0;
    std::map <entityx::Entity, std::pair<int,int> > occurences;

    StartPoint::Handle startpoint;
    for(auto en: manager.entities_with_components(startpoint))
        entity_queue.push_back(en);

    while(true)
    {
        if(!(entity_queue.size() > queue_front))
        {
            int cur_priority = INT32_MAX;
            entityx::Entity en_force;
            bool forced = false;
            for(auto &p : occurences)
            {
                auto p_en = p.first;
                ports_handle = p_en.component<Ports>();
                if(ports_handle->joined_in_count == ports_handle->ports_in_count &&
                   p.second.first < ports_handle->ports_in_count && p.second.second < cur_priority)
                {
                    forced = true;
                    cur_priority = p.second.second;
                    en_force = p.first;
                }

            }

            if(forced)
            {
                CircuitTypeIndex::Handle index = en_force.component<CircuitTypeIndex>();
                entity_queue.push_back(en_force);
            }
            else
                break;
        }

        entityx::Entity cur_entity = entity_queue[queue_front++];
        ports_handle = cur_entity.component<Ports>();

        if(ports_handle->joined_in_count != ports_handle->ports_in_count)
            continue;

        auto & ports_out = cont.ports.get_ports_out(ports_handle->index);
        //auto & ports_in = cont.ports.get_ports_in(ports_handle->index);

        if(occurences.find(cur_entity) == occurences.end())
            occurences[cur_entity] = std::make_pair( 0, ++occurence_priority);
        int cur_occ = ++occurences[cur_entity].first;

        if(cur_occ < ports_handle->ports_in_count)
            continue;
        else if (cur_occ > ports_handle->ports_in_count && !cur_entity.has_component<StartPoint>())
            continue;

        if(cur_entity.has_component<Algorithm>())
            v[result_size++] = cur_entity;

        for(PortOUT& port_out: ports_out)
        {
            if(!port_out.joined)
                continue;
            wire_handle =  port_out.wire.component<Wire>();
            entity_queue.push_back(wire_handle->entity_in);
        }
    }

    return result_size;
}

void GatesProcessingSystem::receive(const ResetSequence &ev)
{
    std::cout<<"reset sequence"<<std::endl;
    result_size = get_sequence(sequence,enX.entities, container);
}
