#ifndef PORTSCONTAINER_H
#define PORTSCONTAINER_H

#include <iostream>
#include <vector>
#include <utility>
#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>
#include <components/port.h>


struct PortNames
{
    std::map<std::string, int> in;
    std::map<std::string, int> out;
    std::map<std::string, int> mem;
};

struct PortInf
{
    PortInf(int size, sf::Vector2f pos, bool out)
        :pos(pos), size(size), out(out){}
    sf::Vector2f pos;
    int size;
    bool out;
};


struct PortOUT
{
    PortOUT()
        :data(0), mask(0), size(0), pos(sf::Vector2f(0,0)), joined(false){}

    uint8_t data,
    mask,
    size;
    sf::Vector2f pos;
    entityx::Entity wire;
    bool joined;
};

struct PortIN
{
    PortIN()
        :joined(false), size(0), pos(sf::Vector2f(0,0)){}

    PortOUT * source;
    bool joined;
    uint8_t size;
    sf::Vector2f pos;
    entityx::Entity wire;
};


class PortsContainer
{
public:
    std::vector <std::vector <PortInf> > meta_data;
    std::vector < std::pair < entityx::Entity,std::vector <PortIN> > > ports_in;
    std::vector < std::pair < entityx::Entity,std::vector <PortOUT> > > ports_out;

    PortsContainer();
    void add(std::vector <PortInf> v);
    int create(int index, entityx::Entity en);
    void destroy(int index);
    std::vector <PortIN> & get_ports_in(int index);
    std::vector <PortOUT> & get_ports_out(int index);
};

#endif // PORTSCONTAINER_H
