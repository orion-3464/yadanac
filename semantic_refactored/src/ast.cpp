#include "ast.hpp"

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

BaseType DataType::get_type() const { return type; }

void DataType::printAST(std::ostream &out) const {
    out << "DataType(" << type << ")";
}

// --------- CONST CLASS ---------

Const::Const() {}
Const::Const(int n) : num(n) {}

void Const::printAST(std::ostream &out) const {
    out << "Const(" << num << ")";
}

/*
void sem_analyze() override {
    type = TYPE_INT;
}
*/

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

// --------- TYPE CLASS ---------

Type::Type(DataType *t, Expr *c) : DataType(t->get_type()), bracket_list(c) { delete t; }
    
Type::~Type() {
    if(bracket_list) delete bracket_list;
}

void Type::printAST(std::ostream &out) const {
    out << "Type(" << get_type() << ", " << *bracket_list  << ")";
}

// -------- ARRAY PAR CLASS --------

ArrayPar::ArrayPar(DataType *t, Expr *c) : DataType(t->get_type()), const_list(c) { delete t; }

ArrayPar::~ArrayPar() {
        if(const_list) delete const_list;
    }

void ArrayPar::printAST(std::ostream &out) const {
    out << "ArrayPar(" << get_type() << "[]"  << *const_list  << ")";
}

// -------- REF PAR CLASS --------

RefPar::RefPar(DataType *t) : DataType(t->get_type()) {}
 
RefPar::~RefPar() {}

void RefPar::printAST(std::ostream &out) const {
    out << "RefPar(" << "ref" << get_type()  << ")";
}

// ------------- ID CLASS --------------

Id::Id() {}
Id::Id(std::string s) : name(s) {}

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

FparDef::FparDef() : name(nullptr), type(nullptr) {} 
FparDef::FparDef(Expr *i, DataType *t) : name(i), type(t) {}

FparDef::~FparDef() {
    if(name) delete name;
    if(type) delete type;
}

void FparDef::printAST(std::ostream &out) const {
    out << "FparDef(" << *name  << " as " << *type << ")";
}

// void FparDef::sem_analyze() override{
// 	st.insert(name, type); //san assign, apla to kanei i function
// }

// -------- COLFPARDEF CLASS --------

ColFparDef::ColFparDef(FparDef *f) : def(f) {}

ColFparDef::~ColFparDef() {
    if(def) delete def;
}
	
void ColFparDef::printAST(std::ostream &out) const {
    out << "ColFparDef(" << " : "  << *def << ")";
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

IsDataType::IsDataType(DataType *t) : type(t) {}

IsDataType::~IsDataType() {
    delete type;
}

void IsDataType::printAST(std::ostream &out) const {
    out << "IsDataType(" << " is " << type << ")";
}

// --------- COLID CLASS ---------

ColId::ColId(Expr *i) : name(i) {}

ColId::~ColId() {
    delete name;
}
	
void ColId::printAST(std::ostream &out) const {
    out << "ColId(" << " : " <<  *name  << ")";
}

// void ColId::sem_analyze() override {
// 	st.lookup(name, "loop"); //loop is a "kind" type
// 	//has no type cause it's a tag
// 	//lookup does the check		
// }

// --------- ONECOLEXPR CLASS ---------

OneColExpr::OneColExpr(Expr *e) : expr(e) {}

OneColExpr::~OneColExpr() {
    delete expr;
}

void OneColExpr::printAST(std::ostream &out) const {
    out << "OneColExpr(" << " : " <<  *expr  << ")";
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

// ---------- STR CLASS ----------

Str::Str(std::string s) : val(s) {}

void Str::printAST(std::ostream &out) const {
    out << "Str(" << val << ")";
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

VarDef::VarDef(Expr *i, DataType *t) : type(t), name(i) {}
    
VarDef::~VarDef() {
    if(type) delete type;
    if(name) delete name;
}

void VarDef::printAST(std::ostream &out) const {
    out << "VarDef(" << *name << " is " << *type << ")";
}

// void VarDef::sem_analyze() override {
// 	st.insert(name, type);
// }

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

// --------- NOT_COND CLASS ---------

NotCond::NotCond(Expr *c) : cond(c) {}

NotCond::~NotCond() {
    if(cond) delete cond;
}

void NotCond::printAST(std::ostream &out) const {
    out << "NotCond(" << "not " << *cond  << ")";
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

// --------- UNARYOP CLASS ---------

UnaryOpExpr::UnaryOpExpr(std::string *o, Expr *e) : op(*o), expr(e) { delete o; }

UnaryOpExpr::~UnaryOpExpr() {
    if(expr) delete expr;
}

void UnaryOpExpr::printAST(std::ostream &out) const {
    out << op << "(" << *expr << ")";
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

// --------- BOOL_VAL CLASS ---------

BoolVal::BoolVal(char bv) : boolval(bv) {}

void BoolVal::printAST(std::ostream &out) const {
    out << "BoolVal" << "("<< (boolval ? "true" : "false")  << ")";
}

// --------- SKIP CLASS ---------

Skip::Skip() {}

void Skip::printAST(std::ostream &out) const {
    out << "Skip(" <<  ")";
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

// --------- BREAK CLASS ---------

Break::Break(ColId *c) : col_id(c) {}

Break::~Break() {
    if(col_id) delete col_id;
}

void Break::printAST(std::ostream &out) const {
    out << "Break(";
    (col_id) ? out << *col_id  << ")" : out << "no-id)";
}

// void Break::sem_analyze() override {
// 	if(col_id)col_id->sem_analyze();
// 	else st.lookup("loop");
// }

// --------- CONTINUE CLASS ---------

Continue::Continue(ColId *c) : col_id(c) {}

Continue::~Continue() {
    if(col_id) delete col_id;
}

void Continue::printAST(std::ostream &out) const {
    out << "Continue(";
    (col_id) ? out << *col_id  << ")" : out << "no-id)";
}

// void Continue::sem_analyze() override {
// 	if(col_id)col_id->sem_analyze();
// 	else st.lookup("loop");
// }

// --------- RETURN CLASS ---------

Return::Return(Expr *e) : expr(e) {}

Return::~Return() {
    delete expr;
}
    
void Return::printAST(std::ostream &out) const {
    out << "Return(" << *expr << ")";
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
    out << "IfThenElse(" << *cond << ", "<< *block << ", " << *elif << ", ";
    (els) ? out << *els  << ")" : out << "no-else)";
}

// void IfThenElse::sem_analyze() override {
// 	cond->check_type(TYPE_BOOL);
// 	block->sem_analyze();
// 	elif->sem_analyze(); //check in elif_list if it is nullptr
// 	if (els != nullptr) els->sem_analyze();
// }

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

// --------- ELSE CLASS ---------

Else::Else(Block *b) : block(b) {}

Else::~Else() {
    if(block) delete block;
}

void Else::printAST(std::ostream &out) const {
    out << "Else(" << *block  << ")";
}

// --------- LOOP CLASS ---------

Loop::Loop(Expr *i, Block *b) : name(i), block(b) {}

Loop::~Loop() {
    if(block) delete block;
    if(name) delete name;
}

void Loop::printAST(std::ostream &out) const {
    out << "Loop(";
    (name) ? out << *name << ", " : out << "no-name loop, "; 
    out <<  *block  << ")";
}

// void Loop::sem_analyze() override {
// 	st.enterScope();
// 	if(name) st.insert(name, "loop"); //loop is a kind type (enum)
// 	else st.insert("", "loop")
// 	block->sem_analyze();
// }