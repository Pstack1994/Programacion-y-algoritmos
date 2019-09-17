#include <stdio.h>
#include <stdlib.h>

double * creavector(int n, double valor);
double **creamatriz(int r, int c);
void liberamatriz(double **matriz, int m);
double ** create_matrix(int m, int n);

int main(){
    double *vector;
    vector= creavector(4,1);
    double **matriz;
    matriz=creamatriz(4,3);


    for(int i=0; i<4; i++){
        printf("%lf ", vector[i]);
    }

    liberamatriz(matriz, 4);
    free(vector);


    return 0;
}

double * creavector(int n, double valor){
    double *vector;
    vector= (double*)malloc(n*sizeof(double));

    if(vector!=NULL){
        for(int i=0; i<n; i++){
            vector[i]=valor;
         }
    }else {
        return NULL;
    }
    return vector;
}

double **creamatriz(int r, int c){
    double** matriz;
    matriz=(double**)malloc(r*sizeof(double));

    for(int i=0; i<r;i++){
        matriz[i]=(double*)malloc(c*sizeof(double));
    }
    return matriz;
}

void liberamatriz(double **matriz, int m){
    for(int i=0; i<m;i++){
        free(matriz[i]);
    }

    free(matriz);

}

double ** create_matrix(int m, int n){
    double **mat;
    mat=(double**)malloc(m+sizeof(double*));
    mat[0]=(double*)malloc(m*n*sizeof(double));

    for(int i=1; i<m; i++){
        mat[i]=mat[i-1]+n;
    }
    return mat;
}
