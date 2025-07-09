%top{
#include <cstdio>
#include <stack>
#include <cstring>
#include "parser.hpp"
}

%{
#define TAB_LEN 4

#define T_eof   0

/*helper function for block-style detection*/
int block_style = 0; 

void detect_block_style(FILE *f) {
    char line[1024];
    while (fgets(line, sizeof(line), f)) {
        if (strstr(line, "begin")) {
            block_style = 1; 
            rewind(f);       
            return;
        }
    }
    rewind(f);
}

std::stack<int> indent_stack;
int current_indent = 0;
int blocks = 0;
int at_no = 0;
int found_begin = 0;
int num_lines =1;
int count=0;
%}

/* LEXER DEFINITIONS */

L [[:alpha:]]
D [[:digit:]]
S [[:blank:]]
P [[:punct:]]{-}[\\\"\']
ESC_SIMPLE  \\[ntr0\'\"\\]
ESC_HEX     \\x[[:xdigit:]]{2}
ESC         ({ESC_SIMPLE}|{ESC_HEX})

/* LEXER STARTING STATES */

%x COMMENT
%s BEGIN_END
%s DRIVER

/* LEXER OPTIONS */

%option outfile="lexer.cpp"
%option yylineno noyywrap nodefault
%option pointer 
	// %option bison-bridge

%%
	if(block_style==1)BEGIN(BEGIN_END);

\n          { if(!count)++num_lines; count=0; }
    
"and"       return T_and; 
"as"        return T_as;
"begin"     return T_begin;  
"break"     return T_break;
"byte"      return T_byte; 
"continue"  return T_cont; 
"decl"      return T_decl; 
"def"       { BEGIN(DRIVER); ++blocks; return T_def; } 
"elif"      { BEGIN(DRIVER); ++blocks; return T_elif; } 
"else"      { BEGIN(DRIVER); ++blocks; return T_else; } 
"end"       return T_end; 
"exit"      return T_exit; 
"false"     return T_false; 
"if"        { BEGIN(DRIVER); ++blocks; return T_if; } 
"is"        return T_is; 
"int"       return T_int; 
"loop"      { BEGIN(DRIVER); ++blocks; return T_loop; }
"not"       return T_not;
"or"        return T_or;
"ref"       return T_ref; 
"return"    return T_ret; 
"skip"      return T_skip; 
"true"      return T_true; 
"var"       return T_var; 
":="        return T_asgn; 
":"         return T_col; 
"<="        return T_leq; 
">="        return T_geq; 
"<>"        return T_neq; 
	
[\+\-\*\/\%\!\&\|\=\<\>\(\)\[\]\,]  return yytext[0]; 

{L}({L}|{D}|_)*     return T_id; 
{D}+                return T_const; 

'({D}|{L}|{ESC}|{P}|" ")'   return T_char; 

\"({L}|{D}|{ESC}|{S}|{P})*\"    return T_str;

<BEGIN_END>^{S}+    /* nothing */

    /* OFFSIDE RULE */
^{S}+(\n|\#|"(*") {
                        char *input = yytext;

                        for(int i=0; i < yyleng; ++i) {
                            if(yytext[i]=='(') {
                                unput('*');
                                unput('(');
                                break;
                            }
                            else if(yytext[i]=='#'){
                                unput('#');
                                break;
                            }
                            else if(yytext[i]=='\n') {
                                unput('\n'); 
                                break;
                            }
                        }
                   }

^{S}+               {   
                        char *input = yytext;
                        int spaces = 0;
                        
                        for(int i = 0; i < yyleng; i++) 
                            spaces += (yytext[i] == '\t') ? TAB_LEN : 1;      
            
                        current_indent = spaces;
                        int current_level = (!indent_stack.empty()) ? indent_stack.top() : 0;
                        
                        if(current_indent > current_level) {
                            if(YY_START == DRIVER) {
                                indent_stack.push(current_indent);
                                BEGIN(INITIAL);
                            }
                            else if(current_level==0) {
                                /*nothing, because this is the case where def main has indetation!=0*/
                            }
                            else {
                                printf("\033[1;31m");  
                                printf("\n Wrong identation on line %d \n", yylineno);
                                printf("\033[0m");
                                yyterminate();
                            }
                        }
                                    
                        else if(current_indent < current_level && YY_START == INITIAL) {
                            indent_stack.pop();
                            int current = (!indent_stack.empty()) ? indent_stack.top() : 0;
                            
                
                            if(current>current_indent) {
                                yyless(0);
                                unput('\n');
                                count=1;
                                ++at_no;
                                printf("\033[0;33m");
                                printf("\n Just put an auto-end on line %d or line %d \n", yylineno, num_lines);
                                printf("\n Current identation level is %d and used case 1\n", current_indent);
                                printf("\033[0m");
                                return T_auto_end;
                            }
                            else if(current==current_indent){
                                ++at_no;
                                printf("\033[0;33m");
                                printf("\n Just put an auto-end on line %d or line %d\n", yylineno, num_lines);
                                printf("\n Current identation level is %d and used case 2\n", current_indent);
                                printf("\033[0m");
                                return T_auto_end;
                            }

                            printf("\033[1;31m"); 
                            printf("\n Wrong identation on line %d \n", yylineno);
                            printf("\033[0m");
                            yyterminate();
                        }

                        else {
                            if(YY_START == DRIVER) {	
                                if(current_indent<current_level) {
                                    yyless(0);
                                    unput('\n');
                                    count=1;
                                }
                                BEGIN(INITIAL);
                                ++at_no;
                                printf("\033[0;33m");
                                printf("\n Just put an auto-end on line %d or line %d\n", yylineno, num_lines);
                                printf("\n Current identation level is %d and used case 3\n", current_indent);
                                printf("\033[0m");
                                return T_auto_end;
                            }
                            
                            else {
                            /*nothing, because it means (current_indent==current_level && !flag), so we are inside a block with correct indetation*/ 
                            }
                        }
                    }

<BEGIN_END><<EOF>>      yyterminate();

<<EOF>> { 	
            if(indent_stack.empty()){
                printf("\033[1;32m");
                printf("\n all done \n");
                printf("\033[0m");
                return T_eof;
            }
            indent_stack.pop();
            
            if(!indent_stack.empty()){
                yyless(0);
            }
            ++at_no;
            printf("\033[0;33m");
            printf("\n Just put an auto-end on line %d or line %d \n", yylineno, num_lines);
                    printf("\n Current identation level is %d and used case 4\n", current_indent);
            printf("\033[0m");
            
            return T_auto_end; 
	 }

{S}                         { /*nothing*/ }

    /* COMMENT RULES */

\#.*                      { /* ignore one-line comments */ }

"(*"                        { BEGIN(COMMENT); }
<COMMENT>[^*]*              { /*nothing*/ }
<COMMENT>"*"+[^*)]*         { /*nothing*/ }
<COMMENT>"*"+")"            { BEGIN(INITIAL); }

    /* NOTHING MATCHED */

.   { printf("\033[1;31m"); fprintf(stderr, "illegal token\n"); printf("\033[0m"); exit(1); }
%%

