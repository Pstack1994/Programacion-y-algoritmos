#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int dato;
    struct nodo * siguiente;
}nodo;


void insertarnodo(int numero, nodo**n);
void desplegarlista(nodo*n);
void liberar(nodo *n);
int getkthvalue(int k, nodo *n);
int isequal();

int main(){
    int valor;
    int comparacion;
    nodo *n=NULL; //lista vacia
    nodo *n2=NULL;

    for(int i=0; i<100;i++){
    insertarnodo(i,&n);
    }
    for(int i=100; i>0;i--){
    insertarnodo(i,&n2);
    }

    desplegarlista(n);
    printf("\n");
    desplegarlista(n2);

    comparacion=isequal(n,n2);

    valor=getkthvalue(2,n);

    printf("\n%d", valor);
    liberar(n);
    liberar(n2);
    return 0;
}



void insertarnodo(int numero, nodo **n){
        nodo* node=(nodo*)malloc(sizeof(nodo));
        (*node).dato=numero;
        (*node).siguiente=*n;
        *n=node;
}

void desplegarlista(nodo*n){
    while(n!=NULL){
    printf("%d ",(*n).dato);
    n=(*n).siguiente;
    }

}

void liberar(nodo *n){
   nodo *q = n;
   while(q != NULL){
       n = (*n).siguiente;
       free(q);
       q = n;
       }
}

int getkthvalue(int k, nodo *n){
    int contador=0;
    nodo *q = n;
    while(q != NULL && contador<k){
        q = q->siguiente;
        contador++;
        }
        return (*q).dato;

}
int isequal(nodo *n, nodo *n2 ){
    nodo *q=n;
    nodo *p=n2;

    while(q!=NULL && p!= NULL){
        int k=(*q).dato;
        if((*q).dato != (*p).dato){
            printf("Las listas no son iguales");
            return 0;
        }
        q= q->siguiente;
        p=p->siguiente;
    }
    if(q==NULL && p==NULL){
    printf("Las listas son iguales");
    } else {
        printf("Las listas son diferentes");
        return 0;
        }
    return 1;
}
