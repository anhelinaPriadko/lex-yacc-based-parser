#include "codegen.h"
#include <typeinfo>
#include <iomanip>
#include <sstream> // std::ostringstream

static std::string escapeString(const std::string& s) {
    std::ostringstream o;
    for (char c : s) {
        switch (c) {
            case '\\': o << "\\\\"; break;
            case '\"': o << "\\\""; break;
            case '\n': o << "\\n"; break;
            case '\t': o << "\\t"; break;
            default: o << c; break;
        }
    }
    return o.str();
}

std::string CodeGenerator::generate(ASTNode* node) {
    out.str("");
    out.clear();
    // C++ headers
    out << "#include <iostream>\n";
    out << "#include <string>\n";
    out << "#include <cmath>\n\n";
    out << "using namespace std;\n\n";

    BlockStmt* root = dynamic_cast<BlockStmt*>(node);
    if (!root) {
        out << "int main() { return 0; }\n";
        return str();
    }

    // forward declarations for functions
    for (auto n : root->stmts) {
        FunctionDecl* fd = dynamic_cast<FunctionDecl*>(n);
        if (fd) {
            std::string rett = typeToCpp(fd->ret);
            out << rett << " " << fd->name << "(";
            for (size_t i=0;i<fd->params.size();++i) {
                ParamDecl* p = dynamic_cast<ParamDecl*>(fd->params[i]);
                if (p) out << typeToCpp(p->type) << " " << p->id;
                else out << "int p" << i;
                if (i+1<fd->params.size()) out << ", ";
            }
            out << ");\n";
        }
    }
    out << "\n";

    for (auto n : root->stmts) {
        VarDeclList* vlist = dynamic_cast<VarDeclList*>(n);
        if (vlist) {
            std::string baset = typeToCpp(vlist->baseType);
            for (auto vdnode : vlist->decls) {
                VarDecl* vd = dynamic_cast<VarDecl*>(vdnode);
                if (!vd) continue;
                out << baset << " " << vd->id;
                if (vd->init) out << " = " << generateExpr(vd->init);
                out << ";\n";
            }
            out << "\n";
            continue;
        }
        FunctionDecl* fd = dynamic_cast<FunctionDecl*>(n);
        if (fd) {
            std::string rett = typeToCpp(fd->ret);
            if (fd->name == "main") {
                out << "int main() {\n";
                indent = 1;
                if (fd->body) {
                    for (auto s : fd->body->stmts) {
                        emitIndent(); out << generateStmt(s);
                        if (generateStmt(s).back() != '\n') out << "\n";
                    }
                }
                out << "    return 0;\n";
                out << "}\n\n";
                continue;
            } else {
                out << rett << " " << fd->name << "(";
                for (size_t i=0;i<fd->params.size();++i) {
                    ParamDecl* p = dynamic_cast<ParamDecl*>(fd->params[i]);
                    if (p) out << typeToCpp(p->type) << " " << p->id;
                    else out << "int p" << i;
                    if (i+1<fd->params.size()) out << ", ";
                }
                out << ") {\n";
                indent = 1;
                if (fd->body) {
                    for (auto s : fd->body->stmts) {
                        emitIndent(); out << generateStmt(s);
                        if (generateStmt(s).back() != '\n') out << "\n";
                    }
                }
                if (rett != "void") {
                    emitIndent(); out << "return 0;\n";
                }
                out << "}\n\n";
                continue;
            }
        }
        std::string s = generateStmt(n);
        if (!s.empty()) {
            out << s;
            if (s.back() != '\n') out << "\n";
        }
    }
    return str();
}

std::string CodeGenerator::generateExpr(ASTNode* node) {
    if (!node) return "0";
    if (NumberExpr* n = dynamic_cast<NumberExpr*>(node)) {
        std::ostringstream o; o << std::setprecision(15) << n->value; return o.str();
    }
    if (StringExpr* s = dynamic_cast<StringExpr*>(node)) {
        return std::string("\"") + escapeString(s->value) + "\"";
    }
    if (VarExpr* v = dynamic_cast<VarExpr*>(node)) return v->name;
    if (BinaryExpr* b = dynamic_cast<BinaryExpr*>(node)) {
        std::string L = generateExpr(b->left), R = generateExpr(b->right), op = b->op;
        if (op == "=") return L + " = " + R;
        return "(" + L + " " + op + " " + R + ")";
    }
    if (UnaryExpr* u = dynamic_cast<UnaryExpr*>(node)) {
        if (u->op == "!") return "(!" + generateExpr(u->operand) + ")";
        if (u->op == "++" || u->op == "--") return u->op + generateExpr(u->operand);
        return "(" + u->op + generateExpr(u->operand) + ")";
    }
    if (PostfixExpr* p = dynamic_cast<PostfixExpr*>(node))
        return generateExpr(p->base) + p->op;
    if (CallExpr* c = dynamic_cast<CallExpr*>(node)) {
        VarExpr* fn = dynamic_cast<VarExpr*>(c->callee);
        if (fn && fn->name == "print") {
            std::ostringstream call;
            call << "cout";
            for (size_t i=0;i<c->args.size();++i) {
                call << " << " << generateExpr(c->args[i]);
                if (i+1 < c->args.size()) call << " << \" \"";
            }
            call << " << endl";
            return call.str();
        }
        std::ostringstream call;
        call << (fn ? fn->name : "/*call*/") << "(";
        for (size_t i=0;i<c->args.size();++i) {
            call << generateExpr(c->args[i]);
            if (i+1<c->args.size()) call << ", ";
        }
        call << ")";
        return call.str();
    }
    if (ConditionalExpr* ce = dynamic_cast<ConditionalExpr*>(node))
        return "(" + generateExpr(ce->cond) + " ? " + generateExpr(ce->thenExpr) + " : " + generateExpr(ce->elseExpr) + ")";
    return "0";
}

