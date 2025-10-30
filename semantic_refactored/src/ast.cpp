#include "ast.hpp"
#include "lexer.hpp"
#include "symbol.hpp"

// -------- EXPR CLASS --------

Expr::Expr() : expr_type(VOID) {}

Expr::Expr(const Expr &other) : expr_type(other.expr_type) {}

void Expr::check_type(ExprType expected_type1, ExprType expected_type2)
{
    sem_analyze();

    ExprType expression_type;

    // during type checking TYPE_BYTE and TYPE_BOOL are equivalent

    if (expected_type1 == TYPE_BOOL) expected_type1 = TYPE_BYTE;
    if (expected_type2 == TYPE_BOOL) expected_type2 = TYPE_BYTE;
    (expr_type == TYPE_BOOL) ? expression_type = TYPE_BYTE : expression_type = expr_type;

    if (expression_type != expected_type1 && expression_type != expected_type2)
    {
        std::cout << expected_type1 << " || " << expected_type2 << " - " << expression_type << std::endl;
        std::cout << "type_mismatch" << std::endl; // yyerror("type_mismatch"); TO DO
    }
}

ExprType Expr::get_type() const { return expr_type; }

// -------- BLOCK CLASS --------

Block::Block() : stmt_list() {}

Block::~Block()
{
    if (!stmt_list.empty()) {
        for (auto stmt : stmt_list)
            if (stmt)
                delete stmt;
        stmt_list.clear();
    }
}

void Block::set_auto_end(bool auto_end) { has_auto_end = auto_end; }

void Block::append(Stmt *s) { stmt_list.push_back(s); }

bool Block::empty() const { return stmt_list.empty(); }

void Block::printAST(std::ostream &out) const
{
    out << "Block(";

    bool first = true;
    for (const auto &s : stmt_list)
    {
        if (!first)
            out << ", ";
        first = false;
        (s) ? out << *s : out << "null-stmt";
    }
    if (has_auto_end)
        out << ", OFFSIDE_RULE_SYNTAX";
    else
        out << ", BEGIN_END_SYNTAX";
    out << ")";
}

void Block::sem_analyze()
{
    for (const auto &s : stmt_list)
    {
        s->sem_analyze();
    }
}

// -------- DATA TYPE CLASS --------

DataType::DataType(BaseType t) : type(t) {}
DataType::DataType(const DataType &other) : type(other.type) {}

BaseType DataType::get_base_type() const { return type; }

void DataType::printAST(std::ostream &out) const
{
    out << "DataType(" << type << ")";
}

void DataType::sem_analyze() { return; }

// --------- CONST CLASS ---------

Const::Const() {}
Const::Const(int n) : num(n) {}

int Const::get_num() const { return num; }

void Const::set_empty() { empty = 1; }

int Const::isempty() { return empty; }

void Const::printAST(std::ostream &out) const { out << "Const(" << num << ")"; }

void Const::sem_analyze() { expr_type = TYPE_INT; }

// ------- BRACKET LIST CLASS -------

BracketList::BracketList() : b_list() {}

BracketList::~BracketList()
{
    for (auto b : b_list)
        if (b)
            delete b;

    b_list.clear();
}

std::vector<int> BracketList::get_sizes() const
{
    std::vector<int> sizes;
    for (const auto &c : b_list)
    {
        sizes.push_back(c->get_num());
    }
    return sizes;
}

void BracketList::append(Const *c) { b_list.push_back(c); }

void BracketList::prepend(Const *c)
{
    if (c == nullptr)
    {
        Const *con = new Const(42);
        con->set_empty();
        b_list.insert(b_list.begin(), con);
    }
    else
        b_list.insert(b_list.begin(), c);
}

void BracketList::printAST(std::ostream &out) const
{
    out << "BracketList(";
    bool first = true;
    for (const auto &c : b_list)
    {
        if (!first)
            out << ", ";
        first = false;
        out << "[";
        out << *c;
        out << "]";
    }
    out << ")";
}

void BracketList::sem_analyze()
{
    for (const auto &b : b_list)
    {
        // if(b->get_num() <= 0) printf("error") ;
        b->sem_analyze();
    }
}

// --------- TYPE CLASS ---------

Type::Type(DataType *t, BracketList *c) : DataType(*t), bracket_list(c)
{
    delete t;
}

