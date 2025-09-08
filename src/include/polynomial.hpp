#ifndef POLYNOMIAL_H
# define POLYNOMIAL_H

#include <string>

class Polynomial {
public:
    Polynomial();
    Polynomial(const Polynomial &obj);
    ~Polynomial();
    Polynomial &operator=(const Polynomial &obj);

private:
    double determinant;
};

#endif
