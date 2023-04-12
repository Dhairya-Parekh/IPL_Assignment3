#ifndef AST_HH
#define AST_HH

#include "type.hh"
#include <vector>

namespace IPL
{
    class abstract_astnode
    {
    public:
        virtual ~abstract_astnode() {}
        virtual void print(int blanks) = 0;
        enum typeExp astnode_type;
        
    };
    
    class statement_astnode : public abstract_astnode
    {
    public:
        virtual ~statement_astnode() {}
    };
    class expression_astnode : public abstract_astnode
    {
    private:
        std::string type_;
        bool is_lvalue_;
        int cvalue_;
    public:
        virtual ~expression_astnode() {}
        void set_type(std::string type);
        void set_lvalue(bool is_lvalue);
        std::string get_type();
        std::string get_dereferenced_type();
        bool has_lvalue();
        int get_cvalue();
        void set_cvalue(int cvalue);
    };
    class reference_astnode : public expression_astnode
    {
    public:
        virtual ~reference_astnode() {}
    };

    class empty_astnode : public statement_astnode
    {
    public:
        empty_astnode();
        void print(int blanks);
    };
    class seq_astnode : public statement_astnode
    {
    private:
        std::vector<statement_astnode *> statements_;

    public:
        seq_astnode();
        void add_statement(statement_astnode *statement);
        void print(int blanks);
    };
    class assignS_astnode : public statement_astnode
    {
    private:
        expression_astnode *expression1_;
        expression_astnode *expression2_;

    public:
        assignS_astnode(expression_astnode *expression1, expression_astnode *expression2);
        void print(int blanks);
    };
    class if_astnode : public statement_astnode
    {
    private:
        expression_astnode *condition_;
        statement_astnode *then_;
        statement_astnode *else_;

    public:
        if_astnode(expression_astnode *Condition, statement_astnode *Then, statement_astnode *Else);
        void print(int blanks);
    };
    class while_astnode : public statement_astnode
    {
    private:
        expression_astnode *condition_;
        statement_astnode *body_;

    public:
        while_astnode(expression_astnode *condition, statement_astnode *body);
        void print(int blanks);
    };
    class for_astnode : public statement_astnode
    {
    private:
        expression_astnode *init_;
        expression_astnode *condition_;
        expression_astnode *update_;
        statement_astnode *body_;

    public:
        for_astnode(expression_astnode *init, expression_astnode *condition, expression_astnode *update, statement_astnode *body);
        void print(int blanks);
    };
    class return_astnode : public statement_astnode
    {
    private:
        expression_astnode *expression_;

    public:
        return_astnode(expression_astnode *expression);
        void print(int blanks);
    };
    class proccall_astnode : public statement_astnode
    {
    private:
        std::string name_;
        std::vector<expression_astnode *> arguments_;

    public:
        proccall_astnode(std::string name);
        void add_argument(expression_astnode *argument);
        void print(int blanks);
    };

    class op_binary_astnode : public expression_astnode
    {
    private:
        expression_astnode *expression1_;
        expression_astnode *expression2_;
        enum op_binary_type op_;

    public:
        op_binary_astnode(expression_astnode *expression1, expression_astnode *expression2, enum op_binary_type op);
        void print(int blanks);
    };
    class op_unary_astnode : public expression_astnode
    {
    private:
        expression_astnode *expression_;
        enum op_unary_type op_;

    public:
        op_unary_astnode(expression_astnode *expression, enum op_unary_type op);
        void print(int blanks);
    };
    class int_astnode : public expression_astnode
    {
    private:
        int value_;

    public:
        int_astnode(int value);
        void print(int blanks);
    };
    class float_astnode : public expression_astnode
    {
    private:
        float value_;

    public:
        float_astnode(float value);
        void print(int blanks);
    };
    class string_astnode : public expression_astnode
    {
    private:
        std::string value_;

    public:
        string_astnode(std::string value);
        void print(int blanks);
    };
    class assignE_astnode : public expression_astnode
    {
    private:
        expression_astnode *expression1_;
        expression_astnode *expression2_;

    public:
        assignE_astnode(expression_astnode *expression1, expression_astnode *expression2);
        void print(int blanks);
        expression_astnode *get_expression1();
        expression_astnode *get_expression2();
    };
    class funcall_astnode : public expression_astnode
    {
    private:
        std::string name_;
        std::vector<expression_astnode *> arguments_;

    public:
        funcall_astnode(std::string name);
        void add_argument(expression_astnode *argument);
        void print(int blanks);
    };

    class identifier_astnode : public reference_astnode
    {
    private:
        std::string name_;

    public:
        identifier_astnode(std::string name);
        void print(int blanks);
    };
    class member_astnode : public reference_astnode
    {
    private:
        expression_astnode *expression_;
        identifier_astnode *name_;

    public:
        member_astnode(expression_astnode *expression, identifier_astnode *name);
        void print(int blanks);
    };
    class array_astnode : public reference_astnode
    {
    private:
        expression_astnode *expression1_;
        expression_astnode *expression2_;

    public:
        array_astnode(expression_astnode *expression1, expression_astnode *expression2);
        void print(int blanks);
    };
    class arrow_astnode : public reference_astnode
    {
    private:
        expression_astnode *expression_;
        identifier_astnode *name_;

    public:
        arrow_astnode(expression_astnode *expression, identifier_astnode *name);
        void print(int blanks);
    };
    class Compound_Statement {
        private:
            abstract_astnode* ast_;
        public:
            Compound_Statement();
            void set_ast(abstract_astnode* ast);
            abstract_astnode* get_ast();
    };
    class Expression_List {
        private:
            std::vector<expression_astnode*> expressions_;
        public:
            Expression_List();
            void add_expression(expression_astnode* expression);
            std::vector<expression_astnode*> get_expressions();
    };
}

#endif