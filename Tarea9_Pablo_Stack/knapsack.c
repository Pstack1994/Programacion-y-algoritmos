#include <stdio.h>
#include <stdlib.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

typedef struct Item{
    int *v;
    int m;
    int n;
}Item;

Item lee_vector(char *filename);
int ** knapsack(Item valor, Item peso, int nitems, int pesototal);
void buscar_items(int** matriz, int *valor, int *peso, int nitems, int pesototal);

int main (int argc, char *argv[]){
    int nitems;
    int pesototal=atoi(argv[1]);
    int **mochila;
    Item valor, peso;
    valor=lee_vector(argv[2]);
    peso=lee_vector(argv[3]);
    nitems=valor.m;

    mochila=knapsack(valor, peso, nitems, pesototal);
    printf("El valor maximo que se puede llevar en la mochila es: %d\n", mochila[nitems-1][pesototal]);
    //calcular los elementos que se seleccionaron utilizando la tabla
    buscar_items(mochila, valor.v, peso.v, nitems-1, pesototal);

    for(int i=0; i<nitems; i++){
        free(mochila[i]);
    }
    free(mochila);
    free(valor.v);
    free(peso.v);
return 0;
}


//lee los vectores
Item lee_vector(char *filename){
	int m, n;
	Item vector;
	FILE* fin=NULL;
	fin=fopen(filename, "r");

	if(  !fin  ){
		printf("Error: No se abrio %s\n" , filename);
	}

	fscanf(fin, "%d %d", &m, &n );
	vector.v=(int*)calloc((m+1),sizeof(int));

    for(int i=1; i<m+1; i++){
		fscanf(fin, "%d", &vector.v[i]);
	}
	fclose( fin );
	vector.m=m+1;
	vector.n=n;
	return vector;
}

int ** knapsack(Item valor, Item peso, int nitems, int pesototal){
    int **matriz;
    matriz=(int**)calloc((nitems), sizeof(int*));
     for(int i=0; i<nitems;i++){
        matriz[i]=(int *)calloc((pesototal+1),sizeof(int));
    }

    //ciclos para llenar la tabla
    for(int i=1; i<nitems; i++){
        for(int j=1; j<pesototal+1; j++){
          if(j<peso.v[i]){
              matriz[i][j]=matriz[i-1][j];
          }else {
            matriz[i][j]=MAX((valor.v[i]+(matriz[i-1][j-peso.v[i]])), (matriz[i-1][j]));
          }
        }
    }
    return matriz;
}

void buscar_items(int** matriz, int *valor, int *peso, int nitems, int pesototal){
    if(nitems==0 || pesototal==0){
        return;
    }else{
        if(matriz[nitems][pesototal]==matriz[nitems-1][pesototal]){
            buscar_items(matriz,valor,peso,nitems-1, pesototal);
        }else{
            printf("valor: %d , peso: %d\n", valor[nitems], peso[nitems]);
            buscar_items(matriz, valor, peso, nitems-1, pesototal-peso[nitems]);
        }
    }
}
