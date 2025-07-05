%top{
#include <cstdio>
#include <stack>
}

%{
#define TAB_LEN 4

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

std::stack<int> indent_stack;
int current_indent = 0;
int blocks = 0;
int flag = 0;
int at_no = 0;
FlexLexer *scanner = new yyFlexLexer;
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
%x DRIVER

/* LEXER OPTIONS */

%option outfile="lexer.cpp"
%option yylineno noyywrap
%option c++ pointer 

%%

\n          
    
"and"       return T_and; 
"as"        return T_as;
"begin"     return T_begin; 
"break"     return T_break;
"byte"      return T_byte; 
"continue"  return T_cont; 
"decl"      return T_decl; 
"def"       { flag=1; ++blocks; return T_def; } 
"elif"      { flag=1; ++blocks; return T_elif; } 
"else"      { flag=1; ++blocks; return T_else; } 
"end"       return T_end; 
"exit"      return T_exit; 
"false"     return T_false; 
"if"        { flag=1; ++blocks; return T_if; } 
"is"        return T_is; 
"int"       return T_int; 
"loop"      { flag=1; ++blocks; return T_loop; }
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

    /* OFFSIDE RULE */

^{S}+               {   
                        char *input = yytext;
                        int spaces = 0;
                        
                        for(int i = 0; i < yyleng; i++) 
                            spaces += (yytext[i] == '\t') ? TAB_LEN : 1;      
            
                        current_indent = spaces;
                        int current_level = (!indent_stack.empty()) ? indent_stack.top() : 0;
                        
                        if(current_indent > current_level) {
			    if(flag){
				indent_stack.push(current_indent);
				flag=0;
			    }
			    else if(current_level==0) {
				/*nothing, because this is the case where def main has indetation!=0*/
			    }
			    else {
				printf("\033[1;31m");  
				printf("\n Wrong identation on line %d \n", scanner->lineno());
				printf("\033[0m");
				yyterminate();
			    }
                        }
                        
                        else if(current_indent < current_level && !flag) {
			    indent_stack.pop();
                            int current = (!indent_stack.empty()) ? indent_stack.top() : 0;
				
	
                            if(current>current_indent){
				yyless(0);
				unput('\n');
				++at_no;
				printf("\033[0;33m");
				printf("\n Just put an auto-end on line %d \n", scanner->lineno());
				printf("\n Current identation level is %d and used case 1\n", current_indent);
				printf("\033[0m");
				return T_auto_end;
                            }
			    else if(current==current_indent){
			    	++at_no;
				printf("\033[0;33m");
			    	printf("\n Just put an auto-end on line %d \n", scanner->lineno());
				printf("\n Current identation level is %d and used case 2\n", current_indent);
				printf("\033[0m");
	                        return T_auto_end;
			    }
                            printf("\033[1;31m"); 
                            printf("\n Wrong identation on line %d \n", scanner->lineno());
                            printf("\033[0m");
                            yyterminate();
                        }

                        else {
				if(flag){	
                                	if(current_indent<current_level){
						yyless(0);
						unput('\n');
					}
                               		flag=0;
					++at_no;
				        printf("\033[0;33m");
					printf("\n Just put an auto-end on line %d \n", scanner->lineno());
					printf("\n Current identation level is %d and used case 3\n", current_indent);
					printf("\033[0m");
                                	return T_auto_end;
                                }
				
			        else {
				    /*nothing, because it means (current_indent==current_level && !flag), so we are inside a block with correct indetation*/ 
				}
			         
                        }
                    }

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
		printf("\n Just put an auto-end on line %d \n", scanner->lineno());
                printf("\n Current identation level is %d and used case 4\n", current_indent);
		printf("\033[0m");
		
		return T_auto_end; 
	  }

{S}                         { /*nothing*/ }

    /* COMMENT RULES */

\#.*\n                      { /* ignore one-line comments */ }

"(*"                        { BEGIN(COMMENT); }
<COMMENT>[^*]*              { /*nothing*/ }
<COMMENT>"*"+[^*)]*         { /*nothing*/ }
<COMMENT>"*"+")"            { BEGIN(INITIAL); }

    /* NOTHING MATCHED */

.   { printf("\033[1;31m"); fprintf(stderr, "illegal token\n"); printf("\033[0m"); exit(1); }
%%

int main() {
    int token;

    do {
	token = scanner->yylex();
	const char* lexeme = (token == T_auto_end) ? "<auto-end>" : scanner->YYText(); /*for cosmetic reasons for the output*/
        printf("token = %d, lexeme = %s\n", token, lexeme);
    } while (token != T_eof);

    printf("\n Scanned text consists of %d lines\n", scanner->lineno());

    printf("\n Scanned text consists of %d blocks\n", blocks);
    
    printf("\n Scanned text consists of %d auto-ends\n", at_no);
   
    delete scanner;
    return 0;
}
