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

ExprType STEntry::get_type() {
    return type;
}



Scope::Scope() {}
void Scope::insert(std::string name, ExprType type, IdKind kind, const std::vector<int> &size, std::map<std::string, ExprType> const &params) {
	if (locals.find(name) != locals.end()){
    	//yyerror("Duplicate variable declaration");
    }

	switch(kind) {
    	case KIND_ID:
			if(type == TYPE_INT_ARRAY || type == TYPE_BYTE_ARRAY)locals[name] = STEntry(type, size);
			else locals[name] = STEntry(type);
    		break;  
		case KIND_FUNC:
			locals[name] = STEntry(type, params); //type here is func return type
			break;
		case KIND_PROC:
 			locals[name] = STEntry(params);
			break;
		case KIND_LOOP:
			locals[name] = STEntry();
    }
}

STEntry *Scope::lookup(std::string n) {
    if (locals.find(n) == locals.end()) return nullptr;
    return &(locals[n]);
}

void SymbolTable::insert(std::string name, ExprType type, IdKind kind, const std::vector<int> &size, std::map<std::string, ExprType> const &params) {
    scopes.back().insert(name, type, kind, size, params);
}

STEntry *SymbolTable::lookup(std::string n) {
	for(auto s = scopes.rbegin(); s != scopes.rend(); ++s) {
      	STEntry *e = s->lookup(n);
      	if (e != nullptr) return e;
    }
    //yyerror("Variable not found");
    return nullptr;
}

void SymbolTable::nested_pop(std::string n) {
	auto target_scope = scopes.rend();

	for(auto s = scopes.rbegin(); s != scopes.rend(); ++s) {
      	STEntry *e = s->lookup(n);
      	if (e != nullptr) target_scope = s;
		else printf("error");
    }

	while(scopes.rbegin() != target_scope) {
		exitScope();
	}
	exitScope(); //must pop target scope too
}

void SymbolTable::enterScope() {
    scopes.push_back(Scope());
}

void SymbolTable::exitScope() {
    scopes.pop_back();
}
