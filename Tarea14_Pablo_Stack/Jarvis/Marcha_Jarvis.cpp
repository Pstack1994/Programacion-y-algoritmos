#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <ctime>
#include "../convexhull.h"

using namespace std;

int main(){
    vector<punto> puntos;
    punto actual, pi;

    unsigned t0, t1;

    t0=clock();
    puntos=datos_aleatorios(100);
    vector<punto> resultado;
    resultado=Marcha_Jarvis(puntos);
    t1 = clock();

    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Tiempo: " << time << endl;
    //numero de datos aleatorios
    cout<<endl;

    imprime_puntos(resultado);

    return 0;
}
