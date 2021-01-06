#include "parser.h"
#include "store.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  char *inpname;
  int i;
  for (i = 0; i < argc - 1; i++) {
    inpname = argv[i + 1];
    analizatorSkladni(inpname);
  }
  printf("-----------------------\n");
  printf("Funkcje w podanych plikach: \n");
  store_print();
  printf("-----------------------\n");
  store_clear();
  return 0;
}
