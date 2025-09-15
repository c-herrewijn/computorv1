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
	NEW_TOKEN,
	READING_NUMBER
};

enum ParserState {
	READING_NEW_TERM,
	READING_TERM_ORDER,
};

#endif
