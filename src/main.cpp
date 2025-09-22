#include "token.hpp"
#include "polynomial.hpp"
#include "enums.hpp"
#include "term.hpp"

#include <iostream>
#include <iterator>

int main(int argc, char *argv[]) {
	// input validation
	if (argc < 2) {
		std::cout << "Please provide the equation as argument" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (argc > 2) {
		std::cout << "Please provide the equation as single argument" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::string in_str{argv[1]};

	// lexing (create tokens)
	std::vector<Token> tokens = Token::tokenize(in_str);
	if (tokens.empty()) {
		std::cout << "Empty equation is not valid" << std::endl;
		exit(EXIT_FAILURE);
	}

	// parsing (tokens to 2 sets of terms)
	Polynomial polynomial(tokens);

	// normalize input
	polynomial.normalize();
	polynomial.print_normalzed();
	polynomial.print_normalzed_simplified();

	// solve
	if (polynomial.get_order() > 2) {
		std::cout << "The polynomial degree is strictly greater than 2, I can't solve." << std::endl;
		exit(EXIT_SUCCESS);
	}
	polynomial.solve();
}
