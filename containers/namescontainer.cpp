#include "namescontainer.h"

NamesContainer::NamesContainer()
{

}

void NamesContainer::new_name(std::string name)
{
    int index = names.size();
    names[index] = name;
    indexes[name] = index;
}

std::string &NamesContainer::get_name(int index)
{
    return names[index];
}

int NamesContainer::get_index(std::string &name)
{
    return indexes[name];
}
