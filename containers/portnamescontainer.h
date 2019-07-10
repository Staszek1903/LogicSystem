#ifndef PORTNAMESCONTAINER_H
#define PORTNAMESCONTAINER_H

#include "portscontainer.h"

class PortNamesContainer
{
    struct NamePorts
    {
        std::map<int, std::string> in;
        std::map<int, std::string> out;
        std::map<int, std::string> mem;

        NamePorts();
        NamePorts(const PortNames & other);
    };

    std::vector <NamePorts > names;

public:
    enum
    {
        IN,
        OUT,
        MEM,
    };

    PortNamesContainer();

    void add_ports_info(PortNames & names);
    std::string get_name(size_t part_id, size_t port_nr, int port_type);
};

#endif // PORTNAMESCONTAINER_H
