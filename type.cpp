#include "type.hh"

namespace IPL
{
    std::ostream &operator<<(std::ostream &strm, Category category)
    {
        switch (category)
        {
        case Category::Variable:
            strm << "Variable";
            break;
        case Category::Const:
            strm << "Const";
            break;
        case Category::Function:
            strm << "Function";
            break;
        case Category::Struct:
            strm << "Struct";
            break;
        }
        return strm;
    }
    std::ostream &operator<<(std::ostream &strm, Scope scope)
    {
        switch (scope)
        {
        case Scope::Global:
            strm << "Global";
            break;
        case Scope::Local:
            strm << "Local";
            break;
        case Scope::Param:
            strm << "Param";
            break;
        }
        return strm;
    }
    std::ostream &operator<<(std::ostream &strm, BaseType base_type)
    {
        switch (base_type)
        {
        case BaseType::Null:
            strm << "Null";
            break;
        case BaseType::Void:
            strm << "Void";
            break;
        case BaseType::Int:
            strm << "Int";
            break;
        case BaseType::Struct:
            strm << "Struct";
            break;
        case BaseType::Array:
            strm << "Array";
            break;
        case BaseType::Pointer:
            strm << "Pointer";
            break;
        }
        return strm;
    }
    std::ostream &operator<<(std::ostream &strm, Type* type)
    {
        switch (type->get_base_type())
        {
        case BaseType::Null:
            strm << "Null";
            break;
        case BaseType::Void:
            strm << "Void";
            break;
        case BaseType::Int:
            strm << "Int";
            break;
        case BaseType::Struct:
            strm << type->get_name();
            break;
        case BaseType::Array:
            strm << "Array";
            break;
        case BaseType::Pointer:
            strm << "Pointer";
            break;
        default:
            strm << "Unknown";
            break;
        }
        return strm;
    }

    Type* generate_type(Type* base_type, int stars, std::vector<int> arrays){
        Type* type = base_type;
        for(int i = 0; i < stars; i++){
            type = new Type(BaseType::Pointer, "", type);
            type->set_size(4);
        }
        for(unsigned int i = 0; i < arrays.size(); i++){
            int size = type->get_size()*arrays[i];
            type = new Type(BaseType::Array, "", type, arrays[i]);
            type->set_size(size);
        }
        return type;
    }
}
