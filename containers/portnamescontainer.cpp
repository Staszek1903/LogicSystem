#include "portnamescontainer.h"

PortNamesContainer::PortNamesContainer()
{

}

void PortNamesContainer::add_ports_info(PortNames &names)
{
    this->names.push_back(NamePorts(names));
}

std::string PortNamesContainer::get_name(size_t part_id, size_t port_nr, int port_type)
{

    if(part_id >= names.size())
        return "!PART ID";

    NamePorts & cur_part = names.at(part_id);
    std::map <int, std::string> * cur_type;

    switch (port_type) {
    case IN:
        cur_type = &(cur_part.in);
        break;
    case OUT:
        cur_type = &(cur_part.out);
        break;
    case MEM:
        cur_type = &(cur_part.mem);
        break;
    default:
        return "COS SIE SPIERDOLILO";
    }

    if(cur_type->find(port_nr) == cur_type->end())
        return "!PORT NR";
    return cur_type->at(port_nr);
}

PortNamesContainer::NamePorts::NamePorts()
{

}

PortNamesContainer::NamePorts::NamePorts(const PortNames &other)
{
    for(auto p : other.in)
        in[p.second] = p.first;
    for(auto p : other.out)
        out[p.second] = p.first;
    for(auto p : other.mem)
        mem[p.second] = p.first;
}