Type::~Type()
{
    if (bracket_list)
        delete bracket_list;
    
    bracket_list = nullptr;
}

std::vector<int> Type::get_dims() const
{
    if (bracket_list)
        return bracket_list->get_sizes();
    else
        return {};
}

void Type::printAST(std::ostream &out) const
{
    out << "Type(" << type << ", " << *bracket_list << ")";
}

void Type::sem_analyze() { return; }

// -------- ARRAY PAR CLASS --------

ArrayPar::ArrayPar(DataType *t, BracketList *c) : Type(t, c)
{
    bracket_list->prepend(nullptr);
}

void ArrayPar::printAST(std::ostream &out) const
{
    out << "ArrayPar(" << type << "[]";
    Type::printAST(out);
    out << ")";
}

void ArrayPar::sem_analyze() { return; }

// -------- REF PAR CLASS --------

RefPar::RefPar(DataType *t) : Type(t, nullptr) {}

RefPar::~RefPar() {}

void RefPar::printAST(std::ostream &out) const
{
    out << "RefPar(" << "ref" << type << ")";
}

void RefPar::sem_analyze() { return; }

// ------------- ID CLASS --------------

Id::Id() {}
Id::Id(std::string s) : name(s) {}

std::string Id::get_name() const { return name; }

void Id::printAST(std::ostream &out) const { out << "Id(" << name << ")"; }

void Id::sem_analyze()
{
    STEntry *e = st.lookup(name);
    if (!e)
    {
        std::cout<<"error on id sem analyze"<<std::endl;
        return;
    }
    expr_type = e->get_type();
}

// ---------- ID LIST CLASS -----------

IdList::IdList() : id_list() {}

IdList::~IdList()
{
    for (auto i : id_list)
        if (i)
            delete i;
}

void IdList::append(Id *i) { id_list.push_back(i); }
void IdList::prepend(Id *i) { id_list.insert(id_list.begin(), i); }
bool IdList::empty() const { return id_list.empty(); }

std::vector<std::string> IdList::get_names() const
{
    std::vector<std::string> names;

    for (const auto &id : id_list)
    {

        names.push_back(id->get_name());
    }

    return names;
}

void IdList::printAST(std::ostream &out) const
{
    out << "IdList(";
    bool first = true;
    for (const auto &i : id_list)
    {
        if (!first)
            out << ", ";
        first = false;
        out << *i;
    }
    out << ")";
}

void IdList::sem_analyze()
{
    for (const auto &i : id_list)
    {
        i->sem_analyze();
    }
    return;
}
// -------- FPARDEF CLASS --------

FparDef::FparDef() : name_list(nullptr), type(nullptr) {}
FparDef::FparDef(const FparDef &other) : name_list(other.name_list), type(other.type) {}
FparDef::FparDef(IdList *i, Type *t) : name_list(i), type(t) {}

FparDef::~FparDef()
{
    if (name_list)
        delete name_list;
    if (type)
        delete type;
    name_list = nullptr;
    type = nullptr;
}

IdList *FparDef::get_idlist() const { return name_list; }

Type *FparDef::get_type() const { return type; }

void FparDef::printAST(std::ostream &out) const
{
    out << "FparDef(" << *name_list << " as " << *type << ")";
}

void FparDef::sem_analyze()
{
    std::vector<std::string> names = name_list->get_names();
    std::vector<int> dimensions = type->get_dims();
    BaseType b_type = type->get_base_type();

    for (auto s : names)
        std::cout << "Definition's names are " << s << std::endl;
    for (auto d : dimensions)
        std::cout << "Definition's dimentions are " << d << std::endl;
    std::cout << b_type << std::endl;

    if (dimensions.empty())
    {
        for (const auto &name : names)
        {
            switch (b_type)
            {
            case INT:
                st.insert(name, TYPE_INT, KIND_ID, {}, {});
                break;
            case BYTE:
                st.insert(name, TYPE_BYTE, KIND_ID, {}, {});
                break;
            }
        }
    }
    else
    {
        for (const auto &name : names)
        {
            switch (b_type)
            {
            case INT:
                st.insert(name, TYPE_INT_ARRAY, KIND_ID, dimensions, {});
                break;
            case BYTE:
                st.insert(name, TYPE_BYTE_ARRAY, KIND_ID, dimensions, {});
                break;
            }
        }
    }
}

