#include "token.hpp"
#include "polynomial.hpp"
#include "enums.hpp"
#include "term.hpp"

#include <iostream>

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

	// parse
	// todo: split token into terms on + - or = sign

	// debug
	std::cout << in_str << std::endl;

	// print tokenize
	std::cout << "tokens: " << std::endl;
	for (Token t : tokens) {
		t.print();
	}

	std::cout << "first term: " << std::endl;
	Term first_term{tokens};
	first_term.print();

}
