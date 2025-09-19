#include "term.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <cassert>

/*
constructors
*/
Term::Term(int number, int order) : number(number), order(order) {}
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
	for (size_t i = 0; i < tokens.size(); i++) {
		switch (state) {
		case READING_NEW_TERM:
			if (tokens[i].symbol == MINUS_SYMBOL) {
				if (i != 0) {
					std::cout << "minus sign should be first token only" << std::endl;
					exit(EXIT_FAILURE);
				}
				if (tokens.size() == 1) {
					std::cout << "minus sign should not be the only token" << std::endl;
					exit(EXIT_FAILURE);
				}
				sign = -1;
			} else if (tokens[i].type == NUMBER) {
				number = tokens[i].number * sign;
				state = READING_STAR_SYMBOL;
			} else if (tokens[i].symbol == X_CHAR) {
				number = 1;
				order = 1;
				state = READING_POWER_SYMBOL;
			} else {
				std::cout << "invalid token: '" << tokens[i].to_string() <<
				          "'; term should start with number or 'X' char" << std::endl;
				exit(EXIT_FAILURE);
			}
			break;
		case READING_STAR_SYMBOL:
			if (tokens[i].symbol != STAR_SYMBOL) {
				std::cout << "invalid token: '" << tokens[i].to_string() << "'; expected: '*'"
				          << std::endl;
				exit(EXIT_FAILURE);
			}
			// there should be at least 1 token after the star symbol
			if (i + 1 == tokens.size()) {
				std::cout << "token: '" << tokens[i].to_string() <<
				          "' is not a valid end-token." << std::endl;
				exit(EXIT_FAILURE);
			}
			state = READING_X_CHAR;
			break;
		case READING_X_CHAR:
			if (tokens[i].symbol != X_CHAR) {
				std::cout << "invalid token: '" << tokens[i].to_string() << "'; expected: 'X'"
				          << std::endl;
				exit(EXIT_FAILURE);
			}
			order = 1; // at least first order term
			state = READING_POWER_SYMBOL;
			break;
		case READING_POWER_SYMBOL:
			if (tokens[i].symbol != POWER_SYMBOL) {
				std::cout << "invalid token: '" << tokens[i].to_string() << "'; expected: '^'"
				          << std::endl;
				exit(EXIT_FAILURE);
			}
			// there should be at least 1 token after the power symbol
			if (i + 1 == tokens.size()) {
				std::cout << "token: '" << tokens[i].to_string() <<
				          "' is not a valid end-token." << std::endl;
				exit(EXIT_FAILURE);
			}
			state = READING_TERM_ORDER;
			break;
		case READING_TERM_ORDER:
			if (tokens[i].type != NUMBER) {
				std::cout << "invalid token: '" << tokens[i].to_string() <<
				          "'; expected a number" << std::endl;
				exit(EXIT_FAILURE);
			}
			order = tokens[i].number;
			if (tokens.size() > i + 1) {
				std::cout << "Too many tokens (" << std::to_string(tokens.size()) <<
				          ") to create a term!" << std::endl;
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
		return std::to_string(number);
	}
	if (number != 1) {
		str.append(std::to_string(number));
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
