#ifndef NEWDIREVENT_H
#define NEWDIREVENT_H

struct NewDirEvent
{
    NewDirEvent(int id, std::string &dir)
        :id(id), dir(dir){}
    int id;
    std::string dir;
};

#endif // NEWDIREVENT_H
