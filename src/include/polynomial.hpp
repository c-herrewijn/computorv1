#ifndef POLYNOMIAL_H
# define POLYNOMIAL_H

#include "term.hpp"
#include <vector>

class Polynomial {
public:
	Polynomial();
	Polynomial(const Polynomial &obj);
	~Polynomial();
	Polynomial &operator=(const Polynomial &obj);

	std::vector<Term> lhs_terms;
	std::vector<Term> rhs_terms;

	// normalized form
	int constant = 0;
	int order_one = 0;
	int order_two = 0;

	double discriminant;

private:
};

#endif
