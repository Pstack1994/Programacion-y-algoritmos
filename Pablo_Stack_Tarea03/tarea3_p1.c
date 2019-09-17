#include <stdio.h>

struct mystruct {
    double a;
    char *b;
    char c;
};

int main(){
    struct mystruct x;
    printf("\n Tamaño de la estructura: %ld \n",sizeof(x));
    printf("\n Tamaño de a: %ld \n",sizeof(x.a));
    printf("\n Tamaño de b: %ld \n",sizeof(x.b));
    printf("\n Tamaño de c: %ld \n",sizeof(x.c));
    return 0;
}
