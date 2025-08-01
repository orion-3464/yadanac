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

%token 			T_and   "and"
%token 			T_as    "as"
%token 			T_begin "begin"
%token 			T_break "break"
%token<dtype> 	T_byte  "byte"
%token 			T_cont  "continue"
%token 			T_decl  "decl"
%token 			T_def   "def"
%token 			T_elif  "elif"
%token 			T_else  "else"
%token 			T_end   "end"
%token 			T_exit  "exit"
%token<btype> 	T_false "false"
%token 			T_if    "if"
%token 			T_is    "is"
%token<dtype> 	T_int   "int"
%token 			T_loop  "loop"
%token 			T_not   "not"
%token 			T_or    "or"
%token 			T_ref   "ref"
%token 			T_ret   "return"
%token 			T_skip  "skip"
%token<btype> 	T_true  "true"
%token 			T_var   "var"

%token T_asgn   ":="
%token T_col    ":"
%token T_geq    ">="
%token T_leq    "<="
%token T_neq    "<>"

%token<name> 	T_id 
%token<num> 	T_const 
%token<str> 	T_str   
%token<ch_cnst> T_char  
%token 			T_auto_end 

%left<op> 		"or"
%left<op> 		"and"
%precedence 	UNOTNOT
%nonassoc<op> 	'=' "<>" '>' '<' "<=" ">="
%left<op> 		'+' '-' '|' 
%left<op> 		'*' '/' '%' '&'
%precedence 	UPLUS UMINUS UNOT

%expect 2

%union {
    int num;
    std::string* name;
    std::string* str;
    std::string* dtype;
    std::string* btype;
    std::string* op;
    char ch_cnst;
    FparType* fpartype;
    Expr* expr;
    Stmt* stmt;
    LocalDef* localdef;
    Cond* cond;
    FparDef* fpardef;
    AST* ast;
}
  
%type<ast>      program header is_data_type col_fpar_def data_type col_id proc_call one_col_expr func_call
%type<localdef> func_def local_def_list func_decl var_def local_def
%type<fpardef>  fpar_def_list fpar_def
%type<expr>     id_list bracket_int_const_list one_id l_value expr expr_list one_expr
%type<fpartype> fpar_type type
%type<stmt>     block stmt_list stmt elif_cond_block_list else_col_block
%type<cond>     cond
%type<op>       '!'

%%

program : func_def { std::cout << "AST: " << *$1 << std::endl; }
	;

func_def    : "def" header local_def_list block { $$ = new FuncDef($2, $3, $4); } 
            ;

local_def_list  : %empty 				   { $$ = new LocalDefList(); }
                | local_def_list local_def { $1->append($2); $$ = $1; }
                ;

header  : T_id is_data_type col_fpar_def { $$ = new Header(new Id($1), $2, $3); } 
        ;

is_data_type    : %empty 		 { $$ = nullptr; } //nothing cause it's non recursive
                | "is" data_type { $$ = new IsDataType($2); }
                ;

col_fpar_def    : %empty 					 { $$ = nullptr; } 
                | ":" fpar_def fpar_def_list { if(!$3->empty()){$3->prepend($2); $$ = $3;} else{$$ = $2} } 
                ;

fpar_def_list   : %empty 					 { $$ = new FparDefList(); }
                | fpar_def_list ',' fpar_def { $1->append($3); $$ = $1; }
                ;

fpar_def    : T_id id_list "as" fpar_type { if(!$2->empty()){$2->prepend(new Id($1)); $$ = new FparDef($2, $4);} else{ $$ = new FparDef(new Id($1), $4);} } 
            ;

id_list : %empty 	   { $$ = new IdList(); }
        | id_list T_id { $1->append(new Id($2)); $$ = $1; }
        ;

data_type   : "int"  { $$ = new DataType($1); } 
            | "byte" { $$ = new DataType($1); } 
            ;

fpar_type   : type					        			{ $$ = $1; }
            | "ref" data_type							{ $$ = new RefPar($2); }
            | data_type '[' ']' bracket_int_const_list  { $$ = new ArrayPar($1, $4); } 
            ;

bracket_int_const_list  : %empty 								 { $$ = new BracketList(); }
                        | bracket_int_const_list '[' T_const ']' { $1->append(new Const($3)); $$ = $1; }
                        ;

local_def   : func_def  { $$ = $1; } 
            | func_decl { $$ = $1; }
            | var_def   { $$ = $1; }
            ;

type    : data_type bracket_int_const_list { $$ = new Type($1, $2); }
        ;

func_decl   : "decl" header  { $$ = new FuncDecl($2); }
            ;

var_def : "var" T_id id_list "is" type { if(!$3->empty()){$3->prepend($2); $$ = new VarDef($3, $5);} else{$$ = new VarDef($2, $5)}; } 
        ;

