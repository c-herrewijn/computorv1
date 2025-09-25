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
	void print_normalzed() const;
	void print_normalzed_simplified() const;
	size_t get_order() const;
	void solve();

private:
	// state
	PolynomialState solution_state = PARSED_INPUT;
	bool has_indeterminate = false;

	// parsed input
	std::vector<Term> lhs_terms;
	std::vector<Term> rhs_terms;

	// normalized form: key=order; value=coefficient
	std::map<size_t, double> normalized_coefficients;
};

#endif
