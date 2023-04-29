#include "ast.hh"
#include <iostream>

int label_number = 0;
RegisterStack R;
int total_registers = R.size();
std::string get_new_instruction_label()
{
    return ".LC" + std::to_string(label_number++);
}
std::vector<std::string> Code;
void backpatch(std::vector<int> list, std::string label)
{
    for (int i : list)
    {
        Code[i] = Code[i] + "\t" + label;
    }
}
std::vector<int> merge(std::vector<int> list1, std::vector<int> list2)
{
    std::vector<int> list;
    list.insert(list.end(), list1.begin(), list1.end());
    list.insert(list.end(), list2.begin(), list2.end());
    return list;
}
int nextinstr()
{
    return Code.size();
}

namespace IPL
{
    ASTNodeType abstract_astnode::get_type()
    {
        return node_type;
    }
    void abstract_astnode::set_type(ASTNodeType type)
    {
        this->node_type = type;
    }
    int abstract_astnode::get_label()
    {
        return label;
    }
    void abstract_astnode::set_label(int label)
    {
        this->label = label;
    }

    std::vector<int> statement_astnode::get_nextlist()
    {
        return nextlist;
    }
    void statement_astnode::set_nextlist(std::vector<int> nextlist)
    {
        this->nextlist = nextlist;
    }

    Address *expression_astnode::get_address()
    {
        return address;
    }
    void expression_astnode::set_address(Address *address)
    {
        this->address = address;
    }
    std::vector<int> expression_astnode::get_truelist()
    {
        return truelist;
    }
    void expression_astnode::set_truelist(std::vector<int> truelist)
    {
        this->truelist = truelist;
    }
    std::vector<int> expression_astnode::get_falselist()
    {
        return falselist;
    }
    void expression_astnode::set_falselist(std::vector<int> falselist)
    {
        this->falselist = falselist;
    }
    std::string expression_astnode::to_arithmetic()
    {
        if (this->is_bool)
        {
            std::string M1 = get_new_instruction_label();
            std::string M2 = get_new_instruction_label();
            std::string M3 = get_new_instruction_label();
            backpatch(this->truelist, M1);
            backpatch(this->falselist, M2);
            Code.push_back(M1 + ":");
            Code.push_back("\tmovl\t$1, " + R.top());
            Code.push_back("\tjmp\t\t" + M3);
            Code.push_back(M2 + ":");
            Code.push_back("\tmovl\t$0, " + R.top());
            return M3;
        }
        else
        {
            std::cout << "Error: Expression is already arithmetic" << std::endl;
            return "";
        }
    }
    void expression_astnode::to_boolean()
    {
        if (!this->is_bool)
        {
            Code.push_back("\tcmpl\t$0, " + R.top());
            this->truelist.push_back(nextinstr());
            this->falselist.push_back(nextinstr() + 1);
            Code.push_back("\tjne\t");
            Code.push_back("\tjmp\t");
        }
        else
        {
            std::cout << "Error: Expression is already boolean" << std::endl;
        }
    }
    bool expression_astnode::get_is_bool()
    {
        return this->is_bool;
    }
    void expression_astnode::set_is_lvalue(bool is_lvalue)
    {
        this->is_lvalue = is_lvalue;
    }
    bool expression_astnode::get_is_lvalue()
    {
        return this->is_lvalue;
    }
    Type *expression_astnode::get_type()
    {
        return this->type;
    }
    void expression_astnode::set_type(Type *type)
    {
        this->type = type;
    }

    identifier_astnode::identifier_astnode(std::string name, int offset)
    {
        this->name = name;
        this->offset = offset;
        this->address = new Address(offset, "ebp");
        this->node_type = ASTNodeType::Identifier;
    }
    std::vector<std::string> identifier_astnode::tree_traversal()
    {
        std::vector<std::string> runtime_constants;
        label = 1;
        return runtime_constants;
    }
    void identifier_astnode::generate_code()
    {
        if(this->type->get_base_type() == BaseType::Int){
            Code.push_back("\tmovl\t" + to_string(address) + ", " + R.top());
        }
        else if(this->type->get_base_type() == BaseType::Struct){
            // Code.push_back("\tmovb\t" + to_string(address) + ", " + R.top());
            // this->address
        }
    }

