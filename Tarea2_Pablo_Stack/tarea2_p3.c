#include <stdio.h>

int main (){

    int i=0;
    do{
        i+=2;

        if(i%7==0){
            continue;
        }

        printf("%d \n", ++i);

    }while(i<98);

    return 0;
}
