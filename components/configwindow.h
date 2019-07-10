#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <entityx/entityx.h>
#include <oopgui/configwindow.h>

struct ConfigWindow : public entityx::Component<ConfigWindow>
{
    ConfigWindow(ConfigWindowBase * (*create)())
        :create(create){}
    ConfigWindowBase * (*create)();
};

//template <typename A>
//struct Gunwo : public entityx::Component<Gunwo<A>>
//{
//    A x;
//    int lel(){std::cout<<"lelele"<<std::endl; return 0;}
//};

#endif // CONFIGWINDOW_H
