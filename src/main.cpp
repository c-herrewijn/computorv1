#include <iostream>
#include <string>

#include <vector>
#include <cctype>
#include <cassert>
#include <limits>

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

struct Token {
	TokenType type;
	TokenSymbol symbol;
	int number;

	void print() {
		if (type == SYMBOL) {
			switch (symbol) {
				case PLUS_SYMBOL:
					std::cout << '+';
					break;
				case MINUS_SYMBOL:
					std::cout << '-';
					break;
				case STAR_SYMBOL:
					std::cout << '*';
					break;
				case POWER_SYMBOL:
					std::cout << '^';
					break;
				case EQUALS_SYMBOL:
					std::cout << '=';
					break;
				case X_CHAR:
					std::cout << 'X';
					break;
				case NON_SYMBOL:
					std::cout << "invalid token: TokenType symbol can not be combined with symbol NON_SYMBOL" << std::endl;
					exit(EXIT_FAILURE);
				default:
					std::cout << "unsupported symbol: " << symbol << std::endl;
					exit(EXIT_FAILURE);
			}
		}
		if (type == NUMBER) {
			std::cout << number;
		}
	}
};

enum TokenizerState {
	NEWTOKEN,
	READING_NUMBER
};

Token symbol_to_token(char c) {
	assert (std::isdigit(c) == false);
	switch (c) {
		case '+':
			return Token{SYMBOL, PLUS_SYMBOL, -1};
		case '-':
			return Token{SYMBOL, MINUS_SYMBOL, -1};
		case '*':
			return Token{SYMBOL, STAR_SYMBOL, -1};
		case '^':
			return Token{SYMBOL, POWER_SYMBOL, -1};
		case '=':
			return Token{SYMBOL, EQUALS_SYMBOL, -1};
		case 'X':
			return Token{SYMBOL, X_CHAR, -1};
		default:
			std::cout << "invalid symbol in equation: '" << c << "'" << std::endl;
			exit(EXIT_FAILURE);
	}
}

Token create_number_token(std::string in_str, size_t idx_start, size_t len) {
	std::string sub_str{in_str, idx_start, len};
	if (len > 10) {
		std::cout << "number in equation to large: '" << sub_str << "'" << std::endl;
		exit(EXIT_FAILURE);
	}
	long long_num = std::stol(sub_str);
	if (long_num > std::numeric_limits<int>::max()) {
		std::cout << "number in equation to large: '" << sub_str << "'" << std::endl;
		exit(EXIT_FAILURE);
	}
	int num = static_cast<int>(long_num);
	return Token{NUMBER, NON_SYMBOL, num};
}


std::vector<Token> tokenize(std::string in_str) {
	// input
	size_t str_len = in_str.size();

	// output
	std::vector<Token> tokens;

	// state
	TokenizerState state = NEWTOKEN;
	size_t idx_num_start;
	size_t idx_num_length = 0;

	// tokenize string
	for (size_t idx_str = 0; idx_str < str_len; idx_str++) {
		char c = in_str[idx_str];
		switch (state) {
			case NEWTOKEN:
				if (c == ' ') {}
				else if (std::isdigit(c)) {
					idx_num_start = idx_str;
					idx_num_length++;
					state = READING_NUMBER;
				}
				else {
					tokens.emplace_back(symbol_to_token(c));
				}
				break;
			case READING_NUMBER:
				if (c == ' ') {
					tokens.emplace_back(create_number_token(in_str, idx_num_start, idx_num_length));
					idx_num_length=0;
					state = NEWTOKEN;
				}
				else if (std::isdigit(c)) {
					idx_num_length++;
				}
				else {
					tokens.emplace_back(create_number_token(in_str, idx_num_start, idx_num_length));
					idx_num_length=0;
					state = NEWTOKEN;
					tokens.emplace_back(symbol_to_token(c));
				}
				break;
			default:
				std::cout << "unsupported state: '" << state << "'" << std::endl;
				exit(EXIT_FAILURE);
		}
	}

	// if needed add final numerical token
	if (state == READING_NUMBER) {
		tokens.emplace_back(create_number_token(in_str, idx_num_start, idx_num_length));
	}
	return tokens;
}


int main(int argc, char *argv[]) {

	if (argc < 2) {
		std::cout << "Please provide the equation as argument" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (argc > 2) {
		std::cout << "Please provide the equation as single argument" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::string in_str{argv[1]};

	// debug
	std::cout << in_str << std::endl;


	// tests symbol_to_token
	// Token a;
	// a = symbol_to_token('+');
	// std::cout << a.symbol << std::endl;
	// a = symbol_to_token('X');
	// std::cout << a.symbol << std::endl;
	// a = symbol_to_token('w'); //fails
	// std::cout << a.symbol << std::endl;


	// tests create_number_token("1234", 0, 4);
	// Token b;
	// b = create_number_token("1234", 0, 4);
	// std::cout << b.number << std::endl;
	// b = create_number_token("--1234", 2, 4);
	// std::cout << b.number << std::endl;
	// b = create_number_token("aa2147483647aaa", 2, 10);
	// std::cout << b.number << std::endl;
	// b = create_number_token("aa11474836470aa", 2, 11);
	// std::cout << b.number << std::endl;
	// b = create_number_token("aa91474836470aa", 2, 10);
	// std::cout << b.number << std::endl;


	// test tokenize
	std::cout << "tokens: " << std::endl;
	std::vector<Token> tokens = tokenize(in_str);
	for (Token t : tokens) {
		t.print();
		std::cout << std::endl;
	}
}
