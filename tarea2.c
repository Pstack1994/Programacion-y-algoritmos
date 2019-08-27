#include <stdio.h>

#define swap(x,y) ((x)=(x)+(y), (y)=(x)-(y), (x)=(x)-(y))
int main (){

//double x=2, y=20;
/*for(int i=0; i<115;i+=2){
/*int i=0;
    do{
        i+=2;
        if(i%7==0){
            continue;
        }
        printf("%d \n", ++i);

    }while(i<98);*/

    //swap(x,y);

    //printf("%f", x);
    //printf("\n");
   // printf("%f", y);


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
