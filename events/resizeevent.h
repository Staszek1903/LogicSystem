#ifndef RESIZEEVENT_H
#define RESIZEEVENT_H

struct ResizeEvent
{
    ResizeEvent(int w, int h)
        :width(w), height(h){}

    int width, height;
};

#endif // RESIZEEVENT_H
