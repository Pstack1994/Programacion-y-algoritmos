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
void rotacion_der(nodo *papa, int bool);
void rotacion_izq(nodo *papa, int bool);
void verifica(nodo *nuevo, nodo **n, nodo **root);
nodo *abuelo (nodo *n);
nodo *tio(nodo *n);
void insertar(nodo **n, nodo *papa, int numero, nodo **root);
void imprime(nodo *n);
void liberar(nodo *n);
void buscar(nodo *n, int numero);

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


void insertar(nodo **n, nodo *papa, int numero, nodo **root){
    if(*n==NULL){
        nodo *nuevo= malloc(sizeof(nodo));
        nuevo->dato=numero;
        nuevo->izq=NULL;
        nuevo->der=NULL;
        nuevo->papa=papa;

        if(nuevo->papa==NULL){
            nuevo->color=NEGRO;
        }else{
            nuevo->color=ROJO;
        }
        *n=nuevo;
        verifica(nuevo, n, root);

        return;
    }

    if(numero>(*n)->dato){
        insertar(&(*n)->der,*n, numero, root);
    }else{
        insertar(&(*n)->izq,*n, numero, root);
    }
}

void imprime(nodo *n){
    if(n==NULL){return; }
    printf("%d ", n->dato);
    if(n->papa != NULL){
    printf(", papa(%d)", n->papa->dato);
    }
    printf(", color: %u \n", n->color);
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

void rotacion_der(nodo *nuevo, int bool){

    nodo *padre=nuevo->papa;
    nuevo->papa=padre->papa;

    if(padre->papa!=NULL){
        if(padre->papa->der==padre){
            padre->papa->der=nuevo;
        }else {
            padre->papa->izq=nuevo;
        }
    }
        nodo *derecha=nuevo->der;
        nuevo->der=padre;
        padre->papa=nuevo;
        padre->izq=derecha;
        if(derecha!=NULL){
            derecha->papa=padre;
        }

        if(bool){
            nuevo->color=NEGRO;
            padre->color=ROJO;
        }
}

void rotacion_izq(nodo *nuevo, int bool){

    nodo *padre=nuevo->papa;
    nuevo->papa=padre->papa;

    if(padre->papa!=NULL){
        if(padre->papa->der==padre){
            padre->papa->der=nuevo;
        }else {
            padre->papa->izq=nuevo;
        }
    }
        nodo *izquierda=nuevo->izq;
        nuevo->izq=padre;
        padre->papa=nuevo;
        padre->der=izquierda;
        if(izquierda!=NULL){
            izquierda->papa=padre;
        }

        if(bool){
            nuevo->color=NEGRO;
            padre->color=ROJO;
        }
}

nodo *abuelo(nodo *n){
    if((n->papa!=NULL) && (n->papa!=NULL)){
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
    return NULL;

}

void verifica(nodo *nuevo, nodo **n, nodo **root){
    if(nuevo->papa==NULL || nuevo->papa->color==NEGRO){
        return;
    }
    nodo *Tio=tio(nuevo);
    nodo *Abuelo=abuelo(nuevo);

    //cambiar color si papá y tio son iguales
    if(Tio!=NULL && Tio->color!=NEGRO){
        if(Tio->color==ROJO && nuevo->papa->color==ROJO){
            cambia_color(nuevo->papa);
        }
    }else{
        //Rotacion derecha
        if(nuevo->papa->izq==nuevo && Abuelo->izq==nuevo->papa){
            rotacion_der(nuevo->papa, 1);
        }
        //rotacion izq
        if(nuevo->papa->der==nuevo && Abuelo->der==nuevo->papa){
            rotacion_izq(nuevo->papa, 1);
        }
        //Rotacion derecha-izquierda
        if(nuevo->papa->izq==nuevo && Abuelo->der==nuevo->papa){
            rotacion_der(nuevo, 0);
            rotacion_izq(nuevo,1 );
        }
        //Rotacion izquierda-derecha
        if(nuevo->papa->der==nuevo && Abuelo->izq==nuevo->papa){
            rotacion_izq(nuevo,0 );
            rotacion_der(nuevo, 1);
        }

        //cambio raiz
        if(nuevo->papa->papa==NULL){
            *root=nuevo->papa;
        }


    }
   verifica(Abuelo, n, root);
}

void buscar(nodo *n, int numero){
    if(n==NULL){
        printf("\nEl numero: %d NO está en el arbol\n", numero);
        return;
    }
    if(numero == n->dato){
        printf("\nEl numero: %d SI está en el arbol\n", numero);
        return;
    }
    if(numero > n->dato){
        buscar(n->der, numero);
    }else{
        buscar(n->izq, numero);
    }

}
