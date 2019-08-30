#include <stdio.h>


int main (){

    unsigned int cast;
    char x;
    unsigned int mascara=255;
    float f=8.5;

    cast=(*(unsigned int*)&f);
    cast=cast>>23;

    x=(cast & mascara)-127;
    printf("%d",x );

    return 0;
}
