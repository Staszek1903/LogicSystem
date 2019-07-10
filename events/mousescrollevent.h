#ifndef MOUSESCROLLEVENT_H
#define MOUSESCROLLEVENT_H

struct MouseScrollEvent{

    MouseScrollEvent(int delta, int wheel)
        :delta(delta), wheel(wheel){}
    int delta;
    int wheel;
};

#endif // MOUSESCROLLEVENT_H
