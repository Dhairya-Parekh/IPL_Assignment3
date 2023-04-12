#if !defined(yyFlexLexerOnce)
 #include <FlexLexer.h>
#endif

struct token
{
   enum yytokentype
   {
      CONSTANT_STRING = 258,
      CONSTANT_INT = 259,
      VOID = 261,
      INT = 262,
      STRUCT = 263,
      FOR = 264,
      WHILE = 265,
      IF = 266,
      ELSE = 267,
      RETURN = 268,
      MAIN = 269,
      PRINTF = 270,
      IDENTIFIER = 271,
      OP_GTE = 272,
      OP_LTE = 273,
      OP_EQ = 274,
      OP_NEQ = 275,
      OP_AND = 276,
      OP_OR = 277,
      OP_INC = 278,
      OP_PTR = 279,
      OP_NOT = 280,
      OP_ADDR = 281,
      OP_GT = 282,
      OP_LT = 283,
      OP_ADD = 284,
      OP_SUB = 285,
      OP_MUL = 286,
      OP_DIV = 287,
      OP_ASSIGN = 288,
      OP_MEM = 289,
      COMMA = 290,
      EOS = 291,
      LRB = 292,
      RRB = 293,
      LCB = 294,
      RCB = 295,
      LSB = 296,
      RSB = 297,
      OTHERS = 298,
      FLOAT = 299,
      CONSTANT_FLOAT = 300,
      EOFILE = 301,
   };
};

#include "parser.tab.hh"
#include "location.hh"

namespace IPL
{
   class Scanner : public yyFlexLexer
   {
   public:
      Scanner(std::istream& in) : yyFlexLexer(in, std::cout)
      {
         loc = new IPL::Parser::location_type();
      };


      virtual int yylex(IPL::Parser::semantic_type *const lval,
                        IPL::Parser::location_type *location);

   private:
      /* yyval ptr */
      IPL::Parser::semantic_type *yylval = nullptr;
      /* location ptr */
      IPL::Parser::location_type *loc = nullptr;
   };

} /* end namespace IPL */

//#endif /* END __IPLSCANNER_HPP__ */


