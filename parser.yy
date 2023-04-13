%skeleton "lalr1.cc"
%require  "3.0.1"

%defines 
%define api.namespace {IPL}
%define api.parser.class {Parser}

%define parse.trace

%code requires{
   namespace IPL {
      class Scanner;
   }
   #include "type.hh"
   #include "symbtab.hh"
   #include "location.hh"
}

%printer { std::cerr << $$; } CONSTANT_STRING
%printer { std::cerr << $$; } CONSTANT_INT
%printer { std::cerr << $$; } VOID
%printer { std::cerr << $$; } INT
%printer { std::cerr << $$; } STRUCT
%printer { std::cerr << $$; } FOR
%printer { std::cerr << $$; } WHILE
%printer { std::cerr << $$; } IF
%printer { std::cerr << $$; } ELSE
%printer { std::cerr << $$; } RETURN
%printer { std::cerr << $$; } MAIN
%printer { std::cerr << $$; } PRINTF
%printer { std::cerr << $$; } IDENTIFIER
%printer { std::cerr << $$; } OP_GTE
%printer { std::cerr << $$; } OP_LTE
%printer { std::cerr << $$; } OP_EQ
%printer { std::cerr << $$; } OP_NEQ
%printer { std::cerr << $$; } OP_AND
%printer { std::cerr << $$; } OP_OR
%printer { std::cerr << $$; } OP_INC
%printer { std::cerr << $$; } OP_PTR
%printer { std::cerr << $$; } OP_NOT
%printer { std::cerr << $$; } OP_ADDR
%printer { std::cerr << $$; } OP_GT
%printer { std::cerr << $$; } OP_LT
%printer { std::cerr << $$; } OP_ADD
%printer { std::cerr << $$; } OP_SUB
%printer { std::cerr << $$; } OP_MUL
%printer { std::cerr << $$; } OP_DIV
%printer { std::cerr << $$; } OP_ASSIGN
%printer { std::cerr << $$; } OP_MEM
%printer { std::cerr << $$; } COMMA
%printer { std::cerr << $$; } EOS
%printer { std::cerr << $$; } LRB
%printer { std::cerr << $$; } RRB
%printer { std::cerr << $$; } LCB
%printer { std::cerr << $$; } RCB
%printer { std::cerr << $$; } LSB
%printer { std::cerr << $$; } RSB
%printer { std::cerr << $$; } OTHERS
%printer { std::cerr << $$; } FLOAT
%printer { std::cerr << $$; } CONSTANT_FLOAT

%parse-param { Scanner  &scanner  }
%locations
%code{
   #include <iostream>
      
   #include "scanner.hh"

   #undef yylex
   #define yylex IPL::Parser::scanner.yylex
   using namespace IPL;
   GST* gst = new GST();
   LST* current_lst = NULL;
   int current_offset = 0;
}

%define api.value.type variant
%define parse.assert

%token '\n' '\t'
%token <std::string> CONSTANT_STRING
%token <std::string> CONSTANT_INT
%token <std::string> VOID
%token <std::string> INT
%token <std::string> STRUCT
%token <std::string> FOR
%token <std::string> WHILE
%token <std::string> IF
%token <std::string> ELSE
%token <std::string> RETURN
%token <std::string> MAIN
%token <std::string> PRINTF
%token <std::string> IDENTIFIER
%token <std::string> OP_GTE
%token <std::string> OP_LTE
%token <std::string> OP_EQ
%token <std::string> OP_NEQ
%token <std::string> OP_AND
%token <std::string> OP_OR
%token <std::string> OP_INC
%token <std::string> OP_PTR
%token <std::string> OP_NOT
%token <std::string> OP_ADDR
%token <std::string> OP_GT
%token <std::string> OP_LT
%token <std::string> OP_ADD
%token <std::string> OP_SUB
%token <std::string> OP_MUL
%token <std::string> OP_DIV
%token <std::string> OP_ASSIGN
%token <std::string> OP_MEM
%token <std::string> COMMA
%token <std::string> EOS
%token <std::string> LRB
%token <std::string> RRB
%token <std::string> LCB
%token <std::string> RCB
%token <std::string> LSB
%token <std::string> RSB
%token <std::string> OTHERS
%token <std::string> FLOAT
%token <std::string> CONSTANT_FLOAT
%token <std::string> EOFILE

%nterm <int> program
%nterm <int> main_definition
%nterm <int> translation_unit
%nterm <int> struct_specifier
%nterm <int> function_definition
%nterm <Type*> type_specifier
%nterm <int> declaration_list
%nterm <int> declaration
%nterm <int> declarator_list
%nterm <int> declarator
%nterm <int> declarator_arr
%nterm <int> parameter_list
%nterm <int> parameter_declaration
%nterm <int> compound_statement
%nterm <int> statement_list
%nterm <int> statement
%nterm <int> selection_statement
%nterm <int> iteration_statement
%nterm <int> procedure_call
%nterm <int> printf_call
%nterm <int> expression
%nterm <int> expression_list
%nterm <int> assignment_expression
%nterm <int> logical_and_expression
%nterm <int> equality_expression
%nterm <int> relational_expression
%nterm <int> additive_expression
%nterm <int> multiplicative_expression
%nterm <int> unary_expression
%nterm <int> postfix_expression
%nterm <int> primary_expression
%nterm <int> unary_operator

%start program

%%

program
: main_definition {
   gst->print();
}
| translation_unit main_definition{
   gst->print();
}

translation_unit
: struct_specifier 
| function_definition
| translation_unit struct_specifier
| translation_unit function_definition

