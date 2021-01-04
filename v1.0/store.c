#include "store.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static fun_t *fun = NULL;

list_t *list_add(list_t *list, int l) {
  list_t *tmp = list;
  if (list == NULL) {
    list = malloc(sizeof(list_t));
    list->x = l;
    list->next = NULL;
  } else {
    while (tmp->next != NULL) {
      tmp = tmp->next;
    }
    tmp->next = malloc(sizeof(list_t));
    tmp = tmp->next;
    tmp->x = l;
    tmp->next = NULL;
  }
  return list;
}

void print_list(list_t *list) {
  list_t *tmp = list;
  while (tmp != NULL) {

    printf("%d \n", tmp->x);
    tmp = tmp->next;
  }
}

void list_clear(list_t *list) {
  list_t *tmp;
  while (list != NULL) {
    tmp = list;
    list = list->next;
    free(tmp);
  }
}

void store_add(char *funame, int ln, char *inpname, char mode) {
  int i;
  fun_t *tmp = fun;
  if (fun == NULL) { // Pierwsza dodana funkcja
    fun = malloc(sizeof(fun_t));
    fun->def = NULL;
    fun->proto = NULL;
    fun->call = NULL;
    fun->next = NULL;
    fun->name = malloc((strlen(funame) + 1) * sizeof(char));
    strcpy(fun->name, funame);

    if (mode == 'd') // Dodanie pozycji
      fun->def = list_add(fun->def, ln);
    else if (mode == 'p')
      fun->proto = list_add(fun->proto, ln);
    else if (mode == 'c')
      fun->call = list_add(fun->call, ln);

  } else { // Kolejna funkcja
    while (strcmp(tmp->name, funame) != 0) {

      if (tmp->next == NULL) {
        tmp->next = malloc(sizeof(fun_t));
        tmp = tmp->next;
        tmp->name = malloc((strlen(funame) + 1) * sizeof(char));

        strcpy(tmp->name, funame);
        tmp->def = NULL;
        tmp->proto = NULL;
        tmp->call = NULL;
        break;
      }
      tmp = tmp->next;
    }

    if (mode == 'd') { // Dodanie pozycji
      tmp->def = list_add(tmp->def, ln);
      printf("chyj\n");
    } else if (mode == 'p')
      tmp->proto = list_add(tmp->proto, ln);
    else if (mode == 'c')
      tmp->call = list_add(tmp->call, ln);
  }
}

void store_add_def(char *funame, int ln, char *inpname) {
  store_add(funame, ln, inpname, 'd');
}

void store_add_proto(char *funame, int ln, char *inpname) {
  store_add(funame, ln, inpname, 'p');
}

void store_add_call(char *funame, int ln, char *inpname) {
  store_add(funame, ln, inpname, 'c');
}
void store_print() {
  fun_t *tmp = fun;
  while (tmp != NULL) {
    printf("\nFunkcja %s: \n", tmp->name);

    printf("Definicje tej funkcji:\n");
    print_list(tmp->def);
    if (tmp->def == NULL)
      printf("Brak\n");

    printf("Prototypy tej funkcji: \n");
    if (tmp->proto == NULL)
      printf("Brak\n");
    print_list(tmp->proto);

    printf("Wezwania tej funkcji: \n");
    if (tmp->call == NULL)
      printf("Brak\n");
    print_list(tmp->call);
    tmp = tmp->next;
  }
}

void store_clear() {
  fun_t *tmp = fun;
  while (fun != NULL) {
    tmp = fun;
    fun = fun->next;
    list_clear(tmp->def);
    list_clear(tmp->proto);
    list_clear(tmp->call);
    free(tmp->name);
    free(tmp);
  }
}
