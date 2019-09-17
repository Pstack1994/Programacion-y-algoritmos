#include "stdio.h"
#include <stdlib.h>
int **pascal(int n);

int main(){

    int n=20;
    int **triangulo;
    triangulo=pascal(n);

    for(int i=0;i<n;i++){
        free(triangulo[i]);
    }
    free(triangulo);

return 0;
}

int **pascal(int n){
    int suma=0;
    int **x;
    x= (int**)malloc(n*sizeof(int*));

    for(int i=0; i<n;i++){
        x[i]=(int *)malloc((i+1)*sizeof(int));
    }

    for(int i=0; i<n;i++){
        x[i][0]=1;
        x[i][i]=1;
        for(int j=1; j<i;j++){
            for(int k=j-1;k<=j;k++){
                suma+=x[i-1][k];
            }
            x[i][j]=suma;
            suma=0;
        }

    }

       for(int i=0; i<n;i++){
            for(int j=0; j<=i;j++){
                printf("%d ",x[i][j]);
             }
            printf("\n");
        }
return x;
}