// -------- COLFPARDEF CLASS --------

ColFparDef::ColFparDef(FparDefList *f) { 
    if (f) {
        def_list = std::move(f->def_list);
        f->def_list.clear();
        delete f;
    }
}

void ColFparDef::printAST(std::ostream &out) const
{
    out << "ColFparDef(" << " : ";
    FparDefList::printAST(out);
    out << ")";
}

// -------- FPARDEFLIST CLASS --------

FparDefList::FparDefList() : def_list() {}

FparDefList::~FparDefList()
{
    for (auto d : def_list)
        if (d)
            delete d;
    def_list.clear();
}

void FparDefList::append(FparDef *d) { def_list.push_back(d); }
void FparDefList::prepend(FparDef *d) { def_list.insert(def_list.begin(), d); }
bool FparDefList::empty() const { return def_list.empty(); }

std::vector<FparDef *> FparDefList::get_fpardeflist() const { return def_list; }

void FparDefList::printAST(std::ostream &out) const
{
    out << "FparDefList(";
    bool first = true;
    for (const auto &d : def_list)
    {
        if (!first)
            out << ", ";
        first = false;
        (d) ? out << *d
            : out << "no-params"; // paizei na min ektyponetai pote to no-params
    }
    out << ")";
}

void FparDefList::sem_analyze()
{
    for (const auto &d : def_list)
    {
        d->sem_analyze();
    }
}

// ----------- HEADER CLASS -----------

Header::Header(Id *s, IsDataType *d, ColFparDef *c) : name(s), is_d_type(d), col_def(c) {}

Header::~Header()
{
    delete name;
    if (is_d_type)
        delete is_d_type;
    if (col_def)
        delete col_def;
    name = nullptr;
    is_d_type = nullptr;
    col_def = nullptr;
}

void Header::printAST(std::ostream &out) const
{
    out << "Header" << "(" << *name << ", ";

    (is_d_type) ? out << *is_d_type << ", " : out << "NO_DATA_TYPE, ";
    (col_def) ? out << *col_def << ")" : out << "NO_COL_DEF)";
}

void Header::sem_analyze()
{
    if (is_d_type)
        is_d_type->sem_analyze();
        
    if (is_d_type && col_def)
    {
        std::vector<FparDef *> fpardeflist = col_def->get_fpardeflist();
        std::vector<std::pair<std::string, ExprType>> params;
        
        for (auto const &fpardef : fpardeflist)
        {
            IdList *name_list = fpardef->get_idlist();
            Type *param_type = fpardef->get_type(); 
            
            std::vector<std::string> names = name_list->get_names();
            std::vector<int> dimensions = param_type->get_dims();
            BaseType b_type = param_type->get_base_type();
            
            ExprType expr_type;
            if (dimensions.empty())
            {
                expr_type = (b_type == INT) ? TYPE_INT : TYPE_BYTE;
            }
            else
            {
                expr_type = (b_type == INT) ? TYPE_INT_ARRAY : TYPE_BYTE_ARRAY;
            }
            
            for (const auto &n : names)
            {
                params.push_back({n, expr_type});
            }
        }
        
        switch (is_d_type->get_base_type())
        {
        case INT:
            st.insert(name->get_name(), TYPE_INT, KIND_FUNC, {}, params);
			st.enterScope();
			st.insert(name->get_name(), TYPE_INT, KIND_FUNC, {}, params);
            break;
        case BYTE:
            st.insert(name->get_name(), TYPE_BYTE, KIND_FUNC, {}, params);
			st.enterScope();
			st.insert(name->get_name(), TYPE_BYTE, KIND_FUNC, {}, params);
            break;
        }

        col_def->sem_analyze();
    }
    else if (is_d_type)
    {
        switch (is_d_type->get_base_type())
        {
        case INT:
            st.insert(name->get_name(), TYPE_INT, KIND_FUNC, {}, {});
			st.enterScope();
			st.insert(name->get_name(), TYPE_INT, KIND_FUNC, {}, {});
            break;
        case BYTE:
            st.insert(name->get_name(), TYPE_BYTE, KIND_FUNC, {}, {});
			st.enterScope();
			st.insert(name->get_name(), TYPE_BYTE, KIND_FUNC, {}, {});
            break;
        }
    }
    else if (col_def)
    {
        std::vector<FparDef *> fpardeflist = col_def->get_fpardeflist();
        std::vector<std::pair<std::string, ExprType>> params;
        
        for (auto const &fpardef : fpardeflist)
        {
            IdList *name_list = fpardef->get_idlist();
            Type *param_type = fpardef->get_type();
            
            std::vector<std::string> names = name_list->get_names();
            std::vector<int> dimensions = param_type->get_dims();
            BaseType b_type = param_type->get_base_type();
            
            ExprType expr_type;
            if (dimensions.empty())
            {
                expr_type = (b_type == INT) ? TYPE_INT : TYPE_BYTE;
            }
            else
            {
                expr_type = (b_type == INT) ? TYPE_INT_ARRAY : TYPE_BYTE_ARRAY;
            }
            
            for (const auto &n : names)
            {
                params.push_back({n, expr_type});
            }
        }
        
        st.insert(name->get_name(), VOID, KIND_PROC, {}, params);
        st.enterScope();
		st.insert(name->get_name(), VOID, KIND_PROC, {}, params);
        col_def->sem_analyze();
    }
    else
    {
        st.insert(name->get_name(), VOID, KIND_PROC, {}, {});
		st.enterScope();
		st.insert(name->get_name(), VOID, KIND_PROC, {}, {});
    }
}

