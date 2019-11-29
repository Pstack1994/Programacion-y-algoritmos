#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cairo.h>
#include "simplifica.h"

using namespace std;


int main(int argc, char *argv[]){
    double tolerancia;
    tolerancia=atof(argv[3]);
    simplificacion(argv[1], argv[2], tolerancia, tolerancia);

    return 0;
}
