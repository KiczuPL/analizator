#include "alex.h"
#include "keyword.h"
#include <ctype.h>
#include <stdio.h>

static int  ln= 0;
static int  lnn=0; /* To samo co ln, ale tymczasowo przypisywana do danego identyfikatora */
static char ident[256];
static FILE *ci= NULL;

void    alex_init4file( FILE *in ) {
   ln= 1;
   ci= in;
}
lexem_t alex_nextLexem( void ) {
  int c;
  while( (c= fgetc(ci)) != EOF ) {
     printf("Znak to %c \n", c); /* Linia, ktora pomagala przy szukaniu bledow */
    /* Obsługa spacji */
    if(c==32)
                        return OTHER;
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
		/* Podkreslniki rowniez moga byc czescia nazwy funkcji*/
    			while( isalnum( c= fgetc(ci) ) || c=='_' ){
	    			 printf("Znak to %c\n", c);	/*Linia, ktora pomagala przy szukaniu bledow */
        			ident[i++] = c; }
      				ungetc( c, ci);
                		ident[i] = '\0';
				lnn=ln;
    			return isKeyword(ident); 		/*Zwraca KEY lub IDENT */
    } 
    /* Obsługa tekstu */
    else if( c == '"' ) {
      		int cp = c;
      		c=fgetc(ci);
                        while(c!= EOF && c != '"') {
                                if (c==10) ln+=1;
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
    /* Obsługa komentarzy - z gwiazdka oraz po podwojnym ukosniku */
    else if( c == '/' ) {
	    	int cp = c;
	    	c= fgetc(ci);
		while (c==32 || c==10){
			if (c==10) ln+=1;
			cp=c;
			c=fgetc(ci);
		}
	    	if (c=='*') {
			c=fgetc(ci);
			cp=c;
			c=fgetc(ci);
		    	while (cp != '*' && c != '/' && c!=EOF){
			    	cp = c;
			    	c= fgetc(ci);
		    }
                }
    		else if (c=='/') {
		   	 while (c!= '\n' && c!=EOF){
			    c=fgetc(ci);
			 }
			 if (c==10) ln+=1;
	    }
		return c==EOF? EOFILE : OTHER;
    }
    /*Naliczanie nowej linii*/
    else if(c==10){
		ln+=1;
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

