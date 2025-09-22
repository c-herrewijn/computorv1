#include "utils.hpp"

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <cctype>
#include <cfloat>

double str_to_double(std::string number_str) {
	size_t num_period_chars = 0;
	for (const char &c : number_str) {
		if (!isdigit(c) && c != '.') {
			std::cout << "Error: string should only contain digits or a decimal point: " << number_str <<
			          std::endl;
			exit(EXIT_FAILURE);
		}
		if (c == '.') {
			num_period_chars++;
		}
		if (num_period_chars > 1) {
			std::cout << "Error: invalid number (too many decimal dots!): " << number_str << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	if (number_str.size() > DBL_DIG) {
		std::cout << "number in equation too precize: '" << number_str << "' (max precision is: " << DBL_DIG
		          << ")" << std::endl;
		exit(EXIT_FAILURE);
	}
	double num = std::stod(number_str);
	if (num > std::numeric_limits<int>::max()) {
		std::cout << "number in equation too large: '" << number_str << "'" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (num < std::numeric_limits<int>::min()) {
		std::cout << "number in equation too small: '" << number_str << "'" << std::endl;
		exit(EXIT_FAILURE);
	}
	return num;
}

std::string double_to_str(double d) {
	std::ostringstream ss;
	ss << std::setprecision(DBL_DIG) << d;
	return ss.str();
}
