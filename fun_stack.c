//#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fun_stack.h"

static stack_t* stack = NULL;

int top_of_funstack() {
	return stack->npar;
}

void put_on_fun_stack(int par_level, char* funame) {
	if (stack == NULL) {
		if ((stack = malloc(sizeof(stack_t))) != NULL) {
			stack->iname = malloc(sizeof(stack->iname) * (strlen(funame) + 1));
			stack->next = NULL;

			stack->npar = par_level;
			strcpy(stack->iname, funame);
		}
	}
	else {
		stack_t* new;
			if ((new = malloc(sizeof(stack_t))) != NULL) {
			new->iname = malloc(sizeof(stack->iname) * (strlen(funame) + 1));

			new->npar = par_level;
			strcpy(new->iname, funame);

			new->next = stack;
			stack = new;
			}
		}
}

char* get_from_fun_stack() {
	char* name = NULL;
	if (stack != NULL) {
		name = malloc(sizeof(stack->iname) * (strlen(stack->iname) + 1));
		stack_t* tmp = stack;
		strcpy(name, stack->iname);
		free(stack->iname);
		stack = stack->next;
		free(tmp);
	}
	return name;
}