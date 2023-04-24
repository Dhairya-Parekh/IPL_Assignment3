#include "rstack.hh"
#include <iostream>

RegisterStack::RegisterStack()
{
    registers.push("%edi");
    registers.push("%esi");
    registers.push("%ebx");
    registers.push("%edx");
    registers.push("%ecx");
    registers.push("%eax");
}

std::string RegisterStack::pop()
{
    if (registers.empty())
    {
        std::cout << "Error: Register stack is empty" << std::endl;
        return "";
    }
    std::string reg = registers.top();
    registers.pop();
    return reg;
}

void RegisterStack::push(std::string reg)
{
    registers.push(reg);
}

std::string RegisterStack::top()
{
    if (registers.empty())
    {
        std::cout << "Error: Register stack is empty" << std::endl;
        return "";
    }
    return registers.top();
}

int RegisterStack::size()
{
    return registers.size();
}

void RegisterStack::swap()
{
    if (registers.size() < 2)
    {
        std::cout << "Error: Register stack has less than 2 elements" << std::endl;
        return;
    }
    std::string reg1 = registers.top();
    registers.pop();
    std::string reg2 = registers.top();
    registers.pop();
    registers.push(reg1);
    registers.push(reg2);
}