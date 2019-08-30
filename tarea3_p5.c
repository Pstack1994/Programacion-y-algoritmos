#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int dato;
    struct nodo * siguiente;
}nodo;


void insertarnodo(int numero, nodo**n);
void desplegarlista(nodo*n);
void liberar();
int getkthvalue();
int isequal();

int main(){
nodo *n=NULL;
insertarnodo(1,&n);
insertarnodo(5,&n);
insertarnodo(3,&n);
desplegarlista(n);

    return 0;
}



void insertarnodo(int numero, nodo **n){
    if(*n==NULL){
        *n=(nodo*)malloc(sizeof(nodo));
        (**n).dato=numero;
        (**n).siguiente=NULL;
    }else {
        insertarnodo(numero, &(**n).siguiente);
    }
}

void desplegarlista(nodo*n){
    if(n== NULL){
        return;
    }
    printf("%d ", (*n).dato);
    desplegarlista((*n).siguiente);
}

void liberar(){

}

int getkthvalue(){

}
int isequal(){

}
