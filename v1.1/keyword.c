#include "keyword.h"
#include "alex.h"
#include <stdio.h>
#include <string.h>
/* Funkcja porównóje podany ident z tablicą słów kluczowych - jeśli chociaż jedno z nich bedzie sie zgadzac funkcja zwroci KEY */
lexem_t isKeyword(char* ident){
	char keyword [33][10] = {"for", "printf", "getc", "int", "include", "if", "while", "fopen", 
	"malloc", "calloc", "realloc", "free", "fgetc", "strcmp", "strcpy", "abs", "fabs",
	"fclose", "atoi", "atof", "assert", "abort", "sqrt", "strcat", "exit", "fprintf", "switch",
       	"isdigit", "isspace", "ungetc", "isalpha"};
	int i = 0;
	for (i=0; i<33; i++){
		if(strcmp(keyword[i], ident) == 0)
			return KEY;
	}
	return IDENT;
}
