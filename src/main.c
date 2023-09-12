#include <stdio.h>
#include <stdlib.h>

#include "debug_print.h"
#include "parse.h"
#include "tokenizer.h"

#define BUFFER_SIZE 1024

int
main(int argc, char const **argv) {
	char *buffer = NULL;

	if (argc > 2) {
		char const *filename = argv[1];

		FILE *const file = fopen(filename, "r");

		if (!file) {
			fprintf(stderr, "Failed to open %s", filename);
			return 1;
		}

		fseek(file, 0, SEEK_END);
		long const size = ftell(file);
		rewind(file);

		buffer = malloc(size + 1);
		fread(buffer, sizeof *buffer, size, file);
		buffer[size] = '\0';

		fclose(file);
	} else {
		buffer = malloc(BUFFER_SIZE * sizeof *buffer);
		fgets(buffer, BUFFER_SIZE, stdin);
	}

	Tokenizer tokenizer = create_tokenizer(buffer);
	Expr *root = parse_additive(&tokenizer);
	print_expr_ast(root);
	free_expr_tree(root);

	free(buffer);
}