// --------- IS DATA_TYPE CLASS ---------

IsDataType::IsDataType(DataType *t) : DataType(*t) {}

void IsDataType::printAST(std::ostream &out) const
{
    out << "IsDataType(" << " is " << type << ")";
}

void IsDataType::sem_analyze() { return; }

// --------- COLID CLASS ---------

Label::Label(Id *i) : name(i) {}

Label::~Label() { delete name; }

void Label::printAST(std::ostream &out) const
{
    out << "Label(" << " : " << *name << ")";
}

Id *Label::get_id() const { return name; }

void Label::sem_analyze()
{
    std::string tag_name = name->get_name();
    st.lookup(tag_name);
}

// --------- ONECOLEXPR CLASS ---------

OneColExpr::OneColExpr(ExprList *e) : ExprList() {
    if (e) {
        expr_list = std::move(e->expr_list);
        e->expr_list.clear();
        delete e;
    }
}

void OneColExpr::printAST(std::ostream &out) const
{
    out << "OneColExpr(" << " : ";
    ExprList::printAST(out);
    out << ")";
}

// --------- EXPR_LIST CLASS ---------

ExprList::ExprList() : expr_list() {}

ExprList::ExprList(const ExprList &other)
    : Expr(other), expr_list(other.expr_list) {}

ExprList::~ExprList()
{
    if (!expr_list.empty())
        for (auto expr : expr_list)
            if (expr)
                delete expr;
        expr_list.clear();
}

void ExprList::append(Expr *e) { expr_list.push_back(e); }
void ExprList::prepend(Expr *e) { expr_list.insert(expr_list.begin(), e); }
bool ExprList::empty() const { return expr_list.empty(); }
std::vector<Expr *> ExprList::get_list() const { return expr_list; }

void ExprList::printAST(std::ostream &out) const
{
    out << "ExprList(";
    bool first = true;
    for (const auto &e : expr_list)
    {
        if (!first)
            out << ", ";
        first = false;
        (e) ? out << *e : out << "null-expr";
    }
    out << ")";
}

void ExprList::sem_analyze()
{
    for (const auto &e : expr_list)
    {
        e->sem_analyze();
    }
}

// ---------- CHAR CLASS ----------

Char::Char(char c) : ch(c) {}

void Char::printAST(std::ostream &out) const { out << "Char(" << ch << ")"; }

void Char::sem_analyze() { expr_type = TYPE_BYTE; }

// ---------- STR CLASS ----------

Str::Str(std::string s) : val(s) {}

std::string Str::get_string() const { return val; }

void Str::printAST(std::ostream &out) const { out << "Str(" << val << ")"; }

void Str::sem_analyze() { expr_type = TYPE_BYTE_ARRAY; }

// --------- LVALUE CLASS ---------

LValue::LValue(Id *i, Str *str, ExprList *e) : id(i), str(str), list(e) {}

LValue::~LValue()
{
    if (id)
        delete id;
    if (str)
        delete str;
    if (list)
        delete list;
    id = nullptr;
    str = nullptr;
    list = nullptr;
}

