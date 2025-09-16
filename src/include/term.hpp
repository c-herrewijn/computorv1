#ifndef TERM_H
# define TERM_H

#include "token.hpp"
#include <string>
#include <vector>

// term in form: number * X ^ order
class Term {
public:
	Term() = delete;
	Term(int number, int order);
	Term(const Term &obj);
	Term(std::vector<Token> tokens);
	~Term();
	Term &operator=(const Term &obj);

	void print() const;
	std::string to_string() const;

	int number;
	int order;

private:

};

#endif
