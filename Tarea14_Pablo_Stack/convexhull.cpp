#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include "convexhull.h"
#include <cmath>

using namespace std;
punto p;

punto encuentra_inicio(vector<pair<double, double> > puntos){
    sort(puntos.begin(),puntos.end(),orden);
    return puntos[0];
}

vector<punto> cargar_datos(string nombre){
    ifstream abrir(nombre);

    vector<punto> puntos;
    double x, y;
    while (true){
        abrir>>x;
        abrir>>y;
        if(abrir.eof()){
            break;
        }

        puntos.push_back(make_pair(x,y));
    }
    return puntos;
}

double producto_cruz(punto p1, punto p2, punto p3){
    int y1 = p1.second - p2.second;
    int y2 = p1.second - p3.second;
    int x1 = p1.first - p2.first;
    int x2 = p1.first - p3.first;
    return y2*x1 - y1*x2; //if result < 0, c in the left, > 0, c in the right, = 0, a,b,c are collinear
}

bool orden(const punto &p1, const punto &p2){
    return p1.first < p2.first;
}

void imprime_puntos(vector<punto>puntos){
    for(int i=0; i<puntos.size(); i++){
        cout<<"x: "<<puntos[i].first<<" y: "<<puntos[i].second<<endl;
    }
}

int distancia(punto p1, punto p2, punto p3){
   int y1 = p1.second - p2.second;
   int y2 = p1.second - p3.second;
   int x1 = p1.second - p2.second;
   int x2 = p1.first - p3.first;
   int d1 = (y1*y1 + x1*x1);
   int d2 = (y2*y2 + x2*x2);
   if(d1 == d2){
        return 0;
    } else if(d1 < d2){
        return -1;
    }
   return 1;
}

vector<punto> Marcha_Jarvis(vector<punto>puntos){
    punto actual, pi;
    pi=encuentra_inicio(puntos);
    actual=pi;

    set<punto> resultado;
    vector<punto> res;
    res.push_back(actual);
    resultado.insert(actual);
    vector<punto> *colineales = new vector<punto>;

    while(true){
        punto proximo=puntos[0];
        for(int i=1; i<puntos.size(); i++){
            if(puntos[i]==actual){
                continue;
            }
            int producto= producto_cruz(actual, proximo, puntos[i]);

            if(producto>0){
                proximo=puntos[i];
                colineales=new vector<punto>;
            }else if(producto==0){//ocurre cuando los tres puntos son colineales
                if(distancia(actual, proximo, puntos[i])<0){
                    colineales->push_back(proximo);
                    proximo=puntos[i];
                }else{
                    colineales->push_back(puntos[i]);
                }
            }
        }

        vector<punto>::iterator it;

        for(it=colineales->begin(); it!=colineales->end(); it++){
            if(!resultado.count(*it)){
                res.push_back(*it);
            }
            resultado.insert(*it); //agrega los puntos colineales al resultado
        }

        if(proximo==pi){
            break;
        }
        if(!resultado.count(proximo)){
            res.push_back(proximo);
        }
        resultado.insert(proximo);
        actual=proximo;
    }
    res.push_back(res[0]);

    ofstream guardar("envolvente_jarvis.txt");
    for(int i=0; i<res.size(); i++){
        guardar<<res[i].first<<" "<<res[i].second<<endl;
    }

    return res;
}

vector<punto>datos_aleatorios(int n){
    srand(0);
    vector<punto> puntos;
    ofstream guardar("aleatorios.txt");
    for(int i=0; i<n; i++){
        puntos.push_back(make_pair(((rand()%1000)-500)/10.0,((rand()%1000)-500)/10.0));
        guardar<<puntos[i].first<<" "<<puntos[i].second<<endl;
    }
    guardar.close();
    return puntos;
}

int pos_punto_inicial(vector<punto> puntos){
    double ymin=puntos[0].second, posmin=0;
    for(int i=1; i<puntos.size(); i++){
        if(puntos[i].second<ymin || (puntos[i].second == ymin && puntos[i].first < puntos[posmin].first)){
            ymin=puntos[i].second;
            posmin=i;
        }
    }
    return posmin;
}

void intercambia_puntos(punto &p1, punto &p2){
    punto aux;
    aux=p1;
    p1=p2;
    p2=aux;
}

int producto_cruz_g(punto p1, punto p2, punto p3){
    int y1 = p1.second - p2.second;
    int y2 = p1.second - p3.second;
    int x1 = p1.first - p2.first;
    int x2 = p1.first - p3.first;

    int valor=y2*x1 - y1*x2;

    return valor;
}

int distancia_g(punto p1, punto p2){
    int dist;
    dist=(p1.first-p2.first)*(p1.first-p2.first)+(p1.second-p2.second)*(p1.second-p2.second);
    return dist;
}

bool ordena_por_angulo(const punto &p1, const punto &p2){
    int valor;
    valor=producto_cruz_g(p, p1, p2);
    if(valor==0){
        if(distancia_g(p,p1)< distancia_g(p, p2)){
            return 1;
        }else{
            return 0;
        }
    }
    double c1x=p1.first - p.first, c1y=p1.second - p.second;
    double c2x=p2.first - p.first, c2y=p2.second - p.second;
    if(atan2(c1y,c1x)-atan2(c2y, c2x)<0){
        return 1;
    }else{
        return 0;
    }

}

bool orientacion(punto p1, punto p2, punto p3){
    int valor=producto_cruz_g(p1,p2,p3);

    if(valor>0){
        return 1; //en sentido de las manacillas
    }else{
        return 0; //en contra de las manecillas
    }
}

vector<punto>Graham(vector<punto> puntos){
     //obtener la posicion del punto mas abajo y a la izquierda
    int posmin=pos_punto_inicial(puntos);
    //poner pareja de puntos con el valor minimo de y y de x en la posicion 0
    intercambia_puntos(puntos[0], puntos[posmin]);
    //ordenar los n-1 puntos restantes con respecto al punto[0]
    p= puntos[0];
    sort(puntos.begin()+1, puntos.end(), ordena_por_angulo);
    //declarar vector s que servira como pila
    vector<punto> s;
    s.push_back(puntos[puntos.size()-1]);
    s.push_back(puntos[0]);
    s.push_back(puntos[1]);

    int i=2;
    while(i<puntos.size()){
        int j= (int)s.size()-1;
        if(orientacion(s[j-1], s[j], puntos[i])){
            s.push_back(puntos[i++]);
        }else{
            s.pop_back();
        }
    }
    ofstream guardar("envolvente_Graham.txt");
    for(int i=0; i<s.size(); i++){
        guardar<<s[i].first<<" "<<s[i].second<<endl;
    }

    //imprime_puntos(s);
    return s;
}

 vector<punto> abrir_imagen(const char *nombre){
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
    vector<punto> puntos;
    ofstream guardap("mano_datos.txt");
    for(int i=0; i<Imagen.m; i++){
        for(int j=0; j<Imagen.n; j++){
            if(Imagen.intensidad[i][j]>0){
                puntos.push_back(make_pair(i,j));
                guardap<<i<<" "<<j<<endl;
            }
        }
    }
    return puntos;
 }
