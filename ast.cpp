#include "ast.hh"
#include <iostream>

int label_number = 0;
RegisterStack R;
int total_registers = R.size();
std::string get_new_instruction_label()
{
    return ".LC" + std::to_string(label_number++);
}

namespace IPL
{
    int expression_astnode::get_label()
    {
        return label;
    }
    void expression_astnode::set_label(int label)
    {
        this->label = label;
    }
    Address *expression_astnode::get_address()
    {
        return address;
    }
    void expression_astnode::set_address(Address *address)
    {
        this->address = address;
    }

    identifier_astnode::identifier_astnode(std::string name, int offset)
    {
        this->name = name;
        this->offset = offset;
        this->address = new Address(offset, "ebp");
    }
    std::vector<std::string> identifier_astnode::tree_traversal()
    {
        std::vector<std::string> runtime_constants;
        label = 1;
        return runtime_constants;
    }
    void identifier_astnode::generate_code()
    {
        std::cout << "\t"
                  << "movl"
                  << "\t" << address << ", " << R.top() << std::endl;
    }

    member_astnode::member_astnode(expression_astnode *expression, identifier_astnode *name)
    {
        this->expression = expression;
        this->name = name;
    }
    std::vector<std::string> member_astnode::tree_traversal()
    {
        std::vector<std::string> runtime_constants;
        std::vector<std::string> expression_constants = expression->tree_traversal();
        runtime_constants.insert(runtime_constants.end(), expression_constants.begin(), expression_constants.end());
        label = expression->get_label();
        return runtime_constants;
    }
    void member_astnode::generate_code()
    {
        std::cout << "member_astnode::generate_code()" << std::endl;
        // expression->generate_code();
    }

    array_astnode::array_astnode(expression_astnode *expression, expression_astnode *index)
    {
        this->expression = expression;
        this->index = index;
    }
    std::vector<std::string> array_astnode::tree_traversal()
    {
        std::vector<std::string> runtime_constants;
        std::vector<std::string> expression_constants = expression->tree_traversal();
        runtime_constants.insert(runtime_constants.end(), expression_constants.begin(), expression_constants.end());
        std::vector<std::string> index_constants = index->tree_traversal();
        runtime_constants.insert(runtime_constants.end(), index_constants.begin(), index_constants.end());
        label = std::max(expression->get_label(), index->get_label());
        return runtime_constants;
    }
    void array_astnode::generate_code()
    {
        std::cout << "array_astnode::generate_code()" << std::endl;
        // expression->generate_code();
        // index->generate_code();
    }

    arrow_astnode::arrow_astnode(expression_astnode *expression, identifier_astnode *name)
    {
        this->expression = expression;
        this->name = name;
    }
    std::vector<std::string> arrow_astnode::tree_traversal()
    {
        std::vector<std::string> runtime_constants;
        std::vector<std::string> expression_constants = expression->tree_traversal();
        runtime_constants.insert(runtime_constants.end(), expression_constants.begin(), expression_constants.end());
        label = expression->get_label();
        return runtime_constants;
    }
    void arrow_astnode::generate_code()
    {
        std::cout << "arrow_astnode::generate_code()" << std::endl;
        // expression->generate_code();
    }

