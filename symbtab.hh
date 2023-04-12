#ifndef SYMBOLTABLE_HH
#define SYMBOLTABLE_HH

#include "type.hh"
#include <vector>
#include <stack>
#include <algorithm>

namespace IPL
{
    class LST_Entry
    {
    private:
        std::string name_;
        SymbolType type_;
        Scope scope_;
        std::string sub_type_;
        int size_;
        int offset_;

    public:
        LST_Entry(std::string name, SymbolType type, Scope scopke, std::string sub_type, int size, int offset);
        std::string get_name();
        SymbolType get_type();
        Scope get_scope();
        std::string get_type_name();
        std::string get_scope_name();
        std::string get_sub_type();
        int get_size();
        int get_offset();
        void set_name(std::string name);
        void set_type(SymbolType type);
        void set_scope(Scope scope);
        void set_sub_type(std::string sub_type);
        void set_size(int size);
        void set_offset(int offset);
        std::string get_dereferenced_type();
    };

    class LST
    {
    private:
        std::vector<LST_Entry *> lst_entries_;

    public:
        LST();
        bool add_lst_entry(LST_Entry *LST_Entry);
        LST_Entry *get_lst_entry_by_name(std::string name);
        std::vector<LST_Entry *> get_lst_entries();
        int get_size();
        void print();
    };

    class GST_Entry
    {
    private:
        std::string name_;
        SymbolType type_;
        Scope scope_;
        std::string sub_type_;
        int size_;
        int offset_;
        LST *lst_;

    public:
        GST_Entry(std::string name, SymbolType type, Scope scope, std::string sub_type, int size, int offset);
        GST_Entry(std::string name, SymbolType type, Scope scope, std::string sub_type, int size, int offset, LST *lst);
        std::string get_name();
        SymbolType get_type();
        Scope get_scope();
        std::string get_type_name();
        std::string get_scope_name();
        std::string get_sub_type();
        int get_size();
        int get_offset();
        LST *get_lst();
        void set_name(std::string name);
        void set_type(SymbolType type);
        void set_scope(Scope scope);
        void set_sub_type(std::string sub_type);
        void set_size(int size);
        void set_offset(int offset);
        void set_lst(LST *lst);
    };

    class GST
    {
    private:
        std::vector<GST_Entry *> gst_entries_;

    public:
        GST();
        bool add_gst_entry(GST_Entry *GST_Entry);
        GST_Entry *get_gst_entry_by_name(std::string name);
        GST_Entry *get_gst_entry_by_name_and_type(std::string name, SymbolType type);
        GST_Entry *get_gst_entry_by_lst(LST *lst);
        std::vector<GST_Entry *> get_gst_entries();
        void print();
    };

    class Type_Specifier
    {
    private:
        std::string type_;

    public:
        Type_Specifier();
        Type_Specifier(std::string type);
        std::string get_type();
        void set_type(std::string type);
        int get_size(GST *gst);
    };

    class Fun_Declarator
    {
    private:
        std::string name_;

    public:
        Fun_Declarator();
        Fun_Declarator(std::string name);
        void set_name(std::string name);
        std::string get_name();
    };

    class Declaration_List
    {
    private:
        std::vector<LST_Entry *> lst_entries_;

    public:
        Declaration_List();
        void add_lst_entry(LST_Entry *lst_entry);
        std::vector<LST_Entry *> get_lst_entries();
    };

    class Declarator
    {
    private:
        std::string stars_;
        std::string name_;
        int size_;

    public:
        Declarator();
        Declarator(std::string name);
        Declarator(std::string name, int size);
        std::string get_name();
        int get_size();
        std::string get_stars();
        void set_name(std::string name);
        void set_size(int size);
        void set_stars(std::string stars);
    };

    class Declarator_List
    {
    private:
        std::vector<Declarator> declarators_;

    public:
        Declarator_List();
        void add_declarator(Declarator declarator);
        std::vector<Declarator> get_declarators();
    };

    class Parameter_List
    {
    private:
        std::stack<LST_Entry *> parameters_;

    public:
        Parameter_List();
        void add_parameter(LST_Entry *parameter);
        LST_Entry * pop();
    };

}
#endif