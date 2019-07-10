#ifndef PROJECT_FUNCS_H
#define PROJECT_FUNCS_H

#include <entityx/entityx.h>

#include <containers/containerscontainer.h>

#include <components/vertexarray.h>
#include <components/wire.h>
#include <components/port.h>
#include <components/position.h>

#include <creators/circutcreator.h>
#include <creators/configcreator.h>
#include <creators/wirecreator.h>

#include <loaders/configparser.h>

#include <vector>
#include <sstream>
#include <map>

struct DATA
{
    int id;
    entityx::Entity en;
    std::string name;
    sf::Vector2f pos;
};

void deleter(entityx::EntityX & enX, ContainersContainer &cont);

void saver(std::string filename, entityx::EntityManager & manager, ContainersContainer & cont);

void loader(entityx::EntityX & en, ContainersContainer &cont, std::string & dir);

int findId(entityx::Entity en, std::vector<DATA> & data);

#endif // PROJECT_FUNCS_H
