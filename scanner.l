%{
       #include "scanner.hh"
       #include "parser.tab.hh"
       #undef  YY_DECL
       #define YY_DECL int IPL::Scanner::yylex( IPL::Parser::semantic_type * const lval, IPL::Parser::location_type *location )
       #define YY_USER_ACTION loc->step(); loc->columns(yyleng);
       using token_type = IPL::Parser::token;
%}

/* %option debug */
%option nodefault
%option yyclass="Scanner"
%option noyywrap
%option c++

%%

%{
       yylval = lval;
       loc = location;
%}

[ \t]
[ \n]  loc->lines();
\/\*.*?\*\/
\/\/.*?
\"([^\"\\]|\\n|\\t|\\\\|\\\")*\"                 { yylval->emplace< std::string >(YYText()); return token_type::CONSTANT_STRING; }
[1-9][[:digit:]]*                                { yylval->emplace< std::string >(YYText()); return token_type::CONSTANT_INT; }
0[bB][01]*                                       { yylval->emplace< std::string >(YYText()); return token_type::CONSTANT_INT; }
0[0-7]*                                          { yylval->emplace< std::string >(YYText()); return token_type::CONSTANT_INT; }
0[xX][0-9a-fA-F]*                                { yylval->emplace< std::string >(YYText()); return token_type::CONSTANT_INT; }
void                                             { yylval->emplace< std::string >(YYText()); return token_type::VOID; }
int                                              { yylval->emplace< std::string >(YYText()); return token_type::INT; }
struct                                           { yylval->emplace< std::string >(YYText()); return token_type::STRUCT; }
for                                              { yylval->emplace< std::string >(YYText()); return token_type::FOR; }
while                                            { yylval->emplace< std::string >(YYText()); return token_type::WHILE; }
if                                               { yylval->emplace< std::string >(YYText()); return token_type::IF; }
else                                             { yylval->emplace< std::string >(YYText()); return token_type::ELSE; }
return                                           { yylval->emplace< std::string >(YYText()); return token_type::RETURN; }
main                                             { yylval->emplace< std::string >(YYText()); return token_type::MAIN; }
printf                                           { yylval->emplace< std::string >(YYText()); return token_type::PRINTF; }
[a-zA-Z_][a-zA-Z0-9_]*                           { yylval->emplace< std::string >(YYText()); return token_type::IDENTIFIER; }
">="                                             { yylval->emplace< std::string >(YYText()); return token_type::OP_GTE; }
"<="                                             { yylval->emplace< std::string >(YYText()); return token_type::OP_LTE; }
"=="                                             { yylval->emplace< std::string >(YYText()); return token_type::OP_EQ; }
"!="                                             { yylval->emplace< std::string >(YYText()); return token_type::OP_NEQ; }
"&&"                                             { yylval->emplace< std::string >(YYText()); return token_type::OP_AND; }
"||"                                             { yylval->emplace< std::string >(YYText()); return token_type::OP_OR; }
"++"                                             { yylval->emplace< std::string >(YYText()); return token_type::OP_INC; }
"->"                                             { yylval->emplace< std::string >(YYText()); return token_type::OP_PTR; }
"!"                                              { yylval->emplace< std::string >(YYText()); return token_type::OP_NOT; }
"&"                                              { yylval->emplace< std::string >(YYText()); return token_type::OP_ADDR; }
">"                                              { yylval->emplace< std::string >(YYText()); return token_type::OP_GT; }
"<"                                              { yylval->emplace< std::string >(YYText()); return token_type::OP_LT; }
"+"                                              { yylval->emplace< std::string >(YYText()); return token_type::OP_ADD; }
"-"                                              { yylval->emplace< std::string >(YYText()); return token_type::OP_SUB; }
"*"                                              { yylval->emplace< std::string >(YYText()); return token_type::OP_MUL; }
"/"                                              { yylval->emplace< std::string >(YYText()); return token_type::OP_DIV; }
"="                                              { yylval->emplace< std::string >(YYText()); return token_type::OP_ASSIGN; }
"."                                              { yylval->emplace< std::string >(YYText()); return token_type::OP_MEM; }
","                                              { yylval->emplace< std::string >(YYText()); return token_type::COMMA; }
";"                                              { yylval->emplace< std::string >(YYText()); return token_type::EOS; }
"("                                              { yylval->emplace< std::string >(YYText()); return token_type::LRB; }
")"                                              { yylval->emplace< std::string >(YYText()); return token_type::RRB; }
"{"                                              { yylval->emplace< std::string >(YYText()); return token_type::LCB; }
"}"                                              { yylval->emplace< std::string >(YYText()); return token_type::RCB; }
"["                                              { yylval->emplace< std::string >(YYText()); return token_type::LSB; }
"]"                                              { yylval->emplace< std::string >(YYText()); return token_type::RSB; }
.                                                { yylval->emplace< std::string >(YYText()); return token_type::OTHERS; }
<<EOF>>                                           yyterminate();
float                                            { yylval->emplace< std::string >(YYText()); return token_type::FLOAT; }
[[:digit:]]+\.[[:digit:]]*                       { yylval->emplace< std::string >(YYText()); return token_type::CONSTANT_FLOAT; }
[[:digit:]]+\.[[:digit:]]*[eE][+-]?[[:digit:]]+  { yylval->emplace< std::string >(YYText()); return token_type::CONSTANT_FLOAT; }
\.[[:digit:]]+                                   { yylval->emplace< std::string >(YYText()); return token_type::CONSTANT_FLOAT; }
\.[[:digit:]]*[eE][+-]?[[:digit:]]+              { yylval->emplace< std::string >(YYText()); return token_type::CONSTANT_FLOAT; }

%%

