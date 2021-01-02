#include "alex.h"
#include "keyword.h"
#include <ctype.h>
#include <stdio.h>

static int  ln= 0;
static int  lnn=0;
static char ident[256];
static FILE *ci= NULL;

void    alex_init4file( FILE *in ) {
   ln= 1;
   ci= in;
}
lexem_t alex_nextLexem( void ) {
  int c;
  while( (c= fgetc(ci)) != EOF ) {
	  //	  printf("Znak to %c \n", c);
    //if( isspace( c ) )
    if(c==32)
                        return OTHER;
    /*else if( c == '\n' ){
                        ln++;
			return OTHER;
    }*/
    else if( c == '(' )
                        return OPEPAR;
    else if( c == ')' )
      return CLOPAR;
    else if( c == '{' ){
                        return OPEBRA;
			}
    else if( c == '}' )
                        return CLOBRA;
    else if( isalpha( c ) ) {
    	int i= 1;
    	ident[0] = c;
    	while( isalnum( c= fgetc(ci) ) || c=='_' ){
	    // printf("Znak to %c\n", c);
        	ident[i++] = c; }
      		ungetc( c, ci);
                ident[i] = '\0';
		lnn=ln;
    	return isKeyword(ident)/* ? OTHER : IDENT*/;
                } 
    else if( c == '"' ) {
      /* Uwaga: tu trzeba jeszcze poprawic obsluge nowej linii w trakcie napisu
         i \\ w napisie 
      */
      int cp = c;
      c=fgetc(ci);
                        while(c!= EOF && c != '"') {
                                cp = c;
				c = fgetc(ci);
      }
      return c==EOF ? EOFILE : OTHER; 
    }
    else if( c == 39){
	    int cp = c;
	    c= fgetc(ci);
	    	while(c!=EOF && c != 39){
			cp = c;
			c = fgetc(ci);
		}
		return c==EOF? EOFILE : OTHER;
    }
    else if( c == '/' ) {
      /* moze byc komentarz */
	    int cp = c;
	    c= fgetc(ci);
	    if (c=='*') {
		    while (cp != '*' && c != '/' && c!=EOF){
			    cp = c;
			    c= fgetc(ci);
		    }
                }
	    else if (c=='/') {
		    while (c!= '\n' && c!=EOF)
			    c=fgetc(ci);
	    }
    }
    if( isdigit( c ) || c == '.' ) {
      /* liczba */
                } 
    else if(c==10 || c==13){
		ln+=1;
	//	printf("Zmiana lini na %d\n", ln);
		return OTHER;
		} 
    else {	
      return OTHER;
                }
        }       
  return EOFILE;
}

char *  alex_ident( void ) {
   return ident;
}

int     alex_getLN() {
        return lnn;
}

