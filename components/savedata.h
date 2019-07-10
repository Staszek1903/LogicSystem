#ifndef SAVEDATA_H
#define SAVEDATA_H

#include <entityx/entityx.h>
#include <containers/containerscontainer.h>
#include <string>

struct SaveData : public entityx::Component<SaveData>
{
    SaveData(void (*func)(std::string, entityx::EntityManager&, ContainersContainer&), entityx::Entity projList)
        :func(func), projList(projList){}
    void (*func)(std::string, entityx::EntityManager&, ContainersContainer&);
    entityx::Entity projList;
};

#endif // SAVEDATA_H
