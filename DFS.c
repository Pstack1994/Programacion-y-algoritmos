#include <stdio.h>
#include <stdlib.h>

int contador=0;
static const int max=100;

void imprime(int mAdj[][max], int m);
void dfs(int mAdj[][max], int visitados[max], int pila[max],  int nodo, int mnodos, int bandera, int scc);
int leer(int mAdj[][max],int mAdjt[][max], char *argv[]);



int main(int argc, char *argv[]){
    int m;

    int mAdj[max][max];
    int mAdjt[max][max];

    //leer la matriz de adyacencia
    m=leer(mAdj, mAdjt, argv);

    //crear variables
    int visitados[m];
    int pila[m];
    int pila2[m];
    int scc=0;

    //inicializar en 0
    for(int i=0; i<m; i++){
        visitados[i]=0;
        pila2[i]=0;
        pila[i]=0;
    }

    //primer dfs
    for(int i=0; i<m; i++){
        if(visitados[i]==0){
            dfs(mAdj, visitados, pila, i, m, 0, scc);
        }
    }
contador=0;
for(int i=0; i<m; i++){
    visitados[i]=0;
}
    //segundo dfs con la matriz de adyacencia traspuesta
    for(int i=m-1; i>=0;i--){
        if(visitados[pila[i]]==0){
            scc++;
            dfs(mAdjt, visitados, pila2, pila[i], m,1, scc);
        }

    }


    printf("N° de SCC: %d", scc);
    printf("\n");
    for(int i=0; i<m; i++){
       printf("Nodo: %d SCC: %d\n",i, visitados[i]);
    }

    return 0;
}


void imprime(int mAdj[][max], int m){
    for(int i=0; i<m; i++){
        for(int j=0; j<m; j++){
            printf("%d ", mAdj[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void dfs(int mAdj[][max], int visitados[max], int pila[max],  int nodo, int mnodos, int bandera, int scc){
    if (bandera==0){
    visitados[nodo]=1;
    } else {
        visitados[nodo]=scc;
    }

    for(int i=0; i<mnodos; i++){
        if(mAdj[nodo][i]&& !visitados[i]){
            dfs(mAdj, visitados, pila, i, mnodos, bandera, scc);
        }
    }
    pila[contador]=nodo;
    contador++;
    //printf("%d ", nodo);

}

int leer(int mAdj[][max],int mAdjt[][max], char *argv[]){
    int m, n, o, p;

    FILE* fin = NULL;
  fin = fopen( argv[ 1 ] , "r" );

  if(  !fin  ){
    printf("Error: No se abrio %s\n" , argv[ 1 ] );
  }

    fscanf(fin, "%d %d", &m, &n );


    for(int i=0; i<m; i++){
        for(int j=0; j<m; j++){
            mAdj[i][j]=0;
            mAdjt[i][j]=0;
        }
    }

    for(int i=0; i<n; i++){
        fscanf(fin, "%d %d", &o, &p );
        mAdj[o][p]=1;
        mAdjt[p][o]=1;
    }

    return m;
}
