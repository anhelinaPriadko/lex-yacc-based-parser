#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <map>
#include <iostream>
#include <stdexcept>
#include <memory>
#include <typeinfo>
#include <cmath>

/* AST — JSON output + small evaluator (Value, Environment).
   This header matches the parser actions and codegen expectations.
*/

struct ASTNode {
    virtual ~ASTNode() = default;
    virtual std::string toJson(int indent = 0) const = 0;

    struct Value {
        enum Kind { NONE, NUMBER, STRING, BOOL, FUNCTION } kind = NONE;
        double num = 0.0;
        std::string str;
        bool b = false;
        ASTNode* func = nullptr; // pointer to FunctionDecl stored as ASTNode*

        Value() : kind(NONE), num(0.0), str(), b(false), func(nullptr) {}
        static Value makeNumber(double v) { Value x; x.kind = NUMBER; x.num = v; return x; }
        static Value makeString(const std::string& s) { Value x; x.kind = STRING; x.str = s; return x; }
        static Value makeBool(bool bb) { Value x; x.kind = BOOL; x.b = bb; return x; }
        static Value makeFunction(ASTNode* f) { Value x; x.kind = FUNCTION; x.func = f; return x; }

        std::string toString() const {
            switch (kind) {
                case NUMBER: {
                    std::ostringstream os; os << std::setprecision(15) << num; return os.str();
                }
                case STRING: return str;
                case BOOL: return b ? "true" : "false";
                case NONE: return "null";
                case FUNCTION: return "<fun>";
                default: return "<unknown>";
            }
        }
        double asNumber() const {
            if (kind == NUMBER) return num;
            if (kind == BOOL) return b ? 1.0 : 0.0;
            try { return std::stod(str); } catch(...) { return 0.0; }
        }
        bool asBool() const {
            if (kind == BOOL) return b;
            if (kind == NUMBER) return num != 0.0;
            if (kind == STRING) return !str.empty();
            return false;
        }
    };

    struct Environment {
        Environment* parent = nullptr;
        std::map<std::string, Value> vars;
        Environment(Environment* p=nullptr) : parent(p) {}
        void set(const std::string& name, const Value& v) {
            Environment* cur = this;
            while (cur) {
                if (cur->vars.find(name) != cur->vars.end()) { cur->vars[name] = v; return; }
                cur = cur->parent;
            }
            vars[name] = v;
        }
        void define(const std::string& name, const Value& v) {
            vars[name] = v;
        }
        Value get(const std::string& name) {
            Environment* cur = this;
            while (cur) {
                auto it = cur->vars.find(name);
                if (it != cur->vars.end()) return it->second;
                cur = cur->parent;
            }
            throw std::runtime_error("Undefined variable: " + name);
        }
        bool has(const std::string& name) {
            Environment* cur = this;
            while (cur) {
                if (cur->vars.find(name) != cur->vars.end()) return true;
                cur = cur->parent;
            }
            return false;
        }
    };

    // default eval returns NONE
    virtual Value eval(Environment& env) const {
        (void)env;
        return Value();
    }
};

// json helpers
static inline std::string indentStr(int n) { return std::string(n, ' '); }
static inline std::string jsonEsc(const std::string& s) {
    std::ostringstream o;
    for (char c : s) {
        switch (c) {
        case '\"': o << "\\\""; break;
        case '\\': o << "\\\\"; break;
        case '\n': o << "\\n"; break;
        case '\t': o << "\\t"; break;
        default: o << c;
        }
    }
    return o.str();
}

struct TypeDescriptor {
    std::string name;
    TypeDescriptor(const std::string& n) : name(n) {}
    std::string toJson() const { return "\"" + jsonEsc(name) + "\""; }
};

// forward declare a few used types (others will be defined in order)
struct BlockStmt;
struct ParamDecl;
struct ReturnException;
struct VarDeclList;
struct VarDecl;
struct ExprStmt;
struct AssignStmt;
struct PrintStmt;
struct UnaryExpr;
struct PostfixExpr;
struct MemberExpr;
struct ConditionalExpr;

