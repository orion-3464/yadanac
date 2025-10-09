#include "symbol.hpp"
#include <iostream>

// -------- STENTRY CLASS --------

STEntry::STEntry(IdKind k) : kind(k) {}
STEntry::STEntry(IdKind k, ExprType t) : kind(k), type(t) {}   //for simple ids
STEntry::STEntry(IdKind k, const std::map<std::string, ExprType> &p) : kind(k), params(p) {}   //for procs
STEntry::STEntry(IdKind k, ExprType t, const std::vector<int>& s) : kind(k), type(t), size(s) {}   //for array ids & strings 
STEntry::STEntry(IdKind k, ExprType t, const std::map<std::string, ExprType> &p) : kind(k), type(t), params(p) {}  //for funcs

std::map<std::string, ExprType> STEntry::get_params() {
    return params;
}

ExprType STEntry::get_type() {
    return type;
}

std::vector<int> STEntry::get_dims() {
    return size;
}

IdKind STEntry::get_kind() {
    return kind;
}

// -------- SCOPE CLASS --------

Scope::Scope() {}

void Scope::insert(std::string name, ExprType type, IdKind kind, const std::vector<int> &size, std::map<std::string, ExprType> const &params) {
    std::cout << "Insert in current scope with name: " << name << " and kind: " << kind << std::endl;
    for(auto param : params) {
        std::cout << "Parameters: " << param.first << ", " << param.second << std::endl;
    }
	if (locals.find(name) != locals.end()){
        printf("error duplicate declaration");
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

ExprType Scope::get_ret_type() {
    STEntry e = locals.begin() -> second;
    return e.get_type();
}

// -------- SYMBOL TABLE CLASS --------

SymbolTable::SymbolTable() {
    scopes.push_back(Scope());

    std::map<std::string, ExprType> params;

    params.insert({"n", TYPE_INT});
    insert("writeInteger", VOID, KIND_PROC, {}, params);
    
    params.erase("n"); 
    params.insert({"b", TYPE_BYTE});
    insert("writeByte", VOID, KIND_PROC, {}, params);

    insert("writeChar", VOID, KIND_PROC, {}, params);

    params.erase("b"); 
    params.insert({"s", TYPE_BYTE_ARRAY});
    insert("writeString", VOID, KIND_PROC, {}, params);

    insert("readInteger", TYPE_INT, KIND_FUNC, {}, {});

    insert("readByte", TYPE_BYTE, KIND_FUNC, {}, {});

    insert("readChar", TYPE_BYTE, KIND_FUNC, {}, {});

    params.erase("s"); 
    params.insert({"n", TYPE_INT});
    params.insert({"s", TYPE_BYTE_ARRAY});
    insert("readString", VOID, KIND_PROC, {}, params);

    params.erase("n");
    params.erase("s"); 
    params.insert({"b", TYPE_BYTE});
    insert("extend", TYPE_INT, KIND_FUNC, {}, params);

    params.erase("b"); 
    params.insert({"i", TYPE_INT});
    insert("shrink", TYPE_BYTE, KIND_FUNC, {}, params);

    params.erase("i"); 
    params.insert({"s", TYPE_BYTE_ARRAY});
    insert("strlen", TYPE_INT, KIND_FUNC, {}, params);

    params.erase("s"); 
    params.insert({"s1", TYPE_BYTE_ARRAY});
    params.insert({"s2", TYPE_BYTE_ARRAY});
    insert("strcmp", TYPE_INT, KIND_FUNC, {}, params);

    params.erase("s1");
    params.erase("s2"); 
    params.insert({"trg", TYPE_BYTE_ARRAY});
    params.insert({"src", TYPE_BYTE_ARRAY});
    insert("strcpy", VOID, KIND_PROC, {}, params);

    insert("strcat", VOID, KIND_PROC, {}, params);
}

void SymbolTable::insert(std::string name, ExprType type, IdKind kind, const std::vector<int> &size, std::map<std::string, ExprType> const &params) {
    std::cout << "Insert in Symbol Table " << name << std::endl;
    scopes.back().insert(name, type, kind, size, params);
}

STEntry *SymbolTable::lookup(std::string n) {
	for(auto s = scopes.rbegin(); s != scopes.rend(); ++s) {
      	STEntry *e = s->lookup(n);
      	if (e != nullptr) return e;
    }
    //yyerror("Variable not found");
    printf("error var not found");
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
    printf("Entered scope \n");
    scopes.push_back(Scope());
}

void SymbolTable::exitScope() {
    printf("Exited scope \n");
    scopes.pop_back();
}

ExprType SymbolTable::get_def() {
    Scope scope = scopes.back();
    return scope.get_ret_type();
}
