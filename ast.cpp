#include "ast.hh"
#include <iostream>
namespace IPL
{
    void abstract_astnode::append_label(std::string label)
    {
        labels += label;
    }
    void abstract_astnode::print_labels()
    {
        std::cout << labels;
    }
    std::string abstract_astnode::get_labels()
    {
        return labels;
    }
    empty_astnode::empty_astnode()
    {
        code = "";
    }
    void empty_astnode::print_code()
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
        if(statement->get_labels() != "")
        {
            append_label(statement->get_labels()+"\n");
        }
    }
    void seq_astnode::print_code()
    {
        for (auto statement : statements)
        {
            statement->print_code();
        }
    }
    assignS_astnode::assignS_astnode(expression_astnode *assignment_expression)
    {
        this->assignment_expression = assignment_expression;
    }
    void assignS_astnode::print_code()
    {
        assignment_expression->print_code();
    }
    if_astnode::if_astnode(expression_astnode *condition, statement_astnode *if_body, statement_astnode *else_body)
    {
        this->condition = condition;
        this->if_body = if_body;
        this->else_body = else_body;
    }
    void if_astnode::print_code()
    {
        std::cout << "if (";
        condition->print_code();
        std::cout << ") {" << std::endl;
        if_body->print_code();
        std::cout << "}" << std::endl;
        if (else_body != NULL)
        {
            std::cout << "else {" << std::endl;
            else_body->print_code();
            std::cout << "}" << std::endl;
        }
    }
    while_astnode::while_astnode(expression_astnode *condition, statement_astnode *body)
    {
        this->condition = condition;
        this->body = body;
    }
    void while_astnode::print_code()
    {
        std::cout << "while (";
        condition->print_code();
        std::cout << ") {" << std::endl;
        body->print_code();
        std::cout << "}" << std::endl;
    }
    for_astnode::for_astnode(assignE_astnode *init, expression_astnode *condition, assignE_astnode *step, statement_astnode *body)
    {
        this->init = init;
        this->condition = condition;
        this->step = step;
        this->body = body;
    }
    void for_astnode::print_code()
    {
        std::cout << "for (";
        init->print_code();
        std::cout << "; ";
        condition->print_code();
        std::cout << "; ";
        step->print_code();
        std::cout << ") {" << std::endl;
        body->print_code();
        std::cout << "}" << std::endl;
    }
    return_astnode::return_astnode(expression_astnode *expression, int local_var_size)
    {
        this->expression = expression;
        this->local_var_size = local_var_size + 4;
    }
    void return_astnode::print_code()
    {
        // Pop local variables
        std::cout << "\t" << "addl" << "\t" << "$" << local_var_size << ", %esp" << std::endl;
        std::cout << "\t" << "movl \t";
        expression->print_code();
        std::cout << ", %eax" << std::endl;
    }
    proccall_astnode::proccall_astnode(std::string name)
    {
        this->name = name;
    }
    void proccall_astnode::add_argument(expression_astnode *argument)
    {
        arguments.push_back(argument);
    }
    void proccall_astnode::print_code()
    {
        std::cout << name << std::endl;
    }
    printf_astnode::printf_astnode(string_astnode *format)
    {
        this->format = format;
        append_label(format->get_labels());
    }
    void printf_astnode::add_argument(expression_astnode *argument)
    {
        arguments.push_back(argument);
    }
    void printf_astnode::print_code()
    {
        // Push arguments in reverse order
        for (auto it = arguments.rbegin(); it != arguments.rend(); ++it)
        {
            std::cout << "\t" << "pushl" << "\t";
            (*it)->print_code();
            std::cout << std::endl;
        }
        // Push format string
        std::cout << "\t" << "pushl" << "\t";
        format->print_code();
        std::cout << std::endl;
        // Call printf
        std::cout << "\t" << "call" << "\t" << "printf" << std::endl;
    }

    op_binary_astnode::op_binary_astnode(expression_astnode *left, expression_astnode *right, OP_Binary op)
    {
        this->op = op;
        this->left = left;
        this->right = right;
    }
    void op_binary_astnode::print_code()
    {
        left->print_code();
        std::cout<< " " << op << " ";
        right->print_code();
    }
    op_unary_astnode::op_unary_astnode(expression_astnode *expression, OP_Unary op)
    {
        this->op = op;
        this->expression = expression;
    }
    void op_unary_astnode::print_code()
    {
        std::cout << op;
        expression->print_code();
    }
    int_astnode::int_astnode(int value)
    {
        this->value = value;
    }
    void int_astnode::print_code()
    {
        std::cout <<"$"<<value;
    }
    string_astnode::string_astnode(std::string value, std::string label)
    {
        this->value = value;
        this->label = label;
        this->append_label(label+": \n\t.string "+value);
    }
    void string_astnode::print_code()
    {
        std::cout << "$" << label;
    }
    assignE_astnode::assignE_astnode(expression_astnode *left, expression_astnode *right)
    {
        this->left = left;
        this->right = right;
    }
    void assignE_astnode::print_code()
    {
        //Assembly code for assignment
        std::cout << "\t" << "movl \t";
        right->print_code();
        std::cout << ", ";
        left->print_code();
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
    void funcall_astnode::print_code()
    {
        std::cout << name << "(";
        for (auto argument : arguments)
        {
            argument->print_code();
            std::cout << ", ";
        }
        std::cout << ")" << std::endl;
    }
    identifier_astnode::identifier_astnode(std::string name, int offset)
    {
        this->name = name;
        this->offset = offset;
    }
    void identifier_astnode::print_code()
    {
        // Print offset from ebp
        std::cout << offset << "(%ebp)";
    }

    member_astnode::member_astnode(expression_astnode *expression, identifier_astnode *name)
    {
        this->expression = expression;
        this->name = name;
    }
    void member_astnode::print_code()
    {
        expression->print_code();
        std::cout << ".";
        name->print_code();
    }
    array_astnode::array_astnode(expression_astnode *expression, expression_astnode *index)
    {
        this->expression = expression;
        this->index = index;
    }
    void array_astnode::print_code()
    {
        expression->print_code();
        std::cout << "[";
        index->print_code();
        std::cout << "]";
    }
    arrow_astnode::arrow_astnode(expression_astnode *expression, identifier_astnode *name)
    {
        this->expression = expression;
        this->name = name;
    }
    void arrow_astnode::print_code()
    {
        expression->print_code();
        std::cout << "->";
        name->print_code();
    }
    
    compound_statement_astnode::compound_statement_astnode(seq_astnode *statements, int local_var_size)
    {
        this->statements = statements;
        this->local_var_size = local_var_size;
        append_label(statements->get_labels());
    }
    void compound_statement_astnode::print_code()
    {
        std::cout << "\t" << "pushl" << "\t" << "%ebp" << std::endl;
        std::cout << "\t" << "movl" << "\t" << "%esp" << ", " << "%ebp" << std::endl;
        
        // Allocate space for local variables
        std::cout << "\t" << "subl" << "\t" << "$" << local_var_size << ", " << "%esp" << std::endl;
        
        statements->print_code();
        
        std::cout << "\t" << "leave" << std::endl;
        std::cout << "\t" << "ret" << std::endl;
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