#ifndef _STORE_H_IS_INCLUDED_
#define _STORE_H_IS_INCLUDED_
typedef struct list {
  int x;
  struct list *next;
} list_t;

typedef struct fun {
  char *name;
  list_t *def;
  list_t *proto;
  list_t *call;
  struct fun *next;
} fun_t;

list_t* list_add(list_t *list, int l);
void print_list(list_t *list);
void list_clean(list_t *list);
void store_add(char *funame, int ln, char *inpname, char mode);
void store_add_def(char *funame, int ln, char *inpname);
void store_add_proto(char *funame, int ln, char *inpname);
void store_add_call(char *funame, int ln, char *inpname);
void store_print();
void store_clear();
#endif