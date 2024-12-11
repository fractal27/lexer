# |--- MAKEFILE FOR ASSEMBLING THE PSEUDOCOMPILER ---|
# |--------------------------------------------------|

# constants
SOURCE=lexer
DESTINATION=$(SOURCE)/../build
#SOURCE_LEXER=$(SOURCE)/lexer.h
#OBJECT_LEXER=$(DESTINATION)/lexer.o
#TARGET_LEXER=$(DESTINATION)/liblexer.so
TEST=$(SOURCE)/tests
SOURCE_TEST=$(TEST)/lexer.test.c
CC=gcc


# Functions

#all: $(DESTINATION) $(OBJECT_LEXER) $(TARGET_LEXER)
all: $(DESTINATION)

$(DESTINATION):
	mkdir -p $(DESTINATION)


test:
	cd $(TEST) && $(MAKE)
	$(DESTINATION)/testRunner --verbose

clean: $(OBJECT_LEXER)
	rm $(DESTINATION)/*.*o $(DESTINATION)/testRunner

# Commands
.PHONY: test all clean

