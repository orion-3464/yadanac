#ifndef __AST_H__
#define __AST_H__

#include <string>
#include <vector>
#include <iostream>
#include "symbol.hpp"

enum BaseType {
    INT,
    BYTE
};

class AST {
	public:
    AST() = default;
    virtual ~AST() = default;

	virtual void printAST(std::ostream &out) const = 0;
    virtual void sem_analyze() = 0;
};
	
// -------- OUT OPERATORS --------

inline std::ostream &operator<<(std::ostream &out, const AST &ast) {
	ast.printAST(out);
	return out;
}

inline std::ostream &operator<<(std::ostream &out, BaseType t) {
  switch (t) {
    case INT: out << "int"; break;

    case BYTE: out << "byte"; break;

    default: break;

  }
  return out;
}
class Expr : public AST {
public:
    Expr() = default;
    Expr(const Expr& other);
    virtual ~Expr() = default;

    ExprType get_type();
    void check_type(ExprType expected_type1, ExprType expected_type2);
protected:
    ExprType expr_type;
};

class Stmt : public AST {
public:
    Stmt() = default;
    virtual ~Stmt() = default;
};

class DataType : public AST {
public:
    DataType(BaseType t);
    DataType(const DataType& other);  

    void printAST(std::ostream &out) const override;
protected:
    BaseType type;
};

class LocalDef : public AST {
};


class Cond : public Expr {
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

class Const : public Expr {
public:
    Const();
    Const(int n);

    void printAST(std::ostream &out) const override;
	void sem_analyze() override;
private:
    int num;
};

class BracketList : public Const {      // Bracket lists are const lists
public:
    BracketList();
    ~BracketList() override;

    void append(Expr *c);
    void printAST(std::ostream &out) const override ;
    void sem_analyze() override;
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

class Id : public Expr {
public:
    Id();
    Id(std::string s);

    void printAST(std::ostream &out) const override;
private:
    std::string name;
};

class IdList : public Id {
public:
    IdList();
    ~IdList() override;
    
	void append(Expr *i);
    void prepend(Expr *i);
    bool empty() const;

    void printAST(std::ostream &out) const override;
private:
    std::vector<Expr *> id_list;
};

class FparDef : public AST {
public:
	FparDef(); 
    FparDef(Expr *i, DataType *t);
    ~FparDef() override;

    void printAST(std::ostream &out) const override;
	// void sem_analyze() override;
private:
    Expr *name_list;
    DataType *type;
};

class FparDefList : public FparDef {
public:
    FparDefList();
    ~FparDefList() override;
	
	void append(FparDef *d);
    void prepend(FparDef *d);
    bool empty() const;

    void printAST(std::ostream &out) const override;
protected:
    std::vector<FparDef *> def_list;
};
class ColFparDef : public FparDefList { 
public:
    ColFparDef(FparDef *f);
	
    void printAST(std::ostream &out) const override;
	// void sem_analyze() override;
};

class IsDataType : public DataType {
public:
    IsDataType(DataType *t);

    void printAST(std::ostream &out) const override;
};

class Header : public AST {
public:
    Header(Expr *s, IsDataType *d, ColFparDef *c);
    ~Header() override;

    void printAST(std::ostream &out) const override;
	// void sem_analyze() override;
private:
    Expr *name;
    IsDataType *is_d_type;
    ColFparDef *col_def;
};

class ColId : public Id {
public:
    ColId(Expr *i);
    ~ColId() override;
	
    void printAST(std::ostream &out) const override;
	// void sem_analyze() override;
private:
    Expr *name;
};

class OneColExpr : public Expr {
public:
    OneColExpr(Expr *e);

    void printAST(std::ostream &out) const override;
};

class Char : public Expr {
public:
    Char(char c);

	void printAST(std::ostream &out) const override;
    void sem_analyze() override;
private:
    char ch;
};

class Str : public Expr {
public:
    Str(std::string s);

    void printAST(std::ostream &out) const override;
    void sem_analyze() override;
private:
    std::string val;
};


class ExprList : public Expr {
public:
    ExprList();
    ~ExprList() override;

    void append(Expr *e);
    void prepend(Expr *e);
    bool empty() const;

    void printAST(std::ostream &out) const override;
	// void sem_analyze() override;
private:
    std::vector<Expr *> expr_list;
};

class LValue : public Expr {
public:
    LValue(Expr *str);
    ~LValue() override;
    
	void append(Expr *e);

    void printAST(std::ostream &out) const override;

	// void sem_analyze() override;
private:
    std::vector<Expr *> list;
};

class LocalDefList : public LocalDef {
public:
    LocalDefList();
    ~LocalDefList() override;
    
	void append(LocalDef *d);
    void prepend(LocalDef *d);
    bool empty() const;

