#ifndef YESNOWINDOW_H
#define YESNOWINDOW_H

#include <entityx/entityx.h>
#include <containers/containerscontainer.h>

struct YesNoWindow : entityx::Component<YesNoWindow>
{
    YesNoWindow(std::string & message, void (*result_func)(entityx::EntityX &, ContainersContainer &))
        :message(message), result_func(result_func){}
    std::string message;
    void (*result_func)(entityx::EntityX &, ContainersContainer &);
};
#endif // YESNOWINDOW_H