    op_binary_astnode::op_binary_astnode(expression_astnode *left, expression_astnode *right, OP_Binary op)
    {
        this->op = op;
        this->left = left;
        this->right = right;
    }
    std::vector<std::string> op_binary_astnode::tree_traversal()
    {
        std::vector<std::string> runtime_constants;
        std::vector<std::string> left_constants = left->tree_traversal();
        runtime_constants.insert(runtime_constants.end(), left_constants.begin(), left_constants.end());
        std::vector<std::string> right_constants = right->tree_traversal();
        runtime_constants.insert(runtime_constants.end(), right_constants.begin(), right_constants.end());
        int l_label = left->get_label();
        int r_label = right->get_label();
        label = l_label == r_label ? l_label + 1 : std::max(l_label, r_label);
        return runtime_constants;
    }
    void op_binary_astnode::generate_code()
    {
        if(op==OP_Binary::OP_ADD || op==OP_Binary::OP_SUB || op==OP_Binary::OP_MUL || op==OP_Binary::OP_DIV)
        {
            int l_label = left->get_label();
            int r_label = right->get_label();
            
            if(l_label>=total_registers && r_label>=total_registers){
                right->generate_code();
                std::cout << "\t" << "pushl" << "\t" << R.top() << std::endl;
                left->generate_code();
                std::string reg = R.pop();
                std::cout << "\t" << "popl" << "\t" << R.top() << std::endl;
                if(op==OP_Binary::OP_ADD)
                    std::cout << "\t" << "addl" << "\t" << R.top() << ", " << reg << std::endl;
                else if(op==OP_Binary::OP_SUB)
                    std::cout << "\t" << "subl" << "\t" << R.top() << ", " << reg << std::endl;
                else if(op==OP_Binary::OP_MUL)
                    std::cout << "\t" << "imull" << "\t" << R.top() << ", " << reg << std::endl;
                else if(op==OP_Binary::OP_DIV)
                    std::cout << "\t" << "idivl" << "\t" << R.top() << ", " << reg << std::endl;
                R.push(reg);
            }
            else if(l_label>=total_registers && r_label<total_registers)
            {
                left->generate_code();
                std::string reg = R.pop();
                right->generate_code();
                if(op==OP_Binary::OP_ADD)
                    std::cout << "\t" << "addl" << "\t" << R.top() << ", " << reg << std::endl;
                else if(op==OP_Binary::OP_SUB)
                    std::cout << "\t" << "subl" << "\t" << R.top() << ", " << reg << std::endl;
                else if(op==OP_Binary::OP_MUL)
                    std::cout << "\t" << "imull" << "\t" << R.top() << ", " << reg << std::endl;
                else if(op==OP_Binary::OP_DIV)
                    std::cout << "\t" << "idivl" << "\t" << R.top() << ", " << reg << std::endl;
                R.push(reg);
            }
            else if(l_label<total_registers && r_label>=total_registers)
            {
                R.swap();
                right->generate_code();
                std::string reg = R.pop();
                left->generate_code();
                if(op==OP_Binary::OP_ADD)
                    std::cout << "\t" << "addl" << "\t" << reg << ", " << R.top() << std::endl;
                else if(op==OP_Binary::OP_SUB)
                    std::cout << "\t" << "subl" << "\t" << reg << ", " << R.top() << std::endl;
                else if(op==OP_Binary::OP_MUL)
                    std::cout << "\t" << "imull" << "\t" << reg << ", " << R.top() << std::endl;
                else if(op==OP_Binary::OP_DIV)
                    std::cout << "\t" << "idivl" << "\t" << reg << ", " << R.top() << std::endl;
                R.push(reg);
                R.swap();
            }
            else
            {
                left->generate_code();
                std::string reg = R.pop();
                right->generate_code();
                if(op==OP_Binary::OP_ADD)
                    std::cout << "\t" << "addl" << "\t" << R.top() << ", " << reg << std::endl;
                else if(op==OP_Binary::OP_SUB)
                    std::cout << "\t" << "subl" << "\t" << R.top() << ", " << reg << std::endl;
                else if(op==OP_Binary::OP_MUL)
                    std::cout << "\t" << "imull" << "\t" << R.top() << ", " << reg << std::endl;
                else if(op==OP_Binary::OP_DIV)
                    std::cout << "\t" << "idivl" << "\t" << R.top() << ", " << reg << std::endl;
                R.push(reg);
            }
        }
        else
        {
            std::cout << "Error operation not handled yet" << std::endl;
        }
    }

