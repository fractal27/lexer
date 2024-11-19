# |--- MAKEFILE FOR ASSEMBLING THE PSEUDOCOMPILER ---|
# |--------------------------------------------------|



# constants
DESTINATION=dest
SOURCE=src
OBJECT_LEXER=$(DESTINATION)/lexer.o
SOURCE_LEXER=$(SOURCE)/lexer.c
CC=gcc

all: liblexer.so $(OBJECT_LEXER)

liblexer.so: $(OBJECT_LEXER)
	$(CC) -shared -o $(DESTINATION)/liblexer.so $(OBJECT_LEXER)

$(OBJECT_LEXER): $(SOURCE_LEXER)
	$(CC) -lm -c $(SOURCE_LEXER) -o $(OBJECT_LEXER)

test: src/tests/Makefile src/tests/test_lexer.c
	cd src/tests && $(MAKE)

.PHONY: test all

