#include <stdio.h>
#include <stdlib.h>

typedef struct Pila{
    int *arr;
    int m;
    int top;
    int valor;
}Pila;

Pila push(Pila entrada, int num);
Pila pop (Pila entrada, Pila salida);
void ver_final(Pila entrada);

/*Hay tres funciones:
1) push sirve para ingresar un numero a la pila de entrada
2) pop sirve para eliminar el primer elemento que se ingreso a la pila (simulando una cola con dos pilas)
3) muestra el ultimo elemento de la pila.
*/
int main(){
    Pila entrada;
    Pila salida;

    //tamaño de las pilas
    entrada.m=5;
    salida.m=5;
    //inicializacion de las posiciones
    entrada.top=salida.top=0;
    //creación de memoria
    entrada.arr=(int*)calloc(entrada.m, sizeof(int));
    salida.arr=(int*)calloc(salida.m, sizeof(int));

    //ejemplo
    entrada=push(entrada,1);
    entrada=push(entrada,2);
    entrada=push(entrada,3);
    entrada=push(entrada,4);
    entrada=push(entrada,5);
    ver_final(entrada);
    entrada=pop(entrada,salida);
    ver_final(entrada);
    entrada=pop(entrada,salida);
    ver_final(entrada);
    entrada=pop(entrada,salida);
    ver_final(entrada);
    entrada=pop(entrada,salida);
    ver_final(entrada);
    entrada=pop(entrada,salida);
    ver_final(entrada);





    free(entrada.arr);
    free(salida.arr);
    return 0;
}

Pila push(Pila entrada, int num){
    if(entrada.top==entrada.m){printf("No hay espacio para insertar\n");return entrada;}
    entrada.arr[entrada.top]=num;
    entrada.top++;
    return entrada;
}
Pila pop (Pila entrada, Pila salida){
    //pasar elementos de una pila a la otra
    if(entrada.top==0){printf("La pila esta vacia, no se pueden seguir removiendo elementos \n");return entrada;}
    entrada.valor=entrada.arr[0];
    entrada.top--;
    while(entrada.top>0){
        salida.arr[salida.top]=entrada.arr[entrada.top];
        salida.top++;
        entrada.top--;
    }
    salida.top--;
    while(salida.top>=0){
        entrada.arr[entrada.top]=salida.arr[salida.top];
        salida.top--;
        entrada.top++;
    }
    printf("El valor que sacaste de la cola es: %d\n",entrada.valor);
    return entrada;

}

void ver_final(Pila entrada){
    if(entrada.top==0){
        printf("La pila está vacia\n");
    }else{
    printf("El final de la cola es: %d\n", entrada.arr[0]);
    }
}
