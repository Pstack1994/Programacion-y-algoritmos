#include <stdio.h>
#include <stdlib.h>

double pumasganan(int p, int a, int n, double matriz[][n]);

int main(int argc, char *argv[]){
    //numero de partidos a jugar
    int n=atoi(argv[1]);
    //a= juegos que lleva ganados america, b=juegos que lleva ganados mis pumas
    int p= atoi(argv[2]), a=atoi(argv[3]);
    //matriz en donde se van a memorizar los resultados;
    double matriz[n][n], probabilidad;
    //inicializar con numero negativo porque no hay probabilidades negativas
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            matriz[i][j]=-1;
        }
    }

    probabilidad=pumasganan(p,a,n,matriz);
    printf("Probabilidad de que ganen mis pumas: %lf", probabilidad);

    return 0;
}

double pumasganan(int p, int a, int n, double matriz[][n]){
    //si llevan el mismo número de juegos ganados por simetría es 0.5
    if(a==p){
        return 0.5;
    }
    //si los pumas han ganado n juegos la probabilidad de que gane pumas es 1
    if(p>=n){
        return 1;
    }
    //si el america ha ganado n juegos la probabilidad de que gane pumas es 0
    if(a>=n){
        return 0;
    }
    //si el valor que estamos buscando ya está calculado regresa ese valor
    if(matriz[a][p]!=-1){
        return matriz[a][p];
    }else{//si no está calculado lo calculamos
        matriz[a][p]=(0.5)*pumasganan(p+1,a,n,matriz)+(0.5)*pumasganan(p, a+1,n,matriz);
        return matriz[a][p];
    }

}
