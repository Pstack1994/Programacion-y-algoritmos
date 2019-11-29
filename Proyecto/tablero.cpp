#include <iostream>

using namespace std;
class Tablero{
private:
char t[64];
void imprime_espacio();
void imprime_separador();
void imprime_renglon(int r);
public:
void inicializa_tablero();
void imprime_tablero();
void pinta(int);
};

void Tablero::imprime_espacio(){
    cout << "|   |   |   |   |   |   |   |   |" << endl;
}


void Tablero:: imprime_separador() {
    cout << "+---+---+---+---+---+---+---+---+" << endl;
}

void Tablero::imprime_renglon(int r) {
    cout<<"| ";
    for(int i=0; i<8; i++){
        cout << t[r*8+i] << " | ";
    }
    cout<<endl;
}


void Tablero::imprime_tablero() {

cout<<endl;
    imprime_separador();
    for(int i=0; i<8; i++){
        imprime_espacio();
        imprime_renglon(i);
        imprime_espacio();
        imprime_separador();
    }
}


void Tablero::inicializa_tablero() {
    int i;
    for (i = 0; i < 64; i++) {
        t[i] = 'v';
    }
}

void Tablero::pinta(int pos){
    t[pos]='Q';
}

int main(){
    Tablero prueba;
    prueba.inicializa_tablero();
    prueba.imprime_tablero();
    prueba.pinta(45);
    prueba.imprime_tablero();

    return 0;
}