// ---------- expressions / statements / decls ----------

struct NumberExpr : ASTNode {
    double value;
    NumberExpr(double v) : value(v) {}
    std::string toJson(int indent = 0) const override {
        std::ostringstream o;
        o << indentStr(indent) << "{ \"type\": \"Number\", \"value\": " << std::setprecision(15) << value << " }";
        return o.str();
    }
    Value eval(Environment& env) const override {
        (void)env;
        return Value::makeNumber(value);
    }
};

struct StringExpr : ASTNode {
    std::string value;
    StringExpr(const std::string& s) : value(s) {}
    std::string toJson(int indent = 0) const override {
        std::ostringstream o;
        o << indentStr(indent) << "{ \"type\": \"String\", \"value\": \"" << jsonEsc(value) << "\" }";
        return o.str();
    }
    Value eval(Environment& env) const override { (void)env; return Value::makeString(value); }
};

struct VarExpr : ASTNode {
    std::string name;
    VarExpr(const std::string& n) : name(n) {}
    std::string toJson(int indent = 0) const override {
        std::ostringstream o;
        o << indentStr(indent) << "{ \"type\": \"Var\", \"name\": \"" << jsonEsc(name) << "\" }";
        return o.str();
    }
    Value eval(Environment& env) const override {
        return env.get(name);
    }
};

struct BinaryExpr : ASTNode {
    std::string op;
    ASTNode* left;
    ASTNode* right;
    BinaryExpr(const std::string& o, ASTNode* l, ASTNode* r) : op(o), left(l), right(r) {}
    ~BinaryExpr() { delete left; delete right; }
    std::string toJson(int indent = 0) const override {
        std::ostringstream o;
        o << indentStr(indent) << "{ \"type\": \"Binary\", \"op\": \"" << jsonEsc(op) << "\",\n";
        o << indentStr(indent + 2) << "\"left\":\n" << left->toJson(indent + 4) << ",\n";
        o << indentStr(indent + 2) << "\"right\":\n" << right->toJson(indent + 4) << "\n";
        o << indentStr(indent) << "}";
        return o.str();
    }
    Value eval(Environment& env) const override {
        if (op == "=") {
            VarExpr* v = dynamic_cast<VarExpr*>(left);
            if (!v) throw std::runtime_error("Left side of assignment is not a variable");
            Value val = right->eval(env);
            env.set(v->name, val);
            return val;
        }
        Value L = left->eval(env);
        Value R = right->eval(env);
        if (op == "+") {
            if (L.kind == Value::STRING || R.kind == Value::STRING)
                return Value::makeString(L.toString() + R.toString());
            return Value::makeNumber(L.asNumber() + R.asNumber());
        }
        if (op == "-") return Value::makeNumber(L.asNumber() - R.asNumber());
        if (op == "*") return Value::makeNumber(L.asNumber() * R.asNumber());
        if (op == "/") return Value::makeNumber(L.asNumber() / R.asNumber());
        if (op == "%") return Value::makeNumber(std::fmod(L.asNumber(), R.asNumber()));
        if (op == "==") return Value::makeBool(L.toString() == R.toString());
        if (op == "!=") return Value::makeBool(L.toString() != R.toString());
        if (op == "<") return Value::makeBool(L.asNumber() < R.asNumber());
        if (op == ">") return Value::makeBool(L.asNumber() > R.asNumber());
        if (op == "<=") return Value::makeBool(L.asNumber() <= R.asNumber());
        if (op == ">=") return Value::makeBool(L.asNumber() >= R.asNumber());
        if (op == "&&") return Value::makeBool(L.asBool() && R.asBool());
        if (op == "||") return Value::makeBool(L.asBool() || R.asBool());
        return Value();
    }
};

