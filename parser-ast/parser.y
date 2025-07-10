%code top {
    #include <stdio.h>
    #include <stdlib.h>
}

%code requires {
    #include <string>
    #include "ast.hpp"
}

%code {
    #include "lexer.hpp"
}

%locations
%define api.pure full

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
%token<num> T_const 
%token<str> T_str   
%token<ch_cnst> T_char  
%token T_auto_end 

%left "or"
%left "and"
%precedence UNOTNOT
%nonassoc '=' "<>" '>' '<' "<=" ">="
%left '+' '-' '|'
%left '*' '/' '%' '&'
%precedence UPLUS UMINUS UNOT

%expect 2

%union {
    int num;
    std::string* str;
    char ch_cnst;
}

%type<ast> cond one_expr func_call expr_list one_col_expr proc_call expr l_value col_id one_id else_col_block elif_cond_block_list 
%type<ast> stmt stmt_list block var_def func_decl type local_def bracket_int_const_list fpar_type data_type id_list fpar_def 
%type<ast> fpar_def_list col_fpar_def is_data_type header local_def_list func_def program

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

void yyerror(YYLTYPE *locp, const char *msg) {
	printf("Syntax error: %s\n at line %d\n", msg, locp->last_line);
	exit(42);
}

int main(int argc, char* argv[]) {
    extern FILE *yyin;
    extern int block_style;
    void detect_block_style(FILE *);
     
    FILE* f = fopen(argv[1], "r");
    if (!f) {
        perror("fopen");
        exit(1);
    }   

    yyin = f;

    detect_block_style(yyin);

    printf("Using %s%s%s syntax.\n",
       block_style == 1 ? "\033[0;33m" : "\033[0;34m",
       block_style == 1 ? "block-delimiter" : "indentation",
       "\033[0m");

	int res = yyparse();
    switch(res) {
        case 0:
            printf("\033[1;32m Successful parsing\n \033[0m");
            break;

        case 1:
            printf("\033[1;31m Syntaxt error in parsing\n \033[0m");
            break;
        
        case 2:
            printf("\033[1;31m Parsing failed due to memory exhaustion\n \033[0m");
            break;
    }

	return res;
}
