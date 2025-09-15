#include "token.hpp"

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

	// debug
	std::cout << in_str << std::endl;

	// test tokenize
	std::cout << "tokens: " << std::endl;
	std::vector<Token> tokens = Token::tokenize(in_str);
	for (Token t : tokens) {
		t.print();
		std::cout << std::endl;
	}
}
