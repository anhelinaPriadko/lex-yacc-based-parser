#pragma once
#include <string>
#include <sstream>
#include "ast.h"

struct CodeGenerator {
    std::ostringstream out;
    int indent = 0;

    void emitIndent() {
        for (int i = 0; i < indent; ++i) out << "    ";
    }

    static std::string typeToCpp(const TypeDescriptor* t) {
        if (!t) return "int";
        if (t->name == "int") return "int";
        if (t->name == "double") return "double";
        if (t->name == "bool") return "bool";
        if (t->name == "void") return "void";
        if (t->name == "ctor") return "void";
        return "int";
    }

    std::string generate(ASTNode* node);
    std::string generateExpr(ASTNode* node);
    std::string generateStmt(ASTNode* node);

    std::string str() { return out.str(); }
};