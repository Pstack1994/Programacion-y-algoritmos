#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include "clases.h"

using namespace std;

Individuo::Individuo(vector<int> aux){
    genes=aux;
}

vector<int> Individuo::get_indiviuo(){
    return genes;
}

Poblacion::Poblacion(int _nbits, int _elementos, bool bandera){
    nbits=_nbits;
    elementos= _elementos;
    if(bandera==0){
    inicializa();
    }else{

    }
}

void Poblacion::add(Individuo ind){
    poblacion.push_back(ind);
}

void Poblacion::inicializa(){
    double digito;
    srand(time(NULL));
    for(int i=0; i<elementos; i++){
        individuo aux;
        for(int j=0; j<nbits; j++){
            digito= rand()%2;
            aux.push_back(digito);
        }
        Individuo ind(aux);
        poblacion.push_back(ind);
    }
}

int Poblacion::get_nbits(){
    return nbits;
}

int Poblacion::get_elementos(){
    return elementos;
}
vector<Individuo> Poblacion::get_poblacion(){
    return poblacion;
}

void Poblacion::show(){
    for(int i=0; i<poblacion.size(); i++){
        individuo aux;
        aux=poblacion[i].get_indiviuo();
        for(int j=0; j<aux.size(); j++){
            cout<<aux[j]<<" ";
        }
        cout<<endl;
    }
}

void UMDA::inicia(Poblacion p){
    int size= p.get_nbits();
    int size2= p.get_elementos();

    for(int i=0; i<size; i++){
        hist.push_back(0);
        proba.push_back(0);
    }
    for(int i=0; i<size2; i++){
        decimal.push_back(0);
    }
}

UMDA::UMDA(int _a, int _b, Poblacion p){
    a= _a;
    b= _b;
    inicia(p);
}

void UMDA::convierte(Poblacion p){
    int m=p.get_elementos();
    int n= p.get_nbits();
    double dec;
    vector<Individuo> aux1;
    aux1=p.get_poblacion();

    for(int i=0; i<m; i++){
        dec=0;
        individuo aux;
        aux=aux1[i].get_indiviuo();
        for(int j=n-1; j>=0; j--){
            if(aux[j]==1){
                dec+=pow(2,n-j-1);
            }

        }
        decimal[i]=dec;
    }

    double delta=(b-a)/pow(2,n);
    for(int i=0; i<m; i++){
        decimal[i]=a + delta*decimal[i];
    }
}

void UMDA::evalua(){
    for (int i=0; i<decimal.size(); i++){
        decimal[i]=2*(decimal[i]-2)*(decimal[i]-2)+4;
    }
}

 multimap<float,Individuo> UMDA::get_mapa(){
     return mapa;
 }

void UMDA::ordena(Poblacion p){
    mapa.clear();
    vector<Individuo> aux;
    individuo aux2;
    aux=p.get_poblacion();

    for(int i=0; i<decimal.size(); i++){
        mapa.insert({decimal[i], aux[i].get_indiviuo()});
    }

    multimap<float, Individuo > ::iterator it;
    for(it=mapa.begin(); it!=mapa.end(); it++){
        for(int i=0; i<p.get_nbits(); i++){
        }
    }
}

void UMDA::probabilidad(Poblacion p){
    double porcentaje=0.6;
    int i=0;
    double nseleccion=porcentaje*p.get_elementos();
    for(int i=0; i<p.get_nbits(); i++){
        proba[i]=0;
    }
    multimap<float, Individuo > ::iterator it;

    for(it=mapa.begin(); i<int(nseleccion);it++){
        individuo aux2;
        aux2=it->second.get_indiviuo();
        for(int j=0; j<p.get_nbits(); j++){
            proba[j]+=aux2[j]/nseleccion;
        }
        i++;
    }
}

vector<float> UMDA::get_probabilidad(){
    return proba;
}

void UMDA::run(int _nbits, int _elementos){
    Poblacion p(_nbits, _elementos, 0);
    convierte(p);
    evalua();
    ordena(p);
    probabilidad(p);
    for(int k=0; k<100; k++){
        Poblacion p1(_nbits, _elementos, 1);
        for(int i=0; i<p1.get_elementos(); i++){
        vector<int> aux;
        double digito;
        for(int j=0; j<p1.get_nbits(); j++){
            digito= (rand()%100)/100.0;
            if(digito>proba[j]){
                aux.push_back(0);
            }else{
                aux.push_back(1);
            }
        }
        Individuo nuevo(aux);
        p1.add(nuevo);

    }
    convierte(p1);
    evalua();
    ordena(p1);
    probabilidad(p1);
    }

    multimap<float, Individuo > ::iterator it;
    individuo aux;
    it=mapa.begin();
    aux=it->second.get_indiviuo();
    double dec=0;
    for(int j=_nbits-1; j>=0; j--){
        if(aux[j]==1){
            dec+=pow(2,_nbits-j-1);
        }

     }
     cout<<"x minima: "<<a+((b-a)/pow(2,_nbits))*dec<<" f(x): "<<it->first<<endl;
}
