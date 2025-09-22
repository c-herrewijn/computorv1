#include "term.hpp"
#include "utils.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <cassert>

/*
constructors
*/
Term::Term(double number, size_t order) : number(number), order(order) {}
Term::Term(const Term &obj) {
	*this = obj;
}
Term::~Term() {}

Term::Term(std::vector<Token> tokens) {
	assert(!tokens.empty());
	// state
	order = 0;
	int sign = 1;
	TermParserState state = READING_NEW_TERM;
	// parse tokens
	for (size_t idx = 0; idx < tokens.size(); idx++) {
		switch (state) {
		case READING_NEW_TERM:
			if (tokens[idx].symbol == MINUS_SYMBOL) {
				if (idx != 0) {
					std::cout << "minus sign should be first token only" << std::endl;
					exit(EXIT_FAILURE);
				}
				if (tokens.size() == 1) {
					std::cout << "minus sign should not be the only token" << std::endl;
					exit(EXIT_FAILURE);
				}
				sign = -1;
			} else if (tokens[idx].type == NUMBER) {
				number = tokens[idx].number * sign;
				state = READING_STAR_SYMBOL;
			} else if (tokens[idx].symbol == X_CHAR) {
				number = 1 * sign;
				order = 1;
				state = READING_POWER_SYMBOL;
			} else {
				std::cout << "invalid token: '" << tokens[idx].to_string() <<
				          "'; term should start with number or 'X' char" << std::endl;
				exit(EXIT_FAILURE);
			}
			break;
		case READING_STAR_SYMBOL:
			if (tokens[idx].symbol != STAR_SYMBOL) {
				std::cout << "invalid token: '" << tokens[idx].to_string() << "'; expected: '*'"
				          << std::endl;
				exit(EXIT_FAILURE);
			}
			// there should be at least 1 token after the star symbol
			if (idx + 1 == tokens.size()) {
				std::cout << "Invalid input; no valid token found after '" << tokens[idx].to_string() << "'" <<
				          std::endl;
				exit(EXIT_FAILURE);
			}
			state = READING_X_CHAR;
			break;
		case READING_X_CHAR:
			if (tokens[idx].symbol != X_CHAR) {
				std::cout << "invalid token: '" << tokens[idx].to_string() << "'; expected: 'X'" << std::endl;
				exit(EXIT_FAILURE);
			}
			order = 1; // at least first order term
			state = READING_POWER_SYMBOL;
			break;
		case READING_POWER_SYMBOL:
			if (tokens[idx].symbol != POWER_SYMBOL) {
				std::cout << "invalid token: '" << tokens[idx].to_string() << "'; expected: '^'" << std::endl;
				exit(EXIT_FAILURE);
			}
			// there should be at least 1 token after the power symbol
			if (idx + 1 == tokens.size()) {
				std::cout << "Invalid input; no valid token found after '" << tokens[idx].to_string() << "'" <<
				          std::endl;
				exit(EXIT_FAILURE);
			}
			state = READING_TERM_ORDER;
			break;
		case READING_TERM_ORDER:
			if (tokens[idx].type != NUMBER) {
				std::cout << "invalid token: '" << tokens[idx].to_string() << "'; expected a number" << std::endl;
				exit(EXIT_FAILURE);
			}
			order = tokens[idx].number;
			if (tokens.size() > idx + 1) {
				std::cout << "Too many tokens (" << tokens.size() << ") to create a term!" << std::endl;
				exit(EXIT_FAILURE);
			}
			break;
		default:
			std::cout << "invalid state: " << state << std::endl;
			exit(EXIT_FAILURE);
		}
	}
}

/*
operators
*/
Term &Term::operator=(const Term &obj) {
	this->number = obj.number;
	this->order = obj.order;
	return *this;
}

/*
member functions
*/
std::string Term::to_string() const {
	std::string str;
	if (number == 0) {
		return std::string("0");
	}
	if (order == 0) {
		return double_to_str(number);
	}
	if (number != 1) {
		str.append(double_to_str(number));
		if (order != 0) {
			str.append(" * ");
		}
	}
	if (order != 0) {
		str.append("X^");
		str.append(std::to_string(order));
	}
	return str;
}

void Term::print() const {
	std::cout << this->to_string() << std::endl;;
}
