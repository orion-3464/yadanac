%{ 
#include <stdio.h>
#include <stdlib.h>
#include "lexer.hpp"
%}

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

%token T_asgn   ":="
%token T_col    ":"
%token T_geq    ">="
%token T_leq    "<="
%token T_neq    "<>"

%token T_id 
%token T_const 
%token T_str   
%token T_char  
%token T_auto_end 

%left "or"
%left "and"
%precedence UNOTNOT
%nonassoc '=' "<>" '>' '<' "<=" ">="
%left '+' '-' '|'
%left '*' '/' '%' '&'
%precedence UPLUS UMINUS UNOT

%expect 2

%%

program : func_def
		;

func_def    : "def" header local_def_list block
            ;

local_def_list  : %empty
                | local_def_list local_def
                ;

header  : T_id is_data_type col_fpar_def
        ;

is_data_type    : %empty
                | "is" data_type
                ;

col_fpar_def    : %empty
                | ":" fpar_def fpar_def_list
                ;

fpar_def_list   : %empty
                | fpar_def_list ',' fpar_def
                ;

fpar_def    : T_id id_list "as" fpar_type
            ;

id_list : %empty
        | id_list T_id
        ;

data_type   : "int"
            | "byte"
            ;

fpar_type   : type 
            | "ref" data_type
            | data_type '[' ']' bracket_int_const_list
            ;

bracket_int_const_list  : %empty
                        | bracket_int_const_list '[' T_const ']'
                        ;

local_def   : func_def
            | func_decl
            | var_def
            ;

type    : data_type bracket_int_const_list
        ;

func_decl   : "decl" header
            ;

var_def : "var" T_id id_list "is" type
        ;

block   : "begin" stmt stmt_list "end"
        | stmt stmt_list T_auto_end 
        ;

stmt_list   : %empty
            | stmt_list stmt
            ;

stmt    : "skip"
        | l_value ":=" expr
        | proc_call
        | "exit"
        | "return" ":" expr
        | "if" cond ":" block elif_cond_block_list else_col_block
        | "loop" one_id ":" block 
        | "break" col_id
        | "continue" col_id
        ;

elif_cond_block_list    : %empty
                        | elif_cond_block_list "elif" cond ":" block
                        ;

else_col_block  : %empty
                | "else" ":" block
                ;

one_id  : %empty
        | T_id
        ;

col_id  : %empty
        | ":" T_id
        ;

l_value : T_id
        | T_str
        | l_value '[' expr ']'
        ;

expr    : T_const
        | T_char
        | l_value
        | '(' expr ')' 
        | func_call
        | '+' expr %prec UPLUS
        | '-' expr %prec UMINUS
        | expr '+' expr
        | expr '-' expr
        | expr '*' expr
        | expr '/' expr
        | expr '%' expr
        | "true"
        | "false"
        | '!' expr %prec UNOT
        | expr '&' expr
        | expr '|' expr
        ;

proc_call   : T_id one_col_expr
            ;

one_col_expr    : %empty
                | ":" expr expr_list
                ;

expr_list   : %empty
            | expr_list ',' expr
            ; 

func_call   : T_id '(' one_expr ')'
            ;

one_expr    : %empty
            | expr expr_list
            ;

cond    : expr 
        | '(' cond ')'
        | "not" cond %prec UNOTNOT
        | cond "and" cond
        | cond "or" cond
        | expr '=' expr
        | expr "<>" expr
        | expr '<' expr
        | expr '>' expr
        | expr "<=" expr
        | expr ">=" expr
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