    member_astnode::member_astnode(expression_astnode *expression, identifier_astnode *name)
    {
        this->expression = expression;
        this->name = name;
        this->node_type = ASTNodeType::Member;
        this->address = new Address(expression->get_address()->get_offset() + name->get_address()->get_offset(), expression->get_address()->get_base());
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
        // std::cout << "member_astnode::generate_code()" << std::endl;
        if(this->type->get_base_type() == BaseType::Int){
            Code.push_back("\tmovl\t" + to_string(address) + ", " + R.top());
        }
        else if(this->type->get_base_type() == BaseType::Struct){
            // Code.push_back("\tmovb\t" + to_string(address) + ", " + R.top());
            // this->address
        }
        // expression->generate_code();
    }

    array_astnode::array_astnode(expression_astnode *expression, expression_astnode *index)
    {
        this->expression = expression;
        this->index = index;
        this->node_type = ASTNodeType::Array;
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
        this->node_type = ASTNodeType::Arrow;
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
        this->node_type = ASTNodeType::Op_binary;
        switch (op)
        {
        case OP_Binary::OP_ADD:
        case OP_Binary::OP_SUB:
        case OP_Binary::OP_MUL:
        case OP_Binary::OP_DIV:
            this->is_bool = false;
            break;
        case OP_Binary::OP_LT:
        case OP_Binary::OP_GT:
        case OP_Binary::OP_LTE:
        case OP_Binary::OP_GTE:
        case OP_Binary::OP_EQ:
        case OP_Binary::OP_NEQ:
        case OP_Binary::OP_AND:
        case OP_Binary::OP_OR:
            this->is_bool = true;
            break;
        default:
            this->is_bool = false;
            break;
        }
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
        if (op == OP_Binary::OP_ADD || op == OP_Binary::OP_SUB || op == OP_Binary::OP_MUL || op == OP_Binary::OP_DIV)
        {
            int l_label = left->get_label();
            int r_label = right->get_label();

            if (l_label >= total_registers && r_label >= total_registers)
            {
                right->generate_code();
                if (right->get_is_bool())
                {
                    std::string M = right->to_arithmetic();
                    Code.push_back(M + ":");
                }
                Code.push_back("\tpushl\t" + R.top());
                left->generate_code();
                if (left->get_is_bool())
                {
                    std::string M = left->to_arithmetic();
                    Code.push_back(M + ":");
                }
                std::string reg = R.pop();
                Code.push_back("\tpopl\t" + R.top());
                if (op == OP_Binary::OP_ADD)
                    Code.push_back("\taddl\t" + R.top() + ", " + reg);
                else if (op == OP_Binary::OP_SUB)
                    Code.push_back("\tsubl\t" + R.top() + ", " + reg);
                else if (op == OP_Binary::OP_MUL)
                    Code.push_back("\timull\t" + R.top() + ", " + reg);
                else if (op == OP_Binary::OP_DIV)
                    Code.push_back("\tidivl\t" + R.top() + ", " + reg);
                R.push(reg);
            }
            else if (l_label >= total_registers && r_label < total_registers)
            {
                left->generate_code();
                if (left->get_is_bool())
                {
                    std::string M = left->to_arithmetic();
                    Code.push_back(M + ":");
                }
                std::string reg = R.pop();
                right->generate_code();
                if (right->get_is_bool())
                {
                    std::string M = right->to_arithmetic();
                    Code.push_back(M + ":");
                }
                if (op == OP_Binary::OP_ADD)
                    Code.push_back("\taddl\t" + R.top() + ", " + reg);
                else if (op == OP_Binary::OP_SUB)
                    Code.push_back("\tsubl\t" + R.top() + ", " + reg);
                else if (op == OP_Binary::OP_MUL)
                    Code.push_back("\timull\t" + R.top() + ", " + reg);
                else if (op == OP_Binary::OP_DIV)
                    Code.push_back("\tidivl\t" + R.top() + ", " + reg);
                R.push(reg);
            }
            else if (l_label < total_registers && r_label >= total_registers)
            {
                R.swap();
                right->generate_code();
                if (right->get_is_bool())
                {
                    std::string M = right->to_arithmetic();
                    Code.push_back(M + ":");
                }
                std::string reg = R.pop();
                left->generate_code();
                if (left->get_is_bool())
                {
                    std::string M = left->to_arithmetic();
                    Code.push_back(M + ":");
                }
                if (op == OP_Binary::OP_ADD)
                    Code.push_back("\taddl\t" + reg + ", " + R.top());
                else if (op == OP_Binary::OP_SUB)
                    Code.push_back("\tsubl\t" + reg + ", " + R.top());
                else if (op == OP_Binary::OP_MUL)
                    Code.push_back("\timull\t" + reg + ", " + R.top());
                else if (op == OP_Binary::OP_DIV)
                    Code.push_back("\tidivl\t" + reg + ", " + R.top());
                R.push(reg);
                R.swap();
            }
            else
            {
                left->generate_code();
                if (left->get_is_bool())
                {
                    std::string M = left->to_arithmetic();
                    Code.push_back(M + ":");
                }
                std::string reg = R.pop();
                right->generate_code();
                if (right->get_is_bool())
                {
                    std::string M = right->to_arithmetic();
                    Code.push_back(M + ":");
                }
                if (op == OP_Binary::OP_ADD)
                    Code.push_back("\taddl\t" + R.top() + ", " + reg);
                else if (op == OP_Binary::OP_SUB)
                    Code.push_back("\tsubl\t" + R.top() + ", " + reg);
                else if (op == OP_Binary::OP_MUL)
                    Code.push_back("\timull\t" + R.top() + ", " + reg);
                else if (op == OP_Binary::OP_DIV)
                    Code.push_back("\tidivl\t" + R.top() + ", " + reg);
                R.push(reg);
            }
        }
        else if (op == OP_Binary::OP_OR)
        {
            std::string M = get_new_instruction_label();
            left->generate_code();
            if (!left->get_is_bool())
            {
                left->to_boolean();
            }
            Code.push_back(M + ":");
            right->generate_code();
            if (!right->get_is_bool())
            {
                right->to_boolean();
            }
            backpatch(left->get_falselist(), M);
            this->set_truelist(merge(left->get_truelist(), right->get_truelist()));
            this->set_falselist(right->get_falselist());
        }
        else if (op == OP_Binary::OP_AND)
        {
            std::string M = get_new_instruction_label();
            left->generate_code();
            if (!left->get_is_bool())
            {
                left->to_boolean();
            }
            Code.push_back(M + ":");
            right->generate_code();
            if (!right->get_is_bool())
            {
                right->to_boolean();
            }
            backpatch(left->get_truelist(), M);
            this->set_truelist(right->get_truelist());
            this->set_falselist(merge(left->get_falselist(), right->get_falselist()));
        }
        else if (op == OP_Binary::OP_EQ || op == OP_Binary::OP_NEQ || op == OP_Binary::OP_LT || op == OP_Binary::OP_GT || op == OP_Binary::OP_LTE || op == OP_Binary::OP_GTE)
        {
            int l_label = left->get_label();
            int r_label = right->get_label();

            if (l_label >= total_registers && r_label >= total_registers)
            {
                right->generate_code();
                if (right->get_is_bool())
                {
                    std::string M = right->to_arithmetic();
                    Code.push_back(M + ":");
                }
                Code.push_back("\tpushl\t" + R.top());
                left->generate_code();
                if (left->get_is_bool())
                {
                    std::string M = left->to_arithmetic();
                    Code.push_back(M + ":");
                }
                std::string reg = R.pop();
                Code.push_back("\tpopl\t" + R.top());
                Code.push_back("\tcmpl\t" + R.top() + ", " + reg);
                R.push(reg);
            }
            else if (l_label >= total_registers && r_label < total_registers)
            {
                left->generate_code();
                if (left->get_is_bool())
                {
                    std::string M = left->to_arithmetic();
                    Code.push_back(M + ":");
                }
                std::string reg = R.pop();
                right->generate_code();
                if (right->get_is_bool())
                {
                    std::string M = right->to_arithmetic();
                    Code.push_back(M + ":");
                }
                Code.push_back("\tcmpl\t" + R.top() + ", " + reg);
                R.push(reg);
            }
            else if (l_label < total_registers && r_label >= total_registers)
            {
                R.swap();
                right->generate_code();
                if (right->get_is_bool())
                {
                    std::string M = right->to_arithmetic();
                    Code.push_back(M + ":");
                }
                std::string reg = R.pop();
                left->generate_code();
                if (left->get_is_bool())
                {
                    std::string M = left->to_arithmetic();
                    Code.push_back(M + ":");
                }
                Code.push_back("\tcmpl\t" + reg + ", " + R.top());
                R.push(reg);
                R.swap();
            }
            else
            {
                left->generate_code();
                if (left->get_is_bool())
                {
                    std::string M = left->to_arithmetic();
                    Code.push_back(M + ":");
                }
                std::string reg = R.pop();
                right->generate_code();
                if (right->get_is_bool())
                {
                    std::string M = right->to_arithmetic();
                    Code.push_back(M + ":");
                }
                Code.push_back("\tcmpl\t" + R.top() + ", " + reg);
                R.push(reg);
            }
            // std::vector<int> L1 = {nextinstr()};
            this->set_truelist(std::vector<int>{nextinstr()});
            this->set_falselist(std::vector<int>{nextinstr() + 1});
            if (op == OP_Binary::OP_EQ)
                Code.push_back("\tje\t");
            else if (op == OP_Binary::OP_NEQ)
                Code.push_back("\tjne\t");
            else if (op == OP_Binary::OP_LT)
                Code.push_back("\tjl\t");
            else if (op == OP_Binary::OP_GT)
                Code.push_back("\tjg\t");
            else if (op == OP_Binary::OP_LTE)
                Code.push_back("\tjle\t");
            else if (op == OP_Binary::OP_GTE)
                Code.push_back("\tjge\t");
            Code.push_back("\tjmp\t");
        }
        else
        {
            std::cout << "Error operation not handled yet" << std::endl;
        }
        Code.push_back("");
    }

