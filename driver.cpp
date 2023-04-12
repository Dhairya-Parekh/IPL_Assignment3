#include <cstring>
#include <cstddef>
#include <istream>
#include <iostream>
#include <fstream>

#include "scanner.hh"
#include "parser.tab.hh"

IPL::GST* gst = new IPL::GST();
std::map<std::string, IPL::abstract_astnode*> func_ast_map;
std::map<std::string, std::string> predefined {
  {"printf", "void"},
  {"scanf", "void"},
  {"mod", "int"}
};
bool compareGSTEntryByName(IPL::GST_Entry* p1, IPL::GST_Entry* p2) {
    std::string name1 = p1->get_type()==IPL::SymbolType::Struct ? "struct "+ p1->get_name() : p1->get_name();
    std::string name2 = p2->get_type()==IPL::SymbolType::Struct ? "struct "+ p2->get_name() : p2->get_name();
    return name1 < name2;
}
bool compareLSTEntryByName(IPL::LST_Entry* p1, IPL::LST_Entry* p2) {
    std::string name1 = p1->get_type()==IPL::SymbolType::Struct ? "struct "+ p1->get_name() : p1->get_name();
    std::string name2 = p2->get_type()==IPL::SymbolType::Struct ? "struct "+ p2->get_name() : p2->get_name();
    return name1 < name2;
}
int main(const int argc, const char **argv)
{

  using namespace std;
  fstream in_file;

  in_file.open(argv[1], ios::in);
  // Generate a scanner
  IPL::Scanner scanner(in_file);
  // Generate a Parser, passing the scanner as an argument.
  // Remember %parse-param { Scanner  &scanner  }
  IPL::Parser parser(scanner);
  
  #ifdef YYDEBUG
   parser.set_debug_level(1);
  #endif 

  parser.parse();

  IPL::GST *structs = new IPL::GST();
  IPL::GST *functions = new IPL::GST();

  // Add all the structs to the structs GST
  for (auto entry : gst->get_gst_entries())
  {
    if (entry->get_type() == IPL::SymbolType::Struct)
    {
      structs->add_gst_entry(entry);
    }
    else if (entry->get_type() == IPL::SymbolType::Func)
    {
      functions->add_gst_entry(entry);
    }
  }

  // Printing in JSON format
  cout << "{\"globalST\": " << endl;
  gst->print();
  cout << "," << endl;
  cout << "\"structs\": [" << endl;
  std::vector <IPL::GST_Entry*> entries = structs->get_gst_entries();
  for (unsigned int i = 0; i < entries.size(); i++)
  {
    cout << "{\"name\": \"struct " << entries[i]->get_name() << "\", \n \"localST\": " << endl;
    entries[i]->get_lst()->print();
    cout << "}";
    if (i != entries.size() - 1)
    {
      cout << ",";
    }
    cout << endl;
  }
  cout << "]," << endl;
  cout << "\"functions\": [" << endl;
  std::vector <IPL::GST_Entry*> entries2 = functions->get_gst_entries();
  sort(entries2.begin(), entries2.end(),compareGSTEntryByName);
  for (unsigned int i = 0; i < entries2.size(); i++)
  {
    cout << "{\"name\": \"" << entries2[i]->get_name() << "\", \n \"localST\": " << endl;
    entries2[i]->get_lst()->print();
    cout << ", \n \"ast\": ";
    if(func_ast_map[entries2[i]->get_name()]!=nullptr){
      
      func_ast_map[entries2[i]->get_name()]->print(0);
      
    }
    else{
      IPL::seq_astnode* seq = new IPL::seq_astnode();
      seq->print(0);
    }
    cout << "}";
    if (i != entries2.size() - 1)
    {
      cout << ",";
    }
    cout << endl;
  }
  cout << "]" << endl;
  cout << "}" << endl;

}

