#include "symbol.hpp"

// -------- STENTRY CLASS --------

STEntry::STEntry(IdKind k) : kind(k) {}
STEntry::STEntry(IdKind k, ExprType t) : kind(k), type(t) {}   //for simple ids
STEntry::STEntry(IdKind k, const std::map<std::string, ExprType> &p) : kind(k), params(p) {}   //for procs
STEntry::STEntry(IdKind k, ExprType t, const std::vector<int>& s) : kind(k), type(t), size(s) {}   //for array ids & strings 
STEntry::STEntry(IdKind k, ExprType t, const std::map<std::string, ExprType> &p) : kind(k), type(t), params(p) {}  //for funcs

ExprType STEntry::get_type() {
    return type;
}

std::vector<int> STEntry::get_dims() {
    return size;
}

IdKind STEntry::get_kind() {
    return kind;
}

Scope::Scope() {}
void Scope::insert(std::string name, ExprType type, IdKind kind, const std::vector<int> &size, std::map<std::string, ExprType> const &params) {
	if (locals.find(name) != locals.end()){
    	//yyerror("Duplicate variable declaration");
    }

	switch(kind) {
    	case KIND_ID:
			if(type == TYPE_INT_ARRAY || type == TYPE_BYTE_ARRAY)locals[name] = STEntry(kind, type, size);
			else locals[name] = STEntry(kind, type);
    		break;  
		case KIND_FUNC:
			locals[name] = STEntry(kind, type, params); //type here is func return type
			break;
		case KIND_PROC:
 			locals[name] = STEntry(kind, type, params);
			break;
		case KIND_LOOP:
			locals[name] = STEntry(kind);
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
