#include <stdio.h>
#include <stdlib.h>
#include <arbol_tarea7.h>



int main(){
    int numero=4;
    nodo *n=NULL; //lista vacia
    nodo *papa=NULL;
    nodo *root=n;



    insertar(&n,papa, 10, &n);
    insertar(&n,papa, -10, &n);
    insertar(&n,papa,20, &n);
    insertar(&n,papa,15, &n);
    insertar(&n,papa,17, &n);
    insertar(&n,papa,40,&n);
    insertar(&n,papa,50,&n);
    insertar(&n,papa,60,&n);

    imprime(n);
    buscar(n, 48);
    buscar(n,17);
    liberar(n);
    return 0;
}
