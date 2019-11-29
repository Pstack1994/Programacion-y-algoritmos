#include <iostream>
#include<fstream>
#include<string>
#include <map>

using namespace std;

#define MAX(x, y) (((x) > (y)) ? (x) : (y));

int main(int argc, char *argv[]){
    //abrir archivo de texto
    ifstream abrir ("spam.txt");
    string cadena;
    //declarar mapa
    map<string, int> Spam;
    //contar frecuencias de palabras que aparecen en archivo de texto
    while (!abrir.eof()){
        abrir>>cadena;
        Spam[cadena]++;
    }
    //cerrar
    abrir.close();
    //declarar iterador para recorrer el mapa
    map<string,int>::iterator it;

    ifstream abrir2 ("correo.txt");

    //declarar mapa
    map<string, int> Correo;
    //contar frecuencias de palabras que aparecen en archivo de texto
    while (!abrir2.eof()){
        abrir2>>cadena;
        Correo[cadena]++;
    }
    //cerrar
    abrir2.close();

    map<string,int>::iterator it2;

    map<string, pair<int,int> > Resultado;
    map<string, pair<int,int> >:: iterator itr;

    int total_correo1=0, total_spam1=0;

    for(it=Spam.begin(),it2=Correo.begin(); it!=Spam.end() && it2!=Correo.end();){
        if(it->first == it2->first){
            Resultado[it->first]= make_pair(it2->second,it->second);
            total_correo1+=it2->second;
            total_spam1+=it->second;
            it++;
            it2++;
        }else if(it->first <it2->first){
            it++;
        }else{
            it2++;
        }
    }
    ifstream abrir3 (argv[1]);
    bool bandera;
    map<string, int> prueba;
    map<string,int>::iterator itpr;

    int total_spam=0, total_correo=0;
    while (!abrir3.eof()){
        abrir3>>cadena;
        bandera=Resultado.count(cadena);
        if(bandera!=0){
            total_correo+=Resultado[cadena].first;
            total_spam+=Resultado[cadena].second;
            prueba[cadena]++;
        }
    }

    abrir3.close();

    double pspam=1, pnospam=1;
    for(itpr=prueba.begin(); itpr!=prueba.end();itpr++){
        pnospam*=(double)Resultado[itpr->first].first/total_correo1;
        pspam*=(double)Resultado[itpr->first].second/total_spam1;
    }

    cout<<"Probabilidad de Spam: "<<pspam<<" Probabilidad de no Spam: "<<pnospam<<endl;

    if (pspam>pnospam){
        cout<<"El correo es Spam"<<endl;
    }else {
        cout<<"El correo no es Spam"<<endl;
    }

    return 0;
}
