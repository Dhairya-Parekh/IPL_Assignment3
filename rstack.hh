#ifndef RS_HH
#define RS_HH

#include <stack>
#include <string>

class RegisterStack{
private:
    std::stack<std::string> registers;
public:
    RegisterStack();
    std::string pop();
    void push(std::string reg);
    std::string top();
    int size();
    void swap();
};

#endif