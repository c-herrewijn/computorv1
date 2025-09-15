#include "utils.hpp"

#include <string>
#include <iostream>
#include <limits>

int str_to_int(std::string number_str) {
	if (number_str.size() > 11) { // 10 chars for max_int + 1 char for minus sign
		// not numbers like 00000000000000042 might not be too large, after all
		std::cout << "number in equation to large: '" << number_str << "'" << std::endl;
		exit(EXIT_FAILURE);
	}
	long long_num = std::stol(number_str);
	if (long_num > std::numeric_limits<int>::max()) {
		std::cout << "number in equation to large: '" << number_str << "'" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (long_num < std::numeric_limits<int>::min()) {
		std::cout << "number in equation to small: '" << number_str << "'" << std::endl;
		exit(EXIT_FAILURE);
	}
	int num = static_cast<int>(long_num);
	return num;
}
