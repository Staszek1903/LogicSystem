#ifndef ENUMCONTAINER_H
#define ENUMCONTAINER_H

#include <vector>
#include <oopgui/configwindow.h>

struct WindowCreateContainer
{
    std::vector<ConfigWindowBase * (*)()> creates;
};

#endif // ENUMCONTAINER_H
