#ifndef CONTAINERSCONTAINER_H
#define CONTAINERSCONTAINER_H

#include <containers/drawcontainer.h>
#include <containers/portscontainer.h>
#include <containers/windowcreatecontainer.h>
#include <containers/additionalcontainer.h>
#include <containers/instructioncontainer.h>
#include <containers/memorycontainer.h>
#include <containers/namescontainer.h>
#include <containers/portnamescontainer.h>

struct ContainersContainer
{
    DrawContainer draw;
    PortsContainer ports;
    WindowCreateContainer win_create;
    AdditionalContainer additional;
    InstructionContainer instruction;
    MemoryContainer memory;
    NamesContainer names;
    PortNamesContainer port_names;
};

#endif // CONTAINERSCONTAINER_H
