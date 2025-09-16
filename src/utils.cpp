#include "utils.hpp"

#include <string>
#include <iostream>
#include <limits>
#include <cctype>

size_t str_to_size_t(std::string number_str) {
	for (const char c : number_str) {
		if (!isdigit(c)) {
			std::cout << "Error: string should only contain digits: " << number_str <<
			          std::endl;
			exit(EXIT_FAILURE);
		}
	}
	if (number_str.size() > 10) { // 10 chars for max_int
		std::cout << "number in equation to large: '" << number_str << "'" << std::endl;
		exit(EXIT_FAILURE);
	}
	long long long_num = std::stoll(number_str);
	if (long_num > std::numeric_limits<int>::max()) {
		std::cout << "number in equation to large: '" << number_str << "'" << std::endl;
		exit(EXIT_FAILURE);
	}
	size_t num = static_cast<size_t>(long_num);
	return num;
}
