#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>

struct ASTNode {
    virtual ~ASTNode() = default;
    virtual std::string toJson(int indent = 0) const = 0;
};

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

struct NumberExpr : ASTNode {
    double value;
    NumberExpr(double v) : value(v) {}
    std::string toJson(int indent = 0) const override {
        std::ostringstream o;
        o << indentStr(indent) << "{ \"type\": \"Number\", \"value\": " << std::setprecision(15) << value << " }";
        return o.str();
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
};

struct VarExpr : ASTNode {
    std::string name;
    VarExpr(const std::string& n) : name(n) {}
    std::string toJson(int indent = 0) const override {
        std::ostringstream o;
        o << indentStr(indent) << "{ \"type\": \"Var\", \"name\": \"" << jsonEsc(name) << "\" }";
        return o.str();
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
};

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
};

// --- statements ---

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
        o << indentStr(indent) << "{ \"type\": \"For\",\n";
        o << indentStr(indent + 2) << "\"init\":\n" << (init ? init->toJson(indent + 4) : std::string("null")) << ",\n";
        o << indentStr(indent + 2) << "\"cond\":\n" << (condStmt ? condStmt->toJson(indent + 4) : std::string("null")) << ",\n";
        o << indentStr(indent + 2) << "\"post\":\n" << (postExpr ? postExpr->toJson(indent + 4) : std::string("null")) << ",\n";
        o << indentStr(indent + 2) << "\"body\":\n" << body->toJson(indent + 4) << "\n" << indentStr(indent) << "}";
        return o.str();
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

struct FunctionDecl : ASTNode {
    TypeDescriptor* ret;
    std::string name;
    std::vector<ASTNode*> params;
    BlockStmt* body;
    FunctionDecl(TypeDescriptor* r, const std::string& n, std::vector<ASTNode*>* p, BlockStmt* b) : ret(r), name(n), body(b) {
        if (p) { params = *p; delete p; }
    }
    ~FunctionDecl() { delete ret; for (auto p : params) delete p; delete body; }
    std::string toJson(int indent = 0) const override {
        std::ostringstream o;
        o << indentStr(indent) << "{ \"type\": \"FunctionDecl\", \"name\": \"" << jsonEsc(name) << "\", \"ret\": " << ret->toJson() << ", \"params\": [\n";
        for (size_t i = 0; i < params.size(); ++i) {
            o << params[i]->toJson(indent + 4);
            if (i + 1 < params.size()) o << ",\n"; else o << "\n";
        }
        o << indentStr(indent) << "], \"body\":\n" << body->toJson(indent + 4) << " }";
        return o.str();
    }
};

struct ClassDecl : ASTNode {
    std::string name;
    std::vector<ASTNode*> members; // member declarations / functions
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

// --- global AST root (parser sets this) ---
extern ASTNode* ast_root;