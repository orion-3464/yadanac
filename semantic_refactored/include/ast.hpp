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

enum DefType {
    FUNC_DEF,
    FUNC_DECL,
    VAR_DEF
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

    BaseType get_base_type();

    void printAST(std::ostream &out) const override;
protected:
    BaseType type;
};

class LocalDef : public AST {
public:
    DefType get_type();
protected:
    DefType def_type;
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
	void sem_analyze() override;
private:
    std::vector<Stmt *> stmt_list;
    bool has_auto_end;
};

class Const : public Expr {
public:
    Const();
    Const(int n);

    int get_num();
    void set_empty();
    int isempty();

    void printAST(std::ostream &out) const override;
	void sem_analyze() override;
private:
    int num;
    int empty = 0;
};

class BracketList : public Const {      // Bracket lists are const lists
public:
    BracketList();
    ~BracketList() override;

    std::vector<int> get_sizes();

    void append(Const *c);
    void prepend(Const *c);

    void printAST(std::ostream &out) const override ;
    void sem_analyze() override;
private:
    std::vector<Const *> b_list;
};

class Type : public DataType {
public:
    Type(DataType *t, BracketList *c);
    ~Type() override;

    std::vector<int> get_dims();

	void printAST(std::ostream &out) const override;
    void sem_analyze() override;
protected:
	BracketList *bracket_list;
};

class ArrayPar : public Type {
public:
    ArrayPar(DataType *t, BracketList *c);
    ~ArrayPar() override;

    void printAST(std::ostream &out) const override;
    void sem_analyze() override;
};

class RefPar : public Type {
public:
    RefPar(DataType *t);
    ~RefPar() override;

    void printAST(std::ostream &out) const override;
    void sem_analyze() override;
};

class Id : public Expr {
public:
    Id();
    Id(std::string s);

    std::string get_name();

    void printAST(std::ostream &out) const override;
    void sem_analyze() override;
private:
    std::string name;
};

class IdList : public Id {
public:
    IdList();
    ~IdList() override;
    
	void append(Id *i);
    void prepend(Id *i);
    bool empty() const;

    std::vector<std::string> get_names();

    void printAST(std::ostream &out) const override;
    void sem_analyze() override;
private:
    std::vector<Id *> id_list;
};

class FparDef : public AST {
public:
	FparDef(); 
    FparDef(IdList *i, Type *t);
    ~FparDef() override;

    IdList * get_idlist();

    void printAST(std::ostream &out) const override;
	void sem_analyze() override;
private:
    IdList *name_list;
    Type *type;
};

class FparDefList : public FparDef {
public:
    FparDefList();
    ~FparDefList() override;
	
	void append(FparDef *d);
    void prepend(FparDef *d);
    bool empty() const;
    std::vector<FparDef *> get_fpardeflist(); 

    void printAST(std::ostream &out) const override;
    void sem_analyze() override;
protected:
    std::vector<FparDef *> def_list;
};
class ColFparDef : public FparDefList { 
public:
    ColFparDef(FparDef *f);
	
    void printAST(std::ostream &out) const override;
};

class IsDataType : public DataType {
public:
    IsDataType(DataType *t);

    void printAST(std::ostream &out) const override;
};

class Header : public AST {
public:
    Header(Id *s, IsDataType *d, ColFparDef *c);
    ~Header() override;

    void printAST(std::ostream &out) const override;
	void sem_analyze() override;
private:
    Id *name;
    IsDataType *is_d_type;
    ColFparDef *col_def;
};

class Label : public Id {
public:
    Label(Id *i);
    ~Label() override;
	
    Id * get_id();

    void printAST(std::ostream &out) const override;
    void sem_analyze() override;
    
private:
    Id *name;
};

class ExprList : public Expr {
public:
    ExprList();
    ExprList(const ExprList &other);
    ~ExprList() override;

    void append(Expr *e);
    void prepend(Expr *e);
    bool empty() const;
    std::vector<Expr *> get_list();

    void printAST(std::ostream &out) const override;
	void sem_analyze() override;
protected:
    std::vector<Expr *> expr_list;
};

class OneColExpr : public ExprList {
public:
    OneColExpr(ExprList *e);

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

    std::string get_string();

    void printAST(std::ostream &out) const override;
    void sem_analyze() override;
private:
    std::string val;
};

class LValue : public Expr {
public:
    LValue(Id* i, Str *str, ExprList *e);
    ~LValue() override;
    
	void add(Expr *e);
    ExprType get_type();

    void printAST(std::ostream &out) const override;
    void sem_analyze() override;
private:
    Id *id;
    Str *str;
    ExprList *list;
};

class LocalDefList : public LocalDef {
public:
    LocalDefList();
    ~LocalDefList() override;
    
	void append(LocalDef *d);
    void prepend(LocalDef *d);
    bool empty() const;

    void printAST(std::ostream &out) const override;
    void sem_analyze() override;
private:
	std::vector<LocalDef *> def_list;
};

class FuncDef : public LocalDef {
public:
	FuncDef(Header *h, LocalDef *l, Block *b);
    virtual ~FuncDef() override;

	void printAST(std::ostream &out) const override;
    void sem_analyze() override;
private:
    Header *head;
    LocalDef *def_list;
    Block *block;
};

class VarDef : public LocalDef {
public:
	VarDef(IdList  *i, Type *t);    
    ~VarDef() override;

	void printAST(std::ostream &out) const override;
	void sem_analyze() override;
private:
	Type *type;
	IdList *names;
};

class FuncDecl : public LocalDef {
public:
    FuncDecl(Header *h);
    ~FuncDecl() override;

    void printAST(std::ostream &out) const override;
    void sem_analyze() override;
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
    FuncCall(Id *i, ExprList *e);
    ~FuncCall() override;

    void printAST(std::ostream &out) const override;
    void sem_analyze() override;
private:
    Id *name;
    ExprList *expr;
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
    Assign(LValue *l, Expr *e);
    ~Assign() override;

    void printAST(std::ostream &out) const override;
    void sem_analyze() override;
private:
    LValue *lvalue;
    Expr *expr;
};

class Exit : public Stmt { 
public:
    Exit();

    void printAST(std::ostream &out) const override;
    void sem_analyze() override;
};

class Break : public Stmt {
public:
    Break(Label *c);
    ~Break() override;

    void printAST(std::ostream &out) const override;
	void sem_analyze() override;
private:
    Label *col_id;
};

class Continue : public Stmt {
public:
    Continue(Label *c);
    ~Continue() override;

    void printAST(std::ostream &out) const override;
	void sem_analyze() override;
private:
    Label *col_id;
};

class Return : public Stmt {
public:
    Return(Expr *e);
    ~Return() override;
    
    void printAST(std::ostream &out) const override;
    void sem_analyze() override;
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
    Loop(Id *i, Block *b);
    ~Loop() override;

    void printAST(std::ostream &out) const override;
	void sem_analyze() override;
private:
    Id *name;
    Block *block;
};

#endif /* __AST_H__ */
