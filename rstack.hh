#ifndef RS_HH
#define RS_HH

#include <stack>
#include <vector>
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
    std::vector<std::string> getCallerSaved();
    std::vector<std::string> getCalleeSaved(int num);
    void print();
    bool find(std::string reg);
};

#endif