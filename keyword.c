#include "keyword.h"
#include "alex.h"
#include <stdio.h>
#include <string.h>
lexem_t isKeyword(char* ident){
	//printf("Keyword bada: %s\n", ident);
	if(strcmp(ident, "printf")==0 || strcmp(ident, "getc")==0 || strcmp(ident, "int")==0
			|| strcmp(ident, "include")==0){ 
	//	printf("Keyword ---- ignore\n");
		return OTHER;
	} else {
	//	printf("%s to identyfikator \n", ident);
		return IDENT;
	}
}
