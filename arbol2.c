#include <stdio.h>
#include <stdlib.h>


enum color{
    NEGRO=0, ROJO=1
};

typedef struct nodo {
    int dato;
    unsigned char color;
    struct nodo *papa;
    struct nodo * izq;
    struct nodo * der;
}nodo;

//void insertarnodo(int numero, nodo**n);
void cambia_color(nodo *papa);
nodo *abuelo (nodo *n);
nodo *tio(nodo *n);
nodo *insertar(nodo *n, nodo *papa, int numero);
void imprime(nodo *n);
void liberar(nodo *n);

int main(){
    int numero=4;
    nodo *n=NULL; //lista vacia
    nodo *papa=NULL;



    n=insertar(n,papa, 10);
    n=insertar(n,papa, 11);
    n=insertar(n,papa,9);
   // insertar(&n,papa,8);
   // insertar(&n,papa,7);
    //insertar(&n,papa,6);
    /*insertar(&n,papa,2);
    insertar(&n,papa,4);*/

    imprime(n);
   // printf("%d ", n->izq->papa->dato);
    liberar(n);
    return 0;
}


nodo *insertar(nodo *n, nodo *papa, int numero){
    if(n==NULL){
        nodo *nuevo= malloc(sizeof(nodo));
        nuevo->dato=numero;
        nuevo->izq=NULL;
        nuevo->der=NULL;
        nuevo->papa=papa;
        nodo *t=tio(nuevo);

        if(nuevo->papa==NULL){
            nuevo->color=NEGRO;
        }else{
            nuevo->color=ROJO;
        }

        if(papa!=NULL){
            //condicion del cambio de color si papa y tio son iguales.
            /*if(nuevo->color==ROJO && papa->color==ROJO && papa->papa->izq->color==ROJO && papa->papa->der->color==ROJO){
               cambia_color(papa);
           }*/

            if(papa->der!=NULL){
                if(papa->color==ROJO && papa->papa->izq->color==ROJO && papa->papa->der->color==ROJO){
                    cambia_color(papa);
                }
           }

        }
        n=nuevo;
        return n;

        //return;
    }

    if(numero>n->dato){
        insertar(n->der,n, numero);
    }else{
        insertar(n->izq,n, numero);
    }
}



void imprime(nodo *n){
    if(n==NULL){return; }
    printf("%d ", n->dato);
    if(n->papa != NULL){
    printf("(%d)", n->papa->dato);
    }
    printf("color: %u ", n->color);
    imprime(n->izq);
    imprime(n->der);

}

void liberar(nodo *n){
    if(n==NULL){return; }
    liberar(n->izq);
    liberar(n->der);
    free(n);
}

void cambia_color(nodo *papa){
    papa->papa->izq->color=1-(papa->papa->izq->color);
    papa->papa->der->color=1-(papa->papa->der->color);
    if(papa->papa->papa!=NULL){
        papa->papa->color=1-(papa->papa->color);
    }
}

nodo *abuelo(nodo *n){
    if(n!=NULL && n->papa!=NULL){
        return n->papa->papa;
    }
	else{
		return NULL;
    }
}

nodo *tio(nodo *n){
    nodo *a = abuelo(n);
    if(a!=NULL){
	if (n->papa == a->izq)
		return a->der;
	else
		return a->izq;
    }

}