    op_unary_astnode::op_unary_astnode(expression_astnode *expression, OP_Unary op)
    {
        this->op = op;
        this->expression = expression;
    }
    std::vector<std::string> op_unary_astnode::tree_traversal()
    {
        std::vector<std::string> runtime_constants;
        std::vector<std::string> expression_constants = expression->tree_traversal();
        runtime_constants.insert(runtime_constants.end(), expression_constants.begin(), expression_constants.end());
        label = expression->get_label();
        return runtime_constants;
    }
    void op_unary_astnode::generate_code()
    {
        if(op==OP_Unary::OP_NOT)
        {
            expression->generate_code();
            std::cout << "\t" << "cmpl" << "\t" << "$0, " << R.top() << std::endl;
            std::cout << "\t" << "sete" << "\t" << "%al" << std::endl;
            std::cout << "\t" << "movzbl" << "\t" << "%al, " << R.top() << std::endl;
        }
        else if(op==OP_Unary::OP_SUB)
        {
            expression->generate_code();
            std::cout << "\t" << "negl" << "\t" << R.top() << std::endl;
        }
        else if(op==OP_Unary::OP_INC)
        {
            expression->generate_code();
            if(expression->get_address()==nullptr){
                std::cout << "Error: cannot increment a non-addressable value" << std::endl;
            }
            else{
                std::cout << "\t" << "incl" << "\t" << expression->get_address() << std::endl;
            }
        }
        else
        {
            std::cout << "Error operation not handled yet" << std::endl;
        }
    }

    int_astnode::int_astnode(int value)
    {
        this->value = value;
    }
    std::vector<std::string> int_astnode::tree_traversal()
    {
        std::vector<std::string> runtime_constants;
        label = 0;
        return runtime_constants;
    }
    void int_astnode::generate_code()
    {
        std::cout << "\t"
                  << "movl"
                  << "\t"
                  << "$" << value << ", " << R.top() << std::endl;
    }

    string_astnode::string_astnode(std::string value)
    {
        this->value = value;
    }
    std::vector<std::string> string_astnode::tree_traversal()
    {
        std::vector<std::string> runtime_constants;
        std::string instruction_label = get_new_instruction_label();
        runtime_constants.push_back(instruction_label + ":\n" + "\t" + ".string" + "\t" + value);
        label = 0;
        reference = instruction_label;
        return runtime_constants;
    }
    void string_astnode::generate_code()
    {
        std::cout << "$" << reference;
    }

    assignE_astnode::assignE_astnode(expression_astnode *left, expression_astnode *right)
    {
        this->left = left;
        this->right = right;
    }
    std::vector<std::string> assignE_astnode::tree_traversal()
    {
        std::vector<std::string> runtime_constants;
        std::vector<std::string> left_constants = left->tree_traversal();
        runtime_constants.insert(runtime_constants.end(), left_constants.begin(), left_constants.end());
        std::vector<std::string> right_constants = right->tree_traversal();
        runtime_constants.insert(runtime_constants.end(), right_constants.begin(), right_constants.end());
        label = std::max(left->get_label(), right->get_label());
        return runtime_constants;
    }
    void assignE_astnode::generate_code()
    {
        if (left->get_label() >= total_registers)
        {
            std::cout << "Error: left side of assignment is not a variable" << std::endl;
        }
        else
        {
            right->generate_code();
            std::string reg = R.pop();
            Address *addr = left->get_address();
            if (addr != nullptr)
            {
                std::cout << "\t" << "movl" << "\t" << reg << ", " << addr << std::endl;
            }
            else
            {
                std::cout << "Error: left side of assignment is not a variable" << std::endl;
            }
            R.push(reg);
        }
    }

