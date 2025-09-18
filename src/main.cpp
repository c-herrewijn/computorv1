#include "token.hpp"
#include "polynomial.hpp"
#include "enums.hpp"
#include "term.hpp"

#include <iostream>
#include <iterator>

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

	// lex
	std::vector<Token> tokens = Token::tokenize(in_str);
	if (tokens.empty()) {
		std::cout << "Empty equation is not valid" << std::endl;
		exit(EXIT_FAILURE);
	}

	// parsing
	Polynomial polynomial;
	size_t idx_term_start = 0;
	size_t idx_rhs_start = 0;
	bool parsing_lhs = true; // first terms will be left-hand-side, e.g., to the left of '=' symbol
	std::vector<Term> *parsing_terms = &(polynomial.lhs_terms);

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
			parsing_terms = &(polynomial.rhs_terms);
			parsing_lhs = false;

		}
		if (idx == tokens.size() - 1) {
			if (idx_term_start > idx) {
				std::cout << "Error parsing token at index " << idx << "; final term does not properly end! " <<
				          std::endl;
				exit(EXIT_FAILURE);
			}
			if (parsing_lhs == true) {
				std::cout << "Error parsing token at index " << idx << "; missing '=' symbols! " << std::endl;
				exit(EXIT_FAILURE);
			} else {
				std::vector<Token> term_tokens(std::make_move_iterator(tokens.begin() + idx_term_start),
				                               std::make_move_iterator(tokens.end()));
				parsing_terms->emplace_back(Term{term_tokens});
			}
		}
	}

	// print tokenize
	std::cout << "tokens: " << std::endl;
	for (Token t : tokens) {
		t.print();
	}

	// print lhs
	std::cout << "terms lhs: " << std::endl;
	for (Term t : polynomial.lhs_terms) {
		t.print();
	}

	// print rhs
	std::cout << "terms rhs: " << std::endl;
	for (Term t : polynomial.rhs_terms) {
		t.print();
	}
}
