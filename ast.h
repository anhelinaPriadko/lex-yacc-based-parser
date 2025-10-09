#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>


struct ASTNode {
	virtual ~ASTNode() = default;
	virtual std::string toJson(int indent = 0) const = 0;
};


// helpers
static inline std::string indentStr(int n) { return std::string(n, ' '); }
static inline std::string jsonEsc(const std::string& s) { std::ostringstream o; for (char c : s) { if (c == '\"') o << "\\\""; else if (c == '\\') o << "\\\\"; else if (c == '\n') o << "\\n"; else o << c; } return o.str(); }


struct NumberExpr : ASTNode {
	double value;
	NumberExpr(double v) :value(v) {} 
	std::string toJson(int indent = 0) const override { 
		std::ostringstream o; 
		o << indentStr(indent) << "{ \"type\": \"Number\", \"value\": " << std::setprecision(15) << value << " }"; 
		return o.str(); 
	}
};


struct VarExpr : ASTNode { 
	std::string name; 
	VarExpr(const std::string& n) :name(n) {} 
	std::string toJson(int indent = 0) const override {
		std::ostringstream o; 
		o << indentStr(indent) << "{ \"type\": \"Var\", \"name\": \"" << jsonEsc(name) << "\" }"; 
		return o.str(); 
	} }
;


struct BinaryExpr : ASTNode { 
	std::string op; 
	ASTNode* left; 
	ASTNode* right; 
	BinaryExpr(const std::string& o, ASTNode* l, ASTNode* r) :
		op(o), left(l), right(r) {} 
	~BinaryExpr() { delete left; delete right; } 
	std::string toJson(int indent = 0) const override { 
		std::ostringstream o; 
		o << indentStr(indent) << "{ \"type\": \"Binary\", \"op\": \"" 
			<< jsonEsc(op) << "\",\n"; 
		o << indentStr(indent + 2) << "\"left\":\n" 
			<< left->toJson(indent + 4) << ",\n"; 
		o << indentStr(indent + 2) << "\"right\":\n" 
			<< right->toJson(indent + 4) << "\n"; 
		o << indentStr(indent) << "}"; return o.str(); 
	} 
};


struct AssignStmt : ASTNode { 
	std::string id; 
	ASTNode* expr; 
	AssignStmt(const std::string& i, ASTNode* e) :
		id(i), expr(e) {} 
	~AssignStmt() { delete expr; } 
	std::string toJson(int indent = 0) const override { 
		std::ostringstream o; 
		o << indentStr(indent) << "{ \"type\": \"Assign\", \"id\": \"" 
			<< jsonEsc(id) << "\",\n"; o << indentStr(indent + 2) 
			<< "\"expr\":\n" << expr->toJson(indent + 4) << "\n"; 
		o << indentStr(indent) << "}"; 
		return o.str(); 
	} 
};


struct PrintStmt : ASTNode { 
	ASTNode* expr; 
	PrintStmt(ASTNode* e) :
		expr(e) {} 
	~PrintStmt() { delete expr; } 
	std::string toJson(int indent = 0) const override { 
		std::ostringstream o; 
		o << indentStr(indent) << "{ \"type\": \"Print\", \n"; 
		o << indentStr(indent + 2) << "\"expr\":\n" 
			<< expr->toJson(indent + 4) << "\n"; 
		o << indentStr(indent) << "}"; 
		return o.str(); 
	} 
};


struct IfStmt : ASTNode { 
	ASTNode* cond; 
	ASTNode* thenStmt;
	ASTNode* elseStmt; 
	IfStmt(ASTNode* c, ASTNode* t, ASTNode* e = nullptr) :
		cond(c), thenStmt(t), elseStmt(e) {} 
	~IfStmt() { 
		delete cond; 
		delete thenStmt; 
		if (elseStmt) 
			delete elseStmt; 
	} 
	std::string toJson(int indent = 0) const override { 
		std::ostringstream o; 
		o << indentStr(indent) << "{ \"type\": \"If\",\n"; 
		o << indentStr(indent + 2) << "\"cond\":\n" 
			<< cond->toJson(indent + 4) << ",\n"; 
		o << indentStr(indent + 2) << "\"then\":\n" 
			<< thenStmt->toJson(indent + 4); 
		if (elseStmt) { 
			o << ",\n" << indentStr(indent + 2) 
				<< "\"else\":\n" << elseStmt->toJson(indent + 4) << "\n"; 
		} 
		else 
			o << "\n"; o << indentStr(indent) << "}"; 
		return o.str(); 
	} 
};


struct BlockStmt : ASTNode { 
	std::vector<ASTNode*> stmts; 
	~BlockStmt() { 
		for (auto p : stmts) 
			delete p; 
	} 
	std::string toJson(int indent = 0) const override { 
		std::ostringstream o; 
		o << indentStr(indent) << "{ \"type\": \"Block\", \"stmts\": [\n"; 
		for (size_t i = 0; i < stmts.size(); ++i) { 
			o << stmts[i]->toJson(indent + 4); 
			if (i + 1 < stmts.size()) 
				o << ",\n"; else o << "\n"; 
		} 
		o << indentStr(indent) << "] }"; 
		return o.str(); 
	} 
};


// Global root set by parser actions
extern ASTNode* ast_root; // defined in parser .y