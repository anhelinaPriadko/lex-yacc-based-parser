#include <iostream>
#include <fstream>
#include "ast.h"


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
	}
	if (yyparse() == 0) {
		if (ast_root) {
			std::ofstream out("ast.json");
			out << ast_root->toJson(0) << std::endl;
			out.close();
			std::cout << "Parsed successfully. ast.json generated.\n";
			delete ast_root;
		}
		else std::cout << "Parsed but AST empty.\n";
	}
	else {
		std::cerr << "Parsing failed.\n";
	}
	return 0;
}