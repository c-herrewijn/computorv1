#include "polynomial.hpp"
#include "utils.hpp"
#include <iostream>
#include <cassert>
#include <cmath>

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
	std::cout << "\nStandard reduced form: " << std::endl;
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
	std::cout << " = 0\n" << std::endl;
}

void Polynomial::print_normalzed_simplified() const {
	assert(solution_state != PARSED_INPUT);
	bool first = true;
	std::cout << "Standard simplified form: " << std::endl;
	for (auto coeff=normalized_coefficients.rbegin(); coeff != normalized_coefficients.rend();
	        coeff++) {
		if (coeff->second == 0) {
			continue;
		}
		if (first) {
			std::cout << double_to_str(coeff->second);
			first = false;
		} else {
			if (coeff->second < 0) {
				std::cout << " - " << double_to_str(-1 * coeff->second);
			} else {
				std::cout << " + " << double_to_str(coeff->second);
			}
		}
		if (coeff->first == 1) {
			std::cout << "*X";
		}
		if (coeff->first > 1) {
			std::cout << " * X^" << coeff->first;
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

	this->print_normalzed();
	std::cout << "Polynomial degree: " << order << std::endl;
	std::cout << "Solving ..." << std::endl;
	if (order == 0) {
		this->print_normalzed_simplified();
		if (has_indeterminate == false) {
			if (c != 0) {
				std::cout << "Invalid equation, no solution possible" << std::endl;
			} else {
				std::cout << "No indeternimate to solve, but statement is valid!" << std::endl;
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
		this->print_normalzed_simplified();
		std::cout << b << " * X = " << (-1*c) << std::endl;
		std::cout << "X = " << (-1*c) << " / " << b << std::endl; // todo: calc irreducible fraction
		std::cout << "X = " << (-1*c) / b << std::endl;
	}
	if (order == 2) {
		std::cout << "\nstep 1:" << std::endl;
		this->print_normalzed_simplified();

		std::cout << "\nstep 2: determine A, B and C using ABC-formula:\nA*X^2 + B*X + C = 0" << std::endl;
		std::cout << "A = " << a << std::endl;
		std::cout << "B = " << b << std::endl;
		std::cout << "C = " << c << std::endl;

		std::cout << "\nstep 3: calculate 'Discriminant'" << std::endl;
		std::cout << "Discriminant = B^2 - 4 * A * C" << std::endl;
		std::cout << "Discriminant = " << b << "^2 - 4 * " << a << " * " << c << std::endl;
		std::cout << "Discriminant = " << b *b << " - " << 4*a *c << std::endl;
		double discriminant = b*b - 4*a*c;
		std::cout << "Discriminant = " << discriminant << std::endl;

		std::cout << "\nstep 4: ";
		if (discriminant == 0) {
			std::cout << "general solution formula for discriminant = 0:" << std::endl;
			std::cout << "  X = (-1 * B) / (2 * A)" << std::endl;
			std::cout << "substituting A, B and C:" << std::endl;
			std::cout << "  X = (-1 * " << b << ") / (2 * " << a << ")" << std::endl;
			std::cout << "  X = " << (-1*b) << " / " << (2*a) << std::endl;
			std::cout << "  X = " << (-1*b) / (2*a) << std::endl;
		}
		if (discriminant > 0) {
			std::cout << "general solution formula for discriminant > 0:" << std::endl;
			std::cout << "two solutions:" << std::endl;
			std::cout << "  X = (-1 * B + sqrt(discriminant)) / (2 * A)" << std::endl;
			std::cout << "or: " << std::endl;
			std::cout << "  X = (-1 * B - sqrt(discriminant)) / (2 * A)" << std::endl;
			std::cout << "substituting A and B:" << std::endl;
			std::cout << "solution 1:" << std::endl;
			std::cout << "  X = (-1 * " << b << " + sqrt(" << discriminant << ")) / (2 * " << a <<")"
			          << std::endl;
			std::cout << "  X = (" << (-1 * b) << " + " << std::sqrt(discriminant) << ") / " <<
			          (2 * a) << std::endl;
			std::cout << "  X = " << (-1 * b) + std::sqrt(discriminant) << " / " << (2 * a) << std::endl;
			std::cout << "  X = " << ((-1 * b) + std::sqrt(discriminant)) / (2 * a) << std::endl;
			std::cout << "solution 2:" << std::endl;
			std::cout << "  X = (-1 * " << b << " - sqrt(" << discriminant << ")) / (2 * " << a << ")"
			          << std::endl;
			std::cout << "  X = (" << (-1 * b) << " - " << std::sqrt(discriminant) << ") / "
			          << (2 * a) << std::endl;
			std::cout << "  X = " << (-1 * b) - std::sqrt(discriminant) << " / " << (2 * a) << std::endl;
			std::cout << "  X = " << ((-1 * b) - std::sqrt(discriminant)) / (2 * a) << std::endl;
		}
		if (discriminant < 0) {
			std::cout << "general solution formula for discriminant < 0:" << std::endl;
			std::cout << "two complex solutions:" << std::endl;
			std::cout << "  X = (-1 * B) / (2 * A) + i * sqrt(-1 * discriminant) / (2 * A)" << std::endl;
			std::cout << "or" << std::endl;
			std::cout << "  X = (-1 * B) / (2 * A) - i * sqrt(-1 * discriminant) / (2 * A)" << std::endl;
			std::cout << "substituting A and B:" << std::endl;
			std::cout << "solution 1:" << std::endl;
			std::cout << "  X = (-1 * " << b << ") / (2 * " << a << ") + i * sqrt(-1 * "
			          << discriminant << ") / (2 * " << a << ")" << std::endl;
			std::cout << "  X = " << -1 * b << " / " << 2 * a << " + i * sqrt(" <<
			          -1 * discriminant << ") / " << 2 * a << std::endl;
			std::cout << "  X = " << -1 * b / (2 * a) << " + i * "
			          << std::sqrt(-1 * discriminant) << " / " << 2 * a << std::endl;
			std::cout << "  X = " << -1 * b / (2 * a) << " + i * "
			          << std::sqrt(-1 * discriminant) / (2 * a) << std::endl;
			std::cout << "solution 2:" << std::endl;
			std::cout << "  X = (-1 * " << b << ") / (2 * " << a << ") - i * sqrt(-1 * "
			          << discriminant << ") / (2 * " << a << ")" << std::endl;
			std::cout << "  X = " << -1 * b << " / " << 2 * a << " - i * sqrt(" << -1 * discriminant
			          << ") / " << 2 * a << std::endl;
			std::cout << "  X = " << -1 * b / (2 * a) << " - i * "
			          << std::sqrt(-1 * discriminant) << " / " << 2 * a << std::endl;
			std::cout << "  X = " << -1 * b / (2 * a) << " - i * "
			          << std::sqrt(-1 * discriminant) / (2 * a) << std::endl;
		}
	}
	if (order > 2) {
		std::cout << "The polynomial degree is strictly greater than 2, I can't solve." << std::endl;
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
