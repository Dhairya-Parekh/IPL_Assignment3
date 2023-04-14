#include "ast.hh"
#include <iostream>
namespace IPL
{
    empty_astnode::empty_astnode()
    {
        code = "";
    }
    void empty_astnode::print()
    {
        std::cout << code << std::endl;
    }
    seq_astnode::seq_astnode()
    {
        code = "";
    }
    void seq_astnode::add_statement(statement_astnode *statement)
    {
        statements.push_back(statement);
    }
    void seq_astnode::print()
    {
        for (auto statement : statements)
        {
            statement->print();
        }
    }
    assignS_astnode::assignS_astnode(expression_astnode *assignment_expression)
    {
        this->assignment_expression = assignment_expression;
    }
    void assignS_astnode::print()
    {
        assignment_expression->print();
    }
    if_astnode::if_astnode(expression_astnode *condition, statement_astnode *if_body, statement_astnode *else_body)
    {
        this->condition = condition;
        this->if_body = if_body;
        this->else_body = else_body;
    }
    void if_astnode::print()
    {
        std::cout << "if (";
        condition->print();
        std::cout << ") {" << std::endl;
        if_body->print();
        std::cout << "}" << std::endl;
        if (else_body != NULL)
        {
            std::cout << "else {" << std::endl;
            else_body->print();
            std::cout << "}" << std::endl;
        }
    }
    while_astnode::while_astnode(expression_astnode *condition, statement_astnode *body)
    {
        this->condition = condition;
        this->body = body;
    }
    void while_astnode::print()
    {
        std::cout << "while (";
        condition->print();
        std::cout << ") {" << std::endl;
        body->print();
        std::cout << "}" << std::endl;
    }
    for_astnode::for_astnode(assignE_astnode *init, expression_astnode *condition, assignE_astnode *step, statement_astnode *body)
    {
        this->init = init;
        this->condition = condition;
        this->step = step;
        this->body = body;
    }
    void for_astnode::print()
    {
        std::cout << "for (";
        init->print();
        std::cout << "; ";
        condition->print();
        std::cout << "; ";
        step->print();
        std::cout << ") {" << std::endl;
        body->print();
        std::cout << "}" << std::endl;
    }
    return_astnode::return_astnode(expression_astnode *expression)
    {
        this->expression = expression;
    }
    void return_astnode::print()
    {
        std::cout << "return ";
        expression->print();
        std::cout << std::endl;
    }
    proccall_astnode::proccall_astnode(std::string name)
    {
        this->name = name;
    }
    void proccall_astnode::add_argument(expression_astnode *argument)
    {
        arguments.push_back(argument);
    }
    void proccall_astnode::print()
    {
        std::cout << name << std::endl;
    }
    printf_astnode::printf_astnode(string_astnode *format)
    {
        this->format = format;
    }
    void printf_astnode::add_argument(expression_astnode *argument)
    {
        arguments.push_back(argument);
    }
    void printf_astnode::print()
    {
        std::cout << "printf(";
        format->print();
        for (auto argument : arguments)
        {
            std::cout << ", ";
            argument->print();
        }
        std::cout << ")" << std::endl;
    }

    op_binary_astnode::op_binary_astnode(expression_astnode *left, expression_astnode *right, OP_Binary op)
    {
        this->op = op;
        this->left = left;
        this->right = right;
    }
    void op_binary_astnode::print()
    {
        left->print();
        std::cout<< " " << op << " ";
        right->print();
    }
    op_unary_astnode::op_unary_astnode(expression_astnode *expression, OP_Unary op)
    {
        this->op = op;
        this->expression = expression;
    }
    void op_unary_astnode::print()
    {
        std::cout << op;
        expression->print();
    }
    int_astnode::int_astnode(int value)
    {
        this->value = value;
    }
    void int_astnode::print()
    {
        std::cout << value;
    }
    string_astnode::string_astnode(std::string value)
    {
        this->value = value;
    }
    void string_astnode::print()
    {
        std::cout << value;
    }
    assignE_astnode::assignE_astnode(expression_astnode *left, expression_astnode *right)
    {
        this->left = left;
        this->right = right;
    }
    void assignE_astnode::print()
    {
        left->print();
        std::cout << " = ";
        right->print();
        std::cout << std::endl;
    }
    funcall_astnode::funcall_astnode(identifier_astnode *name)
    {
        this->name = name;
    }
    void funcall_astnode::add_argument(expression_astnode *argument)
    {
        arguments.push_back(argument);
    }
    void funcall_astnode::print()
    {
        std::cout << name << "(";
        for (auto argument : arguments)
        {
            argument->print();
            std::cout << ", ";
        }
        std::cout << ")" << std::endl;
    }
    identifier_astnode::identifier_astnode(std::string name)
    {
        this->name = name;
    }
    void identifier_astnode::print()
    {
        std::cout << name;
    }

    member_astnode::member_astnode(expression_astnode *expression, identifier_astnode *name)
    {
        this->expression = expression;
        this->name = name;
    }
    void member_astnode::print()
    {
        expression->print();
        std::cout << ".";
        name->print();
    }
    array_astnode::array_astnode(expression_astnode *expression, expression_astnode *index)
    {
        this->expression = expression;
        this->index = index;
    }
    void array_astnode::print()
    {
        expression->print();
        std::cout << "[";
        index->print();
        std::cout << "]";
    }
    arrow_astnode::arrow_astnode(expression_astnode *expression, identifier_astnode *name)
    {
        this->expression = expression;
        this->name = name;
    }
    void arrow_astnode::print()
    {
        expression->print();
        std::cout << "->";
        name->print();
    }
    expression_list::expression_list()
    {
    }
    void expression_list::add_expression(expression_astnode *expression)
    {
        expressions.push_back(expression);
    }
    std::vector<expression_astnode *> expression_list::get_expressions()
    {
        return expressions;
    }
}