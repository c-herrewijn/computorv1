#ifndef LEXER_H
# define LEXER_H

#include <string>
#include <iostream>
#include <cassert>
#include <limits>
#include <vector>

enum TokenSymbol {
	PLUS_SYMBOL,
	MINUS_SYMBOL,
	STAR_SYMBOL,
	POWER_SYMBOL,
	EQUALS_SYMBOL,
	X_CHAR,
	NON_SYMBOL
};

enum TokenType {
	SYMBOL,
	NUMBER
};

enum TokenizerState {
	NEWTOKEN,
	READING_NUMBER
};


struct Token {
	TokenType type;
	TokenSymbol symbol;
	int number;

    Token(TokenType t, TokenSymbol s, int n) : type(t), symbol(s), number(n) {}

    Token(char c) : Token::Token(SYMBOL, _charcter_to_symbol(c), -1) {}
    Token(size_t n): Token::Token(NUMBER, NON_SYMBOL, n) {}
    Token(std::string number_str);

    // todo: make private, e.g. convert to class
    TokenSymbol _charcter_to_symbol(char c);

    void print();
};

std::vector<Token> tokenize(std::string in_str);

#endif
