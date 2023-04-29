#include "type.hh"

namespace IPL
{

    // std::ostream &operator<<(std::ostream &strm, OP_Binary op)
    // {
    //     switch (op)
    //     {
    //     case OP_Binary::OP_GTE:
    //         strm << ">=";
    //         break;
    //     case OP_Binary::OP_LTE:
    //         strm << "<=";
    //         break;
    //     case OP_Binary::OP_EQ:
    //         strm << "==";
    //         break;
    //     case OP_Binary::OP_NEQ:
    //         strm << "!=";
    //         break;
    //     case OP_Binary::OP_AND:
    //         strm << "&&";
    //         break;
    //     case OP_Binary::OP_OR:
    //         strm << "||";
    //         break;
    //     case OP_Binary::OP_GT:
    //         strm << ">";
    //         break;
    //     case OP_Binary::OP_LT:
    //         strm << "<";
    //         break;
    //     case OP_Binary::OP_ADD:
    //         strm << "+";
    //         break;
    //     case OP_Binary::OP_SUB:
    //         strm << "-";
    //         break;
    //     case OP_Binary::OP_MUL:
    //         strm << "*";
    //         break;
    //     case OP_Binary::OP_DIV:
    //         strm << "/";
    //         break;
    //     }
    //     return strm;
    // }
    // std::ostream &operator<<(std::ostream &strm, OP_Unary op)
    // {
    //     switch (op)
    //     {
    //     case OP_Unary::OP_INC:
    //         strm << "++";
    //         break;
    //     case OP_Unary::OP_NOT:
    //         strm << "!";
    //         break;
    //     case OP_Unary::OP_ADDR:
    //         strm << "&";
    //         break;
    //     case OP_Unary::OP_MUL:
    //         strm << "*";
    //         break;
    //     case OP_Unary::OP_SUB:
    //         strm << "-";
    //         break;
    //     }
    //     return strm;
    // }
    // std::ostream &operator<<(std::ostream &strm, Category category)
    // {
    //     switch (category)
    //     {
    //     case Category::Variable:
    //         strm << "Variable";
    //         break;
    //     case Category::Const:
    //         strm << "Const";
    //         break;
    //     case Category::Function:
    //         strm << "Function";
    //         break;
    //     case Category::Struct:
    //         strm << "Struct";
    //         break;
    //     }
    //     return strm;
    // }
    // std::ostream &operator<<(std::ostream &strm, Scope scope)
    // {
    //     switch (scope)
    //     {
    //     case Scope::Global:
    //         strm << "Global";
    //         break;
    //     case Scope::Local:
    //         strm << "Local";
    //         break;
    //     case Scope::Param:
    //         strm << "Param";
    //         break;
    //     }
    //     return strm;
    // }
    // std::ostream &operator<<(std::ostream &strm, BaseType base_type)
    // {
    //     switch (base_type)
    //     {
    //     case BaseType::Null:
    //         strm << "Null";
    //         break;
    //     case BaseType::Void:
    //         strm << "Void";
    //         break;
    //     case BaseType::Int:
    //         strm << "Int";
    //         break;
    //     case BaseType::Struct:
    //         strm << "Struct";
    //         break;
    //     case BaseType::Array:
    //         strm << "Array";
    //         break;
    //     case BaseType::Pointer:
    //         strm << "Pointer";
    //         break;
    //     }
    //     return strm;
    // }
    // std::ostream &operator<<(std::ostream &strm, Type* type)
    // {
    //     switch (type->get_base_type())
    //     {
    //     case BaseType::Null:
    //         strm << "Null";
    //         break;
    //     case BaseType::Void:
    //         strm << "Void";
    //         break;
    //     case BaseType::Int:
    //         strm << "Int";
    //         break;
    //     case BaseType::Struct:
    //         strm << type->get_name();
    //         break;
    //     case BaseType::Array:
    //         strm << "Array";
    //         break;
    //     case BaseType::Pointer:
    //         strm << "Pointer";
    //         break;
    //     default:
    //         strm << "Unknown";
    //         break;
    //     }
    //     return strm;
    // }
    // std::ostream &operator<<(std::ostream &strm, Address *address)
    // {
    //     if(address->get_base() == "ebp")
    //         strm << address->get_offset() << "(%ebp)";
    //     else if(address->get_base() == "esp")
    //         strm << address->get_offset() << "(%esp)";
    //     else
    //         strm << address->get_offset() << "(" << address->get_base() << ")" << std::endl;
    //     return strm;
    // }

