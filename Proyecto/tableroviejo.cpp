#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;


void imprime_espacio() {
    cout << "   |   |" << endl;
}

void imprime_separador() {
    cout << "---+---+---" << endl;
}

void imprime_renglon(char t[9], int r) {
    cout << " " << t[r*3+0] << " | " << t[r*3+1] << " | " << t[r*3+2] << endl;
}

void imprime_tablero(char t[9]) {

cout<<endl;
cout<<"el juego consiste en un rompecabezas de 3 x 3, debe ser armado en orden"<<endl;
cout<<"alfabetico (a, b, c, etc..) el asterisco representa un espacio en blanco"<<endl;
cout<<"y debe de quedar en la esquina inferior derecha, tienes 50 movimientos"<<endl;
cout<<"para armarlo o perderas."<<endl; cout<<endl;

    imprime_espacio();
    imprime_renglon(t, 0);
    imprime_espacio();
    imprime_separador();
    imprime_espacio();
    imprime_renglon(t, 1);
    imprime_espacio();
    imprime_separador();
    imprime_espacio();
    imprime_renglon(t, 2);
    imprime_espacio();
}


void inicializa_tablero(char t[9]) {
    int i;
    for (i = 0; i < 9; i++) {
        t[i] = 97 + i;
        if(t[8]=105){t[8]='*';}
        }
}

void revolver(char t[9], char &a){
char  j;
int i, x;
    srand(time(0));
    for (i=0; i<45; i++){

        x= 48 + rand() %4;
        switch (x){
            case '1': if(a==6 || a==3 || a==0) {cout<<"";} else {j=t[a]; t[a]=t[a-1];t[a-1]=j; a= a-1;} break;
            case '2': if(a==2 || a==1 || a==0) {cout<<"";} else {j=t[a]; t[a]=t[a-3]; t[a-3]=j;a=a-3;} break;
            case '0': if(a==6 || a==7 || a==8) {cout<<"";} else {j=t[a]; t[a]=t[a+3]; t[a+3]=j;a=a+3;}break;
            case '3': if(a==2 || a==5 || a==8) {cout<<"";} else {j=t[a]; t[a]=t[a+1]; t[a+1]=j; a=a+1;}break;

        }
    }
}

char mover(char t[9], char &a){
int i;
char c, j;
    system ("cls");

    for(i=1;i<51; ){

    imprime_tablero(t);

        cout<<"elije una opcion: "<<endl;
        cout<<"0) abajo"<<endl;
        cout<<"1) iquierda"<<endl;
        cout<<"2) arriba"<<endl;
        cout<<"3) derecha"<<endl;
        cin>>c;


        switch (c){
            case '1': if(a==6 || a==3 || a==0) {cout<<"elije otra opcion";} else {j=t[a]; t[a]=t[a-1];t[a-1]=j; a= a-1;} break;
            case '2': if(a==2 || a==1 || a==0) {cout<<"elije otra opcion";} else {j=t[a]; t[a]=t[a-3]; t[a-3]=j;a=a-3;} break;
            case '0': if(a==6 || a==7 || a==8) {cout<<"elije otra opcion";} else {j=t[a]; t[a]=t[a+3]; t[a+3]=j;a=a+3;}break;
            case '3': if(a==2 || a==5 || a==8) {cout<<"elije otra ocpion";} else {j=t[a]; t[a]=t[a+1]; t[a+1]=j; a=a+1;}break;

        }
        system("cls");
        if(c=='1' || c=='2' || c== '3' || c=='0'){cout<<"llevas " << i++ << " movimientos"<<endl;} else { cout<<"elije otra opcion"<<endl;}
        if(t[0]=='a' && t[1]=='b' && t[2]=='c'&& t[3]=='d' && t[4]=='e' && t[5]=='f'&& t[6]=='g' && t[7]=='h' && t[8]=='*'){
                system ("cls"); cout<<endl;cout<<"G A N A S T E"<<endl;cout<<endl; cout<<"Para volver a jugar presiona algun caracter, para terminar el juego presiona n: "; cin>> c;
                    if(c=='s'){i=1;system("cls");inicializa_tablero(t); revolver(t,a);}
                    if(c=='n'){return 0;}
                    if(c!='s'){ i=1;system("cls");inicializa_tablero(t); revolver(t,a), mover(t,a);}
        }
    } cout<<endl; cout<<"p e r d i s t e"<<endl; cout<<endl; cout<<"Para volver a jugar presiona algun caracter, para terminar el juego presiona n: "; cin>> c;
                    if(c=='s'){i=1;system("cls");inicializa_tablero(t); revolver(t,a), mover(t,a);}
                    if(c=='n'){return 0;}
                    if(c!='s'){ i=1;system("cls");inicializa_tablero(t); revolver(t,a), mover(t,a);}

return 0;
}







int main() {
    char t[9];
    char a=8;
    inicializa_tablero(t);
    imprime_tablero(t);
    revolver(t, a);
    mover(t, a);
    return 0;
}
