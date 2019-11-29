#include <stdio.h>
#include <stdlib.h>

//programa que implementa un monticulo ternario
/*formulas para encontrar hijos:
izquierda= i*3-1
centro= 1*3
derecha= i*3*/

/*formula para encontrar al padre de cualquier hijo:
padre=(i+1)/3 */
typedef struct Monticulo{
    int *arreglo;
    int posicion;
    int m;
}Monticulo;


//Inicia el Main
int maximo(Monticulo monticulo);
int min(int x, int y);
Monticulo insertar(Monticulo monticulo, int n);
Monticulo elimina_max(Monticulo monticulo);

int main(){
    Monticulo monticulo;
    int max, num, bandera=0;
    //monticulo.m=9;

    monticulo.posicion=1;

    printf("Ingresa la cantidad de nodos: ");
    scanf("%d", &monticulo.m);
    monticulo.arreglo=(int*)calloc(monticulo.m,sizeof(int));

    printf("Ingresa los nodos: \n");
    for(int i=0; i<monticulo.m-1;i++){
    scanf("%d", &num);
    monticulo=insertar(monticulo, num);
    }

    while(bandera!=5){
        printf("\nQue accion deseas hacer: \n 1)Consultar Maximo \n 2)insertar nodo \n 3)Eliminar nodo \n 4)Imprimir monticulo  \n 5)salir\n Eleccion: ");
        scanf("%d", &bandera);
        printf("\n");
        switch(bandera){
            case 1: max=maximo(monticulo);break;
            case 2: printf("Ingresa el numero: "); scanf("%d", &num);monticulo=insertar(monticulo, num);break;
            case 3: monticulo=elimina_max(monticulo);break;
            case 4:
                    for(int i=1; i<monticulo.posicion; i++){
                        printf("%d ", monticulo.arreglo[i]);
                    };break;
            case 5: bandera=5; break;
            default: printf("No es una opcion valida"); break;
        }
    }

    free(monticulo.arreglo);
    return 0;
}

//Termina el main

int min(int x, int y){
    int min;
    if(x<y){
        min=x;
    }else{
        min=y;
    }
    return min;
}

//funcion para insertar
Monticulo insertar(Monticulo monticulo, int n){
    if(monticulo.posicion==monticulo.m){printf("No hay espacio para seguir insertando\n");return monticulo;}
    int i=monticulo.posicion;
    int aux;
    if (monticulo.posicion==1){
        monticulo.arreglo[1]=n;
        monticulo.posicion++;
    }else{


        monticulo.arreglo[monticulo.posicion]=n;
        int a=monticulo.posicion;
        do{
            i=(i+1)/3;
            if(monticulo.arreglo[a]>monticulo.arreglo[i]){
                aux=monticulo.arreglo[a];
                monticulo.arreglo[a]=monticulo.arreglo[i];
                monticulo.arreglo[i]=aux;
                a=i;
            }
        }while(i!=1);

        monticulo.posicion++;

    }

    return monticulo;
}

// consultar el maximo
int maximo(Monticulo monticulo){
    int max;
    max=monticulo.arreglo[1];
    if(monticulo.posicion==1){
        printf("Llegaste al final del monticulo\n");
    }else{
        printf("El maximo es: %d\n", max);
    }
    return max;
}

//funcion para eliminar
Monticulo elimina_max(Monticulo monticulo){
    if(monticulo.posicion<=1){printf("No puedes seguir eliminando\n");return monticulo;}
    int pos_max=1, aux, pos_max_a=1;
    int a=0;
    int posicion=monticulo.posicion-1;
    monticulo.arreglo[1]=monticulo.arreglo[posicion];
    monticulo.posicion--;
    do{
    a++;
    int max=monticulo.arreglo[pos_max];
    for(int i=a*3-1;i<=min(a*3+1, monticulo.posicion);i++){
        if(max<monticulo.arreglo[i]){
            max=monticulo.arreglo[i];
            pos_max=i;
        }
    }
    aux=monticulo.arreglo[pos_max_a];
    monticulo.arreglo[pos_max_a]=max;
    monticulo.arreglo[pos_max]=aux;
    pos_max_a=pos_max;
    }while(a*3+1<monticulo.posicion);
    //monticulo.arreglo[pos_max]=0;

    return monticulo;
}
