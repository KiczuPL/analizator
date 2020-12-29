#include "fun_stack.h"
#include "alex.h"
#include "store.h"
void store_add_def (char* funame,int ln, char* inpname){
printf("store_add_def dziala \n %s %d %s\n", funame, ln, inpname);
}
void store_add_proto (char* funame, int ln, char* inpname){
printf("store_add_proto dziala \n %s %d %s \n", funame, ln, inpname);
}
void store_add_call (char* funame, int ln, char* inpname){
printf("store_add_call dziala \n %s %d %s \n", funame, ln, inpname);
}
void store_print_def (char* funame){
	printf("store_print_def dziala \n");
}
void store_print_proto (char* funame){
	printf("store_print_proto dziala \n");
}
void store_print_call (char*funame){
	printf("store_print_proto dziala \n");
}