void LValue::add(Expr *e) { list->append(e); }

ExprType LValue::get_type() const
{
    return expr_type;
}

void LValue::printAST(std::ostream &out) const
{
    out << "LValue(";
    if (id)
        out << *id << ", ";
    else
        out << *str << ", ";
    out << *list;
    out << ")";
}

void LValue::sem_analyze()
{
    if (list)
        list->sem_analyze();

    STEntry *entry = nullptr;

    if (id)
    {
        id->sem_analyze();
        entry = st.lookup(id->get_name());
        //        std::cout << "Lvalue's id name is " << id -> get_name() << std::endl;

        std::vector<int> dims = entry->get_dims();

        std::vector<Expr *> e_list = list->get_list();

        //        std::cout << "Lvalues expr list size is " << e_list.size() << std::endl;
        //        std::cout << "Lvalues entry list size is " << dims.size() << std::endl;
        if (e_list.empty())
            expr_type = id->get_type();
        else
        {
            ExprType t = id->get_type();
            //            std::cout << "Lvalue's id type is " << t << std::endl;
            if (e_list.size() > entry->get_dims().size())
            {
                std::cout << "Dimensions of dereferencing dont match" << std::endl;
                return;
            }
            else if (e_list.size() == entry->get_dims().size())
            {

                switch (t)
                {
                case TYPE_BYTE_ARRAY:
                    expr_type = TYPE_BYTE;
                    break;
                case TYPE_INT_ARRAY:
					//std::cout<<"IM HERE TYPE INT"<<std::endl;
                    expr_type = TYPE_INT;
                    break;
                default:
                    break;
                }
            }
            else
            {
                expr_type = t;
            }
        }
    }

    else
    {
        str->sem_analyze();
        expr_type = TYPE_BYTE_ARRAY;
    }
}

// --------- LOCAL DEF CLASS ---------

DefType LocalDef::get_type() const { return def_type; }

// --------- LOCAL DEF LIST CLASS ---------

LocalDefList::LocalDefList() : def_list() {}

LocalDefList::~LocalDefList()
{
    if (!def_list.empty())
        for (auto d : def_list)
            if (d)
                delete d;
}

void LocalDefList::append(LocalDef *d) { def_list.push_back(d); }
void LocalDefList::prepend(LocalDef *d)
{
    def_list.insert(def_list.begin(), d);
}
bool LocalDefList::empty() const { return def_list.empty(); }

void LocalDefList::printAST(std::ostream &out) const
{
    out << "LocalDefList(";
    bool first = true;
    for (const auto &d : def_list)
    {
        if (!first)
            out << ", ";
        first = false;
        (d) ? out << *d : out << "null-definition";
    }
    out << ")";
}

void LocalDefList::sem_analyze()
{
    if (!def_list.empty())
        for (const auto &d : def_list)
        {
            d->sem_analyze();
        }
}

// --------- FUNC_DEF CLASS ---------

FuncDef::FuncDef(Header *h, LocalDef *l, Block *b) : head(h), def_list(l), block(b)
{
    def_type = FUNC_DEF;
}

FuncDef::~FuncDef()
{
    if (head)
        delete head;
    if (def_list)
        delete def_list;
    if (block)
        delete block;
    head = nullptr;
    def_list = nullptr;
    block = nullptr;
}

void FuncDef::printAST(std::ostream &out) const
{
    out << "Def" << "(" << *head << ", " << *def_list << ", " << *block << ")";
}

void FuncDef::sem_analyze()
{
    head->sem_analyze();
    if (def_list)
        def_list->sem_analyze();
    block->sem_analyze();
    st.exitScope();
}

// --------- VAR_DEF CLASS ---------

VarDef::VarDef(IdList *i, Type *t) : type(t), names(i) { def_type = VAR_DEF; }

VarDef::~VarDef()
{
    if (type)
        delete type;
    if (names)
        delete names;
    type = nullptr;
    names = nullptr;
}

void VarDef::printAST(std::ostream &out) const
{
    out << "VarDef(" << *names << " is " << *type << ")";
}

