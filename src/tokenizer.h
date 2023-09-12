#pragma once
#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdint.h>

#define X_TOKEN_TYPE_LIST \
	X_TOKEN_TYPE(TOKEN_END) \
	X_TOKEN_TYPE(TOKEN_ERROR) \
	X_TOKEN_TYPE(TOKEN_INTEGER) \
	X_TOKEN_TYPE(TOKEN_PLUS) \
	X_TOKEN_TYPE(TOKEN_MINUS) \
	X_TOKEN_TYPE(TOKEN_MUL) \
	X_TOKEN_TYPE(TOKEN_DIV) \
	X_TOKEN_TYPE(TOKEN_MOD)

#define X_TOKEN_TYPE(TOKEN_TYPE) TOKEN_TYPE,
typedef enum TokenType { X_TOKEN_TYPE_LIST } TokenType;
#undef X_TOKEN_TYPE

typedef struct Token {
	TokenType type;
	union {
		unsigned long int_value;
	};
} Token;

typedef struct Tokenizer {
	char const *cur;
	Token current_token;
} Tokenizer;

Tokenizer create_tokenizer(char const *begin);
void next_token(Tokenizer *);

#endif
