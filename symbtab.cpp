#include "symbtab.hh"
#include <iostream>

namespace IPL
{
    LST_Entry::LST_Entry(std::string name, Category category, Scope scope, Type *type, int size, int offset) : name(name), category(category), scope(scope), type(type), size(size), offset(offset) {}
    std::string LST_Entry::getName() { return name; }
    Category LST_Entry::getCategory() { return category; }
    Scope LST_Entry::getScope() { return scope; }
    Type *LST_Entry::getType() { return type; }
    int LST_Entry::getSize() { return size; }
    int LST_Entry::getOffset() { return offset; }
    void LST_Entry::setName(std::string name) { this->name = name; }
    void LST_Entry::setCategory(Category category) { this->category = category; }
    void LST_Entry::setScope(Scope scope) { this->scope = scope; }
    void LST_Entry::setType(Type *type) { this->type = type; }
    void LST_Entry::setSize(int size) { this->size = size; }
    void LST_Entry::setOffset(int offset) { this->offset = offset; }

    LST::LST() {}
    bool LST::addEntry(LST_Entry *entry)
    {
        if (contains(entry->getName()))
        {
            return false;
        }
        lst.push_back(entry);
        return true;
    }
    LST_Entry *LST::getEntry(std::string name)
    {
        for (auto entry : lst)
        {
            if (entry->getName() == name)
            {
                return entry;
            }
        }
        return nullptr;
    }
    bool LST::contains(std::string name)
    {
        for (auto entry : lst)
        {
            if (entry->getName() == name)
            {
                return true;
            }
        }
        return false;
    }
    int LST::getLocalVarSize()
    {
        int total_size = 0;
        for (auto entry : lst)
        {
            if (entry->getScope() == Scope::Local)
                total_size += entry->getSize();
        }
        return total_size;
    }
    int LST::getLocalParamSize()
    {
        int total_size = 0;
        for (auto entry : lst)
        {
            if (entry->getScope() == Scope::Param)
                total_size += entry->getSize();
        }
        return total_size;
    }
    void LST::print()
    {
        std::cout << "Name\tCategory\tScope\tType\tSize\tOffset" << std::endl;
        for (auto entry : lst)
        {
            std::cout << entry->getName() << "\t" << to_string(entry->getCategory()) << "\t" << to_string(entry->getScope()) << "\t" << to_string(entry->getType()) << "\t" << entry->getSize() << "\t" << entry->getOffset() << std::endl;
        }
    }

    GST_Entry::GST_Entry(std::string name, Category category, Scope scope, Type *type, int size, int offset, LST *lst) : LST_Entry(name, category, scope, type, size, offset), lst(lst) {}
    LST *GST_Entry::getLST() { return lst; }
    void GST_Entry::setLST(LST *lst) { this->lst = lst; }

    GST::GST() {}
    bool GST::addEntry(GST_Entry *entry)
    {
        if (contains(entry->getName()))
        {
            return false;
        }
        gst.push_back(entry);
        return true;
    }
    GST_Entry *GST::getEntry(std::string name)
    {
        for (auto entry : gst)
        {
            if (entry->getName() == name)
            {
                return entry;
            }
        }
        return nullptr;
    }
    bool GST::contains(std::string name)
    {
        for (auto entry : gst)
        {
            if (entry->getName() == name)
            {
                return true;
            }
        }
        return false;
    }
    void GST::print()
    {
        std::cout << "Global Symbol Table" << std::endl;
        std::cout << "Name\tCategory\tScope\tType\tSize\tOffset" << std::endl;
        for (auto entry : gst)
        {
            std::cout << entry->getName() << "\t" << to_string(entry->getCategory()) << "\t" << to_string(entry->getScope()) << "\t" << to_string(entry->getType()) << "\t" << entry->getSize() << "\t" << entry->getOffset() << std::endl;
        }
        for (auto entry : gst)
        {
            std::cout << "\nLocal Symbol Table for " << entry->getName() << std::endl;
            entry->getLST()->print();
        }
    }

    Declarator::Declarator(std::string name) : name(name) { this->stars = 0; }
    std::string Declarator::getName() { return name; }
    int Declarator::getStars() { return stars; }
    std::vector<int> Declarator::getArrays() { return arrays; }
    void Declarator::setName(std::string name) { this->name = name; }
    void Declarator::setStars(int stars) { this->stars = stars; }
    void Declarator::addToArray(int size) { arrays.push_back(size); }

    DeclaratorList::DeclaratorList() {}
    void DeclaratorList::addDeclarator(Declarator *declarator) { declarators.push_back(declarator); }
    std::vector<Declarator *> DeclaratorList::getDeclarators() { return declarators; }

    Parameter::Parameter(Type *type, std::string name) : type(type), name(name) {}
    Type *Parameter::getType() { return type; }
    std::string Parameter::getName() { return name; }

    ParameterList::ParameterList() {}
    void ParameterList::addParameter(Parameter *parameter) { parameters.push_back(parameter); }
    std::vector<Parameter *> ParameterList::getParameters() { return parameters; }
}