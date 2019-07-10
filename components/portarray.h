#ifndef PORTARRAY_H
#define PORTARRAY_H

#include <vector>
#include <iostream>

template <typename T>
struct PortIn
{
    T dane;
    T mask;
};

struct PortOut
{

};

template < int size_IN, int size_OUT>
struct PortArray
{
    PortIn port_in[size_IN];
    PortOut port_out[size_OUT];
};

#endif // PORTARRAY_H
