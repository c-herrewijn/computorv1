#include "polynomial.hpp"

Polynomial::Polynomial() {}
Polynomial::~Polynomial() {}

Polynomial::Polynomial(const Polynomial &obj) {
    *this = obj;
}

Polynomial &Polynomial::operator=(const Polynomial &obj)
{
    this->determinant = obj.determinant;
    return *this;
}
