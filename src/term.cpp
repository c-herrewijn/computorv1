#include "term.hpp"

#include <string>
#include <vector>
#include <iostream>

/*
constructors
*/
Term::Term(int number, int degree) : number(number), degree(degree) {}
Term::Term(const Term &obj) {
	*this = obj;
}
Term::~Term() {}

/*
operators
*/
Term &Term::operator=(const Term &obj) {
	this->number = obj.number;
	this->degree = obj.degree;
	return *this;
}

/*
member functions
*/
std::string Term::to_string() const {
	std::string str;
	if (number == 0) {
		return std::string("0");
	}
	if (number != 1) {
		str.append(std::to_string(number));
		if (degree != 0) {
			str.append(" * ");
		}
	}
	if (degree != 0) {
		str.append("X^");
		str.append(std::to_string(degree));
	}
	return str;
}

void Term::print() const {
	std::cout << this->to_string() << std::endl;;
}
