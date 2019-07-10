#include "memorycontainer.h"

MemoryContainer::MemoryContainer()
{

}

void MemoryContainer::add(int size)
{
    meta_data.push_back(size);
    //std::cout<<"dodano memory meta_data"<<std::endl;
}

int MemoryContainer::create(entityx::Entity en, int index)
{
    std::vector<uint8_t> temp;
    temp.resize(meta_data.at(index));
    mem.push_back(std::make_pair(en, temp));
    return (mem.size()-1);
}

void MemoryContainer::destroy(int index)
{
    std::vector<std::pair<entityx::Entity, std::vector<uint8_t> > >::iterator iter = mem.begin();
    mem.erase(iter + index);

    int size = mem.size();

    Memory::Handle mH;

    for(int i=0; i<size; ++i)
    {
        mH = mem[i].first.component<Memory>();
        mH->index = i;
    }
}

std::vector<uint8_t> &MemoryContainer::get_mem(int index)
{
    return mem[index].second;
}