    op_unary_astnode::op_unary_astnode(expression_astnode *expression, OP_Unary op)
    {
        this->op = op;
        this->expression = expression;
        this->node_type = ASTNodeType::Op_unary;
        switch (op)
        {
        case OP_Unary::OP_NOT:
            this->is_bool = true;
            break;
        default:
            this->is_bool = false;
            break;
        }
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
        if (op == OP_Unary::OP_NOT)
        {
            // expression->set_truelist(this->falselist);
            // expression->set_falselist(this->truelist);
            expression->generate_code();
            this->set_truelist(expression->get_falselist());
            this->set_falselist(expression->get_truelist());
        }
        else if (op == OP_Unary::OP_SUB)
        {
            expression->generate_code();
            Code.push_back("\tnegl\t" + R.top());
        }
        else if (op == OP_Unary::OP_INC)
        {
            expression->generate_code();
            if (expression->get_address() == nullptr)
            {
                std::cout << "Error: cannot increment a non-addressable value" << std::endl;
            }
            else
            {
                Code.push_back("\tincl\t" + to_string(expression->get_address()));
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
        this->node_type = ASTNodeType::Int;
    }
    std::vector<std::string> int_astnode::tree_traversal()
    {
        std::vector<std::string> runtime_constants;
        label = 0;
        return runtime_constants;
    }
    void int_astnode::generate_code()
    {
        Code.push_back("\tmovl\t$" + std::to_string(value) + ", " + R.top());
    }

    string_astnode::string_astnode(std::string value)
    {
        this->value = value;
        this->node_type = ASTNodeType::String;
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
    }
    std::string string_astnode::get_reference()
    {
        return reference;
    }

    assignE_astnode::assignE_astnode(expression_astnode *left, expression_astnode *right)
    {
        this->left = left;
        this->right = right;
        this->node_type = ASTNodeType::AssignE;
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
            if (right->get_is_bool())
            {
                std::string M = right->to_arithmetic();
                Code.push_back(M + ":");
            }
            Address *addr = left->get_address();
            if (addr != nullptr)
            {
                // Code.push_back("\tmovl\t" + R.top() + ", " + to_string(addr));
                if(left->get_type()->get_base_type()==BaseType::Int){
                    Code.push_back("\tmovl\t"+R.top()+", "+to_string(addr));
                }
                else if(left->get_type()->get_base_type()==BaseType::Struct){
                    int size = left->get_type()->get_size();
                    for(int i=0;i<size;i+=4){
                        Code.push_back("\tmovl\t"+to_string(right->get_address())+", "+R.top());
                        Code.push_back("\tmovl\t"+R.top()+", "+to_string(addr));
                        right->get_address()->add_offset(4);
                        addr->add_offset(4);
                    }
                }
            }
            else
            {
                std::cout << "Error: left side of assignment is not a variable" << std::endl;
            }
        }
    }

    funcall_astnode::funcall_astnode(std::string name, int local_param_size)
    {
        this->name = name;
        this->local_param_size = local_param_size;
        this->node_type = ASTNodeType::Funcall;
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
        // Save registers
        std::vector<std::string> saved_registers = R.getCallerSaved();
        int saved_regs = 0;
        for (auto reg = saved_registers.begin(); reg != saved_registers.end(); ++reg)
        {
            Code.push_back("\tpushl\t" + *reg);
            saved_regs++;
        }
        // Make space for return value
        int return_size = this->get_type()->get_size();
        Code.push_back("\tsubl\t$" + std::to_string(return_size) + ", %esp");
        for (auto argument = arguments.rbegin(); argument != arguments.rend(); ++argument)
        {
            (*argument)->generate_code();
            Code.push_back("\tpushl\t" + R.top());
        }
        Code.push_back("\tcall\t" + name);
        Code.push_back("\taddl\t$" + std::to_string(local_param_size) + ", %esp");
        // Restore return value
        if(this->get_type()->get_base_type()==BaseType::Int){
            Code.push_back("\tpopl\t" + R.top());
        }
        else if(this->get_type()->get_base_type()==BaseType::Struct){
            // int size = this->get_type()->get_size();
            // for(int i=0;i<size;i+=4){
            //     Code.push_back("\tpopl\t" + R.top());
            //     this->return_address->add_offset(4);
            // }
            Code.push_back("\taddl\t$" + std::to_string(return_size) + ", %esp");
            this->address = new Address(-(saved_regs*4+return_size), "esp");
        }
        // Restore registers
        for (auto reg = saved_registers.rbegin(); reg != saved_registers.rend(); ++reg)
        {
            Code.push_back("\tpopl\t" + *reg);
        }
    }

    seq_astnode::seq_astnode()
    {
        this->node_type = ASTNodeType::Seq;
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
            this->label = std::max(label, statement->get_label());
        }
        return runtime_constants;
    }
    void seq_astnode::generate_code()
    {
        for (auto statement : statements)
        {
            if (statement->get_type() == ASTNodeType::If || statement->get_type() == ASTNodeType::While || statement->get_type() == ASTNodeType::For)
            {
                // statement->set_nextlist(get_new_instruction_label());
                statement->generate_code();
                std::string M = get_new_instruction_label();
                backpatch(statement->get_nextlist(), M);
                Code.push_back(M + ":");
            }
            else
            {
                statement->generate_code();
            }
            Code.push_back("");
        }
    }

