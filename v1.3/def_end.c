#include "def_end.h"
#include <stdio.h>

int def_end(char *filename, int ln) {
  FILE *in = fopen(filename, "r");
  int line = 1, opbra = 0, clobra = 0;
  char c;
  while (line != ln) {
    c = fgetc(in);
    if (c == '\n')
      line++;
    if (c == EOF) {
      return -1;
    }
  }
  while (c != '{') {
    c = fgetc(in);
    if (c == '\n')
      line++;
  }
  opbra++;
  while (opbra != clobra) {
    c = fgetc(in);
    /*printf("%c", c);*/

    if (c == '"') {
      int cp = c;
      c = fgetc(in);
      while (c != EOF && c != '"') {
        if (c == 10)
          ln += 1;
        cp = c;
        c = fgetc(in);
      }
    } else if (c == 39) {
      int cp = c;
      c = fgetc(in);
      while (c != EOF && c != 39) {
        cp = c;
        c = fgetc(in);
      }
    }
    /* Obsługa komentarzy - z gwiazdka oraz po podwojnym ukosniku */
    else if (c == '/') {
      int cp = c;
      c = fgetc(in);
      while (c == 32 || c == 10) {
        if (c == 10)
          line += 1;
        cp = c;
        c = fgetc(in);
      }
      if (c == '*') {
        c = fgetc(in);
        cp = c;
        c = fgetc(in);
        while (cp != '*' && c != '/' && c != EOF) {
          cp = c;
          c = fgetc(in);
        }
      } else if (c == '/') {
        while (c != '\n' && c != EOF) {
          c = fgetc(in);
        }
        if (c == 10)
          line += 1;
      }
    }

    else if (c == '{') {
      /*printf("KLAMRY: %d   %d", opbra, clobra);*/
      opbra++;
    } else if (c == '}') {
      /*printf("KLAMRY: %d   %d", opbra, clobra);*/
      clobra++;
    } else if (c == '\n') {
      line++;
     /* printf("%d.", line);*/
    } else if (c == EOF) {
      return -1;
    }
  }
  fclose(in);
  /* printf("ZWRACA %d", line);*/
  return line;
}
