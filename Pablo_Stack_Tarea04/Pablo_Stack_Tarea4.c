#include <stdio.h>
#include <stdlib.h>

// se crea una estructura para almacenar la imagen;
typedef struct{
	int **intensidad;//valores de 0 a 255
    char formato[3];// p2 o p5
    char comentario[1];//comentario
    int nmax;// nivel maximo de intensidad
	int m;//filas
	int n;//columnas
    int a;//bandera para saber como escribir dependiendo del formato
} imagen;

 imagen abrir_imagen(char *nombre); //prototipo de funcion
 void escribir_imagen(char *nombre, imagen Imagen);//prototipo de funcion


//inicio del main
int main(){
imagen Imagen;
char *nombre= "baboon.ascii.pgm";//nombre de la imagen que vamos a abrir
char *nombreg="chango2.pgm";//nombre con el que se guardara

Imagen=abrir_imagen(nombre);
escribir_imagen(nombreg, Imagen);

//liberar memoria de imagen
    for(int i=0;i<Imagen.m;i++){
        free(Imagen.intensidad[i]);
    }
    free(Imagen.intensidad);

    return 0;
}





 imagen abrir_imagen(char *nombre){
    imagen Imagen;
    FILE* fin;
	fin = fopen( nombre, "r" );
    char m1[100];

    if(fin==NULL){
	    printf("Error: No se abrio %s\n" , nombre );
	}

    //leer la primera linea para ver si está en p2 (ASCII) o p5 (Binario)
    fscanf(fin, "%s", Imagen.formato);


    if(Imagen.formato[0]=='P' && Imagen.formato[1]=='2'){
        Imagen.a=2;
        //leer segunda linea para conocer el tamaño m y n o ver si tiene algún comentario;
        fscanf(fin, "%s", Imagen.comentario);
        if(Imagen.comentario[0]=='#'){
        fscanf(fin, "%*[^\n]\n"); //saltar linea del comentario
        printf("%s\n", Imagen.comentario);

        fscanf(fin, "%s", m1);
        Imagen.m=atoi(m1);

        fscanf(fin, "%s", m1);
        Imagen.n=atoi(m1);

        printf("%d\n", Imagen.m);
        printf("%d\n", Imagen.n);
        }else {
            Imagen.m= atoi(Imagen.comentario);
            fscanf(fin, "%s", m1);
            Imagen.n=atoi(m1);
        }

        // leer tercera linea, nivel máximo de intensidad de la imagen.
        fscanf(fin, "%s", m1);
        Imagen.nmax=atoi(m1);
        printf("%d \n", Imagen.nmax);

        // reservar memoria y guardar datos en la imagen
        Imagen.intensidad=(int **)malloc(Imagen.m*sizeof(int*));

        for(int i=0; i<Imagen.m;i++){
            Imagen.intensidad[i]=(int *)malloc((Imagen.n)*sizeof(int));
        }

        for(int i=0; i<Imagen.m; i++){
		    for(int j=0; j<Imagen.n; j++){
		    	fscanf(fin, "%s", m1);
                Imagen.intensidad[i][j]=atoi(m1);//leer imagen
		    }
	    }
        fclose( fin );// termina de leer
    }else {
        if(Imagen.formato[0]=='P'  && Imagen.formato[1]=='5'){//caso que imagen sea p5
        Imagen.a=5;
        fscanf(fin, "%s", Imagen.comentario);
        if(Imagen.comentario[0]=='#'){
        fscanf(fin, "%*[^\n]\n");// saltar linea del comentario
        printf("%s\n", Imagen.comentario);

        fscanf(fin, "%s", m1);
        Imagen.m=atoi(m1);

        fscanf(fin, "%s", m1);
        Imagen.n=atoi(m1);

        printf("%d\n", Imagen.m);
        printf("%d\n", Imagen.n);
        }else {
            Imagen.m= atoi(Imagen.comentario);
            fscanf(fin, "%s", m1);
            Imagen.n=atoi(m1);
        }


        // leer tercera linea, nivel máximo de intensidad de la imagen.
        fscanf(fin, "%s\n", m1);
        Imagen.nmax=atoi(m1);
        printf("%d \n", Imagen.nmax);

        // reservar memoria y guardad datos en la imagen
        Imagen.intensidad=(int **)malloc(Imagen.m*sizeof(int*));

        for(int i=0; i<Imagen.m;i++){
            Imagen.intensidad[i]=(int *)malloc((Imagen.n)*sizeof(int));
        }

        for(int i=0; i<Imagen.m; i++){
		    for(int j=0; j<Imagen.n; j++){
		    	Imagen.intensidad[i][j]=getc(fin);// se utiliza get c porque es un caracter
		    }
	    }
        fclose( fin );//termina de leer
        }
    }
    return Imagen;


 }

 void escribir_imagen(char *nombre, imagen Imagen){
     if(Imagen.a==2){
     FILE* guardar = fopen(nombre, "w");
        fprintf(guardar, "%s\n", Imagen.formato);
        fprintf(guardar, "%d", Imagen.m);
        fprintf(guardar, " %d\n", Imagen.n);
        fprintf(guardar, "%d\n", Imagen.nmax);
        for(int i=0; i<Imagen.m;i++){
            for(int j=0; j<Imagen.n;j++){
                fprintf(guardar, "%d\n", Imagen.intensidad[i][j]);
            }
        }
        fclose(guardar);
     }else if (Imagen.a==5){
                 FILE* guardar = fopen(nombre, "w");
        fprintf(guardar, "%s\n", Imagen.formato);
        fprintf(guardar, "%d", Imagen.m);
        fprintf(guardar, " %d\n", Imagen.n);
        fprintf(guardar, "%d\n", Imagen.nmax);
        for(int i=0; i<Imagen.m;i++){
            for(int j=0; j<Imagen.n;j++){
                fprintf(guardar, "%c", Imagen.intensidad[i][j]);
            }
        }
        fclose(guardar);
     } else {
         printf("No es un formato valido");
        }
 }
