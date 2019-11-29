#ifndef ARBOL
#define ARBOL

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
#endif
