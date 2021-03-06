#include <stdlib.h>
#include "store.h"
#include "alex.h"       // analizator leksykalny
#include "fun_stack.h"  // stos funkcji
#include "def_end.h"

#define MAXINDENTLENGHT 256     // maks długość identyfikatora

void
analizatorSkladni (char *inpname)
{                               // przetwarza plik inpname

/* Wyswietlanie bledu jesli plik nie istnieje */	
  FILE *in = fopen (inpname, "r");
  if(in==NULL) {
	  fprintf( stderr, "Analizator składni: błąd: jeden z plików podanych jako argument nie istnieje: %s \n", inpname);
    store_clear();
	  exit(1);
  }

  int nbra = 0;   // bilans nawiasów klamrowych {}
  int npar = 0;   // bilans nawiasów zwykłych ()
  int lnn = 0;
  alex_init4file (in);          // ustaw analizator leksykalny, aby czytał in
  
  lexem_t lex;

  lex = alex_nextLexem ();      // pobierz następny leksem
  while (lex != EOFILE) {
    switch (lex) {
	    case KEY:{
		lexem_t nlex = alex_nextLexem ();
		while (nlex == OTHER){
			nlex = alex_nextLexem();
		}
		if(nlex == OPEPAR){
		put_on_fun_stack(2, "KEY");
		     }
		if(nlex == IDENT){
			char *iname = alex_ident();
			lexem_t nlex = alex_nextLexem ();
			while(nlex == OTHER) {
				nlex = alex_nextLexem();
			}
			if (nlex == OPEPAR){
				npar++;
				lnn = alex_getLN ();
				put_on_fun_stack(npar, iname);
			} else {
				lex=nlex;
				continue;
			}

		}
		     }
		     break;
    case IDENT:{
        char *iname = alex_ident ();   // zapamiętaj identyfikator i patrz co dalej
        lexem_t nlex = alex_nextLexem ();
	/* Petla while zeby program obslugiwal funkcje, dla ktorych miedzy nazwa i nawiasem otwierajacym sa oddzielone spacjami*/
	while(nlex == OTHER){
		nlex = alex_nextLexem();
	}
        if (nlex == OPEPAR) {   // nawias otwierający - to zapewne funkcja
          npar++;
	  lnn = alex_getLN();
	  put_on_fun_stack(npar, iname);       // odłóż na stos funkcji
                                                // stos f. jest niezbędny, aby poprawnie obsłużyć sytuacje typu
                                                // f1( 5, f2( a ), f3( b ) )
	}
        else {                  // nie nawias, czyli nie funkcja
          lex = nlex;
          continue;
        }
      }
      break;
    case OPEPAR:{
      npar++;
		}
      break;
    case CLOPAR:{              // zamykający nawias - to może być koniec prototypu, nagłówka albo wywołania
        if (top_of_funstack () == npar) {       // sprawdzamy, czy liczba nawiasów bilansuje się z wierzchołkiem stosu funkcji
                                                // jeśli tak, to właśnie wczytany nawias jest domknięciem nawiasu otwartego
                                                // za identyfikatorem znajdującym się na wierzchołku stosu
          lexem_t nlex = alex_nextLexem ();     // bierzemy nast leksem
	  while(nlex == OTHER){
		  nlex = alex_nextLexem ();
	  }
          if (nlex == OPEBRA){   // nast. leksem to klamra a więc mamy do czynienia z def. funkcji
	    nbra+=1;
            store_add_def (get_from_fun_stack (), alex_getLN (), inpname,def_end(inpname,alex_getLN()));
	  }
          else if (nbra == 0)   // nast. leksem to nie { i jesteśmy poza blokami - to musi być prototyp
            store_add_proto (get_from_fun_stack (), lnn, inpname);
          else                  // nast. leksem to nie { i jesteśmy wewnątrz bloku - to zapewne wywołanie
            store_add_call (get_from_fun_stack (), lnn, inpname);
        }
        npar--;
      }
      break;
    case OPEBRA:{
      nbra++;
		}
      break;
    case CLOBRA:{
      nbra--;
		}
      break;
    case ERROR:{
        fprintf (stderr, "\nBUUUUUUUUUUUUUUUUUUUUUU!\n"
                 "W pliku %s (linia %d) są błędy składni.\n"
                 "Kończę!\n\n", inpname, alex_getLN ());
        store_clear();
        exit (1);               // to nie jest najlepsze, ale jest proste ;-)
      }
      break;
    default:
      break;
    }
    lex = alex_nextLexem ();
  }
}
