#ifndef NAMESCONTAINER_H
#define NAMESCONTAINER_H

#include <map>
#include <string>

class NamesContainer
{
    std::map <int, std::string> names;
    std::map <std::string, int> indexes;
public:
    NamesContainer();
    void new_name(std::string name);
    std::string & get_name(int index);
    int get_index(std::string & name);
};

#endif // NAMESCONTAINER_H