    empty_astnode::empty_astnode()
    {
        this->node_type = ASTNodeType::Empty;
    }
    std::vector<std::string> empty_astnode::tree_traversal()
    {
        std::vector<std::string> runtime_constants;
        label = 0;
        return runtime_constants;
    }
    void empty_astnode::generate_code()
    {
    }

    assignS_astnode::assignS_astnode(expression_astnode *assignment_expression)
    {
        this->assignment_expression = assignment_expression;
        this->node_type = ASTNodeType::AssignS;
    }
    std::vector<std::string> assignS_astnode::tree_traversal()
    {
        std::vector<std::string> runtime_constants;
        std::vector<std::string> expression_constants = assignment_expression->tree_traversal();
        runtime_constants.insert(runtime_constants.end(), expression_constants.begin(), expression_constants.end());
        label = assignment_expression->get_label();
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
        this->node_type = ASTNodeType::If;
    }
    std::vector<std::string> if_astnode::tree_traversal()
    {
        std::vector<std::string> runtime_constants;
        std::vector<std::string> condition_constants = condition->tree_traversal();
        runtime_constants.insert(runtime_constants.end(), condition_constants.begin(), condition_constants.end());
        this->label = condition->get_label();
        std::vector<std::string> if_body_constants = if_body->tree_traversal();
        runtime_constants.insert(runtime_constants.end(), if_body_constants.begin(), if_body_constants.end());
        this->label = std::max(label, if_body->get_label());
        std::vector<std::string> else_body_constants = else_body->tree_traversal();
        runtime_constants.insert(runtime_constants.end(), else_body_constants.begin(), else_body_constants.end());
        this->label = std::max(label, else_body->get_label());
        return runtime_constants;
    }
    void if_astnode::generate_code()
    {
        std::string M1 = get_new_instruction_label();
        std::string M2 = get_new_instruction_label();
        condition->generate_code();
        if (!condition->get_is_bool())
        {
            condition->to_boolean();
        }
        Code.push_back(M1 + ":");
        if_body->generate_code();
        std::vector<int> temp = merge(if_body->get_nextlist(), std::vector<int>{nextinstr()});
        Code.push_back("\tjmp\t");
        Code.push_back(M2 + ":");
        else_body->generate_code();
        backpatch(condition->get_truelist(), M1);
        backpatch(condition->get_falselist(), M2);
        this->set_nextlist(merge(temp, else_body->get_nextlist()));
    }

