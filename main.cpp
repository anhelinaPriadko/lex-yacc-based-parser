#include <iostream>
#include <fstream>
#include "ast.h"
#include "codegen.h"


extern int yyparse();
extern ASTNode* ast_root;
extern FILE* yyin;


int main(int argc, char** argv) {
    if (argc >= 2) {
        FILE* f = fopen(argv[1], "r");
        if (!f) {
            std::cerr << "Cannot open " << argv[1] << "\n"; return 1;
        }
        yyin = f;
    } else {
        yyin = stdin;
    }
    if (yyparse() == 0) {
        if (ast_root) {
            std::ofstream out("ast.json");
            out << ast_root->toJson(0) << std::endl;
            out.close();
            std::cout << "Parsed successfully. ast.json generated.\n";

            // ��������� C-����
            CodeGenerator cg;
            std::string ccode = cg.generate(ast_root);
            std::ofstream cfile("out.cpp");
            cfile << ccode;
            cfile.close();
            std::cout << "C code generated to out.c\n";

            // ��������� main() ��������������� (�� ������)
            using Node = ASTNode;
            // ... після створення globalEnv
            ASTNode::Environment globalEnv(nullptr);
            bool foundMain = false;
            BlockStmt* rootBlock = dynamic_cast<BlockStmt*>(ast_root);
            if (rootBlock) {
                // 1) register all top-level functions in global environment
                for (auto n : rootBlock->stmts) {
                    FunctionDecl* fd = dynamic_cast<FunctionDecl*>(n);
                    if (fd) {
                        globalEnv.define(fd->name, ASTNode::Value::makeFunction(fd));
                    }
                }

                // 2) evaluate global variable declarations
                for (auto n : rootBlock->stmts) {
                    VarDeclList* vlist = dynamic_cast<VarDeclList*>(n);
                    if (vlist) vlist->eval(globalEnv);
                }

                // 3) find and call main()
                for (auto n : rootBlock->stmts) {
                    FunctionDecl* fd = dynamic_cast<FunctionDecl*>(n);
                    if (fd && fd->name == "main") {
                        foundMain = true;
                        try {
                            std::cout << "Executing main()...\n";
                            fd->call(globalEnv, std::vector<ASTNode::Value>{});
                        } catch (const std::exception& e) {
                            std::cerr << "Runtime error during main(): " << e.what() << std::endl;
                        }
                        break;
                    }
                }
            }


            if (!foundMain) {
                std::cout << "No function 'main' found; AST saved but no execution performed.\n";
            }

            delete ast_root;
        }
        else std::cout << "Parsed but AST empty.\n";
    }
    else {
        std::cerr << "Parsing failed.\n";
    }
    return 0;
}