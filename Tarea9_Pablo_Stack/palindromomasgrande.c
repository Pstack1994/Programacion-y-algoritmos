#include <stdio.h>
#include <stdlib.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y));

int palindromomasgrande(int n, char *cadena);
/*para compilar:
gcc palindromomasgrande.c
./a.out 12 programarenc
*/

/*El algoritmo tiene una complejidad o(n^2) tanto para espacio como para tiempo*/

int main(int arg, char *argv[]){
    int n=atoi(argv[1]), maximo;
    maximo=palindromomasgrande(n,argv[2]);
    printf("La secuencia palindromica mas grande es: %d\n", maximo);

    return 0;
}

int palindromomasgrande(int n, char * cadena){
    int matriz[n][n];
    //se inicializa en uno porque el maximo palindromo de una cadena de largo 1 es 1
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i==j){
                matriz[i][j]=1;
            }else{
                matriz[i][j]=0;
            }
        }
    }
    //Empezar a buscar palindromos desde que tienen 2 letras ya que solventamos el caso anterior inicializando en 1
    for(int nletras=2; nletras<=n; nletras++){
        for(int i=0; i<n-nletras+1; i++){//i es el inicio de la palabra
            int j=nletras+i-1;// j es el final de la palabra
            //si solo hay 2 letras y las dos son iguales el palindormo más grande es de tamaño 2
            if(nletras==2 && cadena[i]==cadena[j]){
                matriz[i][j]=2;
            }else if(cadena[i]==cadena[j]){
                //si hay mas de dos letras y la primera letra de la palabra y la ultima son iguales
                matriz[i][j]=matriz[i+1][j-1]+2;
            }else{
                //si la primer y ultima letra de la palabra son diferentes encuentras el maximo
                matriz[i][j]=MAX(matriz[i+1][j], matriz[i][j-1])
            }
        }
    }
    return matriz[0][n-1];
}