    while_astnode::while_astnode(expression_astnode *condition, statement_astnode *body)
    {
        this->condition = condition;
        this->body = body;
        this->node_type = ASTNodeType::While;
    }
    std::vector<std::string> while_astnode::tree_traversal()
    {
        std::vector<std::string> runtime_constants;
        std::vector<std::string> condition_constants = condition->tree_traversal();
        this->label = condition->get_label();
        runtime_constants.insert(runtime_constants.end(), condition_constants.begin(), condition_constants.end());
        std::vector<std::string> body_constants = body->tree_traversal();
        this->label = std::max(label, body->get_label());
        runtime_constants.insert(runtime_constants.end(), body_constants.begin(), body_constants.end());
        return runtime_constants;
    }
    void while_astnode::generate_code()
    {
        std::string M1 = get_new_instruction_label();
        std::string M2 = get_new_instruction_label();
        Code.push_back(M1 + ":");
        condition->generate_code();
        if (!condition->get_is_bool())
        {
            condition->to_boolean();
        }
        Code.push_back(M2 + ":");
        body->generate_code();
        Code.push_back("\tjmp\t\t" + M1);
        backpatch(condition->get_truelist(), M2);
        backpatch(body->get_nextlist(), M1);
        this->set_nextlist(condition->get_falselist());
    }

