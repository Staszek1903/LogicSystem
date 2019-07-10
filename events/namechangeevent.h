#ifndef NAMECHANGEEVENT_H
#define NAMECHANGEEVENT_H

#include <string>

struct NameChangeEvent
{
    NameChangeEvent(std::string name)
        :name(name){}
    std::string name;
};

#endif // NAMECHANGEEVENT_H