struct_specifier
: STRUCT IDENTIFIER {
   LST* lst = new LST();
   GST_Entry* gst_entry = new GST_Entry(
      $1+" "+$2,
      Category::Struct,
      Scope::Global,
      new Type(BaseType::Null),
      0,
      0,
      lst
   );
   bool success = gst->addEntry(gst_entry);
   if(!success) {
      error(@1, "The struct \"" + $2 + "\" has a previous declaration");
   }
   current_lst = lst;
   current_offset = 0;
} LCB declaration_list RCB EOS {
   GST_Entry* gst_entry = gst->getEntry($1+" "+$2);
   gst_entry->setSize(gst_entry->getLST()->getTotalSize());
   current_lst = NULL;
   current_offset = 0;
}

function_definition
: type_specifier IDENTIFIER LRB RRB {
   LST* lst = new LST();
   GST_Entry* gst_entry = new GST_Entry(
      $2,
      Category::Function,
      Scope::Global,
      $1,
      0,
      0,
      lst
   );
   bool success = gst->addEntry(gst_entry);
   if(!success) {
      error(@1, "The function \"" + $2 + "\" has a previous defination");
   }
   current_lst = lst;
   current_offset = 0;
} compound_statement {
   current_lst = NULL;
   current_offset = 0;
}
| type_specifier IDENTIFIER LRB {
   LST* lst = new LST();
   GST_Entry* gst_entry = new GST_Entry(
      $2,
      Category::Function,
      Scope::Global,
      $1,
      0,
      0,
      lst
   );
   bool success = gst->addEntry(gst_entry);
   if(!success) {
      error(@1, "The function \"" + $2 + "\" has a previous defination");
   }
   current_lst = lst;
   current_offset = 12;
} parameter_list RRB {
   current_offset = 0;
} compound_statement {
   current_lst = NULL;
   current_offset = 0;
}

main_definition
: INT MAIN LRB RRB {
   LST* lst = new LST();
   GST_Entry* gst_entry = new GST_Entry(
      $2,
      Category::Function,
      Scope::Global,
      new Type(BaseType::Int),
      0,
      0,
      lst
   );
   bool success = gst->addEntry(gst_entry);
   if(!success) {
      error(@1, "Multiple defination of main function");
   }
   current_lst = lst;
   current_offset = 0;
} compound_statement {
   current_lst = NULL;
   current_offset = 0;
}

type_specifier
: VOID {
   $$ = new Type(BaseType::Void);
}
| INT {
   $$ = new Type(BaseType::Int);
   $$->set_size(4);
}
| STRUCT IDENTIFIER {
   GST_Entry* gst_entry = gst->getEntry($1+" "+$2);
   if(gst_entry == NULL) {
      error(@1, "The struct \"" + $2 + "\" has no previous declaration");
   }
   $$ = new Type(BaseType::Struct, $1+" "+$2);
}

parameter_list
: parameter_declaration
| parameter_list COMMA parameter_declaration

parameter_declaration
: type_specifier declarator

declaration_list
: declaration
| declaration_list declaration

declaration
: type_specifier declarator_list EOS

declarator_list
: declarator
| declarator_list COMMA declarator

declarator
: declarator_arr
| OP_MUL declarator

declarator_arr
: IDENTIFIER
| declarator_arr LSB CONSTANT_INT RSB

compound_statement
: LCB RCB
| LCB statement_list RCB
| LCB declaration_list statement_list RCB

statement_list
: statement
| statement_list statement

statement
: EOS
| LCB statement_list RCB
| assignment_expression EOS
| selection_statement
| iteration_statement
| procedure_call
| printf_call
| RETURN expression EOS

assignment_expression
: unary_expression OP_ASSIGN expression

expression
: logical_and_expression
| expression OP_OR logical_and_expression

logical_and_expression
: equality_expression
| logical_and_expression OP_AND equality_expression

equality_expression
: relational_expression
| equality_expression OP_EQ relational_expression
| equality_expression OP_NEQ relational_expression

relational_expression
: additive_expression
| relational_expression OP_LT additive_expression
| relational_expression OP_GT additive_expression
| relational_expression OP_LTE additive_expression
| relational_expression OP_GTE additive_expression

additive_expression
: multiplicative_expression
| additive_expression OP_ADD multiplicative_expression
| additive_expression OP_SUB multiplicative_expression

multiplicative_expression
: unary_expression
| multiplicative_expression OP_MUL unary_expression
| multiplicative_expression OP_DIV unary_expression

unary_expression
: postfix_expression
| unary_operator unary_expression

postfix_expression
: primary_expression
| postfix_expression OP_INC
| IDENTIFIER LRB RRB
| IDENTIFIER LRB expression_list RRB
| postfix_expression OP_MEM IDENTIFIER
| postfix_expression OP_PTR IDENTIFIER
| postfix_expression LSB expression RSB

primary_expression
: IDENTIFIER
| CONSTANT_INT
| LRB expression RRB

unary_operator
: OP_SUB
| OP_NOT
| OP_ADDR
| OP_MUL

selection_statement
: IF LRB expression RRB statement ELSE statement

iteration_statement
: WHILE LRB expression RRB statement
| FOR LRB assignment_expression EOS expression EOS assignment_expression RRB statement

procedure_call
: IDENTIFIER LRB RRB EOS
| IDENTIFIER LRB expression_list RRB EOS

printf_call
: PRINTF LRB CONSTANT_STRING RRB EOS
| PRINTF LRB CONSTANT_STRING COMMA expression_list RRB EOS

expression_list
: expression
| expression_list COMMA expression

%%

void 
IPL::Parser::error( const location_type &l, const std::string &err_message )
{
   std::cout << "Error at line " << l.begin.line << ": " << err_message <<"\n";
   exit(1);
}

