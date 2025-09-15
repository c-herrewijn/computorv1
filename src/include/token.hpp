#ifndef TOKEN_H
# define TOKEN_H

#include "enums.hpp"

#include <string>
#include <vector>

class Token {
public:
	Token() = delete;
	Token(char c);
	Token(size_t n);
	Token(std::string number_str);
	Token(const Token &obj);

	~Token();
	Token &operator=(const Token &obj);

	void print() const;
	std::string to_string() const;
	static std::vector<Token> tokenize(std::string in_str);

	TokenType type;
	TokenSymbol symbol;
	int number;

private:
	Token(TokenType t, TokenSymbol s, int n);
	static TokenSymbol charcter_to_symbol(char c);
};

#endif
