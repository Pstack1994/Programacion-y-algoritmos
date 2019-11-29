#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include "clases.h"

using namespace std;

int main(){
    int nbits=20;
    int nelementos=400;

    Poblacion p(nbits,nelementos, 0);
    UMDA hola(-10,10,p);
    hola.run(nbits, nelementos);
    return 0;
}
