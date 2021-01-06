#ifndef _STORE_H_IS_INCLUDED_
#define _STORE_H_IS_INCLUDED_

typedef struct list {
  int x;
  int y;
  struct list *next;
} list_t;

typedef struct file {
  char *name;
  list_t *list;
  struct file *next;
} file_t;

typedef struct fun {
  char *name;
  file_t *def;
  file_t *proto;
  file_t *call;
  struct fun *next;
} fun_t;

list_t *list_add(list_t *list, int ln, int ln2);
file_t *file_add(file_t *list, char *name, int ln, int ln2);
void file_clear(file_t *file);
void print_list(list_t *list);
void list_clear(list_t *list);
void store_add(char *funame, int ln, char *inpname, char mode, int ln2);
void store_add_def(char *funame, int ln, char *inpname, int ln2);
void store_add_proto(char *funame, int ln, char *inpname);
void store_add_call(char *funame, int ln, char *inpname);
void store_print( void );
void store_clear( void );
#endif
