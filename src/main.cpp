#include <iostream>
#include <string>

#include <vector>

enum TokenSymbol {
    PLUS_SYMBOL,
    MINUS_SYMBOL,
    STAR_SYMBOL,
    POWER_SYMBOL,
    EQUALS_SYMBOL,
    X_CHAR
};

enum TokenType {
    NUMBER,
    SYMBOL
};

struct Token {
    TokenType type;
    TokenSymbol symbol;
    int number;
};


std::vector<Token> tokenize(std::string in_str) {
    // TODO tokenize

    std::vector<Token> tokens;
    return tokens;
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

    // debug
    std::cout << in_str << std::endl;

    std::vector<Token> tokens = tokenize(in_str);

}
