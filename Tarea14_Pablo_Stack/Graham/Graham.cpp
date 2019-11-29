#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <algorithm>
#include <cmath>
#include <ctime>
#include "../convexhull.h"

using namespace std;

int main(){
    vector<punto> puntos;
    vector<punto> resultado;

    unsigned t0, t1;

    puntos=abrir_imagen("mano.pgm");
    t0=clock();
    resultado=Graham(puntos);
    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Tiempo: " << time << endl;
    return 0;
}
