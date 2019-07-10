#include "configcreator.h"

ConfigCreator::ConfigCreator()
{

}

void ConfigCreator::setDir(std::string dir)
{
    this->dir = dir;
}

void ConfigCreator::addSection(std::string section, std::vector<std::vector<std::string> > &data)
{
    dane[section] = data;
}

void ConfigCreator::create()
{
    std::fstream file;
    file.open(dir, std::ios::out);

    if(!file.good())
    {
        std::cout<<"nie utworzono pliku : "<<dir<<std::endl;
        return;
    }

    for(auto &entry : dane)
    {
        std::string section = "@" + entry.first;
        file<<section<<std::endl;
        for(auto &line : entry.second)
        {
            file<<'\t';
            for(auto &word : line)
            {
                file<<" "<<word;
            }
            file<<";"<<std::endl;
        }
    }
    file.close();
    std::cout<<"file created"<<std::endl;
}
