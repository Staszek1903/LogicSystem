#ifndef LOADDATA_H
#define LOADDATA_H

#include <entityx/entityx.h>
#include <containers/containerscontainer.h>

struct LoadData: public entityx::Component<LoadData>
{
    LoadData(void (*delete_func)(entityx::EntityX &, ContainersContainer &),
             void (*load_func)(entityx::EntityX &, ContainersContainer &, std::string &), std::string &dir)
        :dir(dir), delete_func(delete_func), load_func(load_func){}

    std::string dir;
    void (*delete_func)(entityx::EntityX &, ContainersContainer &);
    void (*load_func)(entityx::EntityX &, ContainersContainer &, std::string &);
};
#endif // LOADDATA_H
