#ifndef GATESASSEMBLER_H
#define GATESASSEMBLER_H

#include <vector>
#include <map>
#include <sstream>
#include <containers/instructioncontainer.h>
#include <containers/portscontainer.h>

class GatesAssembler
{
    enum Special
    {
        NONE_SPECIAL,
        BYTE_0,
        BYTE_1,
        BYTE_2,
        BYTE_3
    };

    struct InstructionTemplate
    {
        uint8_t id;
        unsigned int arguments;
    };

    PortNames &names;

    std::map <std::string, InstructionTemplate> instruction_map;

public:
    GatesAssembler(PortNames &names);
    void operator()(std::vector<uint8_t> & machine_vec,std::vector< std::vector <std::string> > & asm_vec);

private:
    std::vector <uint8_t> assemble_line(std::vector<std::string>&line);
    int get_specjal(std::string & arg);
    int get_type( std::string & arg );
    int get_adr(std::string& arg , int &type, int special);
};

#endif // GATESASSEMBLER_H
