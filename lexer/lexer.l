%{
#include <cstdio>
#include <stack>
#include <deque>

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

#define T_auto_end 1033

std::deque<int> tokenq;

int lineno = 1;

int identation_level = 0;
int blocks = 1;

std::stack<int> ident_levels;
%}

L [A-Za-z]
D [0-9]
ESC_SIMPLE  \\[ntr0'"\\]
ESC_HEX     \\x[0-9a-f]{2}
ESC         ({ESC_SIMPLE}|{ESC_HEX})
STRCHAR     [ -~]

%x COMMENT

%option noyywrap

%%
    
    if(!tokenq.empty()) {
        int cur_token = tokenq.front();
        tokenq.pop_front();
        return cur_token;
    }

"and"       { tokenq.push_back(T_and); }
"as"        { tokenq.push_back(T_as); }
"begin"     { tokenq.push_back(T_begin); }
"break"     { tokenq.push_back(T_break); }
"byte"      { tokenq.push_back(T_byte); }
"continue"  { tokenq.push_back(T_cont); }
"decl"      { tokenq.push_back(T_decl); }
"def"       { tokenq.push_back(T_def); }
"elif"      { tokenq.push_back(T_elif); }
"else"      { tokenq.push_back(T_else); }
"end"       { tokenq.push_back(T_end); }
"exit"      { tokenq.push_back(T_exit); }
"false"     { tokenq.push_back(T_false); }
"if"        { tokenq.push_back(T_if); }
"is"        { tokenq.push_back(T_is); }
"int"       { tokenq.push_back(T_int); }
"loop"      { tokenq.push_back(T_loop); }
"not"       { tokenq.push_back(T_not); }
"or"        { tokenq.push_back(T_or); }
"ref"       { tokenq.push_back(T_ref); }
"return"    { tokenq.push_back(T_ret); }
"skip"      { tokenq.push_back(T_skip); }
"true"      { tokenq.push_back(T_true); }
"var"       { tokenq.push_back(T_var); }

":="        { tokenq.push_back(T_asgn); }
":"         { tokenq.push_back(T_col); }
"<="        { tokenq.push_back(T_leq); }
">="        { tokenq.push_back(T_geq); }
"<>"        { tokenq.push_back(T_neq); }

[\+\-\*\/\%\!\&\|\=\<\>\(\)\[\]\,] { tokenq.push_back(yytext[0]); }

{L}({L}|{D}|_)* { tokenq.push_back(T_id); }
{D}+            { tokenq.push_back(T_const); }

'({D}|{L}|{ESC})'   { tokenq.push_back(T_char); }

\"({STRCHAR}*)\"    { tokenq.push_back(T_str); }

\n                          { ++lineno; printf("I am counting a new line\n");}
\r+                         { /*nothing*/ }
^[ \t]+                     {   
                                char *word = yytext;
                                int spaces = 0;
                                while(*word) {
                                    if(*word == ' ') ++spaces;
                                    if(*word == '\t') spaces += 4;
                                    ++word;
                                }
                                
                                if(spaces > identation_level) {
                                    identation_level = spaces;
                                    ident_levels.push(identation_level);
                                    printf("identation level is %d\n", identation_level);

                                }
                                else {
                                    identation_level = spaces;
                                    int current_level = ident_levels.top();
                                    while(current_level > identation_level) {
                                        ident_levels.pop();
                                        ++blocks;
                                        printf("I am counting a block!!!!\n");
                                        printf("identation level is %d\n", current_level);
                                        current_level = ident_levels.top();
                                        tokenq.push_back(T_auto_end);
                                    }
                                }
                            }
[ \t]                       { /*nothing*/ }

\#.*\n                      { ++lineno; printf("I am counting a single line comment\n");}
"(*"                        { BEGIN(COMMENT); }
<COMMENT>"*)"               { BEGIN(INITIAL); }
<COMMENT>\n                 { ++lineno; printf("I am counting a line in a multiline comment\n");}
<COMMENT>"*"                { /*nothing*/ }
<COMMENT>[^*\n]+            { /*nothing*/ }    

.   { fprintf(stderr, "illegal token\n"); exit(1); }
%%

int main() {
  int token;
  ident_levels.push(0);

  do {
    token = yylex();
    printf("token = %d, lexeme = %s\n", token, yytext);
  } while (token != T_eof);

  printf("\n Scanned text consists of %d lines\n", lineno);
  printf("\n Scanned text consists of %d blocks\n", blocks);
  return 0;
}
        