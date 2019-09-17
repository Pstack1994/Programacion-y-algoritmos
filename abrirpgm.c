#include <stdio.h>
#include <stdlib.h>


typedef struct{
	int **intensidad;
    char formato[3];
    char comentario[1];
    int nmax;
	int m;
	int n;
} imagen;


int main(){
imagen Imagen;

char *nombre= "baboon.ascii.pgm";

FILE* fin;
	fin = fopen( nombre, "r" );
    char m1[100];

    if(fin==NULL){
	    printf("Error: No se abrio %s\n" , nombre );
	}

    //leer la primera linea para ver si está en p2 (ASCII) o p5 (Binario)


    fscanf(fin, "%s", Imagen.formato);

    if(Imagen.formato[0]=='P' && Imagen.formato[1]=='2'){
        printf("El formato es P2\n");
        //leer segunda linea para conocer el tamaño m y n o ver si tiene algún comentario;
        fscanf(fin, "%s", Imagen.comentario);
        if(Imagen.comentario[0]=='#'){
        fscanf(fin, "%*[^\n]\n");
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

        // reservar memoria y guardad datos en la imagen
        Imagen.intensidad=(int **)malloc(Imagen.m*sizeof(int*));

        for(int i=0; i<Imagen.m;i++){
            Imagen.intensidad[i]=(int *)malloc((Imagen.n)*sizeof(int));
        }

        for(int i=0; i<Imagen.m; i++){
		    for(int j=0; j<Imagen.n; j++){
		    	fscanf(fin, "%s", m1);
                Imagen.intensidad[i][j]=atoi(m1);
		    }
	    }

      FILE* guardar = fopen("chango.pgm", "w");
        fprintf(guardar, "%s\n", Imagen.formato);
        fprintf(guardar, "%d", Imagen.m);
        fprintf(guardar, " %d\n", Imagen.n);
        fprintf(guardar, "%d\n", Imagen.nmax);
        for(int i=0; i<Imagen.m;i++){
            for(int j=0; j<Imagen.n;j++){
                fprintf(guardar, "%d\n", Imagen.intensidad[i][j]);
            }
        }
        fclose( fin );
        fclose(guardar);

    }else {
        if(Imagen.formato[0]=='P' && Imagen.formato[1]=='5'){
            printf("El formato es P5\n");


        }
    }


    //liberar imagen
   for(int i=0;i<Imagen.m;i++){
        free(Imagen.intensidad[i]);
    }
    free(Imagen.intensidad);

    return 0;
}
