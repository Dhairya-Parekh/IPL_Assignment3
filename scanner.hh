
/*If FlexLexer.h has not been included before */

#if !defined(yyFlexLexerOnce)
 #include <FlexLexer.h>
#endif
// parser.tab.hh defines 
// struct token
//     {
//       enum yytokentype
//       {
//         MNEMONIC = 258,
//         SYMBOL = 259,
//         ...

struct token
{
   enum yytokentype
   {
      STRUCT = 258,
      IF = 259,
      ELSE = 260,
      RETURN = 261,
      FOR = 262,
      WHILE = 263,
      VOID = 264,
      INT = 265,
      FLOAT = 266,
      OR_OP = 267,
      AND_OP = 268,
      EQ_OP = 269,
      NE_OP = 270,
      LE_OP = 271,
      GE_OP = 272,
      INC_OP = 273,
      PTR_OP = 274,
      INT_CONSTANT = 275,
      FLOAT_CONSTANT = 276,
      STRING_LITERAL = 277,
      IDENTIFIER = 278,
      EOFILE = 279,
      OTHERS = 280,
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


