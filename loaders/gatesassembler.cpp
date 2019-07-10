#include "gatesassembler.h"

GatesAssembler::GatesAssembler(PortNames &names)
    :names(names)
{
    instruction_map["not"] = {NOT, 2};
    instruction_map["or"] = {OR, 3};
    instruction_map["xor"] = {XOR, 3};
    instruction_map["nor"] = {NOR, 3};
    instruction_map["and"] = {AND, 3};
    instruction_map["add"] = {ADD, 3};
    instruction_map["sub"] = {SUB, 3};
    instruction_map["mov"] = {MOV, 2};
    instruction_map["equ"] = {EQU, 3};
    instruction_map["lst"] = {LST, 3};
    instruction_map["adr32"] = {ADR32, 2};
}

void GatesAssembler::operator()(std::vector <uint8_t> & machine_vec, std::vector < std::vector <std::string> > &asm_vec)
{
    std::cout<<"------------GATES ASSEMBLY-----------"<<std::endl;

    for(auto & line: asm_vec)
    {
        auto r = assemble_line(line);
        for( uint8_t i : r)
            machine_vec.push_back(i);
    }

    std::cout<<"result size: "<<machine_vec.size()<<std::endl<<
               "result code:";
    for(uint8_t a: machine_vec)
        std::cout<<" "<<(int) a;
    std::cout<<std::endl<<"------------ASSEMBLY END-----------"<<std::endl;
}

std::vector<uint8_t> GatesAssembler::assemble_line(std::vector<std::string> &line)
{
    std::vector <uint8_t> ret_vec;

    if(instruction_map.find(line[0]) == instruction_map.end())
    {
        std::cout<<"nieznana instrukcja ["<<line[0]<<"]"<<std::endl;
        return ret_vec;
    }

    InstructionTemplate templ = instruction_map[line[0]];

    if(line.size() -1 != templ.arguments)
    {
        std::cout<<"zla liczba argumentow w linii"<<std::endl;
        for(auto& s: line)
            std::cout<<s<<" ";
        std::cout<<std::endl;

        return ret_vec;
    }

    std::cout<<line[0]<<" "<<(int)templ.id<<std::endl;
    ret_vec.push_back(templ.id);

    line.erase(line.begin());

    std::vector<std::pair<int,int> > temp_machine;

    for(auto& arg: line)
    {
        int special = get_specjal(arg);

        int type = get_type(arg);
        if(type == -1)
            return ret_vec;

        int adr = get_adr(arg, type, special);

        temp_machine.push_back({type, adr});
        std::cout<<arg<<" "<<adr<<" "<<std::endl;
    }

    bool arg2 = (templ.arguments == 2);

    ret_vec.push_back(temp_machine[0].first);
    ret_vec.push_back(temp_machine[0].second);
    ret_vec.push_back((arg2)? 0 : temp_machine[1].first);
    ret_vec.push_back((arg2)? 0 : temp_machine[1].second);
    ret_vec.push_back((arg2)? temp_machine[1].first : temp_machine[2].first);
    ret_vec.push_back((arg2)? temp_machine[1].second : temp_machine[2].second);

    return ret_vec;
}

int GatesAssembler::get_specjal(std::string &arg)
{
    size_t open_b = arg.find('[',0);
    size_t close_b = arg.find(']',0);

    if(open_b != std::string::npos && close_b != std::string::npos)
    {
        std::cout<<"SPECJAL"<<std::endl;

        std::string inst = arg.substr(0,open_b);
        std::string adr = arg.substr(open_b +1, (close_b - open_b) -1);

        std::cout<<"ADDRESS_INST: [" <<inst<<"]"<<std::endl;
        std::cout<<"ADDRESS_ARG: "<<adr<<std::endl;


        if(inst == "byte0")
            return BYTE_0;
        else if(inst == "byte1")
            return BYTE_1;
        else if(inst == "byte2")
            return BYTE_2;
        else if(inst == "byte3")
            return BYTE_3;
         std::cout<<"NO SPECJAL"<<std::endl;
    }


    return NONE_SPECIAL;
}

