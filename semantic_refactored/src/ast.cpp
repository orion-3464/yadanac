#include "ast.hpp"
#include "lexer.hpp"
#include "symbol.hpp"

// -------- EXPR CLASS --------

Expr::Expr(const Expr& other) : expr_type(other.expr_type) {}

void Expr::check_type(ExprType expected_type1, ExprType expected_type2) {
    sem_analyze();
    if(expr_type != expected_type1 || expr_type != expected_type2) printf("ERRORRRRR"); // yyerror("type_mismatch"); TO DO
}

ExprType Expr::get_type() {
    return expr_type;
}

// -------- BLOCK CLASS --------

Block::Block() : stmt_list() {}
    
Block::~Block() {
    if(!stmt_list.empty())
        for (auto stmt : stmt_list)
            if(stmt) delete stmt;
}

void Block::set_auto_end(bool auto_end) {
    has_auto_end = auto_end;
}

void Block::append(Stmt *s) { 
    stmt_list.push_back(s); 
}

bool Block::empty() const { 
    return stmt_list.empty(); 
}

void Block::printAST(std::ostream &out) const {
    out << "Block(";

    bool first = true;
    for(const auto &s : stmt_list) {
        if (!first) out << ", ";
        first = false;
        (s) ? out << *s : out << "null-stmt";
    }
    if(has_auto_end) out << ", OFFSIDE_RULE_SYNTAX";
    else out << ", BEGIN_END_SYNTAX";
    out << ")";
}

/*
void Block::sem_analyze() override {
    for(const auto &s : stmt_list) {
        s->sem_analyze();
    }
    st.exitScope();
}
*/

// -------- DATA TYPE CLASS --------

DataType::DataType(BaseType t) : type(t) {}
DataType::DataType(const DataType& other) : type(other.type) {}

void DataType::printAST(std::ostream &out) const {
    out << "DataType(" << type << ")";
}

// --------- CONST CLASS ---------

Const::Const() {}
Const::Const(int n) : num(n) {}

void Const::printAST(std::ostream &out) const {
    out << "Const(" << num << ")";
}

void Const::sem_analyze() {
    expr_type = TYPE_INT;
}

// ------- BRACKET LIST CLASS -------

BracketList::BracketList() : b_list() {}
 
BracketList::~BracketList() {
    for(auto b : b_list) 
        if(b) delete b;
}

void BracketList::append(Expr *c) { b_list.push_back(c); }
void BracketList::printAST(std::ostream &out) const {
    out << "BracketList(";
    bool first = true;
    for (const auto &c : b_list) {
        if (!first) out << ", ";
        first = false;
        out << "[";
        out << *c;
        out << "]";
    }
    out << ")";
}

void BracketList::sem_analyze() {
    for(const auto &b: b_list) {
        b -> sem_analyze();
    }
}

// --------- TYPE CLASS ---------

Type::Type(DataType *t, Expr *c) : DataType(*t), bracket_list(c) { delete t; }
    
Type::~Type() {
    if(bracket_list) delete bracket_list;
}

void Type::printAST(std::ostream &out) const {
    out << "Type(" << type << ", " << *bracket_list  << ")";
}

// -------- ARRAY PAR CLASS --------

ArrayPar::ArrayPar(DataType *t, Expr *c) : DataType(*t), const_list(c) { delete t; }

ArrayPar::~ArrayPar() {
        if(const_list) delete const_list;
    }

void ArrayPar::printAST(std::ostream &out) const {
    out << "ArrayPar(" << type << "[]"  << *const_list  << ")";
}

// -------- REF PAR CLASS --------

RefPar::RefPar(DataType *t) : DataType(*t) {}
 
RefPar::~RefPar() {}

void RefPar::printAST(std::ostream &out) const {
    out << "RefPar(" << "ref" << type  << ")";
}

// ------------- ID CLASS --------------

Id::Id() {}
Id::Id(std::string s) : name(s) {}

std::string Id::get_name() {
    return name;
}

void Id::printAST(std::ostream &out) const {
    out << "Id(" << name << ")";
}

// ---------- ID LIST CLASS -----------

IdList::IdList() : id_list() {}

IdList::~IdList() {
    for(auto i : id_list) 
        if(i) delete i;
}
    
