#ifndef POLYNOMIAL_H
# define POLYNOMIAL_H

#include "term.hpp"
#include "enums.hpp"
#include <vector>

class Polynomial {
public:
	Polynomial() = delete;
	Polynomial(const std::vector<Token> tokens);
	Polynomial(const Polynomial &obj);
	~Polynomial();
	Polynomial &operator=(const Polynomial &obj);

	void solve();
	void print();

private:
	// state
	PolynomialState solution_state = PARSED_INPUT;
	bool has_indeterminate = false;

	// parsed input
	std::vector<Term> lhs_terms;
	std::vector<Term> rhs_terms;

	// normalized form
	int a_order_two = 0;
	int b_order_one = 0;
	int c_constant = 0;

	// solution
	double discriminant;
	std::vector<double> solutions;
};

#endif