struct UnaryExpr : ASTNode {
    std::string op;
    ASTNode* operand;
    UnaryExpr(const std::string& o, ASTNode* v) : op(o), operand(v) {}
    ~UnaryExpr() { delete operand; }
    std::string toJson(int indent = 0) const override {
        std::ostringstream o;
        o << indentStr(indent) << "{ \"type\": \"Unary\", \"op\": \"" << jsonEsc(op) << "\", \"expr\":\n"
          << operand->toJson(indent + 4) << " }";
        return o.str();
    }
    Value eval(Environment& env) const override {
        if (op == "+") return Value::makeNumber(operand->eval(env).asNumber());
        if (op == "-") return Value::makeNumber(-operand->eval(env).asNumber());
        if (op == "!") return Value::makeBool(!operand->eval(env).asBool());
        if (op == "++" || op == "--") {
            VarExpr* v = dynamic_cast<VarExpr*>(operand);
            if (!v) {
                double val = operand->eval(env).asNumber();
                val = (op == "++") ? val + 1 : val - 1;
                return Value::makeNumber(val);
            }
            Value cur = env.get(v->name);
            double nv = cur.asNumber() + (op == "++" ? 1.0 : -1.0);
            env.set(v->name, Value::makeNumber(nv));
            return Value::makeNumber(nv);
        }
        return Value();
    }
};

struct PostfixExpr : ASTNode {
    ASTNode* base;
    std::string op;
    PostfixExpr(ASTNode* b, const std::string& o) : base(b), op(o) {}
    ~PostfixExpr() { delete base; }
    std::string toJson(int indent = 0) const override {
        std::ostringstream o;
        o << indentStr(indent) << "{ \"type\": \"Postfix\", \"op\": \"" << jsonEsc(op) << "\", \"base\":\n"
          << base->toJson(indent + 4) << " }";
        return o.str();
    }
    Value eval(Environment& env) const override {
        VarExpr* v = dynamic_cast<VarExpr*>(base);
        if (!v) {
            double val = base->eval(env).asNumber();
            return Value::makeNumber(val);
        }
        Value cur = env.get(v->name);
        double old = cur.asNumber();
        double nv = old + (op == "++" ? 1.0 : -1.0);
        env.set(v->name, Value::makeNumber(nv));
        return Value::makeNumber(old);
    }
};

// --- statements and block ---

struct ExprStmt : ASTNode {
    ASTNode* expr;
    ExprStmt(ASTNode* e) : expr(e) {}
    ~ExprStmt() { if (expr) delete expr; }
    std::string toJson(int indent = 0) const override {
        std::ostringstream o;
        if (!expr) return indentStr(indent) + std::string("{ \"type\": \"ExprStmt\", \"expr\": null }");
        o << indentStr(indent) << "{ \"type\": \"ExprStmt\", \"expr\":\n" << expr->toJson(indent + 4) << " }";
        return o.str();
    }
    Value eval(Environment& env) const override {
        if (!expr) return Value();
        return expr->eval(env);
    }
};

struct AssignStmt : ASTNode {
    std::string id;
    ASTNode* expr;
    AssignStmt(const std::string& i, ASTNode* e) : id(i), expr(e) {}
    ~AssignStmt() { delete expr; }
    std::string toJson(int indent = 0) const override {
        std::ostringstream o;
        o << indentStr(indent) << "{ \"type\": \"Assign\", \"id\": \"" << jsonEsc(id) << "\", \"expr\":\n"
          << expr->toJson(indent + 4) << " }";
        return o.str();
    }
    Value eval(Environment& env) const override {
        Value v = expr->eval(env);
        env.set(id, v);
        return v;
    }
};

struct PrintStmt : ASTNode {
    ASTNode* expr;
    PrintStmt(ASTNode* e) : expr(e) {}
    ~PrintStmt() { delete expr; }
    std::string toJson(int indent = 0) const override {
        std::ostringstream o;
        o << indentStr(indent) << "{ \"type\": \"Print\", \"expr\":\n" << expr->toJson(indent + 4) << " }";
        return o.str();
    }
    Value eval(Environment& env) const override {
        Value v = expr->eval(env);
        std::cout << v.toString() << std::endl;
        return Value();
    }
};

