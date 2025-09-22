#ifndef TERM_H
# define TERM_H

#include "token.hpp"
#include <string>
#include <vector>

// term in form: number * X ^ order
class Term {
public:
	Term() = delete;
	Term(double number, size_t order);
	Term(const Term &obj);
	Term(std::vector<Token> tokens);
	~Term();
	Term &operator=(const Term &obj);

	void print() const;
	std::string to_string() const;

	double number;
	size_t order; // todo: order can not be negative

private:

};

#endif
