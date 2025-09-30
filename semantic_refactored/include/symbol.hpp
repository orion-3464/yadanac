#ifndef __SYMBOL_HPP__
#define __SYMBOL_HPP__

#include <string>
#include <vector>
#include <map>

enum ExprType {
    TYPE_INT,
    TYPE_BYTE,
    TYPE_BOOL,
    TYPE_ARRAY_INT,
    TYPE_ARRAY_BYTE
};

enum IdKind {
    KIND_ID,
    KIND_FUNC,
    KIND_PROC
};

class STEntry {
public:
    STEntry();
    //for funcs
    STEntry(ExprType t, const std::map<std::string, ExprType> &p);
    //for array ids & strings 
    STEntry(ExprType t, const std::vector<int>& s);
    //for simple ids
    STEntry(ExprType t);
    //for procs
    STEntry(const std::map<std::string, ExprType> &p);

private:
    ExprType type;
    std::vector<int> size; 
    std::map<std::string, ExprType> params;
};

class Scope {
public:
    Scope() {}
    void insert(std::string n, ExprType t, IdKind k, const std::vector<int> &s, const std::map<std::string, ExprType> &p);
    STEntry *lookup(std::string n);

private:
    std::map<std::string, STEntry> locals;
};

class SymbolTable {
public:
    void insert(std::string v, ExprType t);      // Den eimai sigouros gia to string to evala stin tixi epeidi einai geniko
    STEntry *lookup(std::string v);

    void enterScope();
    void exitScope();
private:
};

extern SymbolTable st;

#endif //__SYMBOL_HPP__