    for_astnode::for_astnode(assignE_astnode *init, expression_astnode *condition, assignE_astnode *step, statement_astnode *body)
    {
        this->init = init;
        this->condition = condition;
        this->step = step;
        this->body = body;
        this->node_type = ASTNodeType::For;
    }
    std::vector<std::string> for_astnode::tree_traversal()
    {
        std::vector<std::string> runtime_constants;
        std::vector<std::string> init_constants = init->tree_traversal();
        runtime_constants.insert(runtime_constants.end(), init_constants.begin(), init_constants.end());
        this->label = init->get_label();
        std::vector<std::string> condition_constants = condition->tree_traversal();
        runtime_constants.insert(runtime_constants.end(), condition_constants.begin(), condition_constants.end());
        this->label = std::max(label, condition->get_label());
        std::vector<std::string> step_constants = step->tree_traversal();
        this->label = std::max(label, step->get_label());
        runtime_constants.insert(runtime_constants.end(), step_constants.begin(), step_constants.end());
        std::vector<std::string> body_constants = body->tree_traversal();
        this->label = std::max(label, body->get_label());
        runtime_constants.insert(runtime_constants.end(), body_constants.begin(), body_constants.end());
        return runtime_constants;
    }
    void for_astnode::generate_code()
    {
        std::string M1 = get_new_instruction_label();
        std::string M2 = get_new_instruction_label();
        std::string M3 = get_new_instruction_label();
        init->generate_code();
        Code.push_back(M1 + ":");
        condition->generate_code();
        if (!condition->get_is_bool())
        {
            condition->to_boolean();
        }
        Code.push_back(M2 + ":");
        body->generate_code();
        Code.push_back(M3 + ":");
        step->generate_code();
        Code.push_back("\tjmp\t\t" + M1);
        backpatch(condition->get_truelist(), M2);
        backpatch(body->get_nextlist(), M3);
        this->set_nextlist(condition->get_falselist());
    }