    funcall_astnode::funcall_astnode(identifier_astnode *name)
    {
        this->name = name;
    }
    void funcall_astnode::add_argument(expression_astnode *argument)
    {
        arguments.push_back(argument);
    }
    std::vector<std::string> funcall_astnode::tree_traversal()
    {
        std::vector<std::string> runtime_constants;
        for (auto argument : arguments)
        {
            std::vector<std::string> argument_constants = argument->tree_traversal();
            runtime_constants.insert(runtime_constants.end(), argument_constants.begin(), argument_constants.end());
        }
        label = 0;
        return runtime_constants;
    }
    void funcall_astnode::generate_code()
    {
        std::cout << "funcall_astnode::generate_code()" << std::endl;
        // for (auto argument : arguments)
        // {
        //     argument->generate_code();
        // }
    }

    seq_astnode::seq_astnode()
    {
    }
    void seq_astnode::add_statement(statement_astnode *statement)
    {
        statements.push_back(statement);
    }
    std::vector<std::string> seq_astnode::tree_traversal()
    {
        std::vector<std::string> runtime_constants;
        for (auto statement : statements)
        {
            std::vector<std::string> statement_constants = statement->tree_traversal();
            runtime_constants.insert(runtime_constants.end(), statement_constants.begin(), statement_constants.end());
        }
        return runtime_constants;
    }
    void seq_astnode::generate_code()
    {
        for (auto statement : statements)
        {
            statement->generate_code();
        }
    }

    empty_astnode::empty_astnode()
    {
    }
    std::vector<std::string> empty_astnode::tree_traversal()
    {
        std::vector<std::string> runtime_constants;
        return runtime_constants;
    }
    void empty_astnode::generate_code()
    {
    }

    assignS_astnode::assignS_astnode(expression_astnode *assignment_expression)
    {
        this->assignment_expression = assignment_expression;
    }
    std::vector<std::string> assignS_astnode::tree_traversal()
    {
        std::vector<std::string> runtime_constants;
        std::vector<std::string> expression_constants = assignment_expression->tree_traversal();
        runtime_constants.insert(runtime_constants.end(), expression_constants.begin(), expression_constants.end());
        return runtime_constants;
    }
    void assignS_astnode::generate_code()
    {
        assignment_expression->generate_code();
    }

    if_astnode::if_astnode(expression_astnode *condition, statement_astnode *if_body, statement_astnode *else_body)
    {
        this->condition = condition;
        this->if_body = if_body;
        this->else_body = else_body;
    }
    std::vector<std::string> if_astnode::tree_traversal()
    {
        std::vector<std::string> runtime_constants;
        std::vector<std::string> condition_constants = condition->tree_traversal();
        runtime_constants.insert(runtime_constants.end(), condition_constants.begin(), condition_constants.end());
        std::vector<std::string> if_body_constants = if_body->tree_traversal();
        runtime_constants.insert(runtime_constants.end(), if_body_constants.begin(), if_body_constants.end());
        if (else_body != NULL)
        {
            std::vector<std::string> else_body_constants = else_body->tree_traversal();
            runtime_constants.insert(runtime_constants.end(), else_body_constants.begin(), else_body_constants.end());
        }
        return runtime_constants;
    }
    void if_astnode::generate_code()
    {
        std::cout << "if" << std::endl;
        // std::string else_label = "else" + std::to_string(if_counter);
        // std::string end_label = "end" + std::to_string(if_counter);
        // if_counter++;
        // condition->generate_code();
        // std::cout << "\t" << "popl" << "\t" << "%eax" << std::endl;
        // std::cout << "\t" << "cmpl" << "\t" << "$0" << ", " << "%eax" << std::endl;
        // std::cout << "\t" << "je" << "\t" << else_label << std::endl;
        // if_body->generate_code();
        // std::cout << "\t" << "jmp" << "\t" << end_label << std::endl;
        // std::cout << else_label << ":" << std::endl;
        // if (else_body != NULL)
        // {
        //     else_body->generate_code();
        // }
        // std::cout << end_label << ":" << std::endl;
    }

