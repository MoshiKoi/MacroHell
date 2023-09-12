#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "tokenizer.h"

Tokenizer
create_tokenizer(char const *buffer) {
	Tokenizer tokenizer = {
		.cur = buffer,
	};

	next_token(&tokenizer);

	return tokenizer;
}

void next_integer(Tokenizer *);

void
next_token(Tokenizer *tokenizer) {
	while (*tokenizer->cur) {
		if (isspace(*tokenizer->cur)) {
			++tokenizer->cur;
			continue;
		}

		switch (*tokenizer->cur) {

#define SYMBOL_CASE(CHAR, TOKEN_TYPE) \
	case CHAR: \
		tokenizer->current_token.type = TOKEN_TYPE; \
		++tokenizer->cur; \
		return;

			SYMBOL_CASE('+', TOKEN_PLUS)
			SYMBOL_CASE('-', TOKEN_MINUS)
			SYMBOL_CASE('*', TOKEN_MUL)
			SYMBOL_CASE('/', TOKEN_DIV)
			SYMBOL_CASE('%', TOKEN_MOD)

#undef SYMBOL_CASE

		case '0' ... '9': next_integer(tokenizer); return;
		default: tokenizer->current_token.type = TOKEN_ERROR; return;
		}
	}

	tokenizer->current_token.type = TOKEN_END;
}

void
next_integer(Tokenizer *tokenizer) {
	char const *begin = tokenizer->cur;
	char *end = NULL;

	unsigned long result = strtoull(begin, &end, 10);

	tokenizer->cur = end;
	tokenizer->current_token = (Token){
		.type = TOKEN_INTEGER,
		.int_value = result,
	};
}
