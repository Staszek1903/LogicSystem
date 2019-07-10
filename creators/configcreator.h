#ifndef CONFIGCREATOR_H
#define CONFIGCREATOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

class ConfigCreator
{
    std::map<std::string, std::vector<std::vector<std::string> > > dane;
    std::string dir;


public:
    ConfigCreator();
    void setDir(std::string dir);
    void addSection(std::string section, std::vector<std::vector<std::string> > &data);
    void create();
};

#endif // CONFIGCREATOR_H
