#include "symbol.hpp"


STEntry::STEntry() {}
//for simple ids
STEntry::STEntry(ExprType t) : type(t) {}
//for procs
STEntry::STEntry(const std::map<std::string, ExprType> &p) : params(p) {} 
//for array ids & strings 
STEntry::STEntry(ExprType t, const std::vector<int>& s) : type(t), size(s) {}
//for funcs
STEntry::STEntry(ExprType t, const std::map<std::string, ExprType> &p) : type(t), params(p) {}



Scope::Scope() {}
void Scope::insert(std::string name, ExprType type, IdKind kind, const std::vector<int> &size, std::map<std::string, ExprType> const &params) {
    //kano switch
    if(kind==KIND_ID){
        if (locals.find(name) != locals.end()){
            
        //yyerror("Duplicate variable declaration");
        }
        locals[name] = STEntry(type);
    }    
    
}

STEntry *Scope::lookup(std::string n) {
    if (locals.find(n) == locals.end()) return nullptr;
    return &(locals[n]);
}