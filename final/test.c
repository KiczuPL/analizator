#include <stdio.h>


void ddd(int* a, int* b){
    a=b;
}

int main(){
    int x=1,y=3;
int* a=&x;
int* b=&y;
int* c;
printf("a=%d  b=%d\n",*a, *b);
ddd(a,b);
printf("a=%d  b=%d\n",*a, *b);
return 0;
}