#include <stdio.h>

#include "debug_print.h"
#include "expr.h"

void
print_ul(unsigned long value, int indent_level) {
	printf("%lu\n", value);
}

void
print_token_type(TokenType type, int indent_level) {
	switch (type) {
#define X_TOKEN_TYPE(TOKEN_TYPE) \
	case TOKEN_TYPE: puts(#TOKEN_TYPE); break;
		X_TOKEN_TYPE_LIST
#undef X_TOKEN_TYPE
	}
}

void print_expr_ast_impl(Expr *expr, int indent_level);

#define PRINT(x) \
	_Generic((x), Expr *: print_expr_ast_impl, TokenType: print_token_type, unsigned long: print_ul)( \
		x, indent_level + 1);

#define FIELD(TYPE, NAME, _) \
	for (int i = 0; i < indent_level; ++i) { \
		fputs("  ", stdout); \
	} \
	PRINT(specific_expr.NAME)

#define X_EXPR(TYPE, STRUCT_NAME, UNION_NAME, FIELDS) \
	void print_##UNION_NAME(STRUCT_NAME specific_expr, int indent_level) { \
		FIELDS \
	}

X_EXPR_LIST

#undef X_EXPR

void
print_expr_ast_impl(Expr *expr, int indent_level) {
	if (!expr) {
		puts("NULL");
		return;
	}

	switch (expr->type) {
#define X_EXPR(TYPE, STRUCT_NAME, UNION_NAME, FIELDS) \
	case EXPR_##TYPE: \
		puts(#TYPE ":"); \
		print_##UNION_NAME(expr->UNION_NAME, indent_level); \
		break;

		X_EXPR_LIST

#undef X_EXPR
	}
}

void
print_expr_ast(Expr *expr) {
	print_expr_ast_impl(expr, 1);
}
