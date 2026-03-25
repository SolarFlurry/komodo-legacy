#pragma once

#include "../utils/include.hpp"
#include "token.hpp"
#include "./type.hpp"

struct Expr;
struct Stmt;

struct Module {
	vec<Stmt*> contents = vec<Stmt*>();
	void print ();
};

struct Block {
	vec<Stmt*> stmts;
};

struct Identifier {
	str_view name;
};

struct IfExpr {
	Expr* condition;
	Block* trueBlock;
	Block* falseBlock;
};

struct RValue {
	Identifier ident;
};

struct VarDecl {
	Identifier variable;
	enum Kind {
		Score,
		Const,
		Global,
		FuncParam,
		MemberVar,
	} kind;
	Expr* initial;
};

struct FuncDecl {
	enum Kind {
		Normal,
		MemberFunc,
	} kind;
	Identifier func;
	Type* returnType;
	vec<Identifier*> params;
	vec<Expr*> body;
};

typedef std::variant<int, float, bool, char, str> Literal;

struct BinaryOp {
	enum Ops {
		Add,
		Sub,
		Mul,
		Div,
		Mod,
		Equals,
		Nequals,
		Greater,
		Less,
		GreaterEq,
		LessEq,
		Assign,
		And,
		Or,
	} op;
	Expr* lhs;
	Expr* rhs;
};

struct UnaryOp {
	enum Ops {
		Invert,
		Not,
	} op;
	Expr* operand;
};

struct FuncCall {
	Expr* callee;
	vec<Expr*> args;
};

struct Expr {
	std::variant<Literal, Identifier, BinaryOp, UnaryOp, FuncCall, IfExpr> value;
	Type* type;
	Expr (Token* tkn);
	void print(u32 depth);
};

struct Stmt {
	std::variant<Expr, FuncDecl, VarDecl> value;
	Token* token;
	Stmt (Token* tkn);
	void print();
};