std::string CodeGenerator::generateStmt(ASTNode* node) {
    if (!node) return "";

    // --- VarDeclList (наприклад: "int a = 1, b = 2;") ---
    if (VarDeclList* vlist = dynamic_cast<VarDeclList*>(node)) {
        std::ostringstream o;
        std::string baset = typeToCpp(vlist->baseType);
        for (size_t i = 0; i < vlist->decls.size(); ++i) {
            VarDecl* vd = dynamic_cast<VarDecl*>(vlist->decls[i]);
            if (!vd) continue;
            o << baset << " " << vd->id;
            if (vd->init) o << " = " << generateExpr(vd->init);
            o << ";";
            if (i + 1 < vlist->decls.size()) o << "\n";
        }
        return o.str();
    }

    // --- single VarDecl (rare: if created that way) ---
    if (VarDecl* vd = dynamic_cast<VarDecl*>(node)) {
        std::ostringstream o;
        // best-effort: use auto for unknown exact type inside function bodies
        o << "auto " << vd->id;
        if (vd->init) o << " = " << generateExpr(vd->init);
        o << ";";
        return o.str();
    }

    // --- ExprStmt (including assignments and function calls) ---
    if (ExprStmt* es = dynamic_cast<ExprStmt*>(node)) {
        if (!es->expr) return std::string(";");
        // assignment as expression
        if (BinaryExpr* b = dynamic_cast<BinaryExpr*>(es->expr)) {
            if (b->op == "=") return generateExpr(b->left) + " = " + generateExpr(b->right) + ";";
        }
        return generateExpr(es->expr) + ";";
    }

    if (AssignStmt* a = dynamic_cast<AssignStmt*>(node)) return a->id + " = " + generateExpr(a->expr) + ";";
    if (PrintStmt* p = dynamic_cast<PrintStmt*>(node)) return "cout << " + generateExpr(p->expr) + " << endl;";

    if (IfStmt* i = dynamic_cast<IfStmt*>(node)) {
        std::ostringstream o;
        o << "if (" << generateExpr(i->cond) << ") ";
        if (BlockStmt* bs = dynamic_cast<BlockStmt*>(i->thenStmt)) o << generateStmt(bs);
        else o << "{ " << generateStmt(i->thenStmt) << " }";
        if (i->elseStmt) {
            o << " else ";
            if (BlockStmt* bs2 = dynamic_cast<BlockStmt*>(i->elseStmt)) o << generateStmt(bs2);
            else o << "{ " << generateStmt(i->elseStmt) << " }";
        }
        return o.str();
    }

    if (BlockStmt* b = dynamic_cast<BlockStmt*>(node)) {
        std::ostringstream o;
        o << "{\n";
        indent++;
        for (size_t idx = 0; idx < b->stmts.size(); ++idx) {
            auto s = b->stmts[idx];
            emitIndent();
            std::string gs = generateStmt(s);
            o << gs;
            if (!gs.empty() && gs.back() != '\n') o << "\n";
        }
        indent--;
        emitIndent(); o << "}";
        return o.str();
    }

    if (WhileStmt* w = dynamic_cast<WhileStmt*>(node)) {
        std::ostringstream o;
        o << "while (" << generateExpr(w->cond) << ") ";
        if (BlockStmt* bs = dynamic_cast<BlockStmt*>(w->body)) o << generateStmt(bs);
        else o << "{ " << generateStmt(w->body) << " }";
        return o.str();
    }

    if (DoWhileStmt* d = dynamic_cast<DoWhileStmt*>(node)) {
        std::ostringstream o;
        o << "do ";
        if (BlockStmt* bs = dynamic_cast<BlockStmt*>(d->body)) o << generateStmt(bs);
        else o << "{ " << generateStmt(d->body) << " }";
        o << " while (" << generateExpr(d->cond) << ");";
        return o.str();
    }

    if (ForStmt* f = dynamic_cast<ForStmt*>(node)) {
        std::ostringstream o;
        std::string init = (f->init ? generateStmt(f->init) : "");
        if (!init.empty() && init.back() == ';') init.pop_back();
        std::string cond = (f->condStmt ? generateExpr(f->condStmt) : "");
        std::string post = (f->postExpr ? generateExpr(f->postExpr) : "");
        o << "for (" << init << "; " << cond << "; " << post << ") ";
        if (BlockStmt* bs = dynamic_cast<BlockStmt*>(f->body)) o << generateStmt(bs);
        else o << "{ " << generateStmt(f->body) << " }";
        return o.str();
    }

    if (ReturnStmt* r = dynamic_cast<ReturnStmt*>(node)) {
        if (r->expr) return "return " + generateExpr(r->expr) + ";";
        else return "return;";
    }

    return "/* unhandled stmt */";
}
