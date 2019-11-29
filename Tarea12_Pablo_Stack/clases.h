#include <iostream>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

#ifndef ClASES
#define CLASES
typedef vector<int> individuo;

class Individuo{
    private:
    individuo genes;
    public:
    vector<int> get_indiviuo();
    Individuo(vector<int>);

};

class Poblacion{
    private:
    vector<Individuo> poblacion;
    void inicializa();
    int nbits;
    int elementos;
    public:
    Poblacion(int, int, bool);
    Poblacion();
    void show();
    int get_nbits();
    int get_elementos();
    vector<Individuo> get_poblacion();
    void add(Individuo);
};


class UMDA{
    private:
    int a;
    int b;
    void inicia(Poblacion);
    vector<float> hist;
    vector<float> decimal;
    vector<float> proba;
    multimap<float, Individuo > mapa;
    void convierte(Poblacion);
    void evalua();
    void ordena(Poblacion);
    void probabilidad(Poblacion);
    public:
    UMDA(int, int, Poblacion);
    multimap<float,Individuo> get_mapa();
    vector<float> get_probabilidad();
    void run(int, int);
};

#endif
