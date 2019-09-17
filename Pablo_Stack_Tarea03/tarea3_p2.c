#include <stdio.h>

int main(){
    float a, b, *ptr_a, *ptr_b, **dptr_a, **dptr_b;
    a=-1.0;
    b=5.0;

    printf("a= %f \n", a);
    printf("b= %f \n", b);

    ptr_a=&a;

    dptr_a=&ptr_b;
    //printf("dptr_a= %f ", **dptr_a);
    dptr_b=dptr_a;
    //printf("dptr_b= %f ", dptr_b);
    *dptr_b=ptr_a;
    //printf("dptr_b= %f ", **dptr_b);
    (**dptr_a)=-3.0;
    //printf("dptr_a= %f ", dptr_a);
    printf("a=  %f ", a);
    return 0;
}
