#include <iostream>
#include <vector>
#include<time.h>
#include <iomanip>
#include <fstream>

using namespace std;

//ESTRUCTURA EN DONDE SE GUARDARÁ LA IMAGEN
typedef struct imagen{
    char formato[3];// p2
    char comentario[1];//comentario
    int nmax;// nivel maximo de intensidad
    int m;
    int n;
    vector <vector<int> > intensidad;
}imagen;

//FUNCIONES QUE SE UTILIZARON
imagen abrir_imagen(const char *nombre);
void escribir_imagen(const char *nombre, imagen Imagen);
int dfs(imagen *Imagen, int inodo, int jnodo, int bandera);

//CONTADOR QUE MEDIRÁ EL TAMAÑO DE LOS COMPONENTES CONECTADOS
int contador=0;

//////////////////////////INICIO DEL MAIN//////////////////////////////////////////
int main(int argc, char *argv[]){
    clock_t t_ini, t_fin;
    double secs;
    imagen Imagen;
    int max=0, posimax=0,posjmax=0, min, posimin=0, posjmin=0, c2=0;
    Imagen=abrir_imagen(argv[1]);
    vector <int > sizescc, pos_i, pos_j;

    //dfs para encontrar componentes conectadas
   for(int i=0; i<Imagen.intensidad.size(); i++){
        for(int j=0; j<Imagen.intensidad[0].size(); j++){
            if(Imagen.intensidad[i][j]>0){
                sizescc.push_back(dfs(&Imagen, i, j,-1));
                cout<<"Componente: "<<c2++<<" Tamaño: "<<contador<<endl;
                contador=0;
                pos_i.push_back(i);
                pos_j.push_back(j);
            }
        }

    }

    //encontrar maximo y minimo de los componentes, asi como sus posiciones
    max=sizescc[0];
    min=sizescc[0];

    for(int i=0; i<sizescc.size();i++){
        if(sizescc[i]>=max){
            max=sizescc[i];
            posimax=pos_i[i];
            posjmax=pos_j[i];
        }
        if(sizescc[i]<=min){
            min=sizescc[i];
            posimin=pos_i[i];
            posjmin=pos_j[i];
        }
    }

    cout<<endl;
    cout<<"maximo: "<<max<<" i:"<<posimax<<" j:"<<posjmax<<endl;
    cout<<"minimo: "<<min<<" i:"<<posimin<<" j:"<<posjmin<<endl;

    //segundo dfs para dejar pintados solo el máximo y el minimo componente
    for(int i=0; i<sizescc.size();i++){
        if((pos_i[i]==posimax && pos_j[i]==posjmax) || (pos_i[i]==posimin && pos_j[i]==posjmin)){
            dfs(&Imagen, pos_i[i], pos_j[i], 255);
        }else{
            dfs(&Imagen, pos_i[i], pos_j[i], 0);
        }
    }

    //guardar la imagen
    escribir_imagen(argv[2], Imagen);

    ofstream guardar("numerocomponentes.txt");

    for(int i=0; i<sizescc.size();i++){
        guardar <<i<<" "<<sizescc[i]<<endl;
    }
    guardar.close();


    t_ini = clock();
    t_fin = clock();
    secs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
    printf("%.16g segundos\n", secs);

    return 0;
}


 imagen abrir_imagen(const char *nombre){
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
        //leer segunda linea para conocer el tamaño m y n o ver si tiene algún comentario;
        fscanf(fin, "%s", Imagen.comentario);
        if(Imagen.comentario[0]=='#'){
        fscanf(fin, "%*[^\n]\n"); //saltar linea del comentario
        fscanf(fin, "%s", m1);
        Imagen.m=atoi(m1);

        fscanf(fin, "%s", m1);
        Imagen.n=atoi(m1);
        }else {
            Imagen.m= atoi(Imagen.comentario);
            fscanf(fin, "%s", m1);
            Imagen.n=atoi(m1);
        }

        // leer tercera linea, nivel máximo de intensidad de la imagen.
        fscanf(fin, "%s", m1);
        Imagen.nmax=atoi(m1);
        vector< int> aux;

        for(int i=0; i<Imagen.n; i++){
		    for(int j=0; j<Imagen.m; j++){
		    	fscanf(fin, "%s", m1);
                aux.push_back(atoi(m1));
		    }
            Imagen.intensidad.push_back(aux);
            aux.clear();
	    }
        fclose( fin );// termina de leer
    }
    return Imagen;
 }

 void escribir_imagen(const char *nombre, imagen Imagen){
     FILE* guardar = fopen(nombre, "w");
        fprintf(guardar, "%s\n", Imagen.formato);
        fprintf(guardar, "%d", Imagen.m);
        fprintf(guardar, " %d\n", Imagen.n);
        fprintf(guardar, "%d\n", Imagen.nmax);
        for(int i=0; i<Imagen.n;i++){
            for(int j=0; j<Imagen.m;j++){
                fprintf(guardar, "%d\n", Imagen.intensidad[i][j]);
            }
        }
        fclose(guardar);
 }

int dfs(imagen *Imagen,  int inodo, int jnodo, int bandera){
    int dx[8]={-1,1,0,0,1,1,-1,-1};
    int dy[8]={0,0,1,-1,-1,1,-1,1};

    Imagen->intensidad[inodo][jnodo]=bandera;
    contador++;
    for(int k=0; k<8; k++){
        int I=inodo+dx[k];
        int J=jnodo+dy[k];
        if(I<0 || J<0 || I>=Imagen->intensidad.size() || J>=Imagen->intensidad[0].size()){
            continue;
        }
        if(Imagen->intensidad[I][J]!=0 && Imagen->intensidad[I][J]!=bandera){
            dfs(Imagen, I, J, bandera);
        }
    }
    return contador;
}
