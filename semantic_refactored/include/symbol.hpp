#ifndef __SYMBOL_HPP__
#define __SYMBOL_HPP__

#include <string>

enum ExprType {
    TYPE_INT,
    TYPE_BYTE,
    TYPE_BOOL,
    TYPE_INT_ARRAY,
    TYPE_BYTE_ARRAY
};

class STEntry {
public:
    STEntry(ExprType t);
    ExprType type;
};

class Scope {
public:
    Scope() = default;
    
    void insert(std::string v, ExprType t);
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
