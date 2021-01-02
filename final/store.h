#ifndef _STORE_H_IS_INCLUDED_
#define _STORE_H_IS_INCLUDED_
#include "fun_stack.h"
#include "alex.h"
void store_add_def (char* funame, int ln, char* inpname);
void store_add_proto (char* funame, int ln, char* inpname);
void store_add_call (char* funame, int ln, char* inpname);
void store_print();
void store_clear();
#endif
