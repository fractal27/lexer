# lexer

lexer project implemented in c that provides an example for a shared library lexer.
Turns a string(array of char), into an array of `token_t` in C using the as-type-defined struct `lexer_t` as a building block.
The entire implementation is all in [one file](lexer/lexer.h) stb-style (including the file will get you the 
header definitions, but defining `LEXER_IMPLEMENTATION` will get the c implementation).

---