void IdList::append(Expr *i) { id_list.push_back(i); }
void IdList::prepend(Expr *i) { id_list.insert(id_list.begin(), i); }
bool IdList::empty() const { return id_list.empty(); }

void IdList::printAST(std::ostream &out) const {
    out << "IdList(";
    bool first = true;
    for (const auto &i : id_list) {
        if (!first) out << ", ";
        first = false;
        out << *i;
    }
    out << ")";
}

// -------- FPARDEF CLASS --------

FparDef::FparDef() : name_list(nullptr), type(nullptr) {} 
FparDef::FparDef(Expr *i, DataType *t) : name_list(i), type(t) {}

FparDef::~FparDef() {
    if(name_list) delete name_list;
    if(type) delete type;
}

void FparDef::printAST(std::ostream &out) const {
    out << "FparDef(" << *name_list  << " as " << *type << ")";
}

// void FparDef::sem_analyze() override{
// 	st.insert(name, type); //san assign, apla to kanei i function
// }

// -------- COLFPARDEF CLASS --------

ColFparDef::ColFparDef(FparDef *f) { def_list = {f}; }
	
void ColFparDef::printAST(std::ostream &out) const {
    out << "ColFparDef(" << " : ";
    FparDefList::printAST(out);
    out << ")";
}

// void ColFparDef::sem_analyze() override {
// 	def->sem_analyze();	
// }

// -------- FPARDEFLIST CLASS --------

FparDefList::FparDefList() : def_list() {}

FparDefList::~FparDefList() {
    for(auto d : def_list)
        if(d) delete d;
}
	
void FparDefList::append(FparDef *d) { def_list.push_back(d); }
void FparDefList::prepend(FparDef *d) { def_list.insert(def_list.begin(), d); }
bool FparDefList::empty() const { return def_list.empty(); }

void FparDefList::printAST(std::ostream &out) const {
    out << "FparDefList(";
    bool first = true;
    for (const auto &d : def_list) {  
        if (!first) out << ", ";
        first = false;
        (d) ? out << *d : out << "no-params";
    }
    out << ")";     
}	

// ----------- HEADER CLASS -----------

Header::Header(Expr *s, IsDataType *d, ColFparDef *c) : name(s), is_d_type(d), col_def(c) {}

Header::~Header() {
    delete name;
    if(is_d_type) delete is_d_type;
    if(col_def) delete col_def;
}

void Header::printAST(std::ostream &out) const {
    out << "Header" << "(" << *name << ", ";
    
    (is_d_type) ? out << *is_d_type << ", " : out << "NO_DATA_TYPE, ";  
    (col_def) ? out << *col_def << ")" : out << "NO_COL_DEF)";  
}

// void Header::sem_analyze() override {
// 	if(is_d_type){
// 		data_type = new DataType(is_d_type->type);
// 		st.insert(name, data_type);
// 	}
// 	if(col_def){
// 		col_def->sem_analyze();
// 	}
// }

// --------- IS DATA_TYPE CLASS ---------

IsDataType::IsDataType(DataType *t) : DataType(*t) {}

void IsDataType::printAST(std::ostream &out) const {
    out << "IsDataType(" << " is " << type << ")";
}

// --------- COLID CLASS ---------

Label::Label(Id *i) : name(i) {}

Label::~Label() {
    delete name;
}
	
void Label::printAST(std::ostream &out) const {
    out << "Label(" << " : " <<  *name  << ")";
}

void Label::sem_analyze() {
    std::string tag_name = name -> get_name();
 	st.lookup(tag_name); 	

}

Id *Label::get_id() {
    return name;
}

// --------- ONECOLEXPR CLASS ---------

OneColExpr::OneColExpr(Expr *e) : Expr(*e) {}

void OneColExpr::printAST(std::ostream &out) const {
    out << "OneColExpr(" << " : ";
    Expr::printAST(out);
    out << ")";
}

// --------- EXPR_LIST CLASS ---------

ExprList::ExprList() : expr_list() {}
 
ExprList::~ExprList() {
    if(!expr_list.empty())
    for (auto expr : expr_list)
        if(expr) delete expr;
}

void ExprList::append(Expr *e) { expr_list.push_back(e); }
void ExprList::prepend(Expr *e) { expr_list.insert(expr_list.begin(), e); }
bool ExprList::empty() const { return expr_list.empty(); }

