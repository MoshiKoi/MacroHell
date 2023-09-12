add_executable(main main.c)

add_library(Tokenizer tokenizer.c)
add_library(Parse parse.c)
add_library(Expr expr.c)
add_library(DebugPrint debug_print.c)
target_link_libraries(main Tokenizer Parse Expr DebugPrint)