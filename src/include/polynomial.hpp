#ifndef POLYNOMIAL_H
# define POLYNOMIAL_H

#include "term.hpp"
#include "enums.hpp"
#include <vector>
#include <map>

class Polynomial {
public:
	Polynomial() = delete;
	Polynomial(const std::vector<Token> tokens);
	Polynomial(const Polynomial &obj);
	~Polynomial();
	Polynomial &operator=(const Polynomial &obj);

	void normalize();
	void print_normalzed() const; // TODO: formating mandatory part
	void print_normalzed_simplified() const; // TODO: formatting bonus
	size_t get_order() const;

	void solve(); // TODO:implement abc-formula
	void print() const; // debug

private:
	// state
	PolynomialState solution_state = PARSED_INPUT;
	bool has_indeterminate = false; // TODO: special output for equations without 'X'

	// parsed input
	std::vector<Term> lhs_terms;
	std::vector<Term> rhs_terms;

	// normalized form: key=order; value=coefficient
	std::map<size_t, int> normalized_coefficients; // TODO: support decimal numbers!

	// solution
	double discriminant;
	std::vector<double> solutions;
};

#endif
