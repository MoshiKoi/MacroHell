#pragma once
#ifndef EXPR_H
#define EXPR_H

#include "tokenizer.h"

#define X_EXPR_LIST \
	X_EXPR(INTEGER, Integer, integer, FIELD(unsigned long, value,)) \
	X_EXPR( \
		BINARY_OPERATOR, BinaryOperator, binary_operator, \
		FIELD(TokenType, op,) FIELD(Expr *, left, free_expr_tree) FIELD(Expr *, right, free_expr_tree))

#define X_EXPR(ENUM_NAME, ...) EXPR_##ENUM_NAME,

typedef enum ExprType { X_EXPR_LIST } ExprType;

#undef X_EXPR
#define FIELD(TYPE, NAME, ...) TYPE NAME;

#define X_EXPR(ENUM_NAME, STRUCT_NAME, UNION_NAME, FIELDS) \
	typedef struct STRUCT_NAME { \
		FIELDS \
	} STRUCT_NAME;

typedef struct Expr Expr;

X_EXPR_LIST

#undef X_EXPR
#undef FIELD

#define X_EXPR(ENUM_NAME, STRUCT_NAME, UNION_NAME, FIELDS) STRUCT_NAME UNION_NAME;

struct Expr {
	ExprType type;
	union {
		X_EXPR_LIST
	};
};

#undef X_EXPR

void free_expr_tree(Expr *);

#endif
