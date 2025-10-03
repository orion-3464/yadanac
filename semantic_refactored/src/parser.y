%code top {
    #include <stdio.h>
    #include <stdlib.h>
}
	
%code requires {
    #include <string>
    #include "ast.hpp"
    #include "symbol.hpp"
}

%code {
    #include "lexer.hpp"

	SymbolTable st;
}

%locations
%define api.pure full

%token 			T_and   "and"
%token 			T_as    "as"
%token 			T_begin "begin"
%token 			T_break "break"
%token		 	T_byte  "byte"
%token 			T_cont  "continue"
%token 			T_decl  "decl"
%token 			T_def   "def"
%token 			T_elif  "elif"
%token 			T_else  "else"
%token 			T_end   "end"
%token 			T_exit  "exit"
%token		 	T_false "false"
%token 			T_if    "if"
%token 			T_is    "is"
%token		 	T_int   "int"
%token 			T_loop  "loop"
%token 			T_not   "not"
%token 			T_or    "or"
%token 			T_ref   "ref"
%token 			T_ret   "return"
%token 			T_skip  "skip"
%token		 	T_true  "true"
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
    std::string* op;
    char ch_cnst;
    Expr* expr;
    Stmt* stmt;
    LocalDef* localdef;
    FparDef* fpardef;
    Header* header;
	ColFparDef* colfpardef;
	Label* colid;
	DataType* datatype;
	IsDataType* isdatatype;
	//OneColExpr* onecolexpr;
	LocalDefList* localdeflist;
	FparDefList* fpardeflist;
	IdList* idlist;
	Block*	block;
	ElifList* eliflist;
	ExprList* exprlist;
	BracketList* bracketlist;
	LValue* lvalue;
    Id* id;
    Type* type;
}
  
//%type<onecolexpr>   one_col_expr
%type<lvalue>		l_value
%type<header>		header
%type<isdatatype>	is_data_type
%type<colid>		col_id
%type<colfpardef> 	col_fpar_def
%type<localdeflist> local_def_list
%type<fpardeflist>  fpar_def_list
%type<idlist>  		id_list
%type<block>  		block stmt_list
%type<eliflist>		elif_cond_block_list
%type<localdef> 	func_def func_decl var_def local_def
%type<fpardef>  	fpar_def
%type<bracketlist>	bracket_int_const_list
%type<exprlist>		expr_list one_col_expr one_expr
%type<expr>     	expr func_call cond
%type<datatype> 	data_type 
%type<type>         type fpar_type
%type<stmt>     	stmt else_col_block proc_call
%type<op>       	'!'
%type<id>           one_id 

%%

program : func_def { std::cout << "AST: " << *$1 << std::endl; $1->sem_analyze(); delete $1; }
	    ;

func_def    : "def" header local_def_list block { $$ = new FuncDef($2, $3, $4); } 
            ;

local_def_list  : %empty 				   { $$ = new LocalDefList(); }
                | local_def_list local_def { $1->append($2); $$ = $1; }
                ;

header  : T_id is_data_type col_fpar_def { $$ = new Header(new Id(*$1), $2, $3); delete $1; } 
        ;

is_data_type    : %empty 		 { $$ = nullptr; } //nothing cause it's non recursive
                | "is" data_type { $$ = new IsDataType($2); }
                ;

col_fpar_def    : %empty 					 { $$ = nullptr; } 
                | ":" fpar_def fpar_def_list { $3->prepend($2); $$ = new ColFparDef($3); } 
                ;

fpar_def_list   : %empty 					 { $$ = new FparDefList(); }
                | fpar_def_list ',' fpar_def { $1->append($3); $$ = $1; }
                ;

fpar_def    : T_id id_list "as" fpar_type { $2->prepend(new Id(*$1)); $$ = new FparDef($2, $4); delete $1;}
            ;

id_list : %empty 	   { $$ = new IdList(); }
        | id_list T_id { $1->append(new Id(*$2)); $$ = $1; delete $2; }
        ;

data_type   : "int"  { $$ = new DataType(INT); } 
            | "byte" { $$ = new DataType(BYTE); } 
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

var_def : "var" T_id id_list "is" type {$3->prepend(new Id(*$2)); $$ = new VarDef($3, $5); delete $2;}  
        ;

block   : "begin" stmt_list "end" { $$ = $2; $$->set_auto_end(false); } 
        | stmt_list T_auto_end    { $$ = $1; $$->set_auto_end(true);} 
        ;

