%top{

#include <cstdio>
#include <stack>
#include <cstring>
#include <string>
#include "parser.hpp"
}

%{
#define TAB_LEN 4

#define T_eof   0

int yyline = 1;
int yycolumn = 1;

#define YY_USER_ACTION                              \
    do {                                            \
        yylloc->first_line = yylloc->last_line;     \
        yylloc->first_column = yylloc->last_column; \
        for (int i = 0; i < yyleng; i++) {          \
            if (yytext[i] == '\n') {                \
                yylloc->last_line++;                \
                yylloc->last_column = 0;            \
            } else {                                \
                yylloc->last_column++;              \
            }                                       \
        }                                           \
    } while(0);


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
bool flag=0; //initial state, 1 is for "just found a driver" state

int comment_depth = 0; //needed for nested comments
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
%x EOF_AUTO_END
%s BEGIN_END
%x AUTO_END_EXTRA

/* LEXER OPTIONS */

%option outfile="lexer.cpp"
%option yylineno noyywrap nodefault 
%option pointer 
%option bison-bridge bison-locations

%%
	if(block_style==1)BEGIN(BEGIN_END);

\n          {   
                yylloc->last_line++;
                yylloc->last_column = 0;
                if(!count)++num_lines; 
                count=0; 
            }
    
"and"       { yylval->op = new std::string(yytext); return T_and; } 
"as"        return T_as;
"begin"     return T_begin;  
"break"     return T_break;
"byte"      { return T_byte; } 
"continue"  return T_cont; 
"decl"      return T_decl; 
"def"       { flag=1; ++blocks; return T_def; } 
"elif"      { flag=1; ++blocks; return T_elif; } 
"else"      { flag=1; ++blocks; return T_else; } 
"end"       return T_end; 
"exit"      return T_exit; 
"false"     { return T_false; } 
"if"        { flag=1; ++blocks; return T_if; } 
"is"        return T_is; 
"int"       { return T_int; } 
"loop"      { flag=1; ++blocks; return T_loop; }
"not"       return T_not;
"or"        { yylval->op = new std::string(yytext); return T_or; }
"ref"       return T_ref; 
"return"    return T_ret; 
"skip"      return T_skip; 
"true"      { return T_true; } 
"var"       return T_var; 
":="        return T_asgn; 
":"         return T_col; 
"<="        { yylval->op = new std::string(yytext); return T_leq; } 
">="        { yylval->op = new std::string(yytext); return T_geq; }
"<>"        { yylval->op = new std::string(yytext); return T_neq; } 
	
[\+\-\*\/\%\!\&\|\=\<\>]  { yylval->op = new std::string(yytext); return yytext[0]; }

[\(\)\[\]\,]              { return yytext[0]; }

{L}({L}|{D}|_)*     { yylval->name = new std::string(yytext); return T_id; }
{D}+                { yylval->num = atoi(yytext); return T_const; } 

'({D}|{L}|{ESC}|{P}|" ")'   { yylval->ch_cnst = yytext[0]; return T_char;}

\"({L}|{D}|{ESC}|{S}|{P})*\"    { yylval->str = new std::string(yytext); return T_str; }

<BEGIN_END>^{S}+    /* nothing */


<AUTO_END_EXTRA>{S}+ { 
    int spaces = 0;
    for(int i = 0; i < yyleng; i++) 
        spaces += (yytext[i] == '\t') ? TAB_LEN : 1; 

    int saved_line = yyline;
    int saved_column = yycolumn; 

    current_indent = spaces;
    
    // We should already know indent < stack.top().
    // We just need to pop and see where we land.
    int current_level = (!indent_stack.empty()) ? indent_stack.top() : 0;
    if (current_level>current_indent){
    // Pop the stack to see the *next* level
    indent_stack.pop();
	int current_level = (!indent_stack.empty()) ? indent_stack.top() : 0;


    // Set location for this T_auto_end token
    yylloc->first_line = saved_line;
    yylloc->first_column = saved_column;
    yylloc->last_line = saved_line;
    yylloc->last_column = saved_column;
    ++at_no;

    
    if (current_level > current_indent) {
        // We are still more indented than the target.
        // Need to pop *another* level.
        yyless(0); // Put whitespace back
        
        // Restore location info since yyless(0) resets it
        yyline = saved_line;
        yycolumn = saved_column;
        
        return T_auto_end; // Stay in AUTO_END_EXTRA
    } 
    else if (current_level == current_indent) {
        printf("I poped a level and now i'm going back to normal\n");// We matched the target indent level. We are done.
        BEGIN(INITIAL); // Go back to normal
        return T_auto_end;
    } 
    else { // current_level < current_indent
        // Error: Dedented to an invalid level that was never on the stack
        printf("\033[1;31m"); 
        printf("\n Wrong identation on line %d \n", yylineno);
        printf("\033[0m");
        yyterminate();
    }
	}
	else {BEGIN(INITIAL); printf("im here/n");}
}
    /* OFFSIDE RULE */
^{S}+(\n|\#|"(*") {
                        for(int i=0; i < yyleng; ++i) {
                            if(yytext[i]=='(') {
                                yyless(i);
                                break;
                            }
                            else if(yytext[i]=='#'){
                                yyless(i);
                                break;
                            }
                            else if(yytext[i]=='\n') {
                                yyless(i); 
                                break;
                            }
                        }
                   }

^{S}+               {   
                        int spaces = 0;
                        
                        for(int i = 0; i < yyleng; i++) 
                            spaces += (yytext[i] == '\t') ? TAB_LEN : 1;      
                        
                        int saved_line = yyline;
                        int saved_column = yycolumn;    

                        current_indent = spaces;
                        int current_level = (!indent_stack.empty()) ? indent_stack.top() : 0;
                        
                        if(current_indent > current_level) {
						printf("case1\n");
                            if(flag==1) {
                                indent_stack.push(current_indent);
                                flag=0;
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
                                    
                        else if((current_indent < current_level) && flag==0) {
							printf("case 2\n");
                            indent_stack.pop();
                            int current = (!indent_stack.empty()) ? indent_stack.top() : 0;
                            
                
                            if(current>current_indent) {
                                yyless(0);
                                // restore location after yyless(0)
                                yyline = saved_line;
                                yycolumn = saved_column;
                                count=1;
                                ++at_no;

                                yylloc->first_line = saved_line;
                                yylloc->first_column = saved_column;
                                yylloc->last_line = saved_line;
                                yylloc->last_column = saved_column;
								
								BEGIN(AUTO_END_EXTRA);

                                return T_auto_end;
                            }
                            else if(current==current_indent){
                                ++at_no;

                                yylloc->first_line = saved_line;
                                yylloc->first_column = saved_column;
                                yylloc->last_line = saved_line;
                                yylloc->last_column = saved_column;

                                return T_auto_end;
                            }

                            printf("\033[1;31m"); 
                            printf("\n Wrong identation on line %d \n", yylineno);
                            printf("\033[0m");
                            yyterminate();
                        }

                        else {
							printf("case 3");
                            if(flag==1) {	
                                if(current_indent<current_level) {
                                    yyless(0);

                                    yyline = saved_line;
                                    yycolumn = saved_column;      

                                    count=1;
									flag=0;
									BEGIN(AUTO_END_EXTRA);
									++at_no;

                               		yylloc->first_line = saved_line;
                                	yylloc->first_column = saved_column;
                                	yylloc->last_line = saved_line;
                                	yylloc->last_column = saved_column;

									return T_auto_end;
                                }
                                flag=0;

                                ++at_no;

                                yylloc->first_line = saved_line;
                                yylloc->first_column = saved_column;
                                yylloc->last_line = saved_line;
                                yylloc->last_column = saved_column;

                               return T_auto_end;
                            }
                            
                            else {
                            /*nothing, because it means (current_indent==current_level && INITIAL STATE), so we are inside a block with correct indetation*/ 
                            }
                        }
                    }

<BEGIN_END><<EOF>>      yyterminate();

    /* COMMENT RULES */

\#.*                      { /* ignore one-line comments */ }

"(*"                        { BEGIN(COMMENT); comment_depth = 1; }

<COMMENT>"(*"               { comment_depth++; /* Found a nested start: increase depth */ }

<COMMENT>"*)"               { 
                                comment_depth--;
                                if (comment_depth == 0) {
                                    BEGIN(INITIAL); /* Depth is zero: exit comment state */
                                }
                                /* If depth > 0, we remain in COMMENT state */
                            }

<COMMENT>[^*)]+             { /* Consume the bulk of the text efficiently */ }

<COMMENT><<EOF>>            { 
                                fprintf(stderr, "Error: Unclosed nested comment (started on line %d).\n", yylineno);
                                yyterminate();
                            }
<COMMENT>.                  { /* Catch stray characters not handled above, like '*' or ')' alone */ }

<EOF_AUTO_END>. {
				  		if(indent_stack.empty()) {
                			// all done
                			return T_eof;
            			}
            
						if(flag==1) {
							flag=0;
							yyless(0);
							return T_auto_end;
						}

						indent_stack.pop();

            			if(!indent_stack.empty()){
                			yyless(0);
            			}
            			++at_no;

            			yylloc->first_line = yyline;
            			yylloc->first_column = yycolumn;
            			yylloc->last_line = yyline;
            			yylloc->last_column = yycolumn;
                        
						printf("1 extra auto_end\n");

           				return T_auto_end; 
				}


<<EOF>> {
			BEGIN(EOF_AUTO_END);
			unput('4');
	 	}

{S}                         { /*nothing*/ }


    /* NOTHING MATCHED */

.   { 
        printf("\033[1;31m"); 
        fprintf(stderr, "Illegal token on line %d \n", yylineno); 
        printf("\033[0m"); 
        yyterminate(); 
    }
%%