void VarDef::sem_analyze()
{
    std::vector<std::string> name_list = names->get_names();
    std::vector<int> dimensions = type->get_dims();
    BaseType b_type = type->get_base_type();

    if (dimensions.empty())
    {
        for (const auto &name : name_list)
        {
            switch (b_type)
            {
            case INT:
                st.insert(name, TYPE_INT, KIND_ID, {}, {});
                break;
            case BYTE:
                st.insert(name, TYPE_BYTE, KIND_ID, {}, {});
                break;
            }
        }
    }
    else
    {
        for (const auto &name : name_list)
        {
            switch (b_type)
            {
            case INT:
                st.insert(name, TYPE_INT_ARRAY, KIND_ID, dimensions, {});
                break;
            case BYTE:
                st.insert(name, TYPE_BYTE_ARRAY, KIND_ID, dimensions, {});
                break;
            }
        }
    }
}

// --------- FUNC_DECL CLASS ---------

FuncDecl::FuncDecl(Header *h) : header(h) { def_type = FUNC_DECL; }

FuncDecl::~FuncDecl()
{
    if (header)
        delete header;
}

void FuncDecl::sem_analyze() { header->sem_analyze(); }

void FuncDecl::printAST(std::ostream &out) const
{
    out << "Decl(" << " decl " << *header << ")";
}

// --------- PROC_DECL CLASS ---------

ProcCall::ProcCall(Id *i, ExprList *e) : name(i), col_expr(e) {}

ProcCall::~ProcCall()
{
    if (name)
        delete name;
    if (col_expr)
        delete col_expr;
    name = nullptr;
    col_expr = nullptr;
}

void ProcCall::printAST(std::ostream &out) const
{
    out << "ProcCall(" << *name << ", ";
    (col_expr) ? out << *col_expr << ")" : out << "NO_ARGS)";
}

void ProcCall::sem_analyze()
{
    name->sem_analyze();
    if (col_expr)
        col_expr->sem_analyze();

    STEntry *entry = st.lookup(name->get_name());

    if (entry->get_kind() != KIND_PROC)
        std::cout<<"error not a proc"<<std::endl;

    if (col_expr)
    {
        std::vector<Expr *> expr_list = col_expr->get_list();
        if (entry->get_params().size() != expr_list.size())
        {
            std::cout<<"error wrong dims of expressions in proc call"<<std::endl;
            return;
        }

        int i = 0;
        for (const auto &p : entry->get_params())
        {
            if (p.second != expr_list[i]->get_type())
            {
                std::cout << "Our call values type is " << expr_list[i]->get_type() << std::endl;
                std::cout << "Definition's value type is " << p.second << std::endl;
                std::cout << "error miss match of types in proc call " << name->get_name() << "in parameter " << i << std::endl;
                // return;
            }
            ++i;
        }
    }
}

// --------- FUNC_CALL CLASS ---------

FuncCall::FuncCall(Id *i, ExprList *e) : name(i), expr(e) {}

FuncCall::~FuncCall()
{
    if (name)
        delete name;
    if (expr)
        delete expr;
}

void FuncCall::printAST(std::ostream &out) const
{
    out << "FuncCall(" << *name << ", ";
    (expr) ? out << *expr << ")" : out << "NO_ARGS)";
}

void FuncCall::sem_analyze()
{
    name->sem_analyze();
    if (expr)
        expr->sem_analyze();

    std::cout << "I am calling function " << name->get_name() << std::endl;

    STEntry *entry = st.lookup(name->get_name());

    if (entry->get_kind() != KIND_FUNC)
        std::cout<<"error not a func"<<std::endl;

    if (expr)
    {
        std::vector<Expr *> expr_list = expr->get_list();
        if (entry->get_params().size() != expr_list.size())
        {
            std::cout<<"error wrong number of parameters in func call"<<std::endl;
            return;
        }

        int i = 0;
        for (const auto &p : entry->get_params())
        {
            if (p.second != expr_list[i]->get_type())
            {
                std::cout<<"error wrong type in func call"<<std::endl;
                return;
            }
            ++i;
        }
    }

    expr_type = entry->get_type();
}

// --------- NOT_COND CLASS ---------

NotCond::NotCond(Expr *c) : cond(c) {}

NotCond::~NotCond()
{
    if (cond)
        delete cond;
}

void NotCond::printAST(std::ostream &out) const
{
    out << "NotCond(" << "not " << *cond << ")";
}

void NotCond::sem_analyze()
{
    cond->check_type(TYPE_BOOL, TYPE_BOOL);
    expr_type = TYPE_BOOL;
}

