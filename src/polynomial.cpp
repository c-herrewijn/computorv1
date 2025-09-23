#include "polynomial.hpp"
#include "utils.hpp"
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
			std::vector<Token> term_tokens(
			    std::make_move_iterator(tokens.begin() + static_cast<int>(idx_term_start)),
			    std::make_move_iterator(tokens.begin() + static_cast<int>(idx)));
			parsing_terms->emplace_back(Term{term_tokens});
			idx_term_start = idx + 1; // plus symbol is NOT part of the next Term
		}
		if (tokens[idx].symbol == MINUS_SYMBOL) {
			if (idx != 0 && idx != idx_rhs_start) { // minus symbol at start or after '=' is non-splitting
				if (idx_term_start == idx) {
					std::cout << "invalid location of '-' symbol" << std::endl;
					exit(EXIT_FAILURE);
				}
				std::vector<Token> term_tokens(
				    std::make_move_iterator(tokens.begin() + static_cast<int>(idx_term_start)),
				    std::make_move_iterator(tokens.begin() + static_cast<int>(idx)));
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

			std::vector<Token> term_tokens(
			    std::make_move_iterator(tokens.begin() + static_cast<int>(idx_term_start)),
			    std::make_move_iterator(tokens.begin() + static_cast<int>(idx)));
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
				std::vector<Token> term_tokens(
				    std::make_move_iterator(tokens.begin() +static_cast<int>(idx_term_start)),
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
		for (const Term &t : lhs_terms) {
			auto it = normalized_coefficients.find(t.order);
			if (it == normalized_coefficients.end()) {
				normalized_coefficients.emplace(t.order, t.number);
			} else {
				normalized_coefficients[t.order] += t.number;
			}
		}
		for (const Term &t : rhs_terms) {
			auto it = normalized_coefficients.find(t.order);
			if (it == normalized_coefficients.end()) {
				normalized_coefficients.emplace(t.order, -1*t.number);
			} else {
				normalized_coefficients[t.order] -= t.number;
			}
		}
		solution_state = NORMALIZED;
	}
	// make sure coefficients a, b, and c are always set
	for (size_t order=0; order<=2; order++) {
		auto it = normalized_coefficients.find(order);
		if (it == normalized_coefficients.end()) {
			normalized_coefficients.emplace(order, 0);
		}
	}
}

void Polynomial::print_normalzed() const {
	assert(solution_state != PARSED_INPUT);
	std::cout << "Standard reduced form: " << std::endl;
	for (size_t idx=0; idx < this->get_order() + 1; idx++) {
		if (normalized_coefficients.find(idx) != normalized_coefficients.end()) {
			std::string nr_str = double_to_str(normalized_coefficients.at(idx));
			if (idx==0) {
				std::cout << nr_str << " * X^" << idx;
			} else {
				if (normalized_coefficients.at(idx) < 0) {
					std::string nr_str_abs = double_to_str(-1 * normalized_coefficients.at(idx));
					std::cout << " - " << nr_str_abs << " * X^" << idx;
				} else {
					std::cout << " + "<< nr_str << " * X^" << idx;
				}
			}
		} else {
			if (idx==0) {
				std::cout << "0 * X^" << idx;
			} else {
				std::cout << " + 0 * X^" << idx;
			}
		}
	}
	std::cout << " = 0" << std::endl;
}

void Polynomial::print_normalzed_simplified() const {
	assert(solution_state != PARSED_INPUT);
	bool first = true;
	std::cout << "Standard simplified form: " << std::endl;
	for (const auto &coeff : normalized_coefficients) {
		if (coeff.second == 0) {
			continue;
		}
		if (first) {
			std::cout << double_to_str(coeff.second);
			first = false;
		} else {
			if (coeff.second < 0) {
				std::cout << " - " << double_to_str(-1 * coeff.second);
			} else {
				std::cout << " + " << double_to_str(coeff.second);
			}
		}
		if (coeff.first == 1) {
			std::cout << "*X";
		}
		if (coeff.first > 1) {
			std::cout << "*X^" << coeff.first;
		}
	}
	if (first == true) {
		std::cout << "0";
	}
	std::cout << " = 0" << std::endl;
}

size_t Polynomial::get_order() const {
	assert(solution_state != PARSED_INPUT);
	for (auto iter=normalized_coefficients.rbegin(); iter != normalized_coefficients.rend(); iter++) {
		if (iter->second != 0) {
			return iter->first;
		}
	}
	return 0;
}

void Polynomial::solve() {
	assert(solution_state != PARSED_INPUT);
	size_t order = this->get_order();

	// coeffs for abc-formula
	double a = normalized_coefficients[2];
	double b = normalized_coefficients[1];
	double c = normalized_coefficients[0];

	if (order == 0) {
		if (has_indeterminate == false) {
			if (c != 0) {
				std::cout << "invalid equation, no solution possible" << std::endl;
			} else {
				std::cout << "no indeternimate to solve, but statement is valid!" << std::endl;
			}
		} else {
			if (c != 0) {
				std::cout << "No solution for X." << std::endl;
			} else {
				std::cout << "X can be any number" << std::endl;
			}
		}
	}
	if (order == 1) {
		std::cout << "Solving 1st order equation ..." << std::endl;
		std::cout << b << " * X = " << (-1*c) << std::endl;
		std::cout << "X = " << (-1*c) << " / " << b << std::endl;
		std::cout << "X = " << (-1*c) / b << std::endl;
	}
	if (order == 2) {
		// todo
	}
}

/*
debug
*/
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