stmt_list   : stmt 		 { $$ = new Block(); $$ -> append($1);}
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
                        | elif_cond_block_list "elif" cond ":" block { Elif *elif= new Elif($3, $5); $1->append(elif); $$ = $1; }
                        ;

else_col_block  : %empty 		   { $$ = nullptr; } 
                | "else" ":" block { $$ = new Else($3); }
                ;

one_id  : %empty { $$ = nullptr; }
        | T_id   { $$ = new Id(*$1); delete $1; }
        ;

col_id  : %empty	{ $$ = nullptr; }
        | ":" T_id  { $$ = new Label(new Id(*$2)); delete $2; }
        ;

l_value : T_id                  { $$ = new LValue(new Id(*$1), nullptr, new ExprList()); delete $1; } 
        | T_str                 { $$ = new LValue(nullptr, new Str(*$1), new ExprList()); delete $1; }
        | l_value '[' expr ']'  { $1 -> add($3); $$ = $1; }
        ;

expr    : T_const   				{ $$ = new Const($1); }
        | T_char    				{ $$ = new Char($1); }
        | l_value   				{ $$ = $1; }
        | '(' expr ')' 				{ $$ = $2; }
        | func_call    				{ $$ = $1; }
        | '+' expr %prec UPLUS 		{ $$ = new UnaryOpExpr($1, $2);  }
        | '-' expr %prec UMINUS		{ $$ = new UnaryOpExpr($1, $2);  }
        | expr '+' expr 			{ $$ = new BinOpExpr($1, $2, $3); }
        | expr '-' expr 			{ $$ = new BinOpExpr($1, $2, $3); }
        | expr '*' expr 			{ $$ = new BinOpExpr($1, $2, $3); }
        | expr '/' expr 			{ $$ = new BinOpExpr($1, $2, $3); }
        | expr '%' expr 			{ $$ = new BinOpExpr($1, $2, $3); }
        | "true"  					{ $$ = new BoolVal('\x01'); } 
        | "false" 					{ $$ = new BoolVal('\0'); }
        | '!' expr %prec UNOT		{ $$ = new UnaryOpExpr($1, $2); }
        | expr '&' expr 			{ $$ = new BinOpExpr($1, $2, $3); }
        | expr '|' expr 			{ $$ = new BinOpExpr($1, $2, $3); }
        ;

proc_call   : T_id one_col_expr { $$ = new ProcCall(new Id(*$1), $2); delete $1; } 
            ;

one_col_expr    : %empty 			 { $$ = nullptr; } 
                | ":" expr expr_list {$3->prepend($2); $$ = new OneColExpr($3);}  
                ;

expr_list   : %empty 			 { $$ = new ExprList(); }
            | expr_list ',' expr { $1->append($3); $$ = $1; }
            ; 

func_call   : T_id '(' one_expr ')' { $$ = new FuncCall(new Id(*$1), $3); delete $1; } 
            ;

one_expr    : %empty 		 { $$ = nullptr; } 
            | expr expr_list {$2->prepend($1); $$ = $2;} 
            ;

cond    : expr						{ $$ = $1; }
        | '(' cond ')'				{ $$ = $2; }
        | "not" cond %prec UNOTNOT	{ $$ = new NotCond($2); }
        | cond "and" cond			{ $$ = new BinOpCond($1, $2, $3);  }
        | cond "or" cond			{ $$ = new BinOpCond($1, $2, $3);  }
        | expr '=' expr				{ $$ = new BinOpExpr($1, $2, $3);  } // may fix the leak     
        | expr "<>" expr			{ $$ = new BinOpExpr($1, $2, $3);  }
        | expr '<' expr				{ $$ = new BinOpExpr($1, $2, $3);  } // may fix the leak
        | expr '>' expr				{ $$ = new BinOpExpr($1, $2, $3);  } // may fix the leak
        | expr "<=" expr			{ $$ = new BinOpExpr($1, $2, $3);  }
        | expr ">=" expr			{ $$ = new BinOpExpr($1, $2, $3);  }
        ;

%%

void yyerror(YYLTYPE *locp, const char *msg) {
	printf("Syntax error: %s\n at line %d\n", msg, locp->last_line);
	//exit(42);
}

int main(int argc, char* argv[]) {
    extern FILE *yyin;
    extern int block_style;
    void detect_block_style(FILE *);
    
    FILE* f = nullptr;

    if(argc >= 1) { 
        f = fopen(argv[1], "r");
        if (!f) {
            perror("fopen");
            exit(1);
        }   
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

    fclose(f);
	return res;
}
