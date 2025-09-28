#ifndef __AST_H__
#define __AST_H__

#include <string>
#include <vector>
#include <iostream>
#include "symbol.hpp"

class Header;
class LocalDefList;
class Block;
class Id;
class Type;
class IsDataType;
class ColFparDef;
class FparDef;
class DataType;
class Const;
class Expr;
class OneColExpr;
class Cond;
class Elif;
class Else;
class ColId;
class LocalDef;

class AST {
	public:
    AST() = default;
    virtual ~AST() = default;

	virtual void printAST(std::ostream &out) const = 0;
    //virtual void sem_analyze() = 0;
};
	
// -------- OUT OPERATORS --------

inline std::ostream &operator<<(std::ostream &out, const AST &ast) {
	ast.printAST(out);
	return out;
}

inline std::ostream &operator<<(std::ostream &out, BaseType t) {
  switch (t) {
    case TYPE_INT: out << "int"; break;

    case TYPE_BYTE: out << "byte"; break;

    case TYPE_BOOL: break; // TO DO

    case TYPE_ARRAY: break; // TO DO

    default: break;

  }
  return out;
}

class Expr : public AST {
public:
    Expr() = default;
    virtual ~Expr() = default;
    // void check_type();
};

class Stmt : public AST {
public:
    Stmt() = default;
    virtual ~Stmt() = default;
};

class Block : public Stmt {     // Blocks are statement lists
public:
    Block();
    ~Block() override;

    void set_auto_end(bool auto_end);
	void append(Stmt *s);
    bool empty() const;

    virtual void printAST(std::ostream &out) const override;
	// void sem_analyze() override;
private:
    std::vector<Stmt *> stmt_list;
    bool has_auto_end;
};

class DataType : public AST {
public:
    DataType(BaseType t);

    BaseType get_type() const;

    void printAST(std::ostream &out) const override;
private:
    BaseType type;
};
class Const : public Expr {
public:
    Const();
    Const(int n);

    void printAST(std::ostream &out) const override;
	//void sem_analyze() override;
private:
    int num;
	//BaseType type;
};
class BracketList : public Const {      // Bracket lists are const lists
public:
    BracketList();
    ~BracketList() override;

    void append(Expr *c);
    void printAST(std::ostream &out) const override ;
private:
    std::vector<Expr *> b_list;
};

class Type : public DataType {
public:
    Type(DataType *t, Expr *c);
    ~Type() override;

	void printAST(std::ostream &out) const override;
private:
	Expr *bracket_list;
};

class ArrayPar : public DataType {
public:
    ArrayPar(DataType *t, Expr *c);
    ~ArrayPar() override;

    void printAST(std::ostream &out) const override;
private:
    Expr *const_list;
};

class RefPar : public DataType {
public:
    RefPar(DataType *t);
    ~RefPar() override;

    void printAST(std::ostream &out) const override;
};

class LocalDef : public AST {
};


class FparDef : public AST {
public:
	FparDef() : name(nullptr), type(nullptr) {} 
    FparDef(Expr *i, DataType *t) : name(i), type(t) {}

    ~FparDef() override {
        delete name;
        delete type;
    }

    void printAST(std::ostream &out) const override {
        out << "FparDef(" << *name  << " as " << *type << ")";
    }

	// void sem_analyze() override{
	// 	st.insert(name, type); //san assign, apla to kanei i function
	// }
	
private:
    Expr *name;
    DataType *type;
};

class ColFparDef : public AST {
public:
    ColFparDef(FparDef *f) : def(f) {}

    ~ColFparDef() override {
        delete def;
    }
	
    void printAST(std::ostream &out) const override {
        out << "ColFparDef(" << " : "  << *def << ")";
    }

	// void sem_analyze() override {
	// 	def->sem_analyze();	
	// }

private:
    FparDef *def;
};
 
class ColId : public AST {
public:
    ColId(Expr *i) : name(i) {}

    ~ColId() override {
        delete name;
    }
	
    void printAST(std::ostream &out) const override {
        out << "ColId(" << " : " <<  *name  << ")";
    }

	// void sem_analyze() override {
	// 	st.lookup(name, "loop"); //loop is a "kind" type
	// 	//has no type cause it's a tag
	// 	//lookup does the check		
	// }

private:
    Expr *name;
};


class IsDataType : public AST {
public:
    IsDataType(DataType *t) : type(t) {}

    ~IsDataType() override {
        delete type;
    }

    void printAST(std::ostream &out) const override {
        out << "IsDataType(" << " is " << type << ")";
    }
private:
    DataType *type;
};