int GatesAssembler::get_type(std::string &arg)
{
    if(names.mem.find(arg) != names.mem.end())
        return MEM;
    if(names.in.find(arg) != names.in.end())
        return IN;
    if(names.out.find(arg) != names.out.end())
        return OUT;

    if( arg == ".carry_reg")
        return CARRY_REG;
    if( arg == ".adr32_mem")
        return ADR32_MEM;

    bool is_const = true;
    for(auto a : arg)
        if(!std::isdigit(a))
            is_const = false;

    if(is_const)
        return CONST;

    size_t open_b = arg.find('[',0);
    size_t close_b = arg.find(']',0);

    if(open_b != std::string::npos && close_b != std::string::npos)
    {
        std::string inst = arg.substr(0,open_b);
        std::string adr = arg.substr(open_b +1, (close_b - open_b) -1);
        arg = adr;
        std::cout<<"ADDRESS_INST: [" <<inst<<"]"<<std::endl;
        std::cout<<"ADDRESS_ARG: "<<adr<<std::endl;
        int type = get_type(adr);

        if(inst == "get_adr")
        {
            switch (type) {
            case IN:
                return GET_ADR_IN;
            case OUT:
                return GET_ADR_OUT;
            case MEM:
                return GET_ADR_MEM;
            default:
                return -1;
            }
        }

        if(type == -1 || type == OUT)
        {
            std::cout<<"zła identyfikator lub niedozwolony typ"<<std::endl;
            return -1;
        }

        int in_adr = (inst == "in_adr");
        int out_adr = (inst == "out_adr");
        int mem_adr = (inst == "mem_adr");
        int in_arg = (type == IN);

        std::cout<<"in_adr: "<<in_adr<<" out_adr: "<<out_adr<<" mem_adr: "<<mem_adr<<std::endl;

        int control =in_arg | in_adr<<1 | out_adr<<2 | mem_adr<<3;
        switch (control) {
        case 0b1000:
            return MEM_ADR_MEM;
        case 0b1001:
            return MEM_ADR_IN;
        case 0b0100:
            return OUT_ADR_MEM;
        case 0b0101:
            return OUT_ADR_IN;
        case 0b0010:
            return IN_ADR_MEM;
        case 0b0011:
            return IN_ADR_IN;
        default:
            std::cout<<"BŁĄD W USTALANIU TYPU!!!!!!!!!! : "<<control<<std::endl;
        }

    }

    std::cout<<"zły argument ["<<arg<<"]"<<std::endl;
    return -1;
}

int GatesAssembler::get_adr(std::string &arg, int &type, int special)
{
    std::stringstream ss(arg);
    int adr = 0;
    switch (type) {
    case CONST:
        ss>>adr;
        arg = "const";
        break;
    case MEM:
        adr = names.mem[arg];
        arg = "mem";
        break;
    case IN :
        adr = names.in[arg];
        arg = "in";
        break;
    case OUT:
        adr = names.out[arg];
        arg = "out";
        break;
    case MEM_ADR_MEM:
        adr = names.mem[arg];
        arg = "mem_adr_mem";
        break;
    case MEM_ADR_IN:
        adr = names.in[arg];
        arg = "mem_adr_in";
        break;
    case OUT_ADR_MEM:
        adr = names.mem[arg];
        arg = "out_adr_mem";
        break;
    case OUT_ADR_IN:
        adr = names.in[arg];
        arg = "out_adr_in";
        break;
    case IN_ADR_MEM:
        adr = names.mem[arg];
        std::cout<<"tu nadaje: "<<arg<<" "<<adr<<std::endl;
        arg = "in_adr_mem";
        break;
    case IN_ADR_IN:
        adr = names.in[arg];
        arg = "in_adr_in";
        break;

    case GET_ADR_IN:
        adr = names.in[arg];
        arg = "get_adr_in";
        type = CONST;
        break;
    case GET_ADR_OUT:
        adr = names.out[arg];
        arg = "get_adr_out";
        type = CONST;
        break;
    case GET_ADR_MEM:
        adr = names.mem[arg];
        arg = "get_adr_mem";
        type = CONST;
        break;

    case CARRY_REG:
        adr = 0;
        arg = "carry reg";
        break;

    case ADR32_MEM:
        adr = 0;
        arg = "adr32 register";
        break;

    default:
        std::cout<<"NIEOKREŚLONY TYP"<<std::endl;
        return -1;
    }


    switch (special) {
    case BYTE_0:
        break;
    case BYTE_1:
        adr = adr>>8;
        break;
    case BYTE_2:
        adr = adr>>16;
        break;
    case BYTE_3:
        adr = adr>>24;
        break;
    default:
        break;
    }

    adr &= 255;

    return adr;
}