void ExprList::printAST(std::ostream &out) const {
    out << "ExprList(";
    bool first = true;
    for(const auto &e : expr_list) {
        if (!first) out << ", ";
        first = false;
        (e) ? out << *e : out << "null-expr";
    }
    out << ")";
}

// void ExprList::sem_analyze() override {
// 	for(const auto &e : expr_list){
// 		e->sem_analyze();
// 	} 
// }

// ---------- CHAR CLASS ----------

Char::Char(char c) : ch(c) {}

void Char::printAST(std::ostream &out) const {
    out << "Char(" << ch << ")";
}

void Char::sem_analyze() {
    expr_type = TYPE_BYTE;
}

// ---------- STR CLASS ----------

Str::Str(std::string s) : val(s) {}

void Str::printAST(std::ostream &out) const {
    out << "Str(" << val << ")";
}

void Str::sem_analyze() {
    expr_type = TYPE_BYTE_ARRAY;
}

// --------- LVALUE CLASS ---------

LValue::LValue(Expr *str){ list.push_back(str); }

LValue::~LValue() {
    if(!list.empty())
        for(auto l : list)
            if(l) delete l;
}
    
void LValue::append(Expr *e) { list.push_back(e); }

void LValue::printAST(std::ostream &out) const {
    out << "LValue(";
    bool first = true;
    for (const auto &e : list) {
        if (!first) out << ", ";
        first = false;
        out << *e;
    }
    out << ")";
}

// void LValue::sem_analyze() override {
// 	//not yet, needs more thinking..
// }

// --------- LOCAL DEF LIST CLASS ---------

LocalDefList::LocalDefList() : def_list() {}

LocalDefList::~LocalDefList() {
    if(!def_list.empty())
        for(auto d : def_list) 
            if(d) delete d;
}
    
void LocalDefList::append(LocalDef *d) { def_list.push_back(d); }
void LocalDefList::prepend(LocalDef *d) { def_list.insert(def_list.begin(), d); }
bool LocalDefList::empty() const { return def_list.empty(); }

void LocalDefList::printAST(std::ostream &out) const {
    out << "LocalDefList(";
    bool first = true;
    for (const auto &d : def_list) {
        if (!first) out << ", ";
        first = false;
        (d) ? out << *d : out << "null-definition";
    }
    out << ")";
}

// --------- FUNC_DEF CLASS ---------

FuncDef::FuncDef(Header *h, LocalDef *l, Block *b) : head(h), def_list(l), block(b) {}
    
FuncDef::~FuncDef() {
    if(head) delete head;
    if(def_list) delete def_list;
    if(block) delete block;
}

void FuncDef::printAST(std::ostream &out) const {
    out << "Def" << "(" << *head << ", " << *def_list << ", " << *block << ")";
}

// --------- VAR_DEF CLASS ---------

VarDef::VarDef(Id *i, DataType *t) : type(t), name(i) {}
    
VarDef::~VarDef() {
    if(type) delete type;
    if(name) delete name;
}

void VarDef::printAST(std::ostream &out) const {
    out << "VarDef(" << *name << " is " << *type << ")";
}

void VarDef::sem_analyze() {
 	st.insert(name->get_name(), /**/, KIND_ID, /**/ {});
}

// --------- FUNC_DECL CLASS ---------

FuncDecl::FuncDecl(Header *h) : header(h) {}

FuncDecl::~FuncDecl() {
    delete header;
}

void FuncDecl::printAST(std::ostream &out) const {
    out << "Decl(" << " decl " << *header << ")";
}

// --------- PROC_DECL CLASS ---------

ProcCall::ProcCall(Expr *i, OneColExpr *e) : name(i), col_expr(e) {}

ProcCall::~ProcCall() {
    if(name) delete name;
    if(col_expr) delete col_expr;
}

void ProcCall::printAST(std::ostream &out) const {
    out << "ProcCall(" << *name << ", ";
    (col_expr) ? out << *col_expr  << ")" : out << "NO_ARGS)"; 
}

// --------- FUNC_CALL CLASS ---------

FuncCall::FuncCall(Expr *i, Expr *e) : name(i), expr(e) {}

FuncCall::~FuncCall() {
    if(name) delete name;
    if(expr) delete expr;
}

