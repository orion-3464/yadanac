#ifndef __AST_H__
#define __AST_H__

#include <string>
#include <vector>

class AST {
	public:
	virtual void printAST(std::ostream &out) const=0;

	private:
};
	
inline std::ostream &operator<<(std::ostream &out, const AST &ast) {
	ast.printAST(out);
	return out;
}

class FparType : public AST {
public:
private:
}

class Expr : public Cond {
public:
private: 
};

class Stmt : public AST {
public:
private:
};

class LocalDef : public AST {
public:
private:
};

class Cond : public AST {
public:
private:
};

class Block : public Stmt { //ena block einai ena stmt_list !!
public:
    Block() : stmt_list() {}
    
	void append(Stmt *s) { stmt_list.push_back(s); }
    void prepend(Stmt *s) { stmt_list.insert(stmt_list.begin(), s); }
    bool empty() const { return stmt_list.empty(); }
    virtual void printAST(std::ostream &out) const override {
        out << "Block(";
        bool first = true;
        for (const auto &s : stmt_list) {
            if (!first) out << ", ";
            first = false;
            out << *s;
        }
        out << ")";
    }
private:
    std::vector<Stmt *> stmt_list;
};

class LValue : public Expr {
public:
    LValue(Expr *str){ list.push_back(str); }
    
	void append(Expr *e) { list.push_back(e); }
    virtual void printAST(std::ostream &out) const override {
        out << "LValue(";
        bool first = true;
        for (const auto &e : list) {
            if (!first) out << ", ";
            first = false;
            out << *e;
        }
        out << ")";
    }
private:
    std::vector<Expr *> list;
};

class FuncDef : public LocalDef {
public:
	FuncDef(Header *h, LocalDefList *l, Block *b) : head(h), def_list(l), block(b) {}
    
	void printAST(std::ostream &out) const override {
    	out << "Def" << "(" << *head << ", " << *def_list << ", " << *block << ")";
    }

private:
    Header *head;
    LocalDefList *def_list;
    Block *block;
};

class VarDef : public LocalDef {
public:
	VarDef(Id *i, Type *t) : name(i), type(t) {}
    
	virtual void printAST(std::ostream &out) const override {
    	out << "VarDef(" << *name << " is " << *type << ")";
    }
private:
	Type *type;
	Id *name;
};

class FuncDecl : public LocalDef {
public:
    Decl(Header *h) : header(h) {}

    virtual void printAST(std::ostream &out) const override {
        out << "Decl(" << " decl " << *header << ")";
    }
private:
    Header *header;
};

class LocalDefList : public LocalDef {
public:
    LocalDefList() : def_list() {}
    
	void append(LocalDef *d) { def_list.push_back(d); }
    void prepend(LocalDef *d) { def_list.insert(def_list.begin(), d); }
    bool empty() const { return def_list.empty(); }
    virtual void printAST(std::ostream &out) const override {
        out << "LocalDefList(";
        bool first = true;
        for (const auto &d : def_list) {
            if (!first) out << ", ";
            first = false;
            out << *d;
        }
        out << ")";
    }
private:
	std::vector<LocalDef *> def_list;
};

class Header : public AST {
public:
    Header(Id *s, IsDataType *d, ColFparDef *c) : name(s), is_d_type(d), col_def(c) {}
    
	void printAST(std::ostream &out) const override {
    	out << "Header" << "(" << *name << ", " << *is_d_type << ", " << *col_def << ")";
    }
private:
    Id *name;
    IsDataType *is_d_type;
    ColFparDef *col_def;
};

class ColFparDef : public AST {
public:
    ColFparDef(FparDef *f) : def(f) {}
    
	virtual void printAST(std::ostream &out) const override {
        out << "ColFparDef(" << " : "  << *def << ")";
    }
private:
    FparDef *def;
};

class FparDef : public AST {
public:
	FparDef(Id *i, FparType *t;) : name(i), type(t) {}
    
	virtual void printAST(std::ostream &out) const override {
        out << "FparDef(" << name << " as " << type << ")";
    }
private:
    Id *name;
	FparType *type;
};

class FparDefList : public FparDef {
public:
    FparDefList() : def_list() {}
	