class Header : public AST {
public:
    Header(Expr *s, IsDataType *d, ColFparDef *c) : name(s), is_d_type(d), col_def(c) {}

    ~Header() override {
        delete name;
        if(is_d_type) delete is_d_type;
        if(col_def) delete col_def;
    }

    void printAST(std::ostream &out) const override {
        out << "Header" << "(" << *name << ", ";
        
        (is_d_type) ? out << *is_d_type << ", " : out << "NO_DATA_TYPE, ";  
        (col_def) ? out << *col_def << ")" : out << "NO_COL_DEF)";  
    }

	// void sem_analyze() override {
	// 	if(is_d_type){
	// 		data_type = new DataType(is_d_type->type);
	// 		st.insert(name, data_type);
	// 	}
	// 	if(col_def){
	// 		col_def->sem_analyze();
	// 	}
	// }
private:
    Expr *name;
    IsDataType *is_d_type;
    ColFparDef *col_def;
};

class OneColExpr : public AST {
public:
    OneColExpr(Expr *e) : expr(e) {}

    ~OneColExpr() override {
        delete expr;
    }

    void printAST(std::ostream &out) const override {
        out << "OneColExpr(" << " : " <<  *expr  << ")";
    }
private:
    Expr *expr;
};

class Cond : public Expr {
};

class ExprList : public Expr {
public:
    ExprList() : expr_list() {}
 
    ~ExprList() override {
        for (auto expr : expr_list)
            if(expr) delete expr;
    }

    void append(Expr *e) { expr_list.push_back(e); }
    void prepend(Expr *e) { expr_list.insert(expr_list.begin(), e); }
    bool empty() const { return expr_list.empty(); }

    void printAST(std::ostream &out) const override {
        out << "ExprList(";
        bool first = true;
        for(const auto &e : expr_list) {
            if (!first) out << ", ";
            first = false;
            (e) ? out << *e : out << "null-expr";
        }
        out << ")";
    }
	// void sem_analyze() override {
	// 	for(const auto &e : expr_list){
	// 		e->sem_analyze();
	// 	} 
	// }
private:
    std::vector<Expr *> expr_list;
};

class LValue : public Expr {
public:
    LValue(Expr *str){ list.push_back(str); }

    ~LValue() override {
        for(auto l : list)
            if(l) delete l;
    }
    
	void append(Expr *e) { list.push_back(e); }

    void printAST(std::ostream &out) const override {
        out << "LValue(";
        bool first = true;
        for (const auto &e : list) {
            if (!first) out << ", ";
            first = false;
            out << *e;
        }
        out << ")";
    }

	// void sem_analyze() override {
	// 	//not yet, needs more thinking..
	// }
private:
    std::vector<Expr *> list;
};

class FuncDef : public LocalDef {
public:
	FuncDef(Header *h, LocalDef *l, Block *b) : head(h), def_list(l), block(b) {}
    
    ~FuncDef() override {
        delete head;
        delete def_list;
        delete block;
    }

	void printAST(std::ostream &out) const override {
    	out << "Def" << "(" << *head << ", " << *def_list << ", " << *block << ")";
    }

private:
    Header *head;
    LocalDef *def_list;
    Block *block;
};

class VarDef : public LocalDef {
public:
	VarDef(Expr *i, DataType *t) : type(t), name(i) {}
    
    ~VarDef() override {
        delete type;
        delete name;
    }

	void printAST(std::ostream &out) const override {
    	out << "VarDef(" << *name << " is " << *type << ")";
    }

	// void sem_analyze() override {
	// 	st.insert(name, type);
	// }
private:
	DataType *type;
	Expr *name;
};

class FuncDecl : public LocalDef {
public:
    FuncDecl(Header *h) : header(h) {}

    ~FuncDecl() override {
        delete header;
    }

    void printAST(std::ostream &out) const override {
        out << "Decl(" << " decl " << *header << ")";
    }
private:
    Header *header;
};

class LocalDefList : public LocalDef {
public:
    LocalDefList() : def_list() {}

    ~LocalDefList() override {
        for(auto d : def_list) 
            if(d) delete d;
    }
    
	void append(LocalDef *d) { def_list.push_back(d); }
    void prepend(LocalDef *d) { def_list.insert(def_list.begin(), d); }
    bool empty() const { return def_list.empty(); }

    void printAST(std::ostream &out) const override {
        out << "LocalDefList(";
        bool first = true;
        for (const auto &d : def_list) {
            if (!first) out << ", ";
            first = false;
            (d) ? out << *d : out << "null-definition";
        }
        out << ")";
    }
private:
	std::vector<LocalDef *> def_list;
};

