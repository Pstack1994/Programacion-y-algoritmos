#include "stdio.h"
#include <stdlib.h>

int main(int argc, char *argv[]){

    int n=4;
    int **x;
    x= (int**)malloc(n*sizeof(int*));

    for(int i=0; i<n;i++){
        x[i]=(int *)malloc((i+1)*sizeof(int));
    }

    x[0][0]=x[1][0]=x[1][1]=1;

    for(int i=2; i<n;i++){
        for(int j=1; j<=i;j++){

             //for(int k=1; k<i;k++){
               //  x[i][k]+=x[i-1][j-k]
           //  }

                //x[i][j]=x[i-1][j];

        }

    }

        for(int i=0; i<n;i++){
            for(int j=0; j<=i;j++){
                printf("%d ",x[i][j]);
        }
        printf("\n");
    }





    for(int i=0;i<n;i++){
        free(x[i]);
    }
    free(x);
return 0;
}
