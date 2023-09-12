#pragma once
#ifndef PARSE_H
#define PARSE_H

#include "expr.h"
#include "tokenizer.h"

Expr *parse_primary(Tokenizer *);

#define X_BINARY_LIST \
	X_BINARY(parse_multiplicative, parse_primary, TOKEN_TYPE(TOKEN_MUL) TOKEN_TYPE(TOKEN_DIV)) \
	X_BINARY(parse_additive, parse_multiplicative, TOKEN_TYPE(TOKEN_PLUS) TOKEN_TYPE(TOKEN_MINUS) TOKEN_TYPE(TOKEN_MOD))

#define X_BINARY(NAME, NEXT, TOKENS) Expr *NAME(Tokenizer *);

X_BINARY_LIST

#undef X_BINARY

#endif
