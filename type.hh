#ifndef TYPE_HH
#define TYPE_HH

#include <map>
#include <string>
#include <iostream>
#include <vector>
namespace IPL
{
    enum class OP_Binary
    {
        OP_GTE,
        OP_LTE,
        OP_EQ,
        OP_NEQ,
        OP_AND,
        OP_OR,
        OP_GT,
        OP_LT,
        OP_ADD,
        OP_SUB,
        OP_MUL,
        OP_DIV,
    };
    enum class OP_Unary
    {
        OP_INC,
        OP_NOT,
        OP_ADDR,
        OP_MUL,
        OP_SUB
    };
    enum class Scope
    {
        Global = 0,
        Local = 1,
        Param = 2
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

    std::ostream &operator<<(std::ostream &strm, OP_Binary op);
    std::ostream &operator<<(std::ostream &strm, OP_Unary op);
    std::ostream &operator<<(std::ostream &strm, Scope scope);
    std::ostream &operator<<(std::ostream &strm, Category category);
    std::ostream &operator<<(std::ostream &strm, BaseType base_type);
    std::ostream &operator<<(std::ostream &strm, Type *type);

    Type *generate_type(Type *base_type, int stars, std::vector<int> arrays);
}
#endif