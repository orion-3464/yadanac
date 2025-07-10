#ifndef __AST_H__
#define __AST_H__

#include <string>

class AST {
    public:
    virtual void printAST(std::ostream &out) const 0;

    private:
};

class FuncDef : public AST {

};

class Header : public AST {

};

class FparDef : public AST {

};

class DataType : public AST {

};

class Type : public AST {

};

class FparType : public AST {

};

class LocalDef : public AST {

};

class FuncDecl : public AST {

};

class VarDef : public AST {

};

class Stmt : public AST {

};

class Block : public AST {

};

class ProcCall : public AST {

};

class FuncCall : public AST {

};

class LValue : public AST {

};

class Expr : public AST {

};

class Cond : public AST {

};

class Decl : public FuncDecl {
public:
    Decl(Header *h) : head(h) {}

    virtual void printAST(std::ostream &out) const override {
        out << "Decl(" << *head << ")";
    }
private:
    Header *head;
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

class Str : public LValue {
public:
    Str(std::string s) : val(s) {}

    virtual void printAST(std::ostream &out) const override {
        out << "Str(" << val << ")";
    }
private:
    std::string val;
};

class Id : public LValue {
public:
    ID(std::string s) : name(s) {}

    virtual void printAST(std::ostream &out) const override {
        out << "Id(" << name << ")";
    }
private:
    std::string name;
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

#endif /* __AST_H__ */
