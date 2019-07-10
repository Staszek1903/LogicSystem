#ifndef DIRREADER_H
#define DIRREADER_H

#include <vector>
#include <string>
#include <dirent.h>
#include <iostream>

class DirReader
{
public:
    DirReader();
    std::vector<std::string> operator()(std::string);
};

#endif // DIRREADER_H
