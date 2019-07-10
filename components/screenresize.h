#ifndef SCREENRESIZE_H
#define SCREENRESIZE_H

#include <entityx/entityx.h>

struct ScreenResize: public entityx::Component<ScreenResize>
{
    ScreenResize(int w = 0, int h =0)
        :prev_width(w), prev_height(h){}
    int prev_width, prev_height;
};

#endif // SCREENRESIZE_H
