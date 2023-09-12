#include <stdlib.h>

#include "parse.h"

#define TOKEN_TYPE(NAME) || tokenizer->current_token.type == NAME
#define X_BINARY(NAME, NEXT, TOKENS) \
	Expr *NAME(Tokenizer *tokenizer) { \
		Expr *left = NEXT(tokenizer); \
		while (false TOKENS) { \
			TokenType op = tokenizer->current_token.type; \
			next_token(tokenizer); \
			Expr *right = NEXT(tokenizer); \
			Expr *node = malloc(sizeof *node); \
			node->type = EXPR_BINARY_OPERATOR; \
			node->binary_operator = (BinaryOperator){op, left, right}; \
			left = node; \
		} \
		return left; \
	}

X_BINARY_LIST

Expr *
parse_primary(Tokenizer *tokenizer) {
	if (tokenizer->current_token.type == TOKEN_INTEGER) {
		Expr *expr = malloc(sizeof *expr);

		expr->type = EXPR_INTEGER;
		expr->integer = (Integer){tokenizer->current_token.int_value};

		next_token(tokenizer);
		return expr;
	} else {
		return nullptr;
	}
}