class FparDefList : public FparDef {
public:
    FparDefList() : def_list() {}

    ~FparDefList() override {
        for(auto d : def_list)
            if(d) delete d;
    }
	
	void append(FparDef *d) { def_list.push_back(d); }
    void prepend(FparDef *d) { def_list.insert(def_list.begin(), d); }
    bool empty() const { return def_list.empty(); }

    void printAST(std::ostream &out) const override {
        out << "FparDefList(";
    	bool first = true;
    	for (const auto &d : def_list) {  
    		if (!first) out << ", ";
     		first = false;
            (d) ? out << *d : out << "no-params";
    	}
    	out << ")";     
	}	
private:
    std::vector<FparDef *> def_list;
};

class ProcCall : public Stmt {
public:
    ProcCall(Expr *i, OneColExpr *e) : name(i), col_expr(e) {}

    ~ProcCall() override {
        delete name;
        if(col_expr) delete col_expr;
    }

    void printAST(std::ostream &out) const override {
        out << "ProcCall(" << *name << ", ";
        (col_expr) ? out << *col_expr  << ")" : out << "NO_ARGS)"; 
    }
private:
    Expr *name;
    OneColExpr *col_expr;
};

class FuncCall : public Expr {
public:
    FuncCall(Expr *i, Expr *e) : name(i), expr(e) {}

    ~FuncCall() override {
        delete name;
        if(expr) delete expr;
    }

    void printAST(std::ostream &out) const override {
        out << "FuncCall(" << *name << ", ";
        (expr) ? out << *expr  << ")" : out << "NO_ARGS)";
    }
private:
    Expr *name;
    Expr *expr;
};

class NotCond : public Cond {
public:
    NotCond(Expr *c) : cond(c) {}

    ~NotCond() override {
        delete cond;
    }

    void printAST(std::ostream &out) const override {
        out << "NotCond(" << "not " << *cond  << ")";
    }
private:
    Expr *cond;
};

class BinOpCond : public Cond {
public:
    BinOpCond(Expr *c1, std::string o, Expr *c2) : cond1(c1), op(o), cond2(c2) {}

    ~BinOpCond() override {
        delete cond1;
        delete cond2;
    }

    void printAST(std::ostream &out) const override {
        out << op << "(" << *cond1 << ", " << *cond2  << ")";
    }
private:
    Expr *cond1;
	std::string op;
	Expr *cond2;
};

class Skip : public Stmt {
public:
    Skip() {}

    void printAST(std::ostream &out) const override {
        out << "Skip(" <<  ")";
    }
};

class Assign : public Stmt {
public:
    Assign(Expr *l, Expr *e) : lvalue(l), expr(e) {}

    ~Assign() override {
        delete lvalue;
        delete expr;
    }

    void printAST(std::ostream &out) const override {
        out << "Assign(" << *lvalue << " := " << *expr  << ")";
    }
private:
    Expr *lvalue;
    Expr *expr;
};

class Exit : public Stmt { 
public:
    Exit() {}

    void printAST(std::ostream &out) const override {
        out << "Exit(" << ")";
    }
};

class IfThenElse : public Stmt {
public:
    IfThenElse(Expr *c, Block *b, Stmt *ef, Stmt *e) : cond(c), block(b), elif(ef), els(e) {}

    ~IfThenElse() override {
        delete cond;
        delete block;
        delete elif;
        if(els) delete els;
    }

    void printAST(std::ostream &out) const override {
        out << "IfThenElse(" << *cond << ", "<< *block << ", " << *elif << ", ";
        (els) ? out << *els  << ")" : out << "no-else)";
    }

	// void sem_analyze() override {
    // 	cond->check_type(TYPE_BOOL);
    // 	block->sem_analyze();
    // 	elif->sem_analyze(); //check in elif_list if it is nullptr
	// 	if (els != nullptr) els->sem_analyze();
  	// }
private:
    Expr *cond;
    Block *block;
    Stmt *elif;
    Stmt *els;
};

class Elif : public Stmt {
public:
    Elif() : cond(nullptr), block(nullptr) {}
    Elif(Expr *c, Block *b) : cond(c), block(b) {}

    ~Elif() override {
        delete cond;
        delete block;
    }

    void printAST(std::ostream &out) const override {
        out << "Elif(" << *cond << " : "  << *block  << ")";
    }
private:
    Expr *cond;
	Block *block;
};

class ElifList : public Elif {
public:
    ElifList() : elif_list() {}

