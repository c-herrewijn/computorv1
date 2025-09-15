#ifndef POLYNOMIAL_H
# define POLYNOMIAL_H

class Polynomial {
public:
	Polynomial();
	Polynomial(const Polynomial &obj);
	~Polynomial();
	Polynomial &operator=(const Polynomial &obj);

	int lhs_const = 0;
	int lhs_degree_one = 0;
	int lhs_degree_two = 0;
	int rhs_const = 0;
	int rhs_degree_one = 0;
	int rhs_degree_two = 0;

	double discriminant;

private:
};

#endif
