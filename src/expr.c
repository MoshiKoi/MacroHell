#include <stdlib.h>

#include "expr.h"

#define FIELD(TYPE, NAME, ...) __VA_OPT__(__VA_ARGS__(specific_expr.NAME);)
#define X_EXPR(TYPE, STRUCT_NAME, UNION_NAME, FIELDS) \
	void free_##UNION_NAME(STRUCT_NAME specific_expr) { \
		FIELDS \
	}

X_EXPR_LIST

#undef X_EXPR

void
free_expr_tree(Expr *expr) {
	if (!expr) {
		return;
	}
	
	switch (expr->type) {
#define X_EXPR(TYPE, STRUCT_NAME, UNION_NAME, FIELDS) \
	case EXPR_##TYPE: free_##UNION_NAME(expr->UNION_NAME); break;

		X_EXPR_LIST

#undef X_EXPR
	}

	free(expr);
}
