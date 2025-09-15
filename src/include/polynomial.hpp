#ifndef POLYNOMIAL_H
# define POLYNOMIAL_H

class Polynomial {
public:
	Polynomial();
	Polynomial(const Polynomial &obj);
	~Polynomial();
	Polynomial &operator=(const Polynomial &obj);

private:
	double discriminant;
};

#endif
