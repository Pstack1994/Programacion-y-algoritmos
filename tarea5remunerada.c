#include <stdio.h>
#include <string.h>
#include <math.h>


char conv_char(char c);
void leer_npalabras(FILE *fp, int num_palabras, int num_letras, char arreglo[num_palabras][num_letras]);
void bubblesort(int num_palabras, int num_letras, char arreglo[num_palabras][num_letras]);
int  palabras_unicas(int num_palabras, int num_letras, char arreglo[num_palabras][num_letras]);
void arreglo_unico(int num_palabras, int num_letras, int n_palabras, char arreglo [num_palabras][num_letras], char arreglo_dif[n_palabras][num_letras]);
int busqueda_binaria(int n_palabras, int num_letras, char arreglo [n_palabras][num_letras]);

int main(){

    //abrir archivo .txt
    FILE *fp=fopen("2donq10.txt" , "r");
    if (fp==NULL){
        printf("error\n");
    }

    //inicializar numero de letras por string y numero de palabras
    int num_palabras, num_letras=30;
    printf("Ingrese el número de palabras: ");
    scanf("%d", &num_palabras);
    char arreglo[num_palabras][num_letras];

    //lee las n palabras y las coloca en arreglo[][]
    leer_npalabras(fp, num_palabras, num_letras, arreglo);

    //Ordenamiento burbuja
    bubblesort(num_palabras, num_letras, arreglo);

    //contar cuantas palabras diferentes hay
    int n_palabras=0;
    n_palabras=palabras_unicas(num_palabras, num_letras, arreglo);
    //poner en arreglo_dif[][] las palabras diferentes
    char arreglo_dif[n_palabras][num_letras];
    arreglo_unico(num_palabras,num_letras,n_palabras,arreglo,arreglo_dif);

   //imprimir arreglo_dif[][] ordenado y sin palabras repetidas
    for(int i=0; i<n_palabras;i++){
        printf("%s \n", arreglo_dif[i]);
    }

    //busqueda binaria de alguna palabra
    int bandera;
    bandera=busqueda_binaria(n_palabras, num_letras, arreglo_dif);

    fclose(fp);
    return 0;
}


char conv_char(char c) {
    // mayuscula a minuscula
    if (65 <= c && c <= 90) {
        return c + 32;
    }
    // minuscula
    if (97 <= c && c <= 122) {
        return c;
    }
    // A con acento
    if (c == -127 || c == -95) {
        return 'a';
    }
    // E con acento
    if (c == -119 || c == -87) {
        return 'e';
    }
    // I con acento
    if (c == -115 || c == -83) {
        return 'i';
    }
    // O con acento
    if (c == -109 || c == -77) {
        return 'o';
    }
    // U con acento
    if (c == -102 || c == -70) {
        return 'u';
    }
    // U con dieresis
    if (c == -100 || c == -68) {
        return 'u';
    }
    //ñ
    if(c==-111 || c==-79){
        return 'n';
    }

    return ' ';
}

void leer_npalabras(FILE *fp, int num_palabras, int num_letras, char arreglo[num_palabras][num_letras]){
    int palabra=0, c=0;
    char caracter='a';
    char aux;

    while(!feof(fp) && palabra<num_palabras){
        caracter=conv_char(getc(fp));
        if(caracter!=' '){
            arreglo[palabra][c]=caracter;
            c++;
            while(caracter != ' '){
                aux=getc(fp);
                if(aux==-61){
                    continue;
                }else{
                caracter=conv_char(aux);
                arreglo[palabra][c]=caracter;
                c++;
                }
            }
        }
        if(c!=0){
            arreglo[palabra][c-1]='\0';
            c=0;
            palabra++;
        }
    }
}

void bubblesort(int num_palabras, int num_letras, char arreglo[num_palabras][num_letras]){
    char aux[num_letras];
    for(int i=0; i<num_palabras; i++){
        for(int k=0; k<num_palabras-1;k++){
            if(strcmp(arreglo[k], arreglo[k+1])>0){
            strcpy(aux,arreglo[k+1]);
            strcpy(arreglo[k+1], arreglo[k]);
            strcpy(arreglo[k],aux);
            }
        }
    }
}

int  palabras_unicas(int num_palabras, int num_letras, char arreglo[num_palabras][num_letras]){
    int n_palabras=0;
    for(int i=0; i< num_palabras;i++){
        if( strcmp(arreglo[i],arreglo[i+1])!=0){
            n_palabras++;
        }
    }
    return n_palabras;
}

void arreglo_unico(int num_palabras, int num_letras, int n_palabras, char arreglo [num_palabras][num_letras], char arreglo_dif[n_palabras][num_letras]){
    int a=0;
    for(int i=0; i< num_palabras;i++){
        if( strcmp(arreglo[i],arreglo[i+1])!=0){
            strcpy(arreglo_dif[a],arreglo[i]);
            a++;
        }
    }
}

int busqueda_binaria(int n_palabras, int num_letras, char arreglo_dif[n_palabras][num_letras]){
    char busqueda[num_letras];
    printf("Ingresa la palabra que deseas buscar: ");
    scanf("%s", &busqueda);

    int p_medio,inicio=0,final=n_palabras,comparacion;

    do{
        p_medio=floor((inicio+final)/2);
        comparacion=strcmp(busqueda, arreglo_dif[p_medio]);
        if(comparacion<0){
            final=p_medio-1;
        }
        if(comparacion>0){
            inicio=p_medio+1;
        }
        if(comparacion==0){
            printf("Se encontró en la posición: %d\n", p_medio);
            return 1;
        }

    }while(inicio<=final);

    printf("No se encontró la palabra: %s\n",busqueda);
    return 0;
}
