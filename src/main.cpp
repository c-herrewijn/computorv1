#include "lexer.hpp"

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

	// tests symbol_to_token
	// Token a;
	// a = symbol_to_token('+');
	// std::cout << a.symbol << std::endl;
	// a = symbol_to_token('X');
	// std::cout << a.symbol << std::endl;
	// a = symbol_to_token('w'); //fails
	// std::cout << a.symbol << std::endl;


	// tests create_number_token("1234", 0, 4);
	// Token b;
	// b = create_number_token("1234", 0, 4);
	// std::cout << b.number << std::endl;
	// b = create_number_token("--1234", 2, 4);
	// std::cout << b.number << std::endl;
	// b = create_number_token("aa2147483647aaa", 2, 10);
	// std::cout << b.number << std::endl;
	// b = create_number_token("aa11474836470aa", 2, 11);
	// std::cout << b.number << std::endl;
	// b = create_number_token("aa91474836470aa", 2, 10);
	// std::cout << b.number << std::endl;


	// test tokenize
	std::cout << "tokens: " << std::endl;
	std::vector<Token> tokens = tokenize(in_str);
	for (Token t : tokens) {
		t.print();
		std::cout << std::endl;
	}
}