    return_astnode::return_astnode(expression_astnode *expression, int return_address_offset)
    {
        this->expression = expression;
        this->node_type = ASTNodeType::Return;
        this->return_address = new Address(return_address_offset, "ebp");
    }
    std::vector<std::string> return_astnode::tree_traversal()
    {
        std::vector<std::string> runtime_constants;
        if (expression != NULL)
        {
            std::vector<std::string> expression_constants = expression->tree_traversal();
            runtime_constants.insert(runtime_constants.end(), expression_constants.begin(), expression_constants.end());
            this->label = expression->get_label();
        }
        return runtime_constants;
    }
    void return_astnode::generate_code()
    {
        // std::cout<<"return"<<std::endl;
        if (expression != NULL)
        {
            expression->generate_code();
            if(expression->get_type()->get_base_type()==BaseType::Int){
                Code.push_back("\tmovl\t"+R.top()+", "+to_string(this->return_address));
            }
            else if(expression->get_type()->get_base_type()==BaseType::Struct){
                int size = expression->get_type()->get_size();
                for(int i=0;i<size;i+=4){
                    Code.push_back("\tmovl\t"+to_string(expression->get_address())+", "+R.top());
                    Code.push_back("\tmovl\t"+R.top()+", "+to_string(this->return_address));
                    expression->get_address()->add_offset(4);
                    this->return_address->add_offset(4);
                }
            }
        }
    }

    proccall_astnode::proccall_astnode(std::string name, int local_param_size)
    {
        this->name = name;
        this->local_param_size = local_param_size;
        this->node_type = ASTNodeType::Proccall;
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
            this->label = std::max(label, argument->get_label());
        }
        return runtime_constants;
    }
    void proccall_astnode::generate_code()
    {
        // Evaluate arguments in reverese and push into stack
        for (auto argument = arguments.rbegin(); argument != arguments.rend(); ++argument)
        {
            if((*argument)->get_type()->get_base_type()==BaseType::Int){
                (*argument)->generate_code();
                Code.push_back("\tpushl\t" + R.top());
            }
            else if((*argument)->get_type()->get_base_type()==BaseType::Struct){
                int size = (*argument)->get_type()->get_size();
                for(int i=0;i<size;i+=4){
                    Code.push_back("\tmovl\t"+to_string((*argument)->get_address())+", "+R.top());
                    Code.push_back("\tpushl\t" + R.top());
                    (*argument)->get_address()->add_offset(4);
                }
            }
        }
        Code.push_back("\tcall\t" + name);
        Code.push_back("\taddl\t$" + std::to_string(local_param_size) + ", %esp");
    }

    printf_astnode::printf_astnode(string_astnode *format, int local_param_size)
    {
        this->format = format;
        this->local_param_size = local_param_size;
        this->node_type = ASTNodeType::Printf;
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
            this->label = std::max(label, argument->get_label());
        }
        return runtime_constants;
    }
    void printf_astnode::generate_code()
    {
        for (auto argument = arguments.rbegin(); argument != arguments.rend(); ++argument)
        {
            (*argument)->generate_code();
            Code.push_back("\tpushl\t" + R.top());
        }
        Code.push_back("\tpushl\t$" + format->get_reference());
        Code.push_back("\tcall\tprintf");
        Code.push_back("\taddl\t$" + std::to_string(local_param_size) + ", %esp");
    }

    compound_statement::compound_statement(seq_astnode *statements, int local_var_size)
    {
        this->statements = statements;
        this->local_var_size = local_var_size;
    }
    void compound_statement::populate_runtime_constants()
    {
        runtime_constants = statements->tree_traversal();
        this->label = statements->get_label();
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
        Code.clear();
        Code.push_back("\t.globl " + function_name);
        Code.push_back("\t.type " + function_name + ", @function");
        if (statements)
        {
            populate_runtime_constants();
            print_runtime_constants();
            Code.push_back(function_name + ":");
            // Setup Activation Record
            Code.push_back("\tpushl\t%ebp");
            Code.push_back("\tmovl\t%esp, %ebp");
            // Allocate space for local variables
            Code.push_back("\tsubl\t$" + std::to_string(local_var_size) + ", %esp");
            // Save Registers
            std::vector<std::string> registers = R.getCalleeSaved(label);
            for (auto reg : registers)
            {
                Code.push_back("\tpushl\t" + reg);
            }
            // Generate Code for statements
            statements->generate_code();
            // Restore Registers
            for (auto reg = registers.rbegin(); reg != registers.rend(); ++reg)
            {
                Code.push_back("\tpopl\t" + *reg);
            }
            // Reclaim space for local variables
            Code.push_back("\taddl\t$" + std::to_string(local_var_size + 4) + ", %esp");
            // Restore Activation Record
            Code.push_back("\tleave");
            Code.push_back("\tret");
        }
        // Print Code
        for (auto line : Code)
        {
            std::cout << line << std::endl;
        }
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