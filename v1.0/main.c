#include "parser.h"
#include "store.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	char *inpname;
	int i;
	for(i=0; i<argc-1; i++){
		inpname = argv[i+1];
		analizatorSkladni(inpname);
		printf("------------------- \n");
		printf("Funkcje w pliku %s: \n", inpname);
		store_print();
		store_clear();
		printf("------------------- \n");
	}
	return 0;
}
	
