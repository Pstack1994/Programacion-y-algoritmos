#include <stdio.h>
#include <string.h>

/* Transforma un caracter a minusculas y cualquier otra cosa que no sea letra lo pone ocmo espacio */
char parse_char(char c) {
    if (65 <= c && c <= 90) {
        return c + 32;
    }

    if (97 <= c && c <= 122) {
        return c;
    }

    return ' ';
}

int main(){

FILE *fp=fopen("texto.txt" , "r");
if (fp==NULL){
    printf("error\n");
}

char line[15], longitud[100];
char arreglo[51];
char aux;
int palabras=0, c=0, a=0;

    while(palabras <10){
        a=0;
        fscanf(fp, "%s", line);
        for(int i=0; i<strlen(line);i++){
            aux=parse_char(line[i]);
            if(aux!=' '){
                arreglo[c]=aux;
                c++;
                a++;
                longitud[palabras]=a;
            }
        }
        if(strlen(line)>1){
            palabras ++;
        }

    }
    arreglo[c]='\0';




/*for(int i=0; i<10;i++){
printf("%d ", longitud[i]);
}*/

    for(int i=0; i<1;i++){
        int str1[longitud[i]];
        for (int j=0; j<longitud[i];j++){
            str1[j]=arreglo[j];
        }
        printf("%s\n", str1);
    }
    return 0;
}


/*#include<stdio.h>
#include<string.h> // permite strcmp y strcpy.

int main()
{
    char nombre[10][20];
    char aux[20];//tiene que ser de igual o mayor tamaño que la segunda componente
    //de nombre porque aquí copiaremos esa cadena.
    int i,j,k;
    int l=0;
    printf("Para terminar escriba * \n");
    do
        {
            printf("Introduce un nombre: ");
            gets(nombre[l]);//lee cadenas y las almacena.
            printf("%s \n", nombre[l]);
            l++;
        }
    while (strcmp(nombre[l-1],"*")!=0);//permite comparar cadenas.

    // ORDENAR CADENAS
    for(i=0; i<l-1; i++)
    {
        k=i;
        strcpy(aux, nombre[i]);
        for(j=i+1; j<l; j++)
        {
            if(strcmp(nombre[j], aux)<0)
            {
                k=j;
                strcpy(aux, nombre[j]);
               //permite hacer una copia auxiliar de la cadena nombre[j];
            }
        }
        strcpy(nombre[k],nombre[i]);
        strcpy(nombre[i],aux);
    }

    for(i=0; i<l; i++)
    {
        printf("%s",nombre[i]);
        printf("\n");
    }

  return 0;
}
*/