// --------- BINOP CLASS ---------

BinOpCond::BinOpCond(Expr *c1, std::string *o, Expr *c2)
    : cond1(c1), op(*o), cond2(c2)
{
    delete o;
}

BinOpCond::~BinOpCond()
{
    if (cond1)
        delete cond1;
    if (cond2)
        delete cond2;
}

void BinOpCond::printAST(std::ostream &out) const
{
    out << op << "(" << *cond1 << ", " << *cond2 << ")";
}

void BinOpCond::sem_analyze()
{
    cond1->check_type(TYPE_BOOL, TYPE_BOOL);
    cond2->check_type(TYPE_BOOL, TYPE_BOOL);

    expr_type = TYPE_BOOL;
}

// --------- UNARYOP CLASS ---------

UnaryOpExpr::UnaryOpExpr(std::string *o, Expr *e) : op(*o), expr(e)
{
    delete o;
}

UnaryOpExpr::~UnaryOpExpr()
{
    if (expr)
        delete expr;
}

void UnaryOpExpr::printAST(std::ostream &out) const
{
    out << op << "(" << *expr << ")";
}

void UnaryOpExpr::sem_analyze()
{
    if (op == "!")
    {
        expr->check_type(TYPE_BYTE, TYPE_BYTE);
        expr_type = TYPE_BYTE;
    }
    else
    {
        expr->check_type(TYPE_INT, TYPE_INT);
        expr_type = TYPE_INT;
    }
}

// --------- BINOP_EXPR CLASS ---------

BinOpExpr::BinOpExpr(Expr *e1, std::string *o, Expr *e2)
    : expr1(e1), op(*o), expr2(e2)
{
    delete o;
}

BinOpExpr::~BinOpExpr()
{
    if (expr1)
        delete expr1;
    if (expr2)
        delete expr2;
}

void BinOpExpr::printAST(std::ostream &out) const
{
    out << op << "(" << *expr1 << ", " << *expr2 << ")";
}

void BinOpExpr::sem_analyze()
{
    expr1->check_type(TYPE_INT, TYPE_BYTE);
    expr2->check_type(TYPE_INT, TYPE_BYTE);

    ExprType expr1_type = expr1->get_type();
    ExprType expr2_type = expr2->get_type();
    if (expr1_type != expr2_type)
        std::cout<<"INCOMPATIBLE TYPES"<<std::endl; // RAISE ERROR

    if (op == "+" || op == "-" || op == "/" || op == "*" || op == "%" ||
        op == "&" || op == "|")
        expr_type = expr1_type;
    else
        expr_type = TYPE_BOOL;
}

// --------- BOOL_VAL CLASS ---------

BoolVal::BoolVal(char bv) : boolval(bv) {}

void BoolVal::printAST(std::ostream &out) const
{
    out << "BoolVal" << "(" << (boolval ? "true" : "false") << ")";
}

void BoolVal::sem_analyze() { expr_type = TYPE_BOOL; }

// --------- SKIP CLASS ---------

Skip::Skip() {}

void Skip::printAST(std::ostream &out) const { out << "Skip(" << ")"; }

void Skip::sem_analyze() { return; }

// --------- ASSIGN CLASS ---------

Assign::Assign(LValue *l, Expr *e) : lvalue(l), expr(e) {}

Assign::~Assign()
{
    if (lvalue)
        delete lvalue;
    if (expr)
        delete expr;
}

void Assign::printAST(std::ostream &out) const
{
    out << "Assign(" << *lvalue << " := " << *expr << ")";
}

void Assign::sem_analyze()
{
    lvalue->sem_analyze();
    ExprType exp_type = lvalue->get_type();
    if (exp_type == TYPE_BYTE_ARRAY || exp_type == TYPE_INT_ARRAY)
    {
        std::cout << "Assign in arrays not allowed" << std::endl;
        return;
    }
    expr->check_type(exp_type, exp_type);
	std::cout<<"Checking types in assign"<<" value 1: "<<*lvalue<<" with type: "<<exp_type<<" value 2: "<<*expr<<" with type: "<<expr->get_type()<<std::endl;
}

// --------- EXIT CLASS ---------

Exit::Exit() {}

void Exit::printAST(std::ostream &out) const { out << "Exit(" << ")"; }

void Exit::sem_analyze() { return; }
// --------- BREAK CLASS ---------

