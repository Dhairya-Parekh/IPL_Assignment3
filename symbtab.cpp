#include "symbtab.hh"
#include <iostream>

namespace IPL
{
    bool compareGSTEntryByName(IPL::GST_Entry *p1, IPL::GST_Entry *p2)
    {
        std::string name1 = p1->get_type() == IPL::SymbolType::Struct ? "struct " + p1->get_name() : p1->get_name();
        std::string name2 = p2->get_type() == IPL::SymbolType::Struct ? "struct " + p2->get_name() : p2->get_name();
        return name1 < name2;
    }
    bool compareLSTEntryByName(IPL::LST_Entry *p1, IPL::LST_Entry *p2)
    {
        std::string name1 = p1->get_type() == IPL::SymbolType::Struct ? "struct " + p1->get_name() : p1->get_name();
        std::string name2 = p2->get_type() == IPL::SymbolType::Struct ? "struct " + p2->get_name() : p2->get_name();
        return name1 < name2;
    }
    GST_Entry::GST_Entry(std::string name, SymbolType type, Scope scope, std::string sub_type, int size, int offset)
    {
        name_ = name;
        type_ = type;
        scope_ = scope;
        sub_type_ = sub_type;
        size_ = size;
        offset_ = offset;
        lst_ = NULL;
    }
    GST_Entry::GST_Entry(std::string name, SymbolType type, Scope scope, std::string sub_type, int size, int offset, LST *lst)
    {
        name_ = name;
        type_ = type;
        scope_ = scope;
        sub_type_ = sub_type;
        size_ = size;
        offset_ = offset;
        lst_ = lst;
    }
    std::string GST_Entry::get_name()
    {
        return name_;
    }
    SymbolType GST_Entry::get_type()
    {
        return type_;
    }
    Scope GST_Entry::get_scope()
    {
        return scope_;
    }
    std::string GST_Entry::get_type_name()
    {
        switch (type_)
        {
        case SymbolType::Var:
            return "var";
        case SymbolType::Const:
            return "const";
        case SymbolType::Func:
            return "fun";
        case SymbolType::Struct:
            return "struct";
        default:
            return "unknown";
        }
    }
    std::string GST_Entry::get_scope_name()
    {
        switch (scope_)
        {
        case Scope::Global:
            return "global";
        case Scope::Local:
            return "local";
        case Scope::Param:
            return "param";
        default:
            return "unknown";
        }
    }
    std::string GST_Entry::get_sub_type()
    {
        return sub_type_;
    }
    int GST_Entry::get_size()
    {
        return size_;
    }
    int GST_Entry::get_offset()
    {
        return offset_;
    }
    LST *GST_Entry::get_lst()
    {
        return lst_;
    }
    void GST_Entry::set_name(std::string name)
    {
        name_ = name;
    }
    void GST_Entry::set_type(SymbolType type)
    {
        type_ = type;
    }
    void GST_Entry::set_scope(Scope scope)
    {
        scope_ = scope;
    }
    void GST_Entry::set_sub_type(std::string sub_type)
    {
        sub_type_ = sub_type;
    }
    void GST_Entry::set_size(int size)
    {
        size_ = size;
    }
    void GST_Entry::set_offset(int offset)
    {
        offset_ = offset;
    }
    void GST_Entry::set_lst(LST *lst)
    {
        lst_ = lst;
    }

    LST_Entry::LST_Entry(std::string name, SymbolType type, Scope scope, std::string sub_type, int size, int offset)
    {
        name_ = name;
        type_ = type;
        scope_ = scope;
        sub_type_ = sub_type;
        size_ = size;
        offset_ = offset;
    }
    std::string LST_Entry::get_name()
    {
        return name_;
    }
    SymbolType LST_Entry::get_type()
    {
        return type_;
    }
    Scope LST_Entry::get_scope()
    {
        return scope_;
    }
    std::string LST_Entry::get_type_name()
    {
        switch (type_)
        {
        case SymbolType::Var:
            return "var";
        case SymbolType::Const:
            return "const";
        case SymbolType::Func:
            return "fun";
        case SymbolType::Struct:
            return "struct";
        default:
            return "unknown";
        }
    }
    std::string LST_Entry::get_scope_name()
    {
        switch (scope_)
        {
        case Scope::Global:
            return "global";
        case Scope::Local:
            return "local";
        case Scope::Param:
            return "param";
        default:
            return "unknown";
        }
    }
    std::string LST_Entry::get_sub_type()
    {
        return sub_type_;
    }
    std::string LST_Entry::get_dereferenced_type()
    {
        std::string str = sub_type_;
        size_t star_pos = str.find("*"); // find the first occurrence of "*"
        size_t int_pos = str.find("[");  // find the first occurrence of "["

        if (star_pos != std::string::npos)
        {
            str.erase(star_pos, 1); // remove the first occurrence of "*"
        }
        else if (int_pos != std::string::npos)
        {
            size_t int_end_pos = str.find("]", int_pos); // find the corresponding "]"
            if (int_end_pos != std::string::npos)
            {
                str.erase(int_pos, int_end_pos - int_pos + 1); // remove the first occurrence of "[INT]"
            }
        }
        else
        {
            str = ""; // return an empty string if no pattern is found
        }
        return str;   
    }
    int LST_Entry::get_size()
    {
        return size_;
    }
    int LST_Entry::get_offset()
    {
        return offset_;
    }
    void LST_Entry::set_name(std::string name)
    {
        name_ = name;
    }
    void LST_Entry::set_type(SymbolType type)
    {
        type_ = type;
    }
    void LST_Entry::set_scope(Scope scope)
    {
        scope_ = scope;
    }
    void LST_Entry::set_sub_type(std::string sub_type)
    {
        sub_type_ = sub_type;
    }
    void LST_Entry::set_size(int size)
    {
        size_ = size;
    }
    void LST_Entry::set_offset(int offset)
    {
        offset_ = offset;
    }

