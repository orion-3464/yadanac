#ifndef __LEXER_H__
#define __LEXER_H__

#include "parser.hpp"

int yylex( YYSTYPE* lvalp, YYLTYPE* llocp );
void yyerror ( YYLTYPE *locp, const char *msg );

#endif /* __LEXER_H__ */
