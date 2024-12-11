# MAKEFILE
#

SOURCE=..
DESTINATION=$(SOURCE)/../build
CFLAGS=-lm -lcriterion
CC=gcc

$(DESTINATION)/testRunner: $(SOURCE)/lexer.h ./lexer.test.c
	$(CC) ./lexer.test.c $(CFLAGS) -o $(DESTINATION)/testRunner

