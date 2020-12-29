#include "parser.h"
#include "store.h"

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv){
	char *inpname;
	if (argc>1){
		inpname = argv[1];
	} else return 1;
	analizatorSkladni(inpname);
	return 0;
}
	
