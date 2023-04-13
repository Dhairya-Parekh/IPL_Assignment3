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
    protected:
        std::string name;
        Category category;
        Scope scope;
        Type *type;
        int size;
        int offset;

    public:
        LST_Entry(std::string name, Category category, Scope scope, Type *type, int size, int offset);
        std::string getName();
        Category getCategory();
        Scope getScope();
        Type *getType();
        int getSize();
        int getOffset();
        void setName(std::string name);
        void setCategory(Category category);
        void setScope(Scope scope);
        void setType(Type *type);
        void setSize(int size);
        void setOffset(int offset);
    };

    class LST
    {
    private:
        std::vector<LST_Entry *> lst;

    public:
        LST();
        bool addEntry(LST_Entry *entry);
        LST_Entry *getEntry(std::string name);
        bool contains(std::string name);
        int getTotalSize();
    };

    class GST_Entry : public LST_Entry
    {
    private:
        LST *lst;

    public:
        GST_Entry(std::string name, Category category, Scope scope, Type *type, int size, int offset, LST *lst);
        LST *getLST();
        void setLST(LST *lst);
    };

    class GST
    {
    private:
        std::vector<GST_Entry *> gst;

    public:
        GST();
        bool addEntry(GST_Entry *entry);
        GST_Entry *getEntry(std::string name);
        bool contains(std::string name);
        void print();
    };
}
#endif