#ifndef DISP7SEG_H
#define DISP7SEG_H

#include <entityx/entityx.h>
#include <containers/portscontainer.h>

struct Disp7Seg: public entityx::Component<Disp7Seg>
{
    Disp7Seg(PortIN & port)
        :port(port){}
    PortIN &port;
};

#endif // DISP7SEG_H