	void append(FparDef *d) { def_list.push_back(d); }
    void prepend(FparDef *d) { def_list.insert(def_list.begin(), d); }
    bool empty() const { return def_list.empty(); }
    virtual void printAST(std::ostream &out) const override {
        out << "FparDefList(";
    	bool first = true;
    	for (const auto &d : def_list) {  
    		if (!first) out << ", ";
     		first = false;
      		out << *d;
    	}
    	out << ")";     
	}	
private:
    std::vector<FparDef *> def_list;
};

class IsDataType : public AST {
public:
    IsDataType(DataType *t;) : type(t) {}
    
	virtual void printAST(std::ostream &out) const override {
        out << "IsDataType(" << " is " << type << ")";
    }
private:
    DataType *type;
};

class DataType : public AST {
public:
    DataType(std::string t) : type(t) {}
    
	virtual void printAST(std::ostream &out) const override {
        out << "DataType(" << type << ")";
    }
private:
    std::string type;
};

class Type : public FparType {
public:
    Type(DataType *t, Const *c) : type(t), const_list(c) {}
    
	virtual void printAST(std::ostream &out) const override {
        out << "Type(" << *type << ", " << *const_list  << ")";
    }
private:
    DataType *type;
	Const *const_list;
};

class RefPar : public FparType {
public:
    RefPar(Type *t) : type(t) {}

    virtual void printAST(std::ostream &out) const override {
        out << "RefPar(" << "ref" << *type  << ")";
    }
private:
    Type *type;
};

class ArrayPar : public FparType {
public:
    ArrayPar(DataType *t, Const *c) : type(t), const_list(c) {}

    virtual void printAST(std::ostream &out) const override {
        out << "ArrayPar(" << *type << "[]"  << *const_list  << ")";
    }
private:
    DataType *type;
    Const *const_list;
};

class OneColExpr : public AST {
public:
    OneColExpr(Expr *e) : expr(e) {}

    virtual void printAST(std::ostream &out) const override {
        out << "OneColExpr(" << " : " <<  *expr  << ")";
    }
private:
    Expr *expr;
};

class ProcCall : public AST {
public:
    ProcCall(Id *i, OneColExpr *e) : name(i), col_expr(e) {}

    virtual void printAST(std::ostream &out) const override {
        out << "ProcCall(" << *name << ", " << *col_expr  << ")";
    }
private:
    Id *name;
    OneColExpr *col_expr;
};

class FuncCall : public AST {
public:
    FuncCall(Id *i, Expr *e) : name(i), expr(e) {}

    virtual void printAST(std::ostream &out) const override {
        out << "FuncCall(" << *name << ", " << *expr  << ")";
    }
private:
    Id *name;
    Expr *expr;
};

class NotCond : public Cond {
public:
    NotCond(Cond *c) : cond(c) {}

    virtual void printAST(std::ostream &out) const override {
        out << "NotCond(" << "not " << *cond  << ")";
    }
private:
    Cond *cond;
};

class BinOpCond : public Cond {
public:
    BinOpCond(Cond *c1, std::string o, Cond *c2) : cond1(c1), op(o), cond2(c2) {}

    virtual void printAST(std::ostream &out) const override {
        out << op << "(" << *type << *const_list  << ")";
    }
private:
    Cond *cond1, *cond2;
	std::string op;
};

class Skip : public Stmt {
public:
    Skip() :  {}

    virtual void printAST(std::ostream &out) const override {
        out << "Skip(" <<  ")";
    }
private:
};

class Assign : public Stmt {
public:
    Assign(LValue *l, Expr *e) : lvalue(l), expr(e) {}

    virtual void printAST(std::ostream &out) const override {
        out << "Assign(" << *lvalue << " := " << *expr  << ")";
    }
private:
    LValue *lvalue;
    Expr *expr;
};

class Exit : public Stmt { 
public:
    Exit() : {}

    virtual void printAST(std::ostream &out) const override {
        out << "Exit(" <<  << ")";
    }
private:
};

class IfThenElse : public Stmt {
public:
    IfThenElse(Cond *c, Block *b, Elif *ef, Else *e) : cond(c), block(b), elif(ef), els(e) {}

    virtual void printAST(std::ostream &out) const override {
        out << "IfThenElse(" << *cond << ", " << *block << ", " << *elif << ", " << *els  << ")";
    }
private:
    DataType *type;
    Const *const_list;
};

class Elif : public Stmt {
public:
    Elif(Cond *c, Block *b) : cond(c), block(b) {}

    virtual void printAST(std::ostream &out) const override {
        out << "Elif(" << *cond << " : "  << *block  << ")";
    }
private:
    Block *block;
    Cond *cond;
};

