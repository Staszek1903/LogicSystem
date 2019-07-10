#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <entityx/entityx.h>
#include <vector>
#include <iostream>

struct Algorithm: public entityx::Component<Algorithm>
{
    Algorithm(std::vector<uint8_t> &ref)
        :ref(ref){}
    std::vector <uint8_t> &ref;
};

#endif // ALGORITHM_H
