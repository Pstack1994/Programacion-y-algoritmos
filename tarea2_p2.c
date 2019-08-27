#include <stdio.h>

#define xorswap(x,y) ((x)=(x)^(y), (y)=(x)^(y), (x)=(x)^(y))//swap para enteros

#define swap(x,y) ((x)=(x)+(y), (y)=(x)-(y), (x)=(x)-(y)) //swap para cualquier tipo de datos

int main (){

    int x=2, y=20;
    float a=12.3, b=13;

    xorswap(x,y);
    swap(a,b);

    printf("x= %d \n",x);
    printf("y= %d \n",y);
    printf("a= %f \n",a);
    printf("b= %f \n",b);

    return 0;
}
