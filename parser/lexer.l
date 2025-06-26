%{
#include "lexer.h"
#include "parser.h"

#define T_eof 0
%}

L [A-Za-z]
D [0-9]
W [ \t\n\r]
ESC_SIMPLE  \\[ntr0'"\\]
ESC_HEX     \\x[0-9a-f]{2}
ESC         ({ESC_SIMPLE}|{ESC_HEX})
STRCHAR     [ -~]

%option noyywrap

%%
"and"       { return T_and; }
"as"        { return T_as; }
"begin"     { return T_begin; }
"break"     { return T_break; }
"byte"      { return T_byte; }
"continue"  { return T_cont; }
"decl"      { return T_decl; }
"def"       { return T_def; }
"elif"      { return T_elif; }
"else"      { return T_else; }
"end"       { return T_end; }
"exit"      { return T_exit; }
"false"     { return T_false; }
"if"        { return T_if; }
"is"        { return T_is; }
"int"       { return T_int; }
"loop"      { return T_loop; }
"not"       { return T_not; }
"or"        { return T_or; }
"ref"       { return T_ref; }
"return"    { return T_ret; }
"skip"      { return T_skip; }
"true"      { return T_true; }
"var"       { return T_var; }

":="        { return T_asgn; }
":"         { return T_col; }
"<="        { return T_leq; }
">="        { return T_geq; }
"<>"        { return T_neq; }

[\+\-\*\/\%\!\&\|\=\<\>\(\)\[\]\,] { return yytext[0]; }

{L}({L}|{D}|_)* { return T_id; }
{D}+            { return T_const; }

'({D}|{L}|{ESC})'   { return T_char; }

\"({STRCHAR}*)\"    { return T_str; }

{W}+                        { /*nothing*/ }
\#.*\n                      { /*nothing*/ }

"(*"(.|\n)*"*)"             {/*nothing*/}

.   { fprintf(stderr, "illegal token\n"); exit(1); }
%%

