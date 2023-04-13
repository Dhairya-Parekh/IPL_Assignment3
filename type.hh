#ifndef TYPE_HH
#define TYPE_HH

#include <map>
#include <string>
#include <iostream>
namespace IPL
{
    enum class Scope
    {
        Global=0,
        Local=1,
        Param=2
    };
    enum class Category
    {
        Variable,
        Const,
        Function,
        Struct
    };
    enum class BaseType
    {
        Null,
        Void,
        Int,
        Struct,
        Array,
        Pointer
    };
    class Type
    {
    private:
        BaseType base_type;
        std::string name;
        Type *sub_type;
        int size;
    public:
        Type(BaseType base_type, std::string name, Type *sub_type, int size) : base_type(base_type), name(name), sub_type(sub_type), size(size) {}
        Type(BaseType base_type, std::string name, Type *sub_type) : base_type(base_type), name(name), sub_type(sub_type) {}
        Type(BaseType base_type, std::string name) : base_type(base_type), name(name) {}
        Type(BaseType base_type) : base_type(base_type) {}
        Type() : base_type(BaseType::Null) {}
        BaseType get_base_type() const { return base_type; }
        std::string get_name() const { return name; }
        Type *get_sub_type() const { return sub_type; }
        int get_size() const { return size; }
        void set_base_type(BaseType base_type) { this->base_type = base_type; }
        void set_name(std::string name) { this->name = name; }
        void set_sub_type(Type *sub_type) { this->sub_type = sub_type; }
        void set_size(int size) { this->size = size; }
        
    };
    std::ostream &operator<<(std::ostream &strm, Category category);
    std::ostream &operator<<(std::ostream &strm, Scope scope);
    std::ostream &operator<<(std::ostream &strm, BaseType base_type);
    std::ostream &operator<<(std::ostream &strm, Type* type);
}
#endif