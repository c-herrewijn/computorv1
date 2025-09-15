#include "lexer.hpp"

void Token::print() {
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
			std::cout << 'x';
			break;
		case NON_SYMBOL:
			std::cout <<
			          "invalid token: TokenType symbol can not be combined with symbol NON_SYMBOL" <<
			          std::endl;
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

TokenSymbol Token::_charcter_to_symbol(char c) {
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

Token::Token(std::string number_str) {
	if (number_str.size() > 11) { // 10 chars for max_int + 1 char for minus sign
		// not numbers like 00000000000000042 might not be too large, after all
		std::cout << "number in equation to large: '" << number_str << "'" << std::endl;
		exit(EXIT_FAILURE);
	}
	long long_num = std::stol(number_str);
	if (long_num > std::numeric_limits<int>::max()) {
		std::cout << "number in equation to large: '" << number_str << "'" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (long_num < std::numeric_limits<int>::min()) {
		std::cout << "number in equation to small: '" << number_str << "'" << std::endl;
		exit(EXIT_FAILURE);
	}
	int num = static_cast<int>(long_num);
	this->type = NUMBER;
	this->symbol = NON_SYMBOL;
	this->number = num;
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
			} else {
				tokens.emplace_back(Token(c));
			}
			break;
		case READING_NUMBER:
			if (c == ' ') {
				std::string num_str{in_str, idx_num_start, idx_num_length};
				tokens.emplace_back(Token(num_str));
				idx_num_length=0;
				state = NEWTOKEN;
			} else if (std::isdigit(c)) {
				idx_num_length++;
			} else {
				std::string num_str{in_str, idx_num_start, idx_num_length};
				tokens.emplace_back(Token(num_str));
				idx_num_length=0;
				state = NEWTOKEN;
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
