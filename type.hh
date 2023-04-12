#ifndef TYPE_HH
#define TYPE_HH

#include <map>
#include <string>
namespace IPL
{
    enum class typeExp
    {
        empty_astnode,
        seq_astnode,
        assignS_astnode,
        if_astnode,
        while_astnode,
        for_astnode,
        return_astnode,
        proccall_astnode,
        identifier_astnode,
        arrayref_astnode,
        member_astnode,
        arrow_astnode,
        op_binary_astnode,
        op_unary_astnode,
        assignE_astnode,
        funcall_astnode,
        int_astnode,
        float_astnode,
        string_astnode
    };
    enum class op_binary_type
    {
        OR_OP,
        AND_OP,
        EQ_OP_INT,
        NE_OP_INT,
        LT_OP_INT,
        LE_OP_INT,
        GT_OP_INT,
        GE_OP_INT,
        EQ_OP_FLOAT,
        NE_OP_FLOAT,
        LT_OP_FLOAT,
        LE_OP_FLOAT,
        GT_OP_FLOAT,
        GE_OP_FLOAT,
        PLUS_INT,
        MINUS_INT,
        MULT_INT,
        DIV_INT,
        PLUS_FLOAT,
        MINUS_FLOAT,
        MULT_FLOAT,
        DIV_FLOAT
    };
    enum class op_unary_type
    {
        TO_INT,
        TO_FLOAT,
        UMINUS,
        NOT,
        ADDRESS,
        DEREF,
        PP
    };
    const std::map<op_binary_type, std::string> op_binary_map = {
        {op_binary_type::OR_OP, "OR_OP"},
        {op_binary_type::AND_OP, "AND_OP"},
        {op_binary_type::EQ_OP_INT, "EQ_OP_INT"},
        {op_binary_type::NE_OP_INT, "NE_OP_INT"},
        {op_binary_type::LT_OP_INT, "LT_OP_INT"},
        {op_binary_type::LE_OP_INT, "LE_OP_INT"},
        {op_binary_type::GT_OP_INT, "GT_OP_INT"},
        {op_binary_type::GE_OP_INT, "GE_OP_INT"},
        {op_binary_type::EQ_OP_FLOAT, "EQ_OP_FLOAT"},
        {op_binary_type::NE_OP_FLOAT, "NE_OP_FLOAT"},
        {op_binary_type::LT_OP_FLOAT, "LT_OP_FLOAT"},
        {op_binary_type::LE_OP_FLOAT, "LE_OP_FLOAT"},
        {op_binary_type::GT_OP_FLOAT, "GT_OP_FLOAT"},
        {op_binary_type::GE_OP_FLOAT, "GE_OP_FLOAT"},
        {op_binary_type::PLUS_INT, "PLUS_INT"},
        {op_binary_type::MINUS_INT, "MINUS_INT"},
        {op_binary_type::MULT_INT, "MULT_INT"},
        {op_binary_type::DIV_INT, "DIV_INT"},
        {op_binary_type::PLUS_FLOAT, "PLUS_FLOAT"},
        {op_binary_type::MINUS_FLOAT, "MINUS_FLOAT"},
        {op_binary_type::MULT_FLOAT, "MULT_FLOAT"},
        {op_binary_type::DIV_FLOAT, "DIV_FLOAT"}
    };
    const std::map<op_unary_type, std::string> op_unary_map = {
        {op_unary_type::TO_INT, "TO_INT"},
        {op_unary_type::TO_FLOAT, "TO_FLOAT"},
        {op_unary_type::UMINUS, "UMINUS"},
        {op_unary_type::NOT, "NOT"},
        {op_unary_type::ADDRESS, "ADDRESS"},
        {op_unary_type::DEREF, "DEREF"},
        {op_unary_type::PP, "PP"}
    };
    enum class SymbolType
    {
        Var,
        Const,
        Func,
        Struct
    };
    enum class Scope
    {
        Global,
        Local,
        Param
    };

    
    
}
#endif