struct IfStmt : ASTNode {
    ASTNode* cond;
    ASTNode* thenStmt;
    ASTNode* elseStmt;
    IfStmt(ASTNode* c, ASTNode* t, ASTNode* e = nullptr) : cond(c), thenStmt(t), elseStmt(e) {}
    ~IfStmt() { delete cond; delete thenStmt; if (elseStmt) delete elseStmt; }
    std::string toJson(int indent = 0) const override {
        std::ostringstream o;
        o << indentStr(indent) << "{ \"type\": \"If\", \"cond\":\n" << cond->toJson(indent + 4) << ",\n";
        o << indentStr(indent + 2) << "\"then\":\n" << thenStmt->toJson(indent + 4);
        if (elseStmt) { o << ",\n" << indentStr(indent + 2) << "\"else\":\n" << elseStmt->toJson(indent + 4) << "\n"; }
        else o << "\n";
        o << indentStr(indent) << "}";
        return o.str();
    }
    Value eval(Environment& env) const override {
        if (cond->eval(env).asBool()) return thenStmt->eval(env);
        if (elseStmt) return elseStmt->eval(env);
        return Value();
    }
};

struct BlockStmt : ASTNode {
    std::vector<ASTNode*> stmts;
    BlockStmt() = default;
    BlockStmt(std::vector<ASTNode*>* v) {
        if (v) { stmts = *v; delete v; }
    }
    ~BlockStmt() { for (auto p : stmts) delete p; }
    std::string toJson(int indent = 0) const override {
        std::ostringstream o;
        o << indentStr(indent) << "{ \"type\": \"Block\", \"stmts\": [\n";
        for (size_t i = 0; i < stmts.size(); ++i) {
            o << stmts[i]->toJson(indent + 4);
            if (i + 1 < stmts.size()) o << ",\n"; else o << "\n";
        }
        o << indentStr(indent) << "] }";
        return o.str();
    }
    Value eval(Environment& env) const override {
        Environment localEnv(&env);
        Value last;
        for (auto s : stmts) {
            last = s->eval(localEnv);
        }
        return last;
    }
};

struct SwitchStmt : ASTNode {
    ASTNode* expr;
    BlockStmt* body;
    SwitchStmt(ASTNode* e, BlockStmt* b) : expr(e), body(b) {}
    ~SwitchStmt() { delete expr; delete body; }
    std::string toJson(int indent = 0) const override {
        std::ostringstream o;
        o << indentStr(indent) << "{ \"type\": \"Switch\", \"expr\":\n" << expr->toJson(indent + 4)
          << ",\n" << indentStr(indent + 2) << "\"body\":\n" << body->toJson(indent + 4) << "\n" << indentStr(indent) << "}";
        return o.str();
    }
    Value eval(Environment& env) const override {
        (void)env;
        throw std::runtime_error("Switch not implemented in evaluator");
    }
};

struct WhileStmt : ASTNode {
    ASTNode* cond;
    ASTNode* body;
    WhileStmt(ASTNode* c, ASTNode* b) : cond(c), body(b) {}
    ~WhileStmt() { delete cond; delete body; }
    std::string toJson(int indent = 0) const override {
        std::ostringstream o;
        o << indentStr(indent) << "{ \"type\": \"While\", \"cond\":\n" << cond->toJson(indent + 4)
          << ",\n" << indentStr(indent + 2) << "\"body\":\n" << body->toJson(indent + 4) << "\n" << indentStr(indent) << "}";
        return o.str();
    }
    Value eval(Environment& env) const override {
        while (cond->eval(env).asBool()) {
            body->eval(env);
        }
        return Value();
    }
};

struct DoWhileStmt : ASTNode {
    ASTNode* body;
    ASTNode* cond;
    DoWhileStmt(ASTNode* b, ASTNode* c) : body(b), cond(c) {}
    ~DoWhileStmt() { delete body; delete cond; }
    std::string toJson(int indent = 0) const override {
        std::ostringstream o;
        o << indentStr(indent) << "{ \"type\": \"DoWhile\", \"body\":\n" << body->toJson(indent + 4)
          << ",\n" << indentStr(indent + 2) << "\"cond\":\n" << cond->toJson(indent + 4) << "\n" << indentStr(indent) << "}";
        return o.str();
    }
    Value eval(Environment& env) const override {
        do {
            body->eval(env);
        } while (cond->eval(env).asBool());
        return Value();
    }
};

