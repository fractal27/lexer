# MAKEFILE
#

DEST=../../dest
SRC=..
CC=gcc
CFLAGS=-lm -lcriterion

$(DEST)/lexer_test: $(SRC)/lexer.c ./test_lexer.c
	$(CC) ./test_lexer.c $(SRC)/lexer.c $(CFLAGS) -o $(DEST)/lexer_test

