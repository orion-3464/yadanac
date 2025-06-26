%{ 
#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
%}

%token T_eof   0

%token T_and   "and"
%token T_as    "as"
%token T_begin "begin"
%token T_break "break"
%token T_byte  "byte"
%token T_cont  "continue"
%token T_decl  "decl"
%token T_def   "def"
%token T_elif  "elif"
%token T_else  "else"
%token T_end   "end"
%token T_exit  "exit"
%token T_false "false"
%token T_if    "if"
%token T_is    "is"
%token T_int   "int"
%token T_loop  "loop"
%token T_not   "not"
%token T_or    "or"
%token T_ref   "ref"
%token T_ret   "return"
%token T_skip  "skip"
%token T_true  "true"
%token T_var   "var"

%token T_id 
%token T_const 
%token T_str   
%token T_char  

%token T_asgn  
%token T_col   
%token T_geq   
%token T_leq   
%token T_neq   

%%

program : stmt_list 
		;

stmt_list	: /*nothing*/ 
			| stmt_list stmt 
			;

stmt	: "var" T_id "is" expr
		| 
;

%%

void yyerror(const char *msg) {
	printf("Syntax error: %s\n", msg);
	exit(42);
}

int main() {
	int res = yyparse();
	(res == 0) ? printf("Successful parsing\n") : printf("Error in parsing\n");
	return res;
}