block   : "begin" stmt stmt_list "end" { if(!$3->empty()){$3->prepend($2); $$ = $3;} else{$$ = $2}; } 
        | stmt stmt_list T_auto_end    { if(!$2->empty()){$2->prepend($1); $$ = $2;} else{$$ = $1}; }
        ;

stmt_list   : %empty 		 { $$ = new Block(); }
            | stmt_list stmt { $1->append($2); $$ = $1; }
            ;

stmt    : "skip"                                                        { $$ = new Skip(); }
        | l_value ":=" expr												{ $$ = new Assign($1, $3); }
        | proc_call														{ $$ = $1; }
        | "exit"														{ $$ = new Exit(); }
        | "return" ":" expr                                             { $$ = new Return($3); }
        | "if" cond ":" block elif_cond_block_list else_col_block       { $$ = new IfThenElse($2, $4, $5, $6); } 
        | "loop" one_id ":" block 										{ $$ = new Loop($2, $4); } 
        | "break" col_id												{ $$ = new Break($2); } 
        | "continue" col_id												{ $$ = new Continue($2); } 
        ;

elif_cond_block_list    : %empty 									 { $$ = new ElifList(); }
                        | elif_cond_block_list "elif" cond ":" block { $1->append($3, $5); $$ = $1; }
                        ;

else_col_block  : %empty 		   { $$ = nullptr; } //nothing cause it's non recursive
                | "else" ":" block { $$ = new Else($3); }
                ;

one_id  : %empty { $$ = nullptr; }//nothing cause it's non recursive
        | T_id   { $$ = new Id($1); }
        ;

col_id  : %empty	{ $$ = nullptr; }//nothing cause it's non recursive
        | ":" T_id  { $$ = new ColId(new Id($2)); }
        ;

l_value : T_id                  { $$ = new LValue(Id($1)); } 
        | T_str                 { $$ = new LValue(Str($1)); }
        | l_value '[' expr ']'  { $1->append($3); $$ = $1; }
        ;

expr    : T_const   				{ $$ = new Const($1); }
        | T_char    				{ $$ = new Char($1); }
        | l_value   				{ $$ = $1; }
        | '(' expr ')' 				{ $$ = $2; }
        | func_call    				{ $$ = $1; }
        | '+' expr %prec UPLUS 		{ $$ = UnaryOpExpr($1, $2); }
        | '-' expr %prec UMINUS		{ $$ = UnaryOpExpr($1, $2); }
        | expr '+' expr 			{ $$ = BinOpExpr($1, $2, $3); }
        | expr '-' expr 			{ $$ = BinOpExpr($1, $2, $3); }
        | expr '*' expr 			{ $$ = BinOpExpr($1, $2, $3); }
        | expr '/' expr 			{ $$ = BinOpExpr($1, $2, $3); }
        | expr '%' expr 			{ $$ = BinOpExpr($1, $2, $3); }
        | "true"  					{ $$ = new BoolVal($1); } 
        | "false" 					{ $$ = new BoolVal($1); }
        | '!' expr %prec UNOT		{ $$ = UnaryOpExpr($1, $2); }
        | expr '&' expr 			{ $$ = BinOpExpr($1, $2, $3); }
        | expr '|' expr 			{ $$ = BinOpExpr($1, $2, $3); }
        ;

proc_call   : T_id one_col_expr { $$ = new ProcCall(new Id($1), $2); } 
            ;

one_col_expr    : %empty 			 { $$ = nullptr; } //nothing cause it's non recursive
                | ":" expr expr_list { if(!$3->empty()){$3->prepend($2); $$ = new OneColExpr($3);} else{$$ = new OneColExpr($2)}; } 
                ;

expr_list   : %empty 			 { $$ = new ExprList(); }
            | expr_list ',' expr { $1->append($3); $$ = $1; }
            ; 

func_call   : T_id '(' one_expr ')' { $$ = FuncCall(new Id($1), $3); } 
            ;

one_expr    : %empty 		 { $$ = nullptr; } //nothing cause it's non recursive
            | expr expr_list { if(!$2->empty()){$2->prepend($1); $$ = $2;} else{$$ = $1}; }
            ;

cond    : expr						{ $$ = $1; }
        | '(' cond ')'				{ $$ = $2; }
        | "not" cond %prec UNOTNOT	{ $$ = new NotCond($2); }
        | cond "and" cond			{ $$ = BinOpCond($1, $2, $3); }
        | cond "or" cond			{ $$ = BinOpCond($1, $2, $3); }
        | expr '=' expr				{ $$ = BinOpExpr($1, $2, $3); }
        | expr "<>" expr			{ $$ = BinOpExpr($1, $2, $3); }
        | expr '<' expr				{ $$ = BinOpExpr($1, $2, $3); }
        | expr '>' expr				{ $$ = BinOpExpr($1, $2, $3); }
        | expr "<=" expr			{ $$ = BinOpExpr($1, $2, $3); }
        | expr ">=" expr			{ $$ = BinOpExpr($1, $2, $3); }
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
