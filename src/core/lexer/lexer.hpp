#pragma once

#include "../utils/include.hpp"
#include "../base_definitions/token.hpp"
#include "../helper/error.hpp"

// lexer
struct SymbolEntry {
	str val;
	TokenType type;
};

struct Lexer {
	str src;
	int idx;
	int col;
	int line;
	Lexer(str src) {
		this->src = src;
		this->idx = 0;
		this->col = 0;
		this->line = 0;
	}
	char current() {
		return src[idx];
	}
};

TokenType lookupSymbol(str val);
TokenType lookupKeyword(str val);
void advance(Lexer*);
void skipWhitespace(Lexer*);
bool isEnd(Lexer*);
Token* nextToken(Lexer*);