Break::Break(Label *c) : col_id(c) {}

Break::~Break()
{
    if (col_id)
        delete col_id;
}

void Break::printAST(std::ostream &out) const
{
    out << "Break(";
    (col_id) ? out << *col_id << ")" : out << "no-id)";
}

void Break::sem_analyze()
{
    if (col_id)
        col_id->sem_analyze();
}

// --------- CONTINUE CLASS ---------

Continue::Continue(Label *c) : col_id(c) {}

Continue::~Continue()
{
    if (col_id)
        delete col_id;
}

void Continue::printAST(std::ostream &out) const
{
    out << "Continue(";
    (col_id) ? out << *col_id << ")" : out << "no-id)";
}

void Continue::sem_analyze()
{
    if (col_id)
        col_id->sem_analyze();
}

// --------- RETURN CLASS ---------

Return::Return(Expr *e) : expr(e) {}

Return::~Return() { delete expr; }

void Return::printAST(std::ostream &out) const
{
    out << "Return(" << *expr << ")";
}

void Return::sem_analyze()
{
    ExprType def_type = st.get_def();
    expr->check_type(def_type, def_type);
	std::cout<<"Return Type must be "<<def_type<<" and it is "<<expr->get_type()<<std::endl;
}

// --------- IFTHENELSE CLASS ---------

IfThenElse::IfThenElse(Expr *c, Block *b, Stmt *ef, Stmt *e)
    : cond(c), block(b), elif (ef), els(e) {}

IfThenElse::~IfThenElse()
{
    if (cond)
        delete cond;
    if (block)
        delete block;
    if (elif)
        delete elif;
    if (els)
        delete els;
}

void IfThenElse::printAST(std::ostream &out) const
{
    out << "IfThenElse(" << *cond << ", " << *block << ", ";
    (elif) ? out << *elif << ", " : out << "no-elif, ";
    (els) ? out << *els << ")" : out << "no-else)";
}

void IfThenElse::sem_analyze()
{
    cond->check_type(TYPE_BOOL, TYPE_BOOL);
    block->sem_analyze();
    if (elif)
        elif->sem_analyze();
    if (els)
        els->sem_analyze();
}

// --------- ELIF CLASS ---------

Elif::Elif() : cond(nullptr), block(nullptr) {}
Elif::Elif(Expr *c, Block *b) : cond(c), block(b) {}

Elif::~Elif()
{
    if (cond)
        delete cond;
    if (block)
        delete block;
}

void Elif::printAST(std::ostream &out) const
{
    out << "Elif(" << *cond << " : " << *block << ")";
}

void Elif::sem_analyze()
{
    cond->check_type(TYPE_BOOL, TYPE_BOOL);
    block->sem_analyze();
}

// --------- ELIF_LIST CLASS ---------

ElifList::ElifList() : elif_list() {}

ElifList::~ElifList()
{
    if (!elif_list.empty())
        for (auto e : elif_list)
            if (e)
                delete e;
}

void ElifList::append(Stmt *e) { elif_list.push_back(e); }

void ElifList::printAST(std::ostream &out) const
{
    out << "ElifList(";
    bool first = true;
    for (const auto &e : elif_list)
    {
        if (!first)
            out << ", ";
        first = false;
        out << *e;
    }
    out << ")";
}

void ElifList::sem_analyze()
{
    for (const auto &e : elif_list)
    {
        e->sem_analyze();
    }
}

// --------- ELSE CLASS ---------

Else::Else(Block *b) : block(b) {}

Else::~Else()
{
    if (block)
        delete block;
}

void Else::printAST(std::ostream &out) const
{
    out << "Else(" << *block << ")";
}

void Else::sem_analyze() { block->sem_analyze(); }

// --------- LOOP CLASS ---------

Loop::Loop(Id *i, Block *b) : name(i), block(b) {}

Loop::~Loop()
{
    if (block)
        delete block;
    if (name)
        delete name;
}

void Loop::printAST(std::ostream &out) const
{
    out << "Loop(";
    (name) ? out << *name << ", " : out << "no-name loop, ";
    out << *block << ")";
}

void Loop::sem_analyze()
{
    std::string n;
    if (name)
    {
        std::string n = name->get_name();
        st.insert(n, VOID, KIND_LOOP, {}, {});
    }
    block->sem_analyze();
}
