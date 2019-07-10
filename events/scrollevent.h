#ifndef SCROLLEVENT_H
#define SCROLLEVENT_H

struct ScrollEvent
{
    ScrollEvent(bool h, float n)
        :horizontal(h), new_pos(n){}
    bool horizontal;
    float new_pos;  //0-1
};

#endif // SCROLLEVENT_H
