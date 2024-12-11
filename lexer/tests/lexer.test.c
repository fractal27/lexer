/* this file is lexer.test.c v0.3.0
 * Copyright (C) fractal27 (giacomo.dominici07@gmail.com)
 *======================================================
 * Must be compiled with `-lm lexer.c -lcriterion`
 * and criterion c testing framework must be
 * installed in the end machine.
 */

#include <stdio.h>
#include <criterion/criterion.h>
#define LEXER_H_IMPLEMENTATION
#include "../lexer.h"


static void teardown(void){}

Test(str_num, lexer,.fini = teardown) {
  lexer l;
  char* originalptr = malloc(sizeof(char)*100);
  l.text = originalptr;
  strcpy(l.text,"\"hello\"123");
  lexer newl = collect_tokens(l);

  cr_assert(newl.tokens[0] == string,"Token String(0)");
  cr_assert(!strcmp(newl.values[0].string, "hello"),"Value String(0)");
  cr_assert(newl.tokens[1] == number,"Token Number(1)");
  cr_assert(newl.values[1].i32 == 123,"Value of Number(1)");
  free(originalptr);
}

Test(beg_beg_num_end_end, lexer,.fini = teardown) {
  lexer l;
  char* originalptr = malloc(sizeof(char)*100);
  l.text = originalptr;
  strcpy(l.text,"::123..");
  lexer newl = collect_tokens(l);

  cr_assert(newl.tokens[0] == begin,"Token Begin(0)");
  cr_assert(newl.tokens[1] == begin,"Token Begin(1)");
  cr_assert(newl.tokens[2] == number,"Token Number(2)");
  cr_assert(newl.tokens[3] == end,"Token of End(3)");
  cr_assert(newl.tokens[4] == end,"Token End(4)");

  cr_assert(newl.values[0].other == NULL,"Value of Begin(0)");
  cr_assert(newl.values[1].other == NULL,"Begin(1)");
  cr_assert(newl.values[2].i32 == 123,"Value of Number(2)");
  cr_assert(newl.values[3].other == NULL,"Value of End(3)");
  cr_assert(newl.values[4].other == NULL,"Value of End(4)");

  free(originalptr);
}

Test(if_lpar_num_rpar_beg_id_ass_id_mult_id_end, lexer,  .fini= teardown){
  lexer l;
  char* originalptr =malloc(sizeof(char)*100);
  l.text = originalptr;
  strcpy(l.text,"if(1):id1=id2*id3.");
  lexer newl = collect_tokens(l);
  
  cr_assert(newl.tokens[0]==if_,"Token If(0)");
  cr_assert(newl.tokens[1]==lpar,"Token Lpar(1)");
  cr_assert(newl.tokens[2]==number,"Token Number(2)");
  cr_assert(newl.tokens[3]==rpar,"Token Rpar(3)");
  cr_assert(newl.tokens[4]==begin,"Token Begin(4)");
  cr_assert(newl.tokens[5]==id,"Token ID(5)");
  cr_assert(newl.tokens[6]==assign,"Token assignment(6)");
  cr_assert(newl.tokens[7]==id,"Token ID(7)");
  cr_assert(newl.tokens[8]==mult,"Token *(8)");
  cr_assert(newl.tokens[9]==id,"Token ID(9)");
  cr_assert(newl.tokens[10]==end,"Token End(10)");

  cr_assert(newl.values[0].other==TERMINAL,"Token If(0)");
  cr_assert(newl.values[1].other==TERMINAL,"Token Lpar(1)");
  cr_assert(newl.values[2].i32==1,"Token Number(2)");
  cr_assert(newl.values[3].other==TERMINAL,"Token Rpar(3)");
  cr_assert(newl.values[4].other==TERMINAL,"Token Begin(4)");
  cr_assert(!strcmp(newl.values[5].string,"id1"),"Token ID(5)");
  cr_assert(newl.values[6].other==(void*)OPERATOR,"Token assignment(6)");
  cr_assert(!strcmp(newl.values[7].string,"id2"),"Token ID(7)");
  cr_assert(newl.values[8].other==(void*)OPERATOR,"Token *(8)");
  cr_assert(!strcmp(newl.values[9].string,"id3"),"Token ID(9)");
  cr_assert(newl.values[10].other==TERMINAL,"Token End(10)");

  free(originalptr);
}

Test(if_lpar_num_rpar_beg_id_ass_id_sc_else_begin_id_ass_num_sc_end, lexer,  .fini = teardown){
  lexer l;
  char* originalptr = malloc(sizeof(char)*100);
  l.text = originalptr;
  strcpy(l.text,"if(1): id1=id2;"
                "else:  id3=3;"
                ".");
  lexer newl = collect_tokens(l);
  cr_assert(newl.tokens[0]==if_,"Token If(0)");
  cr_assert(newl.tokens[1]==lpar,"Token Lpar(1)");
  cr_assert(newl.tokens[2]==number,"Token Number(2)");
  cr_assert(newl.tokens[3]==rpar,"Token Rpar(3)");
  cr_assert(newl.tokens[4]==begin,"Token Begin(4)");
  cr_assert(newl.tokens[5]==id,"Token ID(5)");
  cr_assert(newl.tokens[6]==assign,"Token assignment(6)");
  cr_assert(newl.tokens[7]==id,"Token ID(7)");
  cr_assert(newl.tokens[8]==lineseparator,"Token Semicolon(8)");
  cr_assert(newl.tokens[9]==else_,"Token Else(9)");
  cr_assert(newl.tokens[10]==begin,"Token Begin(10)");
  cr_assert(newl.tokens[11]==id,"Token ID(11)");
  cr_assert(newl.tokens[12]==assign,"Token Assignment(12)");
  cr_assert(newl.tokens[13]==number,"Token ID(13)");
  cr_assert(newl.tokens[14]==lineseparator,"Token Semicolon(14)");
  cr_assert(newl.tokens[15]==end,"Token End(15)");

  cr_assert(newl.values[0].other==TERMINAL,"Value of If(0)");
  cr_assert(newl.values[1].other==TERMINAL,"Value of Lpar(1)");
  cr_assert(newl.values[2].i32==1,"Value of Number(2)");
  cr_assert(newl.values[3].other==TERMINAL,"Value of Rpar(3)");
  cr_assert(newl.values[4].other==TERMINAL,"Value of Begin(4)");
  cr_assert(!strcmp(newl.values[5].string,"id1"),"Value of ID(5)");
  cr_assert(newl.values[6].other==(void*)OPERATOR,"Value of Assignment(6)");
  cr_assert(!strcmp(newl.values[7].string,"id2"),"Value of ID(7)");
  cr_assert(newl.values[8].other==TERMINAL,"Value of Semicolon(8)");
  cr_assert(newl.values[9].other==TERMINAL,"Value of Else(9)");
  cr_assert(newl.values[10].other==TERMINAL,"Value of Begin(10)");
  cr_assert(!strcmp(newl.values[11].string,"id3"),"Value of ID(11)");
  cr_assert(newl.values[12].other=(void*)OPERATOR,"Value of Assignment(12)");
  cr_assert(newl.values[13].i32==3,"Value of Number(13)");
  cr_assert(newl.values[14].other==TERMINAL,"Value of Semicolon(14)");
  cr_assert(newl.values[15].other==TERMINAL,"Value of End(15)");
  free(originalptr);
}
