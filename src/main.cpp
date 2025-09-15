#include "token.hpp"
#include "polynomial.hpp"
#include "enums.hpp"

#include <iostream>

Polynomial parse(const std::vector<Token> tokens) {

	// output
	Polynomial expression;

	// state
	ParserState state = READING_NEW_TERM;
	int num = 0;
	int order = 0;
	bool reading_lhs = true;
	bool negative_num = false;

	for (size_t i = 0; i < tokens.size(); i++) {
		switch (state) {
		case READING_NEW_TERM:
			if (tokens[i].type == NUMBER) {
				num = (negative_num) ? -1 * tokens[i].number : tokens[i].number;
				state = READING_TERM_ORDER;
				negative_num = false;
			} else if (tokens[i].type == SYMBOL) {
				switch (tokens[i].symbol) {
				case PLUS_SYMBOL:
					std::cout << "term can not start with token: " << tokens[i].to_string() <<
					          std::endl;
					exit(EXIT_FAILURE);
				case MINUS_SYMBOL:
					if (negative_num == true) {
						std::cout << "double negation when reading token: " << tokens[i].to_string() <<
						          std::endl;
						exit(EXIT_FAILURE);
					}
					negative_num = true;
					break;
				case STAR_SYMBOL:
					std::cout << "term can not start with token: " << tokens[i].to_string() <<
					          std::endl;
					exit(EXIT_FAILURE);
				case POWER_SYMBOL:
					std::cout << "term can not start with token: " << tokens[i].to_string() <<
					          std::endl;
					exit(EXIT_FAILURE);
				case EQUALS_SYMBOL:
					if (i == 0) {
						std::cout << "expression can not start with token: " << tokens[i].to_string() <<
						          std::endl;
						exit(EXIT_FAILURE);
					}
					if (!reading_lhs) {
						std::cout << "token: " << tokens[i].to_string() <<
						          " not valid when reading right hand side!" << std::endl;
						exit(EXIT_FAILURE);
					}
					reading_lhs = false;
					state = READING_NEW_TERM;
					// todo: verify that = is not the final token.
					break;
				case X_CHAR:
					// WIP
					state = READING_TERM_ORDER;
					break;
				default:
					// std::cout << "unsupported SYMBOL token: " << tokens[i].to_string() << std::endl;
					exit(EXIT_FAILURE);
				}
			} else {
				std::cout << "unsupported token type (enumeration: " << tokens[i].type << ")" <<
				          std::endl;
				exit(EXIT_FAILURE);
			}
			break;
		case READING_TERM_ORDER:

			// todo

			break;
		default:
			std::cout << "unsupported state: '" << state << "'" << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	return expression;

}

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

	// parse
	Polynomial eq = parse(tokens) ;

	class main {
	private:
		/* data */
	public:
		main(/* args */) {}
		~main() {}
	};
	// debug
	std::cout << in_str << std::endl;

	// print tokenize
	std::cout << "tokens: " << std::endl;
	for (Token t : tokens) {
		t.print();
		std::cout << std::endl;
	}
	// ---------------------------
}
