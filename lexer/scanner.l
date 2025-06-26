%{
#define T_eof   0

#define T_and   1000
#define T_as    1001
#define T_begin 1002
#define T_break 1003
#define T_byte  1004
#define T_cont  1005
#define T_decl  1006
#define T_def   1007
#define T_elif  1008
#define T_else  1009
#define T_end   1010
#define T_exit  1011
#define T_false 1012
#define T_if    1013
#define T_is    1014
#define T_int   1015
#define T_loop  1016
#define T_not   1017
#define T_or    1018
#define T_ref   1019
#define T_ret   1020
#define T_skip  1021
#define T_true  1022
#define T_var   1023

#define T_asgn  1024
#define T_col   1025
#define T_geq   1026
#define T_leq   1027
#define T_neq   1028

#define T_id    1029
#define T_const 1030
#define T_str   1031
#define T_char  1032
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

int main() {
  int token;
  do {
    token = yylex();
    printf("token = %d, lexeme = %s\n", token, yytext);
  } while (token != T_eof);
  return 0;
}
