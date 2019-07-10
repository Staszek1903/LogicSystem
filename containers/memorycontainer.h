#ifndef MEMORYCONTAINER_H
#define MEMORYCONTAINER_H

#include <vector>
#include <iostream>
#include <entityx/entityx.h>

#include <components/memory.h>

class MemoryContainer
{
    std::vector<int> meta_data; // ilość pamieci dla każdej barmki
    std::vector<std::pair <entityx::Entity,  std::vector <uint8_t> > > mem;
public:
    MemoryContainer();
    void add(int size);
    int create(entityx::Entity en, int index);
    void destroy(int index);
    std::vector<uint8_t> & get_mem(int index);
};

#endif // MEMORYCONTAINER_H