    ~ElifList() override {
        for(auto e : elif_list) {
            if(e) delete e;
        }
    }

    void append(Stmt *e) { elif_list.push_back(e); }
    void printAST(std::ostream &out) const override {
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
    std::vector<Stmt *> elif_list;
};

class Else : public Stmt {
public:
    Else(Block *b) : block(b) {}

    ~Else() override {
        delete block;
    }

    void printAST(std::ostream &out) const override {
        out << "Else(" << *block  << ")";
    }
private:
    Block *block;
};

class Loop : public Stmt {
public:
    Loop(Expr *i, Block *b) : name(i), block(b) {}

    ~Loop() override {
        delete block;
        if(name) delete name;
    }

    void printAST(std::ostream &out) const override {
        out << "Loop(";
        (name) ? out << *name << ", " : out << "no-name loop, "; 
        out <<  *block  << ")";
    }

	// void sem_analyze() override {
	// 	st.enterScope();
	// 	if(name) st.insert(name, "loop"); //loop is a kind type (enum)
	// 	else st.insert("", "loop")
	// 	block->sem_analyze();
	// }
private:
    Expr *name;
    Block *block;
};

class Break : public Stmt {
public:
    Break(ColId *c) : col_id(c) {}

    ~Break() override {
        if(col_id) delete col_id;
    }

    void printAST(std::ostream &out) const override {
        out << "Break(";
        (col_id) ? out << *col_id  << ")" : out << "no-id)";
    }

	// void sem_analyze() override {
	// 	if(col_id)col_id->sem_analyze();
	// 	else st.lookup("loop");
	// }
private:
    ColId *col_id;
};

class Continue : public Stmt {
public:
    Continue(ColId *c) : col_id(c) {}

    ~Continue() override {
        if(col_id) delete col_id;
    }

    void printAST(std::ostream &out) const override {
        out << "Continue(";
        (col_id) ? out << *col_id  << ")" : out << "no-id)";
    }

	// void sem_analyze() override {
	// 	if(col_id)col_id->sem_analyze();
	// 	else st.lookup("loop");
	// }
private:
    ColId *col_id;
};

class Return : public Stmt {
public:
    Return(Expr *e) : expr(e) {}

    ~Return() override {
        delete expr;
    }
    
    void printAST(std::ostream &out) const override {
        out << "Return(" << *expr << ")";
    }
private: 
    Expr *expr;
};

class UnaryOpExpr : public Expr {
public:
  	UnaryOpExpr(std::string o, Expr *e) : op(o), expr(e) {}

    ~UnaryOpExpr() override {
        delete expr;
    }

  	void printAST(std::ostream &out) const override {
    	out << op << "(" << *expr << ")";
  	}
private:
    std::string op;
  	Expr *expr;
};

class BinOpExpr : public Expr {
public:
  	BinOpExpr(Expr *e1, std::string o, Expr *e2) : expr1(e1), op(o), expr2(e2) {}

    ~BinOpExpr() override {
        delete expr1;
        delete expr2;
    }

  	void printAST(std::ostream &out) const override {
    	out << op << "(" << *expr1 << ", " << *expr2 << ")";
  	}
private:
  	Expr *expr1;
  	std::string op;
  	Expr *expr2;
};

class BoolVal : public Expr {
public:
    BoolVal(char bv) : boolval(bv) {}

    void printAST(std::ostream &out) const override {
        out << "BoolVal" << "("<< (boolval ? "true" : "false")  << ")";
    }
private:
    char boolval;
};

class Str : public Expr {
public:
    Str(std::string s) : val(s) {}

    void printAST(std::ostream &out) const override {
        out << "Str(" << val << ")";
    }
private:
    std::string val;
};

class Id : public Expr {
public:
    Id() {}
    Id(std::string s) : name(s) {}

    void printAST(std::ostream &out) const override {
        out << "Id(" << name << ")";
    }
private:
    std::string name;
};

class IdList : public Id {
public:
    IdList() : id_list() {}

    ~IdList() override {
        for(auto i : id_list) 
            if(i) delete i;
    }
    
	void append(Expr *i) { id_list.push_back(i); }
    void prepend(Expr *i) { id_list.insert(id_list.begin(), i); }
    bool empty() const { return id_list.empty(); }

    void printAST(std::ostream &out) const override {
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
    std::vector<Expr *> id_list;
};


class Char : public Expr {
public:
    Char(char c) : ch(c) {}

	void printAST(std::ostream &out) const override {
        out << "Char(" << ch << ")";
    }
private:
    char ch;
};

#endif /* __AST_H__ */
