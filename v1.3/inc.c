#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 8192

void include_find (char *inpname){
	char buf[BUFSIZE];
	char *str;
	int c, len;
	int l;
	char *bibl= NULL;
	FILE *in = fopen(inpname, "r");
	if(in == NULL){
		printf("Wypisywanie bibliotek: Nie można czytać pliku %s, sprawdz poprawnosc wpisanej nazwy \n", inpname);
		exit(1);
	}
	while(fgets (buf, BUFSIZE, in) != NULL) {
		if(strstr(buf, "#include") != NULL){
			str = strtok(buf," ");
			str = strtok(NULL, " ");
			for(l=0; str[l] != '\0'; l++);
			l=l-2;
			while (c<=l && str[c]!='<' && str[c] !='"'){
				c++;
				printf("%c\n", str[c]);
			}
			c++;
			len=0;
			bibl = malloc(l+1);
			while (c<=l && str[c]!='>' && str[c] !='"'){
				bibl[len]= str[c];
				bibl[len+1]='\0';
				c++;
				len++;
			}
			printf("%s\n", bibl);
			free(bibl);
			c=0;
			len=0;
		}
	}
}	
