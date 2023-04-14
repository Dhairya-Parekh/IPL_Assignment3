#ifndef AST_HH
#define AST_HH

#include "type.hh"
#include <vector>

namespace IPL
{
    class abstract_astnode
    {
    protected:
        std::string code;

    public:
        virtual ~abstract_astnode() {}
        virtual void print() = 0;
    };

    class statement_astnode : public abstract_astnode
    {
    public:
        virtual ~statement_astnode() {}
    };
    class expression_astnode : public abstract_astnode
    {
    public:
        virtual ~expression_astnode() {}
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

    public:
        identifier_astnode(std::string name);
        void print();
    };
    class member_astnode : public reference_astnode
    {
    private:
        expression_astnode *expression;
        identifier_astnode *name;

    public:
        member_astnode(expression_astnode *expression, identifier_astnode *name);
        void print();
    };
    class array_astnode : public reference_astnode
    {
    private:
        expression_astnode *expression;
        expression_astnode *index;

    public:
        array_astnode(expression_astnode *expression, expression_astnode *index);
        void print();
    };
    class arrow_astnode : public reference_astnode
    {
    private:
        expression_astnode *expression;
        identifier_astnode *name;

    public:
        arrow_astnode(expression_astnode *expression, identifier_astnode *name);
        void print();
    };

    class op_binary_astnode : public expression_astnode
    {
    private:
        expression_astnode *left;
        expression_astnode *right;
        OP_Binary op;

    public:
        op_binary_astnode(expression_astnode *left, expression_astnode *right, OP_Binary op);
        void print();
    };
    class op_unary_astnode : public expression_astnode
    {
    private:
        expression_astnode *expression;
        OP_Unary op;

    public:
        op_unary_astnode(expression_astnode *expression, OP_Unary op);
        void print();
    };
    class int_astnode : public expression_astnode
    {
    private:
        int value;

    public:
        int_astnode(int value);
        void print();
    };
    class string_astnode : public expression_astnode
    {
    private:
        std::string value;

    public:
        string_astnode(std::string value);
        void print();
    };
    class assignE_astnode : public expression_astnode
    {
    private:
        expression_astnode *left;
        expression_astnode *right;

    public:
        assignE_astnode(expression_astnode *left, expression_astnode *right);
        void print();
    };
    class funcall_astnode : public expression_astnode
    {
    private:
        identifier_astnode *name;
        std::vector<expression_astnode *> arguments;

    public:
        funcall_astnode(identifier_astnode *name);
        void add_argument(expression_astnode *argument);
        void print();
    };

    class empty_astnode : public statement_astnode
    {
    public:
        empty_astnode();
        void print();
    };
    class seq_astnode : public statement_astnode
    {
    private:
        std::vector<statement_astnode *> statements;

    public:
        seq_astnode();
        void add_statement(statement_astnode *statement);
        void print();
    };
    class assignS_astnode : public statement_astnode
    {
    private:
        expression_astnode *assignment_expression;

    public:
        assignS_astnode(expression_astnode *assignment_expression);
        void print();
    };
    class if_astnode : public statement_astnode
    {
    private:
        expression_astnode *condition;
        statement_astnode *if_body;
        statement_astnode *else_body;

    public:
        if_astnode(expression_astnode *condition, statement_astnode *if_body, statement_astnode *else_body);
        void print();
    };
    class while_astnode : public iteration_astnode
    {
    private:
        expression_astnode *condition;
        statement_astnode *body;

    public:
        while_astnode(expression_astnode *condition, statement_astnode *body);
        void print();
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
        void print();
    };
    class return_astnode : public statement_astnode
    {
    private:
        expression_astnode *expression;

    public:
        return_astnode(expression_astnode *expression);
        void print();
    };
    class proccall_astnode : public statement_astnode
    {
    private:
        std::string name;
        std::vector<expression_astnode *> arguments;

    public:
        proccall_astnode(std::string name);
        void add_argument(expression_astnode *argument);
        void print();
    };
    class printf_astnode : public statement_astnode
    {
    private:
        string_astnode *format;
        std::vector<expression_astnode *> arguments;

    public:
        printf_astnode(string_astnode *format);
        void add_argument(expression_astnode *argument);
        void print();
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