    void printAST(std::ostream &out) const override;
private:
	std::vector<LocalDef *> def_list;
};

class FuncDef : public LocalDef {
public:
	FuncDef(Header *h, LocalDef *l, Block *b);
    virtual ~FuncDef() override;

	void printAST(std::ostream &out) const override;
private:
    Header *head;
    LocalDef *def_list;
    Block *block;
};

class VarDef : public LocalDef {
public:
	VarDef(Expr *i, DataType *t);    
    ~VarDef() override;

	void printAST(std::ostream &out) const override;
	// void sem_analyze() override;
private:
	DataType *type;
	Expr *name;
};

class FuncDecl : public LocalDef {
public:
    FuncDecl(Header *h);
    ~FuncDecl() override;

    void printAST(std::ostream &out) const override;
private:
    Header *header;
};

class ProcCall : public Stmt {
public:
    ProcCall(Expr *i, OneColExpr *e);
    ~ProcCall() override;

    void printAST(std::ostream &out) const override;
private:
    Expr *name;
    OneColExpr *col_expr;
};

class FuncCall : public Expr {
public:
    FuncCall(Expr *i, Expr *e);
    ~FuncCall() override;

    void printAST(std::ostream &out) const override;
    void sem_analyze() override;
private:
    Expr *name;
    Expr *expr;
};

class NotCond : public Cond {
public:
    NotCond(Expr *c);
    ~NotCond() override;

    void printAST(std::ostream &out) const override;
    void sem_analyze() override;
private:
    Expr *cond;
};

class BinOpCond : public Cond {
public:
    BinOpCond(Expr *c1, std::string *o, Expr *c2);
    ~BinOpCond() override;

    void printAST(std::ostream &out) const override;
    void sem_analyze() override;
private:
    Expr *cond1;
	std::string op;
	Expr *cond2;
};

class UnaryOpExpr : public Expr {
public:
  	UnaryOpExpr(std::string *o, Expr *e);
    ~UnaryOpExpr() override;

  	void printAST(std::ostream &out) const override;
    void sem_analyze() override;
private:
    std::string op;
  	Expr *expr;
};

class BinOpExpr : public Expr {
public:
  	BinOpExpr(Expr *e1, std::string *o, Expr *e2);
    ~BinOpExpr() override;

  	void printAST(std::ostream &out) const override;
    void sem_analyze() override;
private:
  	Expr *expr1;
  	std::string op;
  	Expr *expr2;
};

class BoolVal : public Expr {
public:
    BoolVal(char bv);

    void printAST(std::ostream &out) const override;
    void sem_analyze() override;
private:
    char boolval;
};

class Skip : public Stmt {
public:
    Skip();

    void printAST(std::ostream &out) const override;
    void sem_analyze() override;
};

class Assign : public Stmt {
public:
    Assign(Expr *l, Expr *e);
    ~Assign() override;

    void printAST(std::ostream &out) const override;
private:
    Expr *lvalue;
    Expr *expr;
};

class Exit : public Stmt { 
public:
    Exit();

    void printAST(std::ostream &out) const override;
};

class Break : public Stmt {
public:
    Break(ColId *c);
    ~Break() override;

    void printAST(std::ostream &out) const override;
	// void sem_analyze() override;
private:
    ColId *col_id;
};

class Continue : public Stmt {
public:
    Continue(ColId *c);
    ~Continue() override;

    void printAST(std::ostream &out) const override;

	// void sem_analyze() override;
private:
    ColId *col_id;
};

class Return : public Stmt {
public:
    Return(Expr *e);
    ~Return() override;
    
    void printAST(std::ostream &out) const override;
private: 
    Expr *expr;
};

class IfThenElse : public Stmt {
public:
    IfThenElse(Expr *c, Block *b, Stmt *ef, Stmt *e);
    ~IfThenElse() override;

    void printAST(std::ostream &out) const override;
	void sem_analyze() override;
private:
    Expr *cond;
    Block *block;
    Stmt *elif;
    Stmt *els;
};

class Elif : public Stmt {
public:
    Elif();
    Elif(Expr *c, Block *b);
    ~Elif() override;

    void printAST(std::ostream &out) const override;
    void sem_analyze() override;
private:
    Expr *cond;
	Block *block;
};

class ElifList : public Elif {
public:
    ElifList();
    ~ElifList() override;

    void append(Stmt *e);
    void printAST(std::ostream &out) const override;
    void sem_analyze() override;
private:
    std::vector<Stmt *> elif_list;
};

class Else : public Stmt {
public:
    Else(Block *b);
    ~Else() override;

    void printAST(std::ostream &out) const override;
    void sem_analyze() override;
private:
    Block *block;
};

class Loop : public Stmt {
public:
    Loop(Expr *i, Block *b);
    ~Loop() override;

    void printAST(std::ostream &out) const override;
	void sem_analyze() override;
private:
    Expr *name;
    Block *block;
};

#endif /* __AST_H__ */