struct ForStmt : ASTNode {
    ASTNode* init;      // expression-stmt or declaration
    ASTNode* condStmt;  // expression-stmt (may be ExprStmt with expr==nullptr)
    ASTNode* postExpr;  // expr (may be nullptr)
    ASTNode* body;
    ForStmt(ASTNode* i, ASTNode* c, ASTNode* p, ASTNode* b) : init(i), condStmt(c), postExpr(p), body(b) {}
    ~ForStmt() { if (init) delete init; if (condStmt) delete condStmt; if (postExpr) delete postExpr; delete body; }
    std::string toJson(int indent = 0) const override {
        std::ostringstream o;
        o << indentStr(indent) << "{ \"type\": \"For\", \n";
        o << indentStr(indent + 2) << "\"init\":\n" << (init ? init->toJson(indent + 4) : std::string("null")) << ",\n";
        o << indentStr(indent + 2) << "\"cond\":\n" << (condStmt ? condStmt->toJson(indent + 4) : std::string("null")) << ",\n";
        o << indentStr(indent + 2) << "\"post\":\n" << (postExpr ? postExpr->toJson(indent + 4) : std::string("null")) << ",\n";
        o << indentStr(indent + 2) << "\"body\":\n" << body->toJson(indent + 4) << "\n" << indentStr(indent) << "}";
        return o.str();
    }
    Value eval(Environment& env) const override {
        if (init) init->eval(env);
        while (true) {
            if (condStmt) {
                Value c = condStmt->eval(env);
                if (!c.asBool()) break;
            }
            body->eval(env);
            if (postExpr) postExpr->eval(env);
        }
        return Value();
    }
};

struct BreakStmt : ASTNode {
    BreakStmt() {}
    std::string toJson(int indent = 0) const override { return indentStr(indent) + std::string("{ \"type\": \"Break\" }"); }
};
struct ContinueStmt : ASTNode {
    ContinueStmt() {}
    std::string toJson(int indent = 0) const override { return indentStr(indent) + std::string("{ \"type\": \"Continue\" }"); }
};

struct ReturnException : public std::exception {
    ASTNode::Value v;
    ReturnException(const ASTNode::Value& vv) : v(vv) {}
};

struct ReturnStmt : ASTNode {
    ASTNode* expr;
    ReturnStmt(ASTNode* e = nullptr) : expr(e) {}
    ~ReturnStmt() { if (expr) delete expr; }
    std::string toJson(int indent = 0) const override {
        if (!expr) return indentStr(indent) + std::string("{ \"type\": \"Return\", \"expr\": null }");
        std::ostringstream o;
        o << indentStr(indent) << "{ \"type\": \"Return\", \"expr\":\n" << expr->toJson(indent + 4) << " }";
        return o.str();
    }
    Value eval(Environment& env) const override {
        Value v = expr ? expr->eval(env) : Value();
        throw ReturnException(v);
        return v;
    }
};

// --- declarations / functions / classes ---

struct VarDecl : ASTNode {
    std::string id;
    ASTNode* init;
    VarDecl(const std::string& i, ASTNode* e) : id(i), init(e) {}
    ~VarDecl() { if (init) delete init; }
    std::string toJson(int indent = 0) const override {
        std::ostringstream o;
        o << indentStr(indent) << "{ \"type\": \"VarDecl\", \"id\": \"" << jsonEsc(id) << "\", \"init\": ";
        if (init) o << "\n" << init->toJson(indent + 4);
        else o << "null";
        o << " }";
        return o.str();
    }
    Value eval(Environment& env) const override {
        if (init) {
            Value v = init->eval(env);
            env.define(id, v);
            return v;
        } else {
            env.define(id, Value());
            return Value();
        }
    }
};