    while_astnode::while_astnode(expression_astnode *condition, statement_astnode *body)
    {
        this->condition = condition;
        this->body = body;
    }
    std::vector<std::string> while_astnode::tree_traversal()
    {
        std::vector<std::string> runtime_constants;
        std::vector<std::string> condition_constants = condition->tree_traversal();
        runtime_constants.insert(runtime_constants.end(), condition_constants.begin(), condition_constants.end());
        std::vector<std::string> body_constants = body->tree_traversal();
        runtime_constants.insert(runtime_constants.end(), body_constants.begin(), body_constants.end());
        return runtime_constants;
    }
    void while_astnode::generate_code()
    {
        std::cout << "while" << std::endl;
        // std::string start_label = "start" + std::to_string(while_counter);
        // std::string end_label = "end" + std::to_string(while_counter);
        // while_counter++;
        // std::cout << start_label << ":" << std::endl;
        // condition->generate_code();
        // std::cout << "\t" << "popl" << "\t" << "%eax" << std::endl;
        // std::cout << "\t" << "cmpl" << "\t" << "$0" << ", " << "%eax" << std::endl;
        // std::cout << "\t" << "je" << "\t" << end_label << std::endl;
        // body->generate_code();
        // std::cout << "\t" << "jmp" << "\t" << start_label << std::endl;
        // std::cout << end_label << ":" << std::endl;
    }

    for_astnode::for_astnode(assignE_astnode *init, expression_astnode *condition, assignE_astnode *step, statement_astnode *body)
    {
        this->init = init;
        this->condition = condition;
        this->step = step;
        this->body = body;
    }
    std::vector<std::string> for_astnode::tree_traversal()
    {
        std::vector<std::string> runtime_constants;
        std::vector<std::string> init_constants = init->tree_traversal();
        runtime_constants.insert(runtime_constants.end(), init_constants.begin(), init_constants.end());
        std::vector<std::string> condition_constants = condition->tree_traversal();
        runtime_constants.insert(runtime_constants.end(), condition_constants.begin(), condition_constants.end());
        std::vector<std::string> step_constants = step->tree_traversal();
        runtime_constants.insert(runtime_constants.end(), step_constants.begin(), step_constants.end());
        std::vector<std::string> body_constants = body->tree_traversal();
        runtime_constants.insert(runtime_constants.end(), body_constants.begin(), body_constants.end());
        return runtime_constants;
    }
    void for_astnode::generate_code()
    {
        std::cout << "for" << std::endl;
        // std::string start_label = "start" + std::to_string(for_counter);
        // std::string end_label = "end" + std::to_string(for_counter);
        // for_counter++;
        // init->generate_code();
        // std::cout << start_label << ":" << std::endl;
        // condition->generate_code();
        // std::cout << "\t" << "popl" << "\t" << "%eax" << std::endl;
        // std::cout << "\t" << "cmpl" << "\t" << "$0" << ", " << "%eax" << std::endl;
        // std::cout << "\t" << "je" << "\t" << end_label << std::endl;
        // body->generate_code();
        // step->generate_code();
        // std::cout << "\t" << "jmp" << "\t" << start_label << std::endl;
        // std::cout << end_label << ":" << std::endl;
    }

    return_astnode::return_astnode(expression_astnode *expression, int local_var_size)
    {
        this->expression = expression;
        this->local_var_size = local_var_size + 4;
    }
    std::vector<std::string> return_astnode::tree_traversal()
    {
        std::vector<std::string> runtime_constants;
        if (expression != NULL)
        {
            std::vector<std::string> expression_constants = expression->tree_traversal();
            runtime_constants.insert(runtime_constants.end(), expression_constants.begin(), expression_constants.end());
        }
        return runtime_constants;
    }
    void return_astnode::generate_code()
    {
        // std::cout<<"return"<<std::endl;
        if (expression != NULL)
        {
            expression->generate_code();
            // std::cout << "\t" << "movl" << "\t" << R.top() << ", " << "%eax" << std::endl;
        }
        // std::cout << "\t" << "movl" << "\t" << "%ebp" << ", " << "%esp" << std::endl;
        // std::cout << "\t" << "popl" << "\t" << "%ebp" << std::endl;
        // std::cout << "\t" << "ret" << std::endl;
        std::cout << "\t"
                  << "addl"
                  << "\t"
                  << "$" << local_var_size << ", "
                  << "%esp" << std::endl;
    }

