#ifndef ENUMS_H
# define ENUMS_H

/*
enums
*/
enum TokenSymbol {
	PLUS_SYMBOL,
	MINUS_SYMBOL,
	STAR_SYMBOL,
	POWER_SYMBOL,
	EQUALS_SYMBOL,
	X_CHAR,
	NON_SYMBOL
};

enum TokenType {
	SYMBOL,
	NUMBER
};

enum TokenizerState {
	NEWTOKEN,
	READING_NUMBER
};

#endif