struct VarDeclList : ASTNode {
    TypeDescriptor* baseType;
    std::vector<ASTNode*> decls;
    VarDeclList(TypeDescriptor* t, std::vector<ASTNode*>* v) : baseType(t) {
        if (v) { decls = *v; delete v; }
    }
    ~VarDeclList() { delete baseType; for (auto p : decls) delete p; }
    std::string toJson(int indent = 0) const override {
        std::ostringstream o;
        o << indentStr(indent) << "{ \"type\": \"VarDeclList\", \"base\": " << baseType->toJson() << ", \"decls\": [\n";
        for (size_t i = 0; i < decls.size(); ++i) {
            o << decls[i]->toJson(indent + 4);
            if (i + 1 < decls.size()) o << ",\n"; else o << "\n";
        }
        o << indentStr(indent) << "] }";
        return o.str();
    }
    Value eval(Environment& env) const override {
        for (auto d : decls) d->eval(env);
        return Value();
    }
};

struct ParamDecl : ASTNode {
    TypeDescriptor* type;
    std::string id;
    ParamDecl(TypeDescriptor* t, const std::string& name) : type(t), id(name) {}
    ~ParamDecl() { delete type; }
    std::string toJson(int indent = 0) const override {
        std::ostringstream o;
        o << indentStr(indent) << "{ \"type\": \"ParamDecl\", \"id\": \"" << jsonEsc(id) << "\", \"decltype\": " << type->toJson() << " }";
        return o.str();
    }
};

struct ClassDecl : ASTNode {
    std::string name;
    std::vector<ASTNode*> members;
    ClassDecl(const std::string& n, std::vector<ASTNode*>* m) : name(n) {
        if (m) { members = *m; delete m; }
    }
    ~ClassDecl() { for (auto p : members) delete p; }
    std::string toJson(int indent = 0) const override {
        std::ostringstream o;
        o << indentStr(indent) << "{ \"type\": \"ClassDecl\", \"name\": \"" << jsonEsc(name) << "\", \"members\": [\n";
        for (size_t i = 0; i < members.size(); ++i) {
            o << members[i]->toJson(indent + 4);
            if (i + 1 < members.size()) o << ",\n"; else o << "\n";
        }
        o << indentStr(indent) << "] }";
        return o.str();
    }
};

// --- FunctionDecl (MUST be before CallExpr because CallExpr does dynamic_cast to it) ---

struct FunctionDecl : ASTNode {
    TypeDescriptor* ret;
    std::string name;
    std::vector<ASTNode*> params; // elements are ParamDecl*
    BlockStmt* body;
    FunctionDecl(TypeDescriptor* r, const std::string& n, std::vector<ASTNode*>* p, BlockStmt* b) : ret(r), name(n), body(b) {
        if (p) { params = *p; delete p; }
    }
    ~FunctionDecl() { delete ret; for (auto p : params) delete p; delete body; }
    std::string toJson(int indent = 0) const override {
        std::ostringstream o;
        o << indentStr(indent) << "{ \"type\": \"FunctionDecl\", \"name\": \"" << jsonEsc(name) << "\", \"ret\": " << (ret ? ret->toJson() : std::string("null")) << ", \"params\": [\n";
        for (size_t i = 0; i < params.size(); ++i) {
            o << params[i]->toJson(indent + 4);
            if (i + 1 < params.size()) o << ",\n"; else o << "\n";
        }
        o << indentStr(indent) << "], \"body\":\n" << (body ? body->toJson(indent + 4) : std::string("null")) << " }";
        return o.str();
    }

    // call with simple local env; throws ReturnException for return
    Value call(Environment& parentEnv, const std::vector<Value>& args) const {
        Environment local(&parentEnv);
        for (size_t i = 0; i < params.size() && i < args.size(); ++i) {
            ParamDecl* pd = dynamic_cast<ParamDecl*>(params[i]);
            if (pd) local.define(pd->id, args[i]);
        }
        try {
            if (body) body->eval(local);
        } catch (const ReturnException& re) {
            return re.v;
        }
        return Value();
    }