    proccall_astnode::proccall_astnode(std::string name)
    {
        this->name = name;
    }
    void proccall_astnode::add_argument(expression_astnode *argument)
    {
        arguments.push_back(argument);
    }
    std::vector<std::string> proccall_astnode::tree_traversal()
    {
        std::vector<std::string> runtime_constants;
        for (auto argument : arguments)
        {
            std::vector<std::string> argument_constants = argument->tree_traversal();
            runtime_constants.insert(runtime_constants.end(), argument_constants.begin(), argument_constants.end());
        }
        return runtime_constants;
    }
    void proccall_astnode::generate_code()
    {
        std::cout << "proccall" << std::endl;
        // std::cout << "\t" << "call" << "\t" << name << std::endl;
        // std::cout << "\t" << "addl" << "\t" << "$" << arguments.size() * 4 << ", " << "%esp" << std::endl;
    }

    printf_astnode::printf_astnode(string_astnode *format)
    {
        this->format = format;
    }
    void printf_astnode::add_argument(expression_astnode *argument)
    {
        arguments.push_back(argument);
    }
    std::vector<std::string> printf_astnode::tree_traversal()
    {
        std::vector<std::string> runtime_constants;
        std::vector<std::string> format_constants = format->tree_traversal();
        runtime_constants.insert(runtime_constants.end(), format_constants.begin(), format_constants.end());
        for (auto argument : arguments)
        {
            std::vector<std::string> argument_constants = argument->tree_traversal();
            runtime_constants.insert(runtime_constants.end(), argument_constants.begin(), argument_constants.end());
        }
        return runtime_constants;
    }
    void printf_astnode::generate_code()
    {
        for (auto argument = arguments.rbegin(); argument != arguments.rend(); ++argument)
        {
            (*argument)->generate_code();
            std::cout << "\t"
                      << "pushl"
                      << "\t" << R.top() << std::endl;
        }
        std::cout << "\t"
                  << "pushl"
                  << "\t";
        format->generate_code();
        std::cout << std::endl;
        std::cout << "\t"
                  << "call"
                  << "\t"
                  << "printf" << std::endl;
    }

    compound_statement::compound_statement(seq_astnode *statements, int local_var_size)
    {
        this->statements = statements;
        this->local_var_size = local_var_size;
    }
    void compound_statement::populate_runtime_constants()
    {
        runtime_constants = statements->tree_traversal();
    }
    void compound_statement::print_runtime_constants()
    {
        for (auto constant : runtime_constants)
        {
            std::cout << constant << std::endl;
        }
    }
    void compound_statement::generate_code(std::string function_name)
    {
        std::cout << "\t"
                  << ".globl " << function_name << std::endl;
        std::cout << "\t"
                  << ".type " << function_name << ", @function" << std::endl;
        if (statements)
        {
            populate_runtime_constants();
            print_runtime_constants();
            std::cout << function_name << ":" << std::endl;
            // Setup Activation Record
            std::cout << "\t"
                      << "pushl"
                      << "\t"
                      << "%ebp" << std::endl;
            std::cout << "\t"
                      << "movl"
                      << "\t"
                      << "%esp"
                      << ", "
                      << "%ebp" << std::endl;
            // Allocate space for local variables
            std::cout << "\t"
                      << "subl"
                      << "\t"
                      << "$" << local_var_size << ", "
                      << "%esp" << std::endl;
            statements->generate_code();
            // Restore Activation Record
            std::cout << "\t"
                      << "leave" << std::endl;
            std::cout << "\t"
                      << "ret" << std::endl;
        }
        std::cout << std::endl;
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