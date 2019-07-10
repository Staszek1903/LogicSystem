#ifndef INTRUCTIONCONTAINER_H
#define INTRUCTIONCONTAINER_H

#include <vector>
#include <iostream>

enum Instructions
{
    NOT,
    OR,
    XOR,
    NOR,
    AND,
    ADD,
    SUB,
    MOV,
    EQU,
    LST,
    ADR32
};

enum Types
{
    CONST,
    MEM,
    IN,
    OUT,
    MEM_ADR_IN,
    MEM_ADR_MEM,
    IN_ADR_IN,
    IN_ADR_MEM,
    OUT_ADR_IN,
    OUT_ADR_MEM,
    GET_ADR_OUT,
    GET_ADR_IN,
    GET_ADR_MEM,
    CARRY_REG,
    ADR32_MEM
};

struct InstructionContainer
{
    std::vector <std::vector <uint8_t> > inst;
};

#endif // INTRUCTIONCONTAINER_H