    std::string to_string(OP_Binary op)
    {
        switch (op)
        {
        case OP_Binary::OP_GTE:
            return ">=";
        case OP_Binary::OP_LTE:
            return "<=";
        case OP_Binary::OP_EQ:
            return "==";
        case OP_Binary::OP_NEQ:
            return "!=";
        case OP_Binary::OP_AND:
            return "&&";
        case OP_Binary::OP_OR:
            return "||";
        case OP_Binary::OP_GT:
            return ">";
        case OP_Binary::OP_LT:
            return "<";
        case OP_Binary::OP_ADD:
            return "+";
        case OP_Binary::OP_SUB:
            return "-";
        case OP_Binary::OP_MUL:
            return "*";
        case OP_Binary::OP_DIV:
            return "/";
        default:
            return "Unknown";
        }
    }
    std::string to_string(OP_Unary op)
    {
        switch (op)
        {
        case OP_Unary::OP_INC:
            return "++";
        case OP_Unary::OP_NOT:
            return "!";
        case OP_Unary::OP_ADDR:
            return "&";
        case OP_Unary::OP_MUL:
            return "*";
        case OP_Unary::OP_SUB:
            return "-";
        default:
            return "Unknown";
        }
    }
    std::string to_string(Category category)
    {
        switch (category)
        {
        case Category::Variable:
            return "Variable";
        case Category::Const:
            return "Const";
        case Category::Function:
            return "Function";
        case Category::Struct:
            return "Struct";
        default:
            return "Unknown";
        }
    }
    std::string to_string(Scope scope)
    {
        switch (scope)
        {
        case Scope::Global:
            return "Global";
        case Scope::Local:
            return "Local";
        case Scope::Param:
            return "Param";
        default:
            return "Unknown";
        }
    }
    std::string to_string(BaseType base_type)
    {
        switch (base_type)
        {
        case BaseType::Null:
            return "Null";
        case BaseType::Void:
            return "Void";
        case BaseType::Int:
            return "Int";
        case BaseType::Struct:
            return "Struct";
        case BaseType::Array:
            return "Array";
        case BaseType::Pointer:
            return "Pointer";
        default:
            return "Unknown";
        }
    }
    std::string to_string(Type *type)
    {
        std::string result = "";
        switch (type->get_base_type())
        {
        case BaseType::Null:
            result = "Null";
            break;
        case BaseType::Void:
            result = "Void";
            break;
        case BaseType::Int:
            result = "Int";
            break;
        case BaseType::Struct:
            result = type->get_name();
            break;
        case BaseType::Array:
            result = "Array";
            break;
        case BaseType::Pointer:
            result = "Pointer";
            break;
        default:
            result = "Unknown";
            break;
        }
        return result+std::to_string(type->get_size());
    }
    std::string to_string(Address *address)
    {
        if (address->get_base() == "ebp")
            return std::to_string(address->get_offset()) + "(%ebp)";
        else if (address->get_base() == "esp")
            return std::to_string(address->get_offset()) + "(%esp)";
        else
            return std::to_string(address->get_offset()) + "(" + address->get_base() + ")";
    }

    Type *generate_type(Type *base_type, int stars, std::vector<int> arrays)
    {
        Type *type = base_type;
        for (int i = 0; i < stars; i++)
        {
            type = new Type(BaseType::Pointer, "", type);
            type->set_size(4);
        }
        for (unsigned int i = 0; i < arrays.size(); i++)
        {
            int size = type->get_size() * arrays[i];
            type = new Type(BaseType::Array, "", type, arrays[i]);
            type->set_size(size);
        }
        return type;
    }

