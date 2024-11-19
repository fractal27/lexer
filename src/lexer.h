#pragma once
#ifndef _LEXER_H
#define MAX_TOKENS 0xFFF
#define MAX_STRING 0xFFF
//4096
//#define FINISH_NUMBER 0xF8
//UNUSED REMOVE??
#define OPERATOR 0xf7ad0
#define TERMINAL NULL

#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


typedef enum etoken_t{
    lineseparator,
    if_,
    assign,
    eq,
    le,
    ge,
    gt,
    lt,
    else_,
    plus,
    minus,
    mult,
    fun,
    string,
    number,
    char_,
    lpar,
    rpar,
    id,
    begin,
    end
} token_t;

typedef struct {
    union {
        long long int i32;
        char* string;
        void* other;
    };
} value;

typedef struct slexer_skeleton /*used statically for syntax checking and analyzing.*/
{
  /*data*/
  const token_t* tokens;
  const size_t tokens_size;// = 0;

  const value* values;
  const size_t value_size; // = 0
} lexer_s;

typedef struct slexer
{
    /* data */
    token_t* tokens;
    size_t tokens_size;// = 0;

    value* values;
    size_t value_size; // = 0

    char* text;
    
    /*for short circuit optimization*/
    bool is_collected;
} lexer;

typedef struct spair {
    void* first;
    void* second;
} pair;

typedef struct {
  token_t* opts_tokens;
  size_t tokens_size;// = 0;

  value* opts_vals;
  size_t op_size;// = 0;

  token_t operation_token;
} opt_t; //operation type

typedef struct stoken_attrs{
	int precedence;
	bool righttoleft;
} tknattrs_t;


lexer collect_tokens(lexer l);

#endif

