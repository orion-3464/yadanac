#ifndef __SYMBOL_HPP__
#define __SYMBOL_HPP__

#include <string>
#include <vector>
#include <map>

enum ExprType {
    TYPE_INT,
    TYPE_BYTE,
    TYPE_BOOL,
    TYPE_INT_ARRAY,
    TYPE_BYTE_ARRAY,
    VOID
};

enum IdKind {
    KIND_ID,
    KIND_FUNC,
    KIND_PROC,
    KIND_LOOP
};

class STEntry {
public:
    //for loops
    STEntry();
    //for simple ids
    STEntry(ExprType t);
    //for array ids & strings 
    STEntry(ExprType t, const std::vector<int>& s);
    //for procs
    STEntry(const std::map<std::string, ExprType> &p);
    //for funcs
    STEntry(ExprType t, const std::map<std::string, ExprType> &p);

    ExprType get_type();

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
    void insert(std::string n, ExprType t, IdKind k, const std::vector<int> &s, const std::map<std::string, ExprType> &p);      // Den eimai sigouros gia to string to evala stin tixi epeidi einai geniko
    STEntry *lookup(std::string v);
    void nested_pop(std::string n);

    void enterScope();
    void exitScope();
private:
    std::vector<Scope> scopes;
};

extern SymbolTable st;

#endif //__SYMBOL_HPP__
