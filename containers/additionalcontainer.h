#ifndef ADDITIONALCONTAINER_H
#define ADDITIONALCONTAINER_H

#include <vector>

struct AdditionalContainer
{
    enum
    {
        NONE,
        BUTTON,
        LED,
        ALGORITHM,
        LATCH,
        PROBE,
        LABEL,
        PIN,
        DISP_7_SEG,
        START_POINT
    };

    std::vector <std::vector <int> > additional;
};

#endif // ADDITIONALCONTAINER_H