void FuncCall::printAST(std::ostream &out) const  {
    out << "FuncCall(" << *name << ", ";
    (expr) ? out << *expr  << ")" : out << "NO_ARGS)";
}

void FuncCall::sem_analyze() {
    //check_scope gia name
    //num of parameters are same of the func
}

// --------- NOT_COND CLASS ---------

NotCond::NotCond(Expr *c) : cond(c) {}

NotCond::~NotCond() {
    if(cond) delete cond;
}

void NotCond::printAST(std::ostream &out) const {
    out << "NotCond(" << "not " << *cond  << ")";
}

void NotCond::sem_analyze() {
    cond -> check_type(TYPE_BOOL, TYPE_BOOL);
    expr_type = TYPE_BOOL;
}

// --------- BINOP CLASS ---------

BinOpCond::BinOpCond(Expr *c1, std::string *o, Expr *c2) : cond1(c1), op(*o), cond2(c2) { delete o; }

BinOpCond::~BinOpCond() {
    if(cond1) delete cond1;
    if(cond2) delete cond2;
}

void BinOpCond::printAST(std::ostream &out) const {
    out << op << "(" << *cond1 << ", " << *cond2  << ")";
}

void BinOpCond::sem_analyze() {
    cond1 -> check_type(TYPE_BOOL, TYPE_BOOL);
    cond2 -> check_type(TYPE_BOOL, TYPE_BOOL);

    expr_type = TYPE_BOOL;
}

// --------- UNARYOP CLASS ---------

UnaryOpExpr::UnaryOpExpr(std::string *o, Expr *e) : op(*o), expr(e) { delete o; }

UnaryOpExpr::~UnaryOpExpr() {
    if(expr) delete expr;
}

void UnaryOpExpr::printAST(std::ostream &out) const {
    out << op << "(" << *expr << ")";
}

void UnaryOpExpr::sem_analyze() {
    if(op == "!") {
        expr -> check_type(TYPE_BYTE, TYPE_BYTE);
        expr_type = TYPE_BYTE;
    }
    else {
        expr -> check_type(TYPE_INT, TYPE_INT);
        expr_type = TYPE_INT;
    }
}

// --------- BINOP_EXPR CLASS ---------

BinOpExpr::BinOpExpr(Expr *e1, std::string *o, Expr *e2) : expr1(e1), op(*o), expr2(e2) { delete o; }

BinOpExpr::~BinOpExpr() {
    if(expr1) delete expr1;
    if(expr2) delete expr2;
}

void BinOpExpr::printAST(std::ostream &out) const {
    out << op << "(" << *expr1 << ", " << *expr2 << ")";
}

void BinOpExpr::sem_analyze() {
    expr1 -> check_type(TYPE_INT, TYPE_BYTE);
    expr2 -> check_type(TYPE_INT, TYPE_BYTE);

    ExprType expr1_type = expr1 -> get_type();
    ExprType expr2_type = expr2 -> get_type();
    if( expr1_type != expr2_type ) printf("INCOMPATIBLE TYPES"); // RAISE ERROR

    if(op == "+" || op == "-" || op == "/" || op == "*" || op == "%" || op == "&" || op == "|") expr_type = expr1_type;
    else expr_type = TYPE_BOOL;
}

// --------- BOOL_VAL CLASS ---------

BoolVal::BoolVal(char bv) : boolval(bv) {}

void BoolVal::printAST(std::ostream &out) const {
    out << "BoolVal" << "("<< (boolval ? "true" : "false")  << ")";
}

void BoolVal::sem_analyze() {
    expr_type = TYPE_BOOL;
}

// --------- SKIP CLASS ---------

Skip::Skip() {}

void Skip::printAST(std::ostream &out) const {
    out << "Skip(" <<  ")";
}

void Skip::sem_analyze() {
    return;
}

// --------- ASSIGN CLASS ---------

Assign::Assign(Expr *l, Expr *e) : lvalue(l), expr(e) {}

Assign::~Assign() {
    if(lvalue) delete lvalue;
    if(expr) delete expr;
}

void Assign::printAST(std::ostream &out) const {
    out << "Assign(" << *lvalue << " := " << *expr  << ")";
}

// --------- EXIT CLASS ---------

Exit::Exit() {}

void Exit::printAST(std::ostream &out) const {
    out << "Exit(" << ")";
}