class ElifList : public ELif {
    ElifList() : elif_list() {}

    void append(Elif *e) { elif_list.push_back(e); }
    virtual void printAST(std::ostream &out) const override {
        out << "ElifList(";
        bool first = true;
        for (const auto &e : elif_list) {
            if (!first) out << ", ";
            first = false;
            out << *e;
        }
        out << ")";
    }
private:
    std::vector<Elif *> elif_list;
};

class Else : public Stmt {
public:
    Else(Block *b) : block(b) {}

    virtual void printAST(std::ostream &out) const override {
        out << "Else(" << *block  << ")";
    }
private:
    Block *block;
};

class Loop : public Stmt {
public:
    Loop(Id *i, Block *b) : name(i), block(b) {}

    virtual void printAST(std::ostream &out) const override {
        out << "Loop(" << *name << ", " <<  *block  << ")";
    }
private:
    Id *name;
    Block *block;
};

class Break : public Stmt {
public:
    Break(ColId *c) : col_id(c) {}

    virtual void printAST(std::ostream &out) const override {
        out << "Break(" << *col_id  << ")";
    }
private:
    ColId *col_id;
};

class Continue : public Stmt {
public:
    Continue(ColId *c) : col_id(c) {}

    virtual void printAST(std::ostream &out) const override {
        out << "Continue(" << *col_id  << ")";
    }
private:
    ColId *col_id;
};

class Return : public Stmt {
public:
    Return(Expr *e) : expr(e) {}
    
    virtual void printAST(std::ostream &out) const override {
        out << "Return(" << *expr << ")";
    }
private: 
    Expr *expr;
};

class UnaryOpExpr : public Expr {
public:
  	UnaryOpExpr(std::string o, Expr *e) : op(o), expr(e) {}
  	void printAST(std::ostream &out) const override {
    	out << op << "(" << *expr << ")";
  	}
private:
  	Expr *expr;
  	char op;
};

class BinOpExpr : public Expr {
public:
  	BinOpExpr(Expr *e1, char o, Expr *e2) : expr1(e1), op(o), expr2(e2) {}
  	void printAST(std::ostream &out) const override {
    	out << op << "(" << *expr1 << ", " << *expr2 << ")";
  	}
private:
  	Expr *expr1;
  	char op;
  	Expr *expr2;
};

class BoolVal : public Expr {
public:
    BoolVal(std::string s) : bool_val(s) {}

    virtual void printAST(std::ostream &out) const override {
        out << bool_val << "(" << ")";
    }
private:
    std::string bool_val;
};

class Str : public Expr {
public:
    Str(std::string s) : val(s) {}

    virtual void printAST(std::ostream &out) const override {
        out << "Str(" << val << ")";
    }
private:
    std::string val;
};

class Id : public Expr {
public:
    Id(std::string s) : name(s) {}

    virtual void printAST(std::ostream &out) const override {
        out << "Id(" << name << ")";
    }
private:
    std::string name;
};

class IdList : public Id {
public:
    IdList() : id_list() {}
    
	void append(Id *i) { id_list.push_back(i); }
    void prepend(Id *i) { id_list.insert(def_list.begin(), i); }
    bool empty() const { return id_list.empty(); }
    virtual void printAST(std::ostream &out) const override {
        out << "IdList(";
        bool first = true;
        for (const auto &i : id_list) {
            if (!first) out << ", ";
            first = false;
            out << *i;
        }
        out << ")";
    }
private:
    std::vector<Id *> id_list;
};

class ColId : public AST {
public:
    ColId(Id *i) : name(i) {}

    virtual void printAST(std::ostream &out) const override {
        out << "ColId(" << " : " <<  *name  << ")";
    }
private:
    Id *name;
};

class Char : public Expr {
public:
    Char(char c) : ch(c) {}

	virtual void printAST(std::ostream &out) const override {
        out << "Char(" << ch << ")";
    }
private:
    char ch;
};

class Const : public Expr {
public:
    Const(int n) : num(n) {}

    virtual void printAST(std::ostream &out) const override {
        out << "Const(" << num << ")";
    }
private:
    int num;
};

class BracketList : public Const {
public:
    BracketList() : b_list() {}
 
    void append(Const *c) { b_list.push_back(c); }
    virtual void printAST(std::ostream &out) const override {
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
private:
    std::vector<Const *> b_list;
};

#endif /* __AST_H__ */
