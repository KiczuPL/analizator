#include "fun_stack.h"
#include "alex.h"
#include "store.h"
#include <string.h>
static char *funkcje[1000];
static int def[1000][200]={0};
static int proto[1000][200]={0};
static int call[1000][200]={0};
static int fn=0;
void store_add_def (char* funame,int ln, char* inpname){
	int i;
	int l=-1;
	char*tmp;
	for (i=0; i<fn; i++){
		tmp = funkcje[i];
		if (strcmp(funame, tmp)==0){
			l=i;
			continue;
		}
	}
	if(l==-1) {
		l=fn;
		funkcje[l]=funame;
		def[l][0]+=1;
		def[l][def[l][0]]=ln;
		fn+=1;
	} else {
		def[l][0]+=1;
		def[l][def[l][0]]=ln;
	}
	printf("Nowy store_add_def dziala \n %s %d %s\n", funkcje[l], def[l][def[l][0]], inpname);
}
void store_add_proto (char* funame, int ln, char* inpname){
	int i;
	int l=-1;
	char*tmp;
	for(i=0; i<fn; i++){
		tmp = funkcje[i];
		if(strcmp(funame, tmp)==0){
			l=i;
			continue;
		}
	}
	if(l==-1) {
		l=fn;
		funkcje[l]=funame;
		proto[l][0]+=1;
		proto[l][proto[l][0]]=ln;
		fn+=1;
	} else {
		proto[l][0]+=1;
		proto[l][proto[l][0]]=ln;
	}
	printf("Nowy store_add_proto dziala \n %s %d %s \n", funkcje[l],proto[l][proto[l][0]] , inpname);
}
void store_add_call (char* funame, int ln, char* inpname){
	int i;
	int l=-1;
	char*tmp;
	for(i=0; i<fn; i++){
		tmp=funkcje[i];
		if(strcmp(funame, tmp)==0){
			l=i;
			continue;
		}
	}
	if(l==-1) {
		l=fn;
		funkcje[l]=funame;
		call[l][0]+=1;
		call[l][call[l][0]]=ln;
		fn+=1;
	} else {
		call[l][0]+=1;
		call[l][call[l][0]]=ln;
	}
	printf("Nowy store_add_call dziala \n %s %d %s \n", funkcje[l], call[l][call[l][0]], inpname);
}
void store_print(){
	int i;
	int l;
	printf("-------------------------------------\n");
	for(i=0;i<fn;i++){
		printf("Funkcja %s: \n", funkcje[i]);
		printf("Definicje tej funkcji:\n");
		for(l=1; l<=def[i][0]; l++){
			printf("%d\n", def[i][l]);
		}
		printf("Prototypy tej funkcji: \n");
		for(l=1; l<=proto[i][0]; l++){
			printf("%d\n", proto[i][l]);
		}
		printf("Wezwania tej funkcji: \n");
		for(l=1; l<=call[i][0]; l++){
			printf("%d\n", call[i][l]);
		}
	}
	printf("----------------------------------\n");
}
