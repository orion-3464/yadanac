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
    STEntry() = default;
    STEntry(IdKind k);  //for loops
    STEntry(IdKind k, ExprType t);    //for simple ids
    STEntry(IdKind k, ExprType t, const std::vector<int>& s);   //for array ids & strings 
    STEntry(IdKind k, const std::vector<std::pair<std::string, ExprType>> &p);  //for procs
    STEntry(IdKind k, ExprType t, const std::vector<std::pair<std::string, ExprType>> &p);  //for funcs

    ExprType get_type();
    std::vector<int> get_dims();
    IdKind get_kind();
    std::vector<std::pair<std::string, ExprType>> get_params();
private:
    IdKind kind;
    ExprType type;
    std::vector<int> size; 
    std::vector<std::pair<std::string, ExprType>> params;
};

class Scope {
public:
    Scope();
    void insert(std::string n, ExprType t, IdKind k, const std::vector<int> &s, const std::vector<std::pair<std::string, ExprType>> &p);
    STEntry *lookup(std::string n);

    ExprType get_ret_type();

private:
    std::map<std::string, STEntry> locals;
};

class SymbolTable {
public:
    SymbolTable();

    void insert(std::string n, ExprType t, IdKind k, const std::vector<int> &s, const std::vector<std::pair<std::string, ExprType>> &p);      // Den eimai sigouros gia to string to evala stin tixi epeidi einai geniko
    STEntry *lookup(std::string v);

    void enterScope();
    void exitScope();

    ExprType get_def();
private:
    std::vector<Scope> scopes;
};

extern SymbolTable st;

#endif //__SYMBOL_HPP__
