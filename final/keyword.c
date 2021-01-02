#include "keyword.h"
#include "alex.h"
#include <stdio.h>
#include <string.h>
lexem_t isKeyword(char* ident){
	char keyword [7][10] = {"for", "printf", "getc", "int", "include", "if", "while"};
	int i = 0;
	for (i=0; i<7; i++){
		if(strcmp(keyword[i], ident) == 0)
			return KEY;
	}
	return IDENT;
}