    Type *are_compatible(Type *type1, Type *type2, OP_Binary op)
    {
        switch (op)
        {
        case OP_Binary::OP_GTE:
        case OP_Binary::OP_LTE:
        case OP_Binary::OP_EQ:
        case OP_Binary::OP_NEQ:
        case OP_Binary::OP_AND:
        case OP_Binary::OP_OR:
        case OP_Binary::OP_GT:
        case OP_Binary::OP_LT:
            if (type1->get_base_type() == BaseType::Int && type2->get_base_type() == BaseType::Int)
                return new Type(BaseType::Int);
            else
                return nullptr;
        case OP_Binary::OP_ADD:
            if (type1->get_base_type() == BaseType::Int && type2->get_base_type() == BaseType::Int)
                return new Type(BaseType::Int);
            else if (type1->get_base_type() == BaseType::Pointer && type2->get_base_type() == BaseType::Int)
                return type1;
            else if (type1->get_base_type() == BaseType::Int && type2->get_base_type() == BaseType::Pointer)
                return type2;
            else
                return nullptr;
        case OP_Binary::OP_SUB:
            if (type1->get_base_type() == BaseType::Int && type2->get_base_type() == BaseType::Int)
                return new Type(BaseType::Int);
            else if (type1->get_base_type() == BaseType::Pointer && type2->get_base_type() == BaseType::Int)
                return type1;
            else if (type1->get_base_type() == BaseType::Pointer && type2->get_base_type() == BaseType::Pointer)
                return new Type(BaseType::Int);
            else
                return nullptr;
        case OP_Binary::OP_MUL:
        case OP_Binary::OP_DIV:
            if (type1->get_base_type() == BaseType::Int && type2->get_base_type() == BaseType::Int)
                return new Type(BaseType::Int);
            else
                return nullptr;
        default:
            return nullptr;
        }
    }

    Type *are_compatible(Type *type, OP_Unary op)
    {
        switch (op)
        {
        case OP_Unary::OP_INC:
        case OP_Unary::OP_SUB:
            if (type->get_base_type() == BaseType::Int)
                return new Type(BaseType::Int);
            else
                return nullptr;
        case OP_Unary::OP_NOT:
            if (type->get_base_type() == BaseType::Int)
                return new Type(BaseType::Int);
            else
                return nullptr;
        case OP_Unary::OP_ADDR:
            return new Type(BaseType::Pointer, "", type);
        case OP_Unary::OP_MUL:
            if (type->get_base_type() == BaseType::Pointer)
                return type->get_sub_type();
            else
                return nullptr;
        default:
            return nullptr;
        }
    }

    Type *are_compatible(Type *type1, Type *type2)
    {
        if (type1->get_base_type() == BaseType::Int && type2->get_base_type() == BaseType::Int)
        {
            return type1;
        }
        else if (type1->get_base_type() == BaseType::Void && type2->get_base_type() == BaseType::Void)
        {
            return type1;
        }
        else if (type1->get_base_type() == BaseType::Struct && type2->get_base_type() == BaseType::Struct)
        {
            if (type1->get_name() == type2->get_name())
                return type1;
            else
                return nullptr;
        }
        else if (type1->get_base_type() == BaseType::Pointer && type2->get_base_type() == BaseType::Int)
        {
            return type1;
        }
        else if (type1->get_base_type() == BaseType::Pointer && type2->get_base_type() == BaseType::Pointer)
        {
            if (are_compatible(type1->get_sub_type(), type2->get_sub_type()) != nullptr)
                return type1;
            else if (type1->get_sub_type()->get_base_type() == BaseType::Void || type2->get_sub_type()->get_base_type() == BaseType::Void)
                return type1;
            else
                return nullptr;
        }
        else if (type1->get_base_type() == BaseType::Pointer && type2->get_base_type() == BaseType::Array)
        {
            if (are_compatible(type1->get_sub_type(), type2->get_sub_type()) != nullptr)
                return type1;
            else if (type1->get_sub_type()->get_base_type() == BaseType::Void)
                return type1;
            else
                return nullptr;
        }
        else if (type1->get_base_type() == BaseType::Array && type2->get_base_type() == BaseType::Array)
        {
            if (are_compatible(type1->get_sub_type(), type2->get_sub_type()) != nullptr)
                return type1;
            else
                return nullptr;
        }
        else
            return nullptr;
    }

    int get_size_from_type(Type *type)
    {
        if (type->get_base_type() == BaseType::Int)
            return 4;
        else if (type->get_base_type() == BaseType::Pointer)
            return 4;
        else if (type->get_base_type() == BaseType::Array)
            return type->get_size()*get_size_from_type(type->get_sub_type());
        else if (type->get_base_type() == BaseType::Struct)
            return type->get_size();
        else
            return 0;
    }
}
