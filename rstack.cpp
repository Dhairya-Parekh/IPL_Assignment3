#include "rstack.hh"
#include <iostream>

RegisterStack::RegisterStack()
{
    registers.push("%eax");
    registers.push("%ecx");
    registers.push("%edx");
    registers.push("%ebx");
    registers.push("%esi");
    registers.push("%edi");
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

std::vector<std::string> RegisterStack::getCallerSaved()
{
    std::vector<std::string> callerSaved;
    if(registers.top() == "%eax")
    {
        return callerSaved;
    }
    else if(registers.top() == "%ecx"){
        callerSaved.push_back("%eax");
        return callerSaved;
    }
    else if(registers.top() == "%edx"){
        callerSaved.push_back("%eax");
        callerSaved.push_back("%ecx");
        return callerSaved;
    }
    else{
        callerSaved.push_back("%eax");
        callerSaved.push_back("%ecx");
        callerSaved.push_back("%edx");
        return callerSaved;
    }
}

std::vector<std::string> RegisterStack::getCalleeSaved(int label){
    int num = std::min(std::max(label-6,0),3);
    std::vector<std::string> calleeSaved;
    if(num == 0){
        return calleeSaved;
    }
    else if(num == 1){
        calleeSaved.push_back("%ebx");
        return calleeSaved;
    }
    else if(num == 2){
        calleeSaved.push_back("%ebx");
        calleeSaved.push_back("%esi");
        return calleeSaved;
    }
    else if(num == 3){
        calleeSaved.push_back("%ebx");
        calleeSaved.push_back("%esi");
        calleeSaved.push_back("%edi");
        return calleeSaved;
    }
    else{
        std::cout << "Error: Invalid number of callee saved registers" << std::endl;
        return calleeSaved;
    }
}