#include "token.hpp"
#include "utils.hpp"

#include <cassert>
#include <iostream>
#include <string>

/*
constructors
*/
Token::Token(const TokenType t, const TokenSymbol s, const int n) : type(t), symbol(s),
	number(n) {}
Token::Token(const char c) : Token::Token(SYMBOL, charcter_to_symbol(c), -1) {}
Token::Token(const size_t n): Token::Token(NUMBER, NON_SYMBOL, n) {}
Token::Token(const std::string number_str) : type(NUMBER), symbol(NON_SYMBOL),
	number(str_to_int(number_str)) {}
Token::Token(const Token &obj) {
	*this = obj;
}
Token::~Token() {}

/*
operators
*/
Token &Token::operator=(const Token &obj) {
	this->type = obj.type;
	this->symbol = obj.symbol;
	this->number = obj.number;
	return *this;
}

/*
member functions
*/
std::string Token::to_string() const {
	std::string str = "";
	if (type == SYMBOL) {
		switch (symbol) {
		case PLUS_SYMBOL:
			str += '+';
			break;
		case MINUS_SYMBOL:
			str += '-';
			break;
		case STAR_SYMBOL:
			str += '*';
			break;
		case POWER_SYMBOL:
			str += '^';
			break;
		case EQUALS_SYMBOL:
			str += '=';
			break;
		case X_CHAR:
			str += 'x';
			break;
		case NON_SYMBOL:
			std::cout <<
			          "invalid token: TokenType SYMBOL can not be combined with symbol NON_SYMBOL" <<
			          std::endl;
			exit(EXIT_FAILURE);
		default:
			std::cout << "unsupported symbol: " << symbol << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	if (type == NUMBER) {
		str = std::to_string(number);
	}
	return str;
}

void Token::print() const {
	std::cout << this->to_string() << std::endl;
}

/*
static functions
*/
std::vector<Token> Token::tokenize(const std::string in_str) {
	// input
	size_t str_len = in_str.size();

	// output
	std::vector<Token> tokens;

	// state
	TokenizerState state = NEW_TOKEN;
	size_t idx_num_start;
	size_t idx_num_length = 0;

	// tokenize string
	for (size_t idx_str = 0; idx_str < str_len; idx_str++) {
		char c = in_str[idx_str];
		switch (state) {
		case NEW_TOKEN:
			if (c == ' ') {}
			else if (std::isdigit(c)) {
				idx_num_start = idx_str;
				idx_num_length++;
				state = READING_NUMBER;
			} else {
				tokens.emplace_back(Token(c));
			}
			break;
		case READING_NUMBER:
			if (c == ' ') {
				std::string num_str{in_str, idx_num_start, idx_num_length};
				tokens.emplace_back(Token(num_str));
				idx_num_length=0;
				state = NEW_TOKEN;
			} else if (std::isdigit(c)) {
				idx_num_length++;
			} else {
				std::string num_str{in_str, idx_num_start, idx_num_length};
				tokens.emplace_back(Token(num_str));
				idx_num_length=0;
				state = NEW_TOKEN;
				tokens.emplace_back(Token(c));
			}
			break;
		default:
			std::cout << "unsupported state: '" << state << "'" << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	// if needed add final numerical token
	if (state == READING_NUMBER) {
		std::string num_str{in_str, idx_num_start, idx_num_length};
		tokens.emplace_back(Token(num_str));
	}
	return tokens;
}

TokenSymbol Token::charcter_to_symbol(const char c) {
	assert(std::isdigit(c) == false);
	switch (c) {
	case '+':
		return PLUS_SYMBOL;
	case '-':
		return MINUS_SYMBOL;
	case '*':
		return STAR_SYMBOL;
	case '^':
		return POWER_SYMBOL;
	case '=':
		return EQUALS_SYMBOL;
	case 'X':
		return X_CHAR;
	case 'x':
		return X_CHAR;
	default:
		std::cout << "invalid symbol in equation: '" << c << "'" << std::endl;
		exit(EXIT_FAILURE);
	}
}
