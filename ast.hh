#ifndef AST_HH
#define AST_HH

#include "type.hh"
#include "rstack.hh"
#include <vector>

namespace IPL
{
    class abstract_astnode
    {
    public:
        virtual ~abstract_astnode() {}
        virtual std::vector<std::string> tree_traversal() = 0;
        virtual void generate_code() = 0;
    };

    class statement_astnode : public abstract_astnode
    {
    public:
        virtual ~statement_astnode() {}
    };
    class expression_astnode : public abstract_astnode
    {
    protected:
        int label;
        Address *address;
    public:
        virtual ~expression_astnode() {}
        int get_label();
        void set_label(int label);
        Address *get_address();
        void set_address(Address *address);
    };
    class reference_astnode : public expression_astnode
    {
    public:
        virtual ~reference_astnode() {}
    };
    class iteration_astnode : public statement_astnode
    {
    public:
        virtual ~iteration_astnode() {}
    };

    class identifier_astnode : public reference_astnode
    {
    private:
        std::string name;
        int offset;

    public:
        identifier_astnode(std::string name, int offset);
        std::vector<std::string> tree_traversal();
        void generate_code();
    };
    class member_astnode : public reference_astnode
    {
    private:
        expression_astnode *expression;
        identifier_astnode *name;

    public:
        member_astnode(expression_astnode *expression, identifier_astnode *name);
        std::vector<std::string> tree_traversal();
        void generate_code();
    };
    class array_astnode : public reference_astnode
    {
    private:
        expression_astnode *expression;
        expression_astnode *index;

    public:
        array_astnode(expression_astnode *expression, expression_astnode *index);
        std::vector<std::string> tree_traversal();
        void generate_code();
    };
    class arrow_astnode : public reference_astnode
    {
    private:
        expression_astnode *expression;
        identifier_astnode *name;

    public:
        arrow_astnode(expression_astnode *expression, identifier_astnode *name);
        std::vector<std::string> tree_traversal();
        void generate_code();
    };

    class op_binary_astnode : public expression_astnode
    {
    private:
        expression_astnode *left;
        expression_astnode *right;
        OP_Binary op;

    public:
        op_binary_astnode(expression_astnode *left, expression_astnode *right, OP_Binary op);
        std::vector<std::string> tree_traversal();
        void generate_code();
    };
    class op_unary_astnode : public expression_astnode
    {
    private:
        expression_astnode *expression;
        OP_Unary op;

    public:
        op_unary_astnode(expression_astnode *expression, OP_Unary op);
        std::vector<std::string> tree_traversal();
        void generate_code();
    };
    class int_astnode : public expression_astnode
    {
    private:
        int value;

    public:
        int_astnode(int value);
        std::vector<std::string> tree_traversal();
        void generate_code();
    };
    class string_astnode : public expression_astnode
    {
    private:
        std::string value;
        std::string reference;

    public:
        string_astnode(std::string value);
        std::vector<std::string> tree_traversal();
        void generate_code();
    };
    class assignE_astnode : public expression_astnode
    {
    private:
        expression_astnode *left;
        expression_astnode *right;
    public:
        assignE_astnode(expression_astnode *left, expression_astnode *right);
        std::vector<std::string> tree_traversal();
        void generate_code();
    };
    class funcall_astnode : public expression_astnode
    {
    private:
        identifier_astnode *name;
        std::vector<expression_astnode *> arguments;

    public:
        funcall_astnode(identifier_astnode *name);
        void add_argument(expression_astnode *argument);
        std::vector<std::string> tree_traversal();
        void generate_code();
    };

    class seq_astnode : public statement_astnode
    {
    private:
        std::vector<statement_astnode*> statements;
    public:
        seq_astnode();
        void add_statement(statement_astnode *statement);
        std::vector<std::string> tree_traversal();
        void generate_code();
    };
    class empty_astnode : public statement_astnode
    {
    public:
        empty_astnode();
        std::vector<std::string> tree_traversal();
        void generate_code();
    };
    class assignS_astnode : public statement_astnode
    {
    private:
        expression_astnode *assignment_expression;

    public:
        assignS_astnode(expression_astnode *assignment_expression);
        std::vector<std::string> tree_traversal();
        void generate_code();
    };
    class if_astnode : public statement_astnode
    {
    private:
        expression_astnode *condition;
        statement_astnode *if_body;
        statement_astnode *else_body;

    public:
        if_astnode(expression_astnode *condition, statement_astnode *if_body, statement_astnode *else_body);
        std::vector<std::string> tree_traversal();
        void generate_code();
    };
    class while_astnode : public iteration_astnode
    {
    private:
        expression_astnode *condition;
        statement_astnode *body;

    public:
        while_astnode(expression_astnode *condition, statement_astnode *body);
        std::vector<std::string> tree_traversal();
        void generate_code();
    };
    class for_astnode : public iteration_astnode
    {
    private:
        assignE_astnode *init;
        expression_astnode *condition;
        assignE_astnode *step;
        statement_astnode *body;

    public:
        for_astnode(assignE_astnode *init, expression_astnode *condition, assignE_astnode *step, statement_astnode *body);
        std::vector<std::string> tree_traversal();
        void generate_code();
    };
    class return_astnode : public statement_astnode
    {
    private:
        expression_astnode *expression;
        int local_var_size;
    public:
        return_astnode(expression_astnode *expression, int local_var_size);
        std::vector<std::string> tree_traversal();
        void generate_code();
    };
    class proccall_astnode : public statement_astnode
    {
    private:
        std::string name;
        std::vector<expression_astnode *> arguments;

    public:
        proccall_astnode(std::string name);
        void add_argument(expression_astnode *argument);
        std::vector<std::string> tree_traversal();
        void generate_code();
    };
    class printf_astnode : public statement_astnode
    {
    private:
        string_astnode *format;
        std::vector<expression_astnode *> arguments;

    public:
        printf_astnode(string_astnode *format);
        void add_argument(expression_astnode *argument);
        std::vector<std::string> tree_traversal();
        void generate_code();
    };
    
    class compound_statement
    {
    private:
        seq_astnode* statements;
        int local_var_size;
        std::vector<std::string> runtime_constants;
    public:
        compound_statement(seq_astnode* statements, int local_var_size);
        void populate_runtime_constants();
        void print_runtime_constants();
        void generate_code(std::string function_name);
    };
    
    class expression_list
    {
    private:
        std::vector<expression_astnode *> expressions;

    public:
        expression_list();
        void add_expression(expression_astnode *expression);
        std::vector<expression_astnode *> get_expressions();
    };
}
#endif