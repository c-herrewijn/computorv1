#ifndef TERM_H
# define TERM_H

#include <string>

class Term {
public:
	Term() = delete;
	Term(int number, int degree);
	Term(const Term &obj);
	~Term();
	Term &operator=(const Term &obj);

	void print() const;
	std::string to_string() const;

	int number;
	int degree;

private:

};

#endif
