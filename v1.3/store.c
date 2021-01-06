#include "store.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static fun_t *fun = NULL;

list_t *list_add(list_t *list, int ln, int ln2) {
  list_t *tmp = list;
  if (list == NULL) {
    list = malloc(sizeof(list_t));
    list->x = ln;
    list->y = ln2;
    list->next = NULL;
  } else {
    while (tmp->next != NULL) {
      tmp = tmp->next;
    }
    tmp->next = malloc(sizeof(list_t));
    tmp = tmp->next;
    tmp->x = ln;
    tmp->y = ln2;
    tmp->next = NULL;
  }
  return list;
}

void list_clear(list_t *list) {
  list_t *tmp;
  while (list != NULL) {
    tmp = list;
    list = list->next;
    free(tmp);
  }
}

void print_list(list_t *list) {
  list_t *tmp = list;
  while (tmp != NULL) {

    if (tmp->y != 0)
      printf("%d-%d ", tmp->x, tmp->y);
    else
      printf("%d ", tmp->x);
    tmp = tmp->next;
  }
}

file_t *file_add(file_t *file, char *name, int ln, int ln2) {
  file_t *tmp = file;
  if (file == NULL) {
    file = malloc(sizeof(file_t));
    file->name = malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(file->name, name);
    file->list = NULL;
    file->list = list_add(file->list, ln, ln2);
    file->next = NULL;
  } else {
    while (tmp->next != NULL)
      tmp = tmp->next;

    while (strcmp(tmp->name, name) != 0) {
      if (tmp->next == NULL) {
        tmp->next = malloc(sizeof(file_t));
        tmp = tmp->next;
        tmp->next = NULL;
        tmp->list = NULL;
        tmp->name = malloc((strlen(name) + 1) * sizeof(char));

        strcpy(tmp->name, name);
        break;
      }
      tmp = tmp->next;
    }
    tmp->list = list_add(tmp->list, ln, ln2);
  }
  return file;
}

void print_file_list(file_t *file) {
  file_t *tmp = file;
  while (tmp != NULL) {
    printf("W pliku %s:\n", tmp->name);
    print_list(tmp->list);
    tmp = tmp->next;
    printf("\n");
  }
}

void file_clear(file_t *file) {
  file_t *tmp = file;
  while (file != NULL) {
    tmp = file;
    file = file->next;
    list_clear(tmp->list);
    free(tmp->name);
  }
}

void store_add(char *funame, int ln, char *inpname, char mode, int ln2) {
  int i;
  fun_t *tmp = fun;
  // printf("Dodaję %c nr: %d z pliku %s funkcja: %s\n", mode, ln, inpname,
  // funame);
  if (fun == NULL) { // Pierwsza dodana funkcja
    fun = malloc(sizeof(fun_t));
    fun->def = NULL;
    fun->proto = NULL;
    fun->call = NULL;
    fun->next = NULL;
    fun->name = malloc((strlen(funame) + 1) * sizeof(char));
    strcpy(fun->name, funame);

    if (mode == 'd') // Dodanie pozycji
      fun->def = file_add(fun->def, inpname, ln, ln2);
    else if (mode == 'p')
      fun->proto = file_add(fun->proto, inpname, ln, ln2);
    else if (mode == 'c')
      fun->call = file_add(fun->call, inpname, ln, ln2);

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
        tmp->next = NULL;
        break;
      }
      tmp = tmp->next;
    }

    if (mode == 'd') // Dodanie pozycji
      tmp->def = file_add(tmp->def, inpname, ln, ln2);
    else if (mode == 'p')
      tmp->proto = file_add(tmp->proto, inpname, ln, ln2);
    else if (mode == 'c')
      tmp->call = file_add(tmp->call, inpname, ln, ln2);
  }
}

void store_add_def(char *funame, int ln, char *inpname, int ln2) {
  store_add(funame, ln, inpname, 'd', ln2);
}

void store_add_proto(char *funame, int ln, char *inpname) {
  store_add(funame, ln, inpname, 'p', 0);
}

void store_add_call(char *funame, int ln, char *inpname) {
  store_add(funame, ln, inpname, 'c', 0);
}
void store_print() {
  fun_t *tmp = fun;
  while (tmp != NULL) {
    printf("\nFunkcja %s:\n", tmp->name);

    printf("Definicje tej funkcji:\n");
    if (tmp->def == NULL)
      printf("Brak\n");
    print_file_list(tmp->def);

    printf("Prototypy tej funkcji: \n");
    if (tmp->proto == NULL)
      printf("Brak\n");
    print_file_list(tmp->proto);

    printf("Wezwania tej funkcji: \n");
    if (tmp->call == NULL)
      printf("Brak\n");
    print_file_list(tmp->call);

    tmp = tmp->next;
  }
}

void store_clear() {
  fun_t *tmp = fun;
  while (fun != NULL) {
    tmp = fun;
    fun = fun->next;
    file_clear(tmp->def);
    file_clear(tmp->proto);
    file_clear(tmp->call);
    free(tmp->name);
    free(tmp);
  }
}