    GST::GST()
    {
        gst_entries_ = std::vector<GST_Entry *>();
    }
    GST_Entry *GST::get_gst_entry_by_name(std::string name)
    {
        for (unsigned int i = 0; i < gst_entries_.size(); i++)
        {
            if (gst_entries_[i]->get_name() == name)
            {
                return gst_entries_[i];
            }
        }
        return nullptr;
    }
    GST_Entry *GST::get_gst_entry_by_name_and_type(std::string name, SymbolType type)
    {
        for (unsigned int i = 0; i < gst_entries_.size(); i++)
        {
            if (gst_entries_[i]->get_name() == name && gst_entries_[i]->get_type() == type)
            {
                return gst_entries_[i];
            }
        }
        return nullptr;
    }
    bool GST::add_gst_entry(GST_Entry *entry)
    {
        std::string name = entry->get_name();
        SymbolType type = entry->get_type();
        GST_Entry *gst_entry = get_gst_entry_by_name_and_type(name, type);
        if (gst_entry != nullptr)
        {
            return false;
        }
        gst_entries_.push_back(entry);
        return true;
    }
    GST_Entry *GST::get_gst_entry_by_lst(LST *lst)
    {
        for (unsigned int i = 0; i < gst_entries_.size(); i++)
        {
            if (gst_entries_[i]->get_lst() == lst)
            {
                return gst_entries_[i];
            }
        }
        return nullptr;
    }
    std::vector<GST_Entry *> GST::get_gst_entries()
    {
        return gst_entries_;
    }
    void GST::print()
    {
        std::sort(gst_entries_.begin(), gst_entries_.end(), compareGSTEntryByName);
        std::cout << "[\n";
        for (unsigned int i = 0; i < gst_entries_.size(); i++)
        {
            std::cout << "\t\t[\n";
            if (gst_entries_[i]->get_type() == SymbolType::Struct)
            {
                std::cout << "\t\t\t\""
                          << "struct " << gst_entries_[i]->get_name() << "\",\n";
            }
            else
            {
                std::cout << "\t\t\t\"" << gst_entries_[i]->get_name() << "\",\n";
            }
            std::cout << "\t\t\t\"" << gst_entries_[i]->get_type_name() << "\",\n";
            std::cout << "\t\t\t\"" << gst_entries_[i]->get_scope_name() << "\",\n";
            if (gst_entries_[i]->get_type() == SymbolType::Func)
            {
                std::cout << "\t\t\t" << 0 << ",\n";
            }
            else
            {
                std::cout << "\t\t\t" << gst_entries_[i]->get_size() << ",\n";
            }
            if (gst_entries_[i]->get_type() == SymbolType::Struct)
            {
                std::cout << "\t\t\t"
                          << "\"-\""
                          << ",\n";
            }
            else
            {
                std::cout << "\t\t\t" << gst_entries_[i]->get_offset() << ",\n";
            }
            std::cout << "\t\t\t\"" << gst_entries_[i]->get_sub_type() << "\"\n";
            if (i == gst_entries_.size() - 1)
            {
                std::cout << "\t\t]\n";
            }
            else
            {
                std::cout << "\t\t],\n";
            }
        }
        std::cout << "]\n";
    }

