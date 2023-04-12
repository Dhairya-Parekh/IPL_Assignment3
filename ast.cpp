#include "ast.hh"
#include <iostream>
namespace IPL
{
    // abstract_astnode Class Methods
    
    // expression_astnode Class Methods
    void expression_astnode::set_type(std::string type)
    {
        type_ = type;
    }
    std::string expression_astnode::get_type()
    {
        return type_;
    }
    std::string expression_astnode::get_dereferenced_type()
    {
        std::string str = type_;
        size_t star_pos = str.find("*"); // find the first occurrence of "*"
        size_t int_pos = str.find("[");  // find the first occurrence of "["
        size_t brc_pos = str.find("(");  // find the first occurrence of "("
        
        if (brc_pos != std::string::npos)
        {
            size_t brc_end_pos = str.find(")", brc_pos); // find the corresponding ")"
            if (brc_end_pos != std::string::npos)
            {
                str.erase(brc_pos, brc_end_pos - brc_pos + 1); // remove the first occurrence of "(...)"
            }
        }
        else if (int_pos != std::string::npos)
        {
            size_t int_end_pos = str.find("]", int_pos); // find the corresponding "]"
            if (int_end_pos != std::string::npos)
            {
                str.erase(int_pos, int_end_pos - int_pos + 1); // remove the first occurrence of "[INT]"
            }
        } 
        else if (star_pos != std::string::npos)
        {
            str.erase(star_pos, 1); // remove the first occurrence of "*"
        }
        else
        {
            str = ""; // return an empty string if no pattern is found
        }
        return str;
    }
    void expression_astnode::set_lvalue(bool is_lvalue)
    {
        is_lvalue_ = is_lvalue;
    }
    bool expression_astnode::has_lvalue()
    {
        return is_lvalue_;
    }
    int expression_astnode::get_cvalue()
    {
        return cvalue_;
    }
    void expression_astnode::set_cvalue(int cvalue)
    {
        cvalue_ = cvalue;
    }
    // empty_astnode Class Methods
    empty_astnode::empty_astnode()
    {
        astnode_type = typeExp::empty_astnode;
    }
    void empty_astnode::print(int blanks)
    {
        std::cout << std::string(blanks, ' ') << "\"empty\"" << std::endl;
    }

    // seq_astnode Class Methods
    seq_astnode::seq_astnode()
    {
        astnode_type = typeExp::seq_astnode;
    }
    void seq_astnode::print(int blanks)
    {
        std::cout << "{" << std::endl;
        std::cout << std::string(blanks, ' ') << "\"seq\": [" << std::endl;
        for (unsigned int i = 0; i < statements_.size(); i++)
        {
            statements_[i]->print(blanks + 8);
            if (i != statements_.size() - 1)
            {
                std::cout << ",";
            }
            std::cout << std::endl;
        }
        std::cout << std::string(blanks, ' ') << "]" << std::endl;
        std::cout << "}" << std::endl;
    }
    void seq_astnode::add_statement(statement_astnode *statement)
    {
        statements_.push_back(statement);
    }

    // assignS_astnode Class Methods
    assignS_astnode::assignS_astnode(expression_astnode *expression1, expression_astnode *expression2)
    {
        astnode_type = typeExp::assignS_astnode;
        expression1_ = expression1;
        expression2_ = expression2;
    }
    void assignS_astnode::print(int blanks)
    {
        std::cout << "{" << std::endl;
        std::cout << std::string(blanks, ' ') << "\"assignS\": {" << std::endl;
        std::cout << std::string(blanks + 4, ' ') << "\"left\": " << std::endl;
        expression1_->print(blanks + 4);
        std::cout << std::string(blanks + 4, ' ') << "," << std::endl;
        std::cout << std::string(blanks + 4, ' ') << "\"right\":" << std::endl;
        expression2_->print(blanks + 4);
        std::cout << std::string(blanks, ' ') << "}" << std::endl;
        std::cout << "}" << std::endl;
    }

    // if_astnode Class Methods
    if_astnode::if_astnode(expression_astnode *Condition, statement_astnode *Then, statement_astnode *Else)
    {
        astnode_type = typeExp::if_astnode;
        condition_ = Condition;
        then_ = Then;
        else_ = Else;
    }
    void if_astnode::print(int blanks)
    {
        std::cout << "{" << std::endl;
        std::cout << std::string(blanks, ' ') << "\"if\": {" << std::endl;
        std::cout << std::string(blanks + 4, ' ') << "\"cond\": " << std::endl;
        condition_->print(blanks + 4);
        std::cout << std::string(blanks + 4, ' ') << "," << std::endl;
        std::cout << std::string(blanks + 4, ' ') << "\"then\": " << std::endl;
        then_->print(blanks + 4);
        std::cout << std::string(blanks + 4, ' ') << "," << std::endl;
        std::cout << std::string(blanks + 4, ' ') << "\"else\": " << std::endl;
        else_->print(blanks + 4);
        std::cout << std::string(blanks, ' ') << "}" << std::endl;
        std::cout << "}" << std::endl;
    }

