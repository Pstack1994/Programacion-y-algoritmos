#include <stdio.h>
#include <stdlib.h>

void Bubble_sort(double *A, int n){
    int cont=1;
    double aux;
    while(cont==1){
        cont=0;
        for(int j=0; j<n-1;j++){
            if(A[j]>A[j+1]){
                aux=A[j];
                A[j]=A[j+1];
                A[j+1]=aux;
                cont=1;
            }
        }
    }

}

int main (){
    double *A;
    int n;
    printf("Ingrese el tamaño del arreglo: ");
    scanf("%d", &n);

    A=(double *)malloc(n*sizeof(double));

    printf("Ingrese los elementos del arreglo: ");
    for(int i=0; i<n; i++){
    scanf("%lf", &A[i]);
    }

    Bubble_sort(A,n);

    for(int i=0; i<n;i++){
        printf("%lf ", A[i]);
    }
    free(A);
    return 0;
}