    LST::LST()
    {
        lst_entries_ = std::vector<LST_Entry *>();
    }
    LST_Entry *LST::get_lst_entry_by_name(std::string name)
    {
        for (unsigned int i = 0; i < lst_entries_.size(); i++)
        {
            if (lst_entries_[i]->get_name() == name)
            {
                return lst_entries_[i];
            }
        }
        return nullptr;
    }
    bool LST::add_lst_entry(LST_Entry *entry)
    {
        std::string name = entry->get_name();
        SymbolType type = entry->get_type();
        LST_Entry *lst_entry = get_lst_entry_by_name(name);
        if (lst_entry != nullptr && lst_entry->get_type() == type)
        {
            return false;
        }
        lst_entries_.push_back(entry);
        return true;
    }
    std::vector<LST_Entry *> LST::get_lst_entries()
    {
        return lst_entries_;
    }
    int LST::get_size()
    {
        int total_size = 0;
        for (unsigned int i = 0; i < lst_entries_.size(); i++)
        {
            total_size += lst_entries_[i]->get_size();
        }
        return total_size;
    }
    void LST::print()
    {
        std::sort(lst_entries_.begin(), lst_entries_.end(), compareLSTEntryByName);
        std::cout << "[\n";
        for (unsigned int i = 0; i < lst_entries_.size(); i++)
        {
            std::cout << "\t\t[\n";
            if (lst_entries_[i]->get_type() == SymbolType::Struct)
            {
                std::cout << "\t\t\t\""
                          << "struct " << lst_entries_[i]->get_name() << "\",\n";
            }
            else
            {
                std::cout << "\t\t\t\"" << lst_entries_[i]->get_name() << "\",\n";
            }
            std::cout << "\t\t\t\"" << lst_entries_[i]->get_type_name() << "\",\n";
            std::cout << "\t\t\t\"" << lst_entries_[i]->get_scope_name() << "\",\n";
            std::cout << "\t\t\t" << lst_entries_[i]->get_size() << ",\n";
            std::cout << "\t\t\t" << lst_entries_[i]->get_offset() << ",\n";
            std::cout << "\t\t\t\"" << lst_entries_[i]->get_sub_type() << "\"\n";
            if (i == lst_entries_.size() - 1)
            {
                std::cout << "\t\t]\n";
            }
            else
            {
                std::cout << "\t\t],\n";
            }
        }
        std::cout << "]\n";
    }

    // Type_Specifier Class Methods
    Type_Specifier::Type_Specifier()
    {
        type_ = "";
    }
    Type_Specifier::Type_Specifier(std::string type)
    {
        type_ = type;
    }
    std::string Type_Specifier::get_type()
    {
        return type_;
    }
    void Type_Specifier::set_type(std::string type)
    {
        type_ = type;
    }
    int Type_Specifier::get_size(GST *gst)
    {
        if (type_ == "int")
        {
            return 4;
        }
        else if (type_ == "float")
        {
            return 4;
        }
        else if (type_ == "void")
        {
            return 0;
        }
        else if (type_.compare(0, 6, "struct") == 0)
        {
            return gst->get_gst_entry_by_name(type_.substr(7))->get_size();
        }
        return 0;
    }

    // Fun_Declarator Class Methods
    Fun_Declarator::Fun_Declarator()
    {
        name_ = "";
    }
    Fun_Declarator::Fun_Declarator(std::string name)
    {
        name_ = name;
    }
    std::string Fun_Declarator::get_name()
    {
        return name_;
    }
    void Fun_Declarator::set_name(std::string name)
    {
        name_ = name;
    }

    // Declaration List Class Methods
    Declaration_List::Declaration_List()
    {
        lst_entries_ = std::vector<LST_Entry *>();
    }
    void Declaration_List::add_lst_entry(LST_Entry *lst_entry)
    {
        lst_entries_.push_back(lst_entry);
    }
    std::vector<LST_Entry *> Declaration_List::get_lst_entries()
    {
        return lst_entries_;
    }

    // Declarator Class Methods
    Declarator::Declarator()
    {
        stars_ = "";
        name_ = "";
        size_ = 1;
    }
    Declarator::Declarator(std::string name)
    {
        stars_ = "";
        name_ = name;
        size_ = 1;
    }
    Declarator::Declarator(std::string name, int size)
    {
        stars_ = "";
        name_ = name;
        this->size_ = size;
    }
    std::string Declarator::get_name()
    {
        return name_;
    }
    std::string Declarator::get_stars()
    {
        return stars_;
    }
    int Declarator::get_size()
    {
        return size_;
    }
    void Declarator::set_name(std::string name)
    {
        name_ = name;
    }
    void Declarator::set_stars(std::string stars)
    {
        stars_ = stars;
    }
    void Declarator::set_size(int size)
    {
        this->size_ = size;
    }

    // Declarator_List Class Methods
    Declarator_List::Declarator_List()
    {
        declarators_ = std::vector<Declarator>();
    }
    void Declarator_List::add_declarator(Declarator declarator)
    {
        declarators_.push_back(declarator);
    }
    std::vector<Declarator> Declarator_List::get_declarators()
    {
        return declarators_;
    }

    // Parameter Class Methods
    Parameter_List::Parameter_List()
    {
        parameters_ = std::stack<LST_Entry *>();
    }
    void Parameter_List::add_parameter(LST_Entry *parameter)
    {
        parameters_.push(parameter);
    }
    LST_Entry *Parameter_List::pop()
    {
        if (parameters_.empty())
        {
            return nullptr;
        }
        LST_Entry *temp = parameters_.top();
        parameters_.pop();
        return temp;
    }

}