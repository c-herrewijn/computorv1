#include "polynomial.hpp"
#include <iostream>
#include <cassert>

/*
constructors
*/

/*
Parse tokens into terms of the polynomial
Splitting tokens are:
 - PLUS_SYMBOL
 - MINUS_SYMBOL
 - EQUALS_SYMBOL
*/
Polynomial::Polynomial(const std::vector<Token> tokens) {
	size_t idx_term_start = 0;
	size_t idx_rhs_start = 0;
	bool parsing_lhs = true; // first terms will be left-hand-side, e.g., to the left of '=' symbol
	std::vector<Term> *parsing_terms = &(this->lhs_terms);

	for (size_t idx=0; idx<tokens.size(); idx++) {
		if (tokens[idx].symbol == PLUS_SYMBOL) {
			if (idx == idx_term_start) {
				std::cout << "Error parsing token at index " << idx << " ; invalid location of '+' symbol" <<
				          std::endl;
				exit(EXIT_FAILURE);
			}
			std::vector<Token> term_tokens(std::make_move_iterator(tokens.begin() + idx_term_start),
			                               std::make_move_iterator(tokens.begin() + idx));
			parsing_terms->emplace_back(Term{term_tokens});
			idx_term_start = idx + 1; // plus symbol is NOT part of the next Term
		}
		if (tokens[idx].symbol == MINUS_SYMBOL) {
			if (idx != 0 && idx != idx_rhs_start) { // minus symbol at start or after '=' is non-splitting
				if (idx_term_start == idx) {
					std::cout << "invalid location of '-' symbol" << std::endl;
					exit(EXIT_FAILURE);
				}
				std::vector<Token> term_tokens(std::make_move_iterator(tokens.begin() + idx_term_start),
				                               std::make_move_iterator(tokens.begin() + idx));
				parsing_terms->emplace_back(Term{term_tokens});
				idx_term_start = idx; // minus symbol IS part of the next Term
			}
		}
		if (tokens[idx].symbol == EQUALS_SYMBOL) {
			if (parsing_lhs == false) {
				std::cout << "Error parsing token at index " << idx << " ; multle '=' symbols are not valid" <<
				          std::endl;
				exit(EXIT_FAILURE);
			}
			if (idx == idx_term_start) {
				std::cout << "Error parsing token at index " << idx << " ; term can not start with '=' symbol" <<
				          std::endl;
				exit(EXIT_FAILURE);
			}
			if (idx == tokens.size() -1) {
				std::cout << "Error parsing token at index " << idx << " ; equation can not end with '=' symbol" <<
				          std::endl;
				exit(EXIT_FAILURE);
			}

			std::vector<Token> term_tokens(std::make_move_iterator(tokens.begin() + idx_term_start),
			                               std::make_move_iterator(tokens.begin() + idx));
			parsing_terms->emplace_back(Term{term_tokens});
			idx_term_start = idx + 1; // equal symbol is NOT part of the next Term
			idx_rhs_start = idx + 1;
			parsing_terms = &(this->rhs_terms);
			parsing_lhs = false;

		}
		if (idx == tokens.size() - 1) {
			if (idx_term_start > idx) {
				std::cout << "Error parsing token at index " << idx << "; final term does not properly end! " <<
				          std::endl;
				exit(EXIT_FAILURE);
			}
			if (parsing_lhs == true) {
				std::cout << "Error parsing equation: missing '=' symbol! " << std::endl;
				exit(EXIT_FAILURE);
			} else {
				std::vector<Token> term_tokens(std::make_move_iterator(tokens.begin() + idx_term_start),
				                               std::make_move_iterator(tokens.end()));
				parsing_terms->emplace_back(Term{term_tokens});
			}
		}
		if (tokens[idx].symbol == X_CHAR) {
			this->has_indeterminate = true;
		}
	}
}

Polynomial::Polynomial(const Polynomial &obj) {
	*this = obj;
}

Polynomial::~Polynomial() {}

/*
operators
*/
Polynomial &Polynomial::operator=(const Polynomial &obj) {
	this->discriminant = obj.discriminant;

	// todo: others

	return *this;
}

/*
member functions
*/
void Polynomial::normalize() {
	if (solution_state == PARSED_INPUT) {
		for (const Term &t : lhs_terms ) {
			auto it = normalized_coefficients.find(t.order);
			if (it == normalized_coefficients.end()) {
				normalized_coefficients.emplace(t.order, t.number);
			}
			else {
				normalized_coefficients[t.order] += t.number;
			}
		}
		for (const Term &t : rhs_terms ) {
			auto it = normalized_coefficients.find(t.order);
			if (it == normalized_coefficients.end()) {
				normalized_coefficients.emplace(t.order, -1*t.number);
			}
			else {
				normalized_coefficients[t.order] -= t.number;
			}
		}
		solution_state = NORMALIZED;
	}
}

void Polynomial::print_normalzed() const {
	assert(solution_state != PARSED_INPUT);
	bool first = true;
	std::cout << "Reduced form: " << std::endl;
	for (const auto &coeff : normalized_coefficients) {
		if (first) {
			std::cout << coeff.second << " * X^" << coeff.first;
			first = false;
		}
		else {
			if (coeff.second < 0) {
				std::cout << " - " << coeff.second * -1 << " * X^" << coeff.first;
			}
			else {
				std::cout << " + "<< coeff.second  << " * X^" << coeff.first;
			}
		}
	}
	if (first == true) {
		std::cout << "0";
	}
	std::cout << " = 0" << std::endl;
}


void Polynomial::print() const {
	// print lhs
	std::cout << "terms lhs: " << std::endl;
	for (Term t : lhs_terms) {
		t.print();
	}

	// print rhs
	std::cout << "terms rhs: " << std::endl;
	for (Term t : rhs_terms) {
		t.print();
	}
};