void Exit::sem_analyze() {
    st.exitScope();
}
// --------- BREAK CLASS ---------

Break::Break(Label *c) : col_id(c) {}

Break::~Break() {
    if(col_id) delete col_id;
}

void Break::printAST(std::ostream &out) const {
    out << "Break(";
    (col_id) ? out << *col_id  << ")" : out << "no-id)";
}

void Break::sem_analyze() {
 	if(col_id) {
        col_id -> sem_analyze(); 
        std::string name = (col_id->get_id())->get_name();
        st.nested_pop(name);
    }
 	else {
        st.exitScope();
    }
}

// --------- CONTINUE CLASS ---------

Continue::Continue(Label *c) : col_id(c) {}

Continue::~Continue() {
    if(col_id) delete col_id;
}

void Continue::printAST(std::ostream &out) const {
    out << "Continue(";
    (col_id) ? out << *col_id  << ")" : out << "no-id)";
}

void Continue::sem_analyze() {
    if(col_id) col_id -> sem_analyze();
}

// --------- RETURN CLASS ---------

Return::Return(Expr *e) : expr(e) {}

Return::~Return() {
    delete expr;
}
    
void Return::printAST(std::ostream &out) const {
    out << "Return(" << *expr << ")";
}

void Return::sem_analyze() {
    st.exitScope();
}

// --------- IFTHENELSE CLASS ---------

IfThenElse::IfThenElse(Expr *c, Block *b, Stmt *ef, Stmt *e) : cond(c), block(b), elif(ef), els(e) {}

IfThenElse::~IfThenElse() {
    if(cond) delete cond;
    if(block) delete block;
    if(elif) delete elif;
    if(els) delete els;
}

void IfThenElse::printAST(std::ostream &out) const {
    out << "IfThenElse(" << *cond << ", "<< *block << ", ";
    (elif) ? out << *elif << ", " : out << "no-elif, ";
    (els) ? out << *els  << ")" : out << "no-else)";
}

void IfThenElse::sem_analyze() {
	cond->check_type(TYPE_BOOL, TYPE_BOOL);
	block->sem_analyze();
	if(elif) elif->sem_analyze();
	if(els) els->sem_analyze();
}

// --------- ELIF CLASS ---------

Elif::Elif() : cond(nullptr), block(nullptr) {}
Elif::Elif(Expr *c, Block *b) : cond(c), block(b) {}

Elif::~Elif() {
    if(cond) delete cond;
    if(block) delete block;
}

void Elif::printAST(std::ostream &out) const {
    out << "Elif(" << *cond << " : "  << *block  << ")";
}

void Elif::sem_analyze() {
	cond->check_type(TYPE_BOOL, TYPE_BOOL);
	block->sem_analyze();
}

// --------- ELIF_LIST CLASS ---------

ElifList::ElifList() : elif_list() {}

ElifList::~ElifList() {
    if(!elif_list.empty())
        for(auto e : elif_list)
            if(e) delete e;
}

void ElifList::append(Stmt *e) { elif_list.push_back(e); }

void ElifList::printAST(std::ostream &out) const {
    out << "ElifList(";
    bool first = true;
    for (const auto &e : elif_list) {
        if (!first) out << ", ";
        first = false;
        out << *e;
    }
    out << ")";
}

void ElifList::sem_analyze() {
    for(const auto &e : elif_list) {
        e->sem_analyze();
    }
}

// --------- ELSE CLASS ---------

Else::Else(Block *b) : block(b) {}

Else::~Else() {
    if(block) delete block;
}

void Else::printAST(std::ostream &out) const {
    out << "Else(" << *block  << ")";
}

void Else::sem_analyze() {
	block->sem_analyze();
}

// --------- LOOP CLASS ---------

Loop::Loop(Id *i, Block *b) : name(i), block(b) {}

Loop::~Loop() {
    if(block) delete block;
    if(name) delete name;
}

void Loop::printAST(std::ostream &out) const {
    out << "Loop(";
    (name) ? out << *name << ", " : out << "no-name loop, "; 
    out <<  *block  << ")";
}

void Loop::sem_analyze() {
	st.enterScope();
    std::string n = name -> get_name();
	std::string loop_name = (!n.empty()) ? n : "default";
    st.insert(loop_name, VOID, KIND_LOOP, {}, {}); 
	block->sem_analyze();
}
