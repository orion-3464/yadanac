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