    // while_astnode Class Methods
    while_astnode::while_astnode(expression_astnode *condition, statement_astnode *body)
    {
        astnode_type = typeExp::while_astnode;
        condition_ = condition;
        body_ = body;
    }
    void while_astnode::print(int blanks)
    {
        std::cout << "{" << std::endl;
        std::cout << std::string(blanks, ' ') << "\"while\": {" << std::endl;
        std::cout << std::string(blanks + 4, ' ') << "\"cond\": " << std::endl;
        condition_->print(blanks + 4);
        std::cout << std::string(blanks + 4, ' ') << "," << std::endl;
        std::cout << std::string(blanks + 4, ' ') << "\"stmt\": " << std::endl;
        body_->print(blanks + 4);
        std::cout << std::string(blanks, ' ') << "}" << std::endl;
        std::cout << "}" << std::endl;
    }

    // for_astnode Class Methods
    for_astnode::for_astnode(expression_astnode *init, expression_astnode *condition, expression_astnode *update, statement_astnode *body)
    {
        astnode_type = typeExp::for_astnode;
        init_ = init;
        condition_ = condition;
        update_ = update;
        body_ = body;
    }
    void for_astnode::print(int blanks)
    {
        std::cout << "{" << std::endl;
        std::cout << std::string(blanks, ' ') << "\"for\": {" << std::endl;
        std::cout << std::string(blanks + 4, ' ') << "\"init\": " << std::endl;
        init_->print(blanks + 4);
        std::cout << std::string(blanks + 4, ' ') << "," << std::endl;
        std::cout << std::string(blanks + 4, ' ') << "\"guard\": " << std::endl;
        condition_->print(blanks + 4);
        std::cout << std::string(blanks + 4, ' ') << "," << std::endl;
        std::cout << std::string(blanks + 4, ' ') << "\"step\": " << std::endl;
        update_->print(blanks + 4);
        std::cout << std::string(blanks + 4, ' ') << "," << std::endl;
        std::cout << std::string(blanks + 4, ' ') << "\"body\": " << std::endl;
        body_->print(blanks + 4);
        std::cout << std::string(blanks, ' ') << "}" << std::endl;
        std::cout << "}" << std::endl;
    }

    // return_astnode Class Methods
    return_astnode::return_astnode(expression_astnode *expression)
    {
        astnode_type = typeExp::return_astnode;
        expression_ = expression;
    }
    void return_astnode::print(int blanks)
    {
        std::cout << "{" << std::endl;
        std::cout << std::string(blanks, ' ') << "\"return\": " << std::endl;
        expression_->print(blanks + 4);
        std::cout << "}" << std::endl;
    }

    // proccall_astnode Class Methods
    proccall_astnode::proccall_astnode(std::string name)
    {
        astnode_type = typeExp::proccall_astnode;
        name_ = name;
        arguments_ = std::vector<expression_astnode *>();
    }
    void proccall_astnode::print(int blanks)
    {
        std::cout << "{" << std::endl;
        std::cout << std::string(blanks, ' ') << "\"proccall\": {" << std::endl;
        std::cout << std::string(blanks + 4, ' ') << "\"fname\": {" << std::endl;
        std::cout << std::string(blanks + 8, ' ') << "\"identifier\": \"" << name_ << "\"" << std::endl;
        std::cout << std::string(blanks + 4, ' ') << "}," << std::endl;
        std::cout << std::string(blanks + 4, ' ') << "\"params\": [" << std::endl;
        for (unsigned int i = 0; i < arguments_.size(); i++)
        {
            std::cout << std::string(blanks + 8, ' ')  << std::endl;
            arguments_[i]->print(blanks + 12);
            if (i != arguments_.size() - 1)
            {
                std::cout << ",";
            }
            std::cout << std::endl;
        }
        std::cout << std::string(blanks + 4, ' ') << "]" << std::endl;
        std::cout << std::string(blanks, ' ') << "}" << std::endl;
        std::cout << "}" << std::endl;
    }
    void proccall_astnode::add_argument(expression_astnode *argument)
    {
        arguments_.push_back(argument);
    }

    // op_binary_astnode Class Methods
    op_binary_astnode::op_binary_astnode(expression_astnode *expression1, expression_astnode *expression2, enum op_binary_type op)
    {
        astnode_type = typeExp::op_binary_astnode;
        expression1_ = expression1;
        expression2_ = expression2;
        op_ = op;
    }
    void op_binary_astnode::print(int blanks)
    {
        std::cout << "{" << std::endl;
        std::cout << std::string(blanks, ' ') << "\"op_binary\": {" << std::endl;
        std::cout << std::string(blanks + 4, ' ') << "\"op\": \"" << op_binary_map.at(op_) << "\"," << std::endl;
        std::cout << std::string(blanks + 4, ' ') << "\"left\": " << std::endl;
        expression1_->print(blanks + 8);
        std::cout << "," << std::endl;
        std::cout << std::string(blanks + 4, ' ') << "\"right\": " << std::endl;
        expression2_->print(blanks + 8);
        std::cout << std::string(blanks, ' ') << "}" << std::endl;
        std::cout << "}" << std::endl;
    }

    // op_unary_astnode Class Methods
    op_unary_astnode::op_unary_astnode(expression_astnode *expression, enum op_unary_type op)
    {
        astnode_type = typeExp::op_unary_astnode;
        expression_ = expression;
        op_ = op;
    }
    void op_unary_astnode::print(int blanks)
    {
        std::cout << "{" << std::endl;
        std::cout << std::string(blanks, ' ') << "\"op_unary\": {" << std::endl;
        std::cout << std::string(blanks + 4, ' ') << "\"op\": \"" << op_unary_map.at(op_) << "\"," << std::endl;
        std::cout << std::string(blanks + 4, ' ') << "\"child\": " << std::endl;
        expression_->print(blanks + 8);
        std::cout << std::string(blanks, ' ') << "}" << std::endl;
        std::cout << "}" << std::endl;
    }

    // int_astnode Class Methods
    int_astnode::int_astnode(int value)
    {
        astnode_type = typeExp::int_astnode;
        value_ = value;
    }
    void int_astnode::print(int blanks)
    {
        std::cout << "{" << std::endl;
        std::cout << std::string(blanks, ' ') << "\"intconst\": " << value_ << std::endl;
        std::cout << "}" << std::endl;
    }

    // float_astnode Class Methods
    float_astnode::float_astnode(float value)
    {
        astnode_type = typeExp::float_astnode;
        value_ = value;
    }
    void float_astnode::print(int blanks)
    {
        std::cout << "{" << std::endl;
        std::cout << std::string(blanks, ' ') << "\"floatconst\": " << value_ << std::endl;
        std::cout << "}" << std::endl;
    }

    // string_astnode Class Methods
    string_astnode::string_astnode(std::string value)
    {
        astnode_type = typeExp::string_astnode;
        value_ = value;
    }
    void string_astnode::print(int blanks)
    {
        std::cout << "{" << std::endl;
        std::cout << std::string(blanks, ' ') << "\"stringconst\": " << value_ << std::endl;
        std::cout << "}" << std::endl;
    }

    // assignE_astnode Class Methods
    assignE_astnode::assignE_astnode(expression_astnode *expression1, expression_astnode *expression2)
    {
        astnode_type = typeExp::assignE_astnode;
        expression1_ = expression1;
        expression2_ = expression2;
    }
    void assignE_astnode::print(int blanks)
    {
        std::cout << "{" << std::endl;
        std::cout << std::string(blanks, ' ') << "\"assignE\": {" << std::endl;
        std::cout << std::string(blanks + 4, ' ') << "\"left\": " << std::endl;
        expression1_->print(blanks + 4);
        std::cout << std::string(blanks + 4, ' ') << "," << std::endl;
        std::cout << std::string(blanks + 4, ' ') << "\"right\": " << std::endl;
        expression2_->print(blanks + 4);
        std::cout << std::string(blanks, ' ') << "}" << std::endl;
        std::cout << "}" << std::endl;
    }
    expression_astnode *assignE_astnode::get_expression1()
    {
        return expression1_;
    }
    expression_astnode *assignE_astnode::get_expression2()
    {
        return expression2_;
    }
    // funcall_astnode Class Methods
    funcall_astnode::funcall_astnode(std::string name)
    {
        astnode_type = typeExp::funcall_astnode;
        name_ = name;
        arguments_ = std::vector<expression_astnode *>();
    }
    void funcall_astnode::print(int blanks)
    {
        std::cout << "{" << std::endl;
        std::cout << std::string(blanks, ' ') << "\"funcall\": {" << std::endl;
        std::cout << std::string(blanks + 4, ' ') << "\"fname\": {" << std::endl;
        std::cout << std::string(blanks + 8, ' ') << "\"identifier\": \"" << name_ << "\"" << std::endl;
        std::cout << std::string(blanks + 4, ' ') << "}," << std::endl;
        std::cout << std::string(blanks + 4, ' ') << "\"params\": [" << std::endl;
        for (unsigned int i = 0; i < arguments_.size(); i++)
        {
            arguments_[i]->print(blanks + 12);   
            if (i != arguments_.size() - 1)
            {
                std::cout << ",";
            }
            std::cout << std::endl;
        }
        std::cout << std::string(blanks + 4, ' ') << "]" << std::endl;
        std::cout << std::string(blanks, ' ') << "}" << std::endl;
        std::cout << "}" << std::endl;
    }
    void funcall_astnode::add_argument(expression_astnode *argument)
    {
        arguments_.push_back(argument);
    }

    // identifier_astnode Class Methods
    identifier_astnode::identifier_astnode(std::string name)
    {
        astnode_type = typeExp::identifier_astnode;
        name_ = name;
    }
    void identifier_astnode::print(int blanks)  
    {
        std::cout << "{" << std::endl;
        std::cout << std::string(blanks, ' ') << "\"identifier\": \"" << name_ << "\"" << std::endl;
        std::cout << "}" << std::endl;
    }

    // member_astnode Class Methods
    member_astnode::member_astnode(expression_astnode *expression, identifier_astnode *name)
    {
        astnode_type = typeExp::member_astnode;
        expression_ = expression;
        name_ = name;
    }
    void member_astnode::print(int blanks)
    {
        std::cout << "{" << std::endl;
        std::cout << std::string(blanks, ' ') << "\"member\": {" << std::endl;
        std::cout << std::string(blanks + 4, ' ') << "\"struct\": " << std::endl;
        expression_->print(blanks + 8);
        std::cout << "," << std::endl;
        std::cout << std::string(blanks + 4, ' ') << "\"field\": " << std::endl;
        name_->print(blanks + 8);
        std::cout << std::string(blanks, ' ') << "}" << std::endl;
        std::cout << "}" << std::endl;
    }

    // array_astnode Class Methods
    array_astnode::array_astnode(expression_astnode *expression1, expression_astnode *expression2)
    {
        astnode_type = typeExp::arrayref_astnode;
        expression1_ = expression1;
        expression2_ = expression2;
    }
    void array_astnode::print(int blanks)
    {
        std::cout << "{" << std::endl;
        std::cout << std::string(blanks, ' ') << "\"arrayref\": {" << std::endl;
        std::cout << std::string(blanks + 4, ' ') << "\"array\": " << std::endl;
        expression1_->print(blanks + 8);
        std::cout << std::string(blanks + 4, ' ') << "," << std::endl;
        std::cout << std::string(blanks + 4, ' ') << "\"index\": " << std::endl;
        expression2_->print(blanks + 8);
        std::cout << std::string(blanks, ' ') << "}" << std::endl;
        std::cout << "}" << std::endl;
    }

    // arrow_astnode Class Methods
    arrow_astnode::arrow_astnode(expression_astnode *expression, identifier_astnode *name)
    {
        astnode_type = typeExp::arrow_astnode;
        expression_ = expression;
        name_ = name;
    }
    void arrow_astnode::print(int blanks)
    {
        std::cout << "{" << std::endl;
        std::cout << std::string(blanks, ' ') << "\"arrow\": {" << std::endl;
        std::cout << std::string(blanks + 4, ' ') << "\"pointer\": " << std::endl;
        expression_->print(blanks + 8);
        std::cout << std::string(blanks + 4, ' ') << "," << std::endl;
        std::cout << std::string(blanks + 4, ' ') << "\"field\": " << std::endl;
        name_->print(blanks + 8);
        std::cout << std::string(blanks, ' ') << "}" << std::endl;
        std::cout << "}" << std::endl;
    }

    // Compound Statement Class Methods
    Compound_Statement::Compound_Statement()
    {
        ast_ = nullptr;
    }
    void Compound_Statement::set_ast(abstract_astnode *ast)
    {
        ast_ = ast;
    }
    abstract_astnode *Compound_Statement::get_ast()
    {
        return ast_;
    }

    // Expression_List Class Methods
    Expression_List::Expression_List()
    {
        expressions_ = std::vector<expression_astnode *>();
    }
    void Expression_List::add_expression(expression_astnode *expression)
    {
        expressions_.push_back(expression);
    }
    std::vector<expression_astnode *> Expression_List::get_expressions()
    {
        return expressions_;
    }

}