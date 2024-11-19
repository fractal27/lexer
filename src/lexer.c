#include <stdio.h>
#include <math.h>
#include "lexer.h"
#include <ctype.h>
#include "debugging.h"

long int intptoll(int* intp, size_t size){
	/*Converts a series of digits into a single long digit.*/

	long int number = 0;

#if defined(CAPTURE_DEBUG) || defined(DEBUG_ALL)
  printf("\t(intptoll): Begin number convertion process\n");//FDP
#if defined(CAPTURE_DEBUG_ADV) || defined(DEBUG_ALL)
  printf("\t(intptoll): |");
#endif
#endif

	for(int i = 0; i<size-1; i++){

#if defined(CAPTURE_DEBUG_ADV) || defined(DEBUG_ALL)
		printf(" %ld ->",number); //FDP
#endif

		number += (long)(pow(10,i)*intp[size-i-1]);
  }

#if defined(CAPTURE_DEBUG_ADV) || defined(DEBUG_ALL)
  printf("| -> `%ld`!\n",number);  //FDP
#endif

	return number;
}

bool separated(char c){
  return isspace(c) || c == '(' || c == '"' || c == '\'' || c == ')' || c == '+' || c == '*' || c == '-' || c == '/' || c == '=' || c == '.' || c == ';';
}

lexer collect_tokens(lexer l){
  /* Restituisce un altro lexer con gli attributi aggiornati dopo la computazione.
     *anchored: se true cambia il lexer originale.
   * */


	token_t* tokens = (token_t*)malloc(sizeof(token_t)*MAX_TOKENS);
	value* values = (value*)malloc(sizeof(value)*MAX_TOKENS);
	char* text = (char*)(l.text);
	int* buffer2 = malloc(sizeof(int)*MAX_TOKENS); //for int tokens
	char* buffer3 = malloc(sizeof(char)*MAX_TOKENS);//for string tokens.
	char* buffer4 = malloc(sizeof(char)*MAX_TOKENS);//for string tokens.
	size_t bsize = 0; // buffer1 size
	size_t vsize = 0; // values size
	size_t j = 1; //to take track of the number of characters thus far.
	size_t i = 0;
	long int lint;

#if defined(CAPTURE_DEBUG) || defined(DEBUG_ALL)
  printf("[.] Begin Tokenization process of `%s`\n",text);
#endif
	while(*text!= '\0' && j < MAX_TOKENS) {
#ifdef DEBUG_ALL
    printf("*text: `%c`;\n",*text);
#endif
		if(isdigit(*text)){
			// initialize buffer2,i for int incapsulation.
			i = 0;
			buffer2[i++] = *text-'0';

#if defined(CAPTURE_DEBUG) || defined(DEBUG_ALL)
      printf("------- CAPTURED INT ------\n"); //FDP
#ifdef CAPTURE_DEBUG_ADV
      printf("(int capture): {"); //FDP
#endif
#endif

			//capture a literal(int)
			while(isdigit(*text)){

#if defined(CAPTURE_DEBUG_ADV) || defined(DEBUG_ALL)
				printf(" `%d`,",*text-'0');
#endif

				buffer2[i++] = (int)(*(text++)-'0');
			}

#if defined(CAPTURE_DEBUG_ADV) || defined(DEBUG_ALL)
      printf("}\n");
#endif

			// reset buffer to current position
			j = 1;
			lint = intptoll(buffer2,i);

#if defined(CAPTURE_DEBUG_ADV) || defined(DEBUG_ALL)
      printf("captured lint: %ld\n",lint);
#endif


			tokens[vsize] = number;
			values[vsize++].i32 = lint;
      j++;
			continue;

		} else if (*text == '"'){
			//initialiing buffer3,i for string incapsulation

			text++;
			i = 0;
			buffer3[i++] = *(text++);

#if defined(CAPTURE_DEBUG) || defined(DEBUG_ALL)
      printf("----- CAPTURED STRING -----\n|"); //FDP
#endif
#if defined(CAPTURE_DEBUG_ADV) || defined(DEBUG_ALL)
      printf("(string capture): {");
#endif
			//get the text of the string ("<text>")
			while(text != NULL && *text != '"' && *text != '\0'){

#if defined(CAPTURE_DEBUG_ADV) || defined(DEBUG_ALL)
				printf(" %c ,",*(text-1)); //FDP
#endif
        buffer3[i++] = *(text++);
			}
#if defined(CAPTURE_DEBUG_ADV) || defined(DEBUG_ALL)
			printf(" %c}\n",*(text-1)); //FDP
#endif

			buffer3[i] = '\0';
			j = 1;

#ifdef DEBUG_BUFFER3
			printf("buffer3: %s\n",buffer3); // FDP
			printf("text: `%s`\n",text); // FDP
#endif

			tokens[vsize] = string;
      values[vsize].string = malloc(sizeof(char)*MAX_STRING);
			strcpy(values[vsize].string,buffer3);
      vsize++;
      text++;
      j++;

			continue;

		} else if(*text=='('){

#if defined(CAPTURE_DEBUG) || defined(DEBUG_ALL)
      printf("----- CAPTURED LPAR -----\n"); //FDP
#endif

      tokens[vsize] = lpar;
      values[vsize++].other = NULL;
    } else if(*text==')'){

#if defined(CAPTURE_DEBUG) || defined(DEBUG_ALL)
			printf("----- CAPTURED RPAR -----\n"); //FDP
#endif

      tokens[vsize] = rpar;
      values[vsize++].other = NULL;
    } else if(*text==':'){

#if defined(CAPTURE_DEBUG) || defined(DEBUG_ALL)
			printf("----- CAPTURED BEGIN -----\n"); //FDP
#endif

      tokens[vsize] = begin;
      values[vsize++].other = NULL;
    } else if(*text=='.'){

#if defined(CAPTURE_DEBUG) || defined(DEBUG_ALL)
			printf("----- CAPTURED END -----\n"); //FDP
#endif

      tokens[vsize] = end;
      values[vsize++].other = NULL;
    } else if(*text==';'){
#if defined(CAPTURE_DEBUG) || defined(DEBUG_ALL)
			printf("----- CAPTURED ; -----\n"); //FDP
#endif

      tokens[vsize] = lineseparator;
      values[vsize++].other = NULL;

    } else if(*text=='*'){

#if defined(CAPTURE_DEBUG) || defined(DEBUG_ALL)
			printf("----- CAPTURED * -----\n"); //FDP
#endif

      tokens[vsize] = mult;
      values[vsize++].other = (void*)OPERATOR;
    } else if(*text=='+'){

#if defined(CAPTURE_DEBUG) || defined(DEBUG_ALL)
			printf("----- CAPTURED + -----\n"); //FDP
#endif

      tokens[vsize] = plus;
      values[vsize++].other = (void*)OPERATOR;
    } else if(*text=='-'){

#if defined(CAPTURE_DEBUG) || defined(DEBUG_ALL)
			printf("----- CAPTURED `-` -----\n"); //FDP
#endif

      tokens[vsize] = minus;
      values[vsize++].other = (void*)OPERATOR;
    } else if(*text=='>' && separated(*(text+1))){

#if defined(CAPTURE_DEBUG) || defined(DEBUG_ALL)
			printf("----- CAPTURED > -----\n"); //FDP
#endif

      tokens[vsize] = gt;
      values[vsize++].other = (void*)OPERATOR;
    } else if(*text=='<' && separated(*(text+1))){

#if defined(CAPTURE_DEBUG) || defined(DEBUG_ALL)
			printf("----- CAPTURED < -----\n"); //FDP
#endif

      tokens[vsize] = lt;
      values[vsize++].other = (void*)OPERATOR;
    } else if(*text=='=' && (!separated(*(text+1) || isspace(*(text+1)) || *(text+1)=='\'' || *(text+1)=='"' )||*(text+1)=='(')){

#if defined(CAPTURE_DEBUG) || defined(DEBUG_ALL)
			printf("----- CAPTURED ASSIGNMENT -----\n"); //FDP
#endif

      tokens[vsize] = assign;
      values[vsize++].other = (void*)OPERATOR;
    } else if(*text=='=' && *(text+1) == '=' && separated(*(text+2))){

#if defined(CAPTURE_DEBUG) || defined(DEBUG_ALL)
			printf("----- CAPTURED EQUALS -----\n"); //FDP
#endif

      tokens[vsize] = eq;
      values[vsize++].other = (void*)OPERATOR;
    } else if(*text=='>' && *(text+1) == '=' && separated(*(text+2))){

#if defined(CAPTURE_DEBUG) || defined(DEBUG_ALL)
			printf("----- CAPTURED COMPARISON >= -----\n"); //FDP
#endif

      tokens[vsize] = ge;
      values[vsize++].other = (void*)OPERATOR;

    } else if(*text=='<' && *(text+1) == '=' && separated(*(text+2))){

#if defined(CAPTURE_DEBUG) || defined(DEBUG_ALL)
			printf("----- CAPTURED COMPARISON <= -----\n"); //FDP
#endif

      tokens[vsize] = le;
      values[vsize++].other = (void*)OPERATOR;

    } else if(*text=='i' && *(text+1)=='f' && separated(*(text+2))){

#if defined(CAPTURE_DEBUG) || defined(DEBUG_ALL)
			printf("----- CAPTURED IF -----\n"); //FDP
#endif

      tokens[vsize] = if_;
      values[vsize++].other = NULL;

      text+=2;
      continue;
    } else if(!strncmp(text,"else",4) && separated(*(text+5))){

#if defined(CAPTURE_DEBUG) || defined(DEBUG_ALL)
			printf("----- CAPTURED ELSE -----\n"); //FDP
#endif

      tokens[vsize] = else_;
      values[vsize++].other = NULL;
      j++;
      text += 4;
      continue;
    } else if(isspace(*text)){
#if defined(CAPTURE_DEBUG) || defined(DEBUG_ALL)
      printf("------- CAPTURED SPACE-LIKE -------\n");
#endif
      j++;
      text++;
      continue;
    } else {
      // TODO: error handling.

#if defined(CAPTURE_DEBUG) || defined(DEBUG_ALL)
			printf("----- CAPTURED ID -----\n"); //FDP
#ifdef CAPTURE_DEBUG_ADV
      printf("(id capture): {"); //FDP
#endif
#endif

      i = 0;
      buffer4[i++] = *(text++);

      while(text != NULL && *text != '\0' && !separated(*text)){

#if defined(CAPTURE_DEBUG_ADV) || defined(DEBUG_ALL)
        printf(" %c,",*(text-1)); //FDP
#endif
        buffer4[i++] = *(text++);
      }

      buffer4[i] = '\0';

#if defined(CAPTURE_DEBUG_ADV) || defined(DEBUG_ALL)
      printf(" %c}\nbuffer4:\"%s\"\n",*(text-1),buffer4); //FDP
#endif

      tokens[vsize] = id;
      values[vsize].string = malloc(sizeof(char)*MAX_STRING);
      strcpy(values[vsize].string,buffer4);
      vsize++;
      j++;
      continue;
		}

		j++;
		text++;
	}

  free(buffer2);
  free(buffer3);
  free(buffer4);

	lexer lfinished = l;
	lfinished.value_size = vsize;
	lfinished.tokens_size = vsize;
	lfinished.values = values;
	lfinished.tokens = tokens;
  lfinished.is_collected = true;
	return lfinished;
}


