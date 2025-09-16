#ifndef TOKEN_H
# define TOKEN_H

#include "enums.hpp"

#include <string>
#include <vector>

class Token {
public:
	Token() = delete;
	Token(const char c);
	Token(const size_t n);
	Token(const std::string number_str);
	Token(const Token &obj);

	~Token();
	Token &operator=(const Token &obj);

	void print() const;
	std::string to_string() const;
	static std::vector<Token> tokenize(const std::string in_str);

	TokenType type;
	TokenSymbol symbol;
	int number;

private:
	Token(const TokenType t, const TokenSymbol s, const int n);
	static TokenSymbol charcter_to_symbol(const char c);
};

#endif
