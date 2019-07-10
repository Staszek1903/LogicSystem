#ifndef COMPONENTSLOADER_H
#define COMPONENTSLOADER_H

#include <creators/listcreator.h>

#include <loaders/configparser.h>
#include <loaders/gatesassembler.h>

#include <containers/containerscontainer.h>

#include <oopgui/bindbuttonwindow.h>
#include <oopgui/constwindow.h>
#include <oopgui/memorywindow.h>

#include <entityx/entityx.h>

#include "dirreader.h"

#include <vector>
#include <string>
#include <sstream>

class ComponentsLoader
{
    ContainersContainer & container;
    entityx::EntityManager & es;

public:
    ComponentsLoader(entityx::EntityManager & es, ContainersContainer &container);
    void load();

private:
    bool create_button(entityx::Entity list, ConfigParser &parser);
    void load_vertex_array(ConfigParser & parser);
    PortNames load_ports(ConfigParser & parser);
    bool load_config_type(ConfigParser &parser);
    void load_additional(ConfigParser & parser);
    void load_algorithm(ConfigParser & parser, PortNames & names);
    void load_memory(ConfigParser & parser, PortNames & names);

};

#endif // COMPONENTSLOADER_H