    Value eval(Environment& env) const override {
        env.define(name, Value::makeFunction((ASTNode*)this));
        return Value();
    }
};

// --- CallExpr (after FunctionDecl) ---

struct CallExpr : ASTNode {
    ASTNode* callee;
    std::vector<ASTNode*> args;
    CallExpr(ASTNode* c, std::vector<ASTNode*>* a) : callee(c) {
        if (a) { args = *a; delete a; }
    }
    ~CallExpr() { delete callee; for (auto p : args) delete p; }
    std::string toJson(int indent = 0) const override {
        std::ostringstream o;
        o << indentStr(indent) << "{ \"type\": \"Call\", \"callee\":\n" << callee->toJson(indent + 4) << ",\n";
        o << indentStr(indent + 2) << "\"args\": [\n";
        for (size_t i = 0; i < args.size(); ++i) {
            o << args[i]->toJson(indent + 4);
            if (i + 1 < args.size()) o << ",\n"; else o << "\n";
        }
        o << indentStr(indent + 2) << "]\n" << indentStr(indent) << "}";
        return o.str();
    }
    Value eval(Environment& env) const override {
        VarExpr* v = dynamic_cast<VarExpr*>(callee);
        if (v) {
            std::string fname = v->name;
            if (fname == "print") {
                for (size_t i=0;i<args.size();++i) {
                    auto val = args[i]->eval(env);
                    std::cout << val.toString();
                    if (i+1<args.size()) std::cout << " ";
                }
                std::cout << std::endl;
                return Value();
            }
            if (env.has(fname)) {
                Value fv = env.get(fname);
                if (fv.kind == Value::FUNCTION && fv.func) {
                    FunctionDecl* fd = dynamic_cast<FunctionDecl*>(fv.func);
                    if (!fd) throw std::runtime_error("Called object is not a function: " + fname);
                    std::vector<Value> argvals;
                    for (auto a : args) argvals.push_back(a->eval(env));
                    return fd->call(env, argvals);
                }
            }
            throw std::runtime_error("Undefined function: " + fname);
        }
        return Value();
    }
};

struct MemberExpr : ASTNode {
    ASTNode* base;
    std::string member;
    MemberExpr(ASTNode* b, const std::string& m) : base(b), member(m) {}
    ~MemberExpr() { delete base; }
    std::string toJson(int indent = 0) const override {
        std::ostringstream o;
        o << indentStr(indent) << "{ \"type\": \"Member\", \"member\": \"" << jsonEsc(member) << "\", \"base\":\n"
          << base->toJson(indent + 4) << " }";
        return o.str();
    }
    Value eval(Environment& env) const override {
        (void)env; (void)member; (void)base;
        throw std::runtime_error("Member access not implemented in evaluator");
    }
};

struct ConditionalExpr : ASTNode {
    ASTNode* cond;
    ASTNode* thenExpr;
    ASTNode* elseExpr;
    ConditionalExpr(ASTNode* c, ASTNode* t, ASTNode* e) : cond(c), thenExpr(t), elseExpr(e) {}
    ~ConditionalExpr() { delete cond; delete thenExpr; delete elseExpr; }
    std::string toJson(int indent = 0) const override {
        std::ostringstream o;
        o << indentStr(indent) << "{ \"type\": \"Conditional\", \"cond\":\n" << cond->toJson(indent + 4) << ",\n";
        o << indentStr(indent + 2) << "\"then\":\n" << thenExpr->toJson(indent + 4) << ",\n";
        o << indentStr(indent + 2) << "\"else\":\n" << elseExpr->toJson(indent + 4) << "\n";
        o << indentStr(indent) << "}";
        return o.str();
    }
    Value eval(Environment& env) const override {
        if (cond->eval(env).asBool()) return thenExpr->eval(env);
        return elseExpr->eval(env);
    }
};

// --- global AST root (set by parser) ---
extern ASTNode* ast_root;
