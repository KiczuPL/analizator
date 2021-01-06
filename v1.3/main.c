#include "parser.h"
#include "store.h"
#include "inc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  char *inpname;
  char opcja[] = "-inc";
  int i=0;
  if (strcmp(argv[1], opcja)==0){
	  printf("---Biblioteki zawarte w:\n");
	  for(i=1; i<argc-1; i++){
		  printf("---Pliku %s \n", argv[i+1]);
		  include_find(argv[i+1]);
	  }
	  i=1;
  }
  for (i; i < argc - 1; i++) {
    inpname = argv[i + 1];
    analizatorSkladni(inpname);
  }
  printf("-----------------------\n");
  printf("Funkcje w podanych plikach %s: \n", inpname);
  store_print();
  printf("-----------------------\n");
  store_clear();
  return 0;
}
