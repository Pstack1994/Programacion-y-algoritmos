#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

vector<vector<double> > cargar_datos(string nombre, vector<double> &etiquetas);
double sigma(double x);
double d_sigma(double x);
double costo(double x, double objetivo);
double d_costo(double x, double objetivo);
vector<vector<double> > cargar_pesos(string nombre);
vector<vector<double> > cargar_bias(string nombre);

class Neurona{
    private:
    int m;
    double b;
    vector <double> peso;
    public:
    Neurona(int);
    double calcula_f(vector<double>);
    int get_size();
    vector<double> get_pesos();
    void modi_pesos(int, double);
    void modi_bias(double);
    void modi_b(double);
    void show();
    double get_b();
    void cargar_pesos(int, double);
    void cargar_bias(double);
};

void Neurona::modi_bias(double v){
    b-= v;
}
Neurona::Neurona(int size){
    m=size;
    for(int i=0; i<size; i++){
        double aux=rand()%100/100.0;///10.0;
        peso.push_back(aux);
    }
    b=rand()%100/100.0;
}

vector<double> Neurona:: get_pesos(){
    return peso;
}

void Neurona::modi_pesos(int pos, double valor){
    peso[pos]-=valor;
   // peso[0]=1;
}

void Neurona::cargar_pesos(int pos, double valor){
    peso[pos]=valor;
}

void Neurona::cargar_bias(double valor){
    b=valor;
}

double Neurona::calcula_f(vector <double> x){
    double f_peso=0;
    for(int i=0; i<x.size(); i++){
        f_peso+=x[i]*peso[i];
    }
    return f_peso;
}

double Neurona:: get_b(){
    return b;
}

int Neurona::get_size(){
    return m;
}

void Neurona::show(){
    for(int i=0; i<peso.size(); i++){
        cout<<peso[i]<<" ";
    }
    cout<<endl;
}

class Capa{
    private:
    vector<Neurona> neuronas;
    vector<double> vec_pesos;
    vector<double> valor_activacion;
    int renglones;
    void inicializa(int, int);
    public:
    void show();
    Capa(int, int);
    void calcula_pesos(vector<double>);
    int get_columnas();
    vector<double> get_vec_pesos();
    void activacion();
    vector<double> get_activacion();
    Neurona get_neurona(int);
    void modifica_peso(int,int, double);
    void cargar_pesosc(int, int, double);
    void cargar_biasc(int, double);
    void modifica_bias(int, double);
    int size();

};

void Capa:: cargar_pesosc(int nneurona, int npeso, double valor){
    neuronas[nneurona].cargar_pesos(npeso, valor);
}

void Capa::cargar_biasc(int nneurona, double valor){
    neuronas[nneurona].cargar_bias(valor);
}

void Capa::modifica_bias(int neurona, double valor){
    neuronas[neurona].modi_bias(valor);
}
void Capa::modifica_peso(int nneurona, int npeso, double valor){
    neuronas[nneurona].modi_pesos(npeso, valor);
}
int Capa::size(){
    return valor_activacion.size();
}
Neurona Capa::get_neurona(int pos){
    return neuronas[pos];
}

void Capa::inicializa(int _renglones, int _columnas ){
    //renglones guarda el numero de capas que se van a crear
    for(int i=0; i<_renglones; i++){
        Neurona aux(_columnas);
        neuronas.push_back(aux);
    }
}

Capa::Capa(int _renglones, int _columnas){
    renglones=_renglones;
    inicializa(_renglones, _columnas);

    for(int i=0; i<renglones; i++){
        vec_pesos.push_back(0);
        valor_activacion.push_back(0);
    }
}

void Capa::show(){
    for(int i=0; i<renglones; i++){
        neuronas[i].show();
    }
}

void Capa::calcula_pesos(vector<double> x){
    for(int i=0; i<renglones; i++){
        vec_pesos[i]=neuronas[i].calcula_f(x) + neuronas[i].get_b();
    }
}

vector<double> Capa::get_vec_pesos(){
    return vec_pesos;
}

vector<double> Capa::get_activacion(){
    return valor_activacion;
}

void Capa:: activacion(){
    for(int i=0; i<valor_activacion.size(); i++){
        valor_activacion[i]=sigma(vec_pesos[i]);
    }

}

class Red_Neuronal{
    private:
    vector<Capa> capas;
    int renglones;
    double lr;
    public:
    double accuracy;
    Red_Neuronal(vector<int>, int, double);
    void propagacion(vector<double>);
    void propagacion_atras(double, vector<double> );
    void actualiza_peso(int, int, int, double);
    void show(int);
    void guardar_pesos(vector<int>, int);
    void carga_pesosr(int, int, int, double);
    void cargar_biasr(int, int, double);
    void clasificar(vector<double>, double);
    void configuracion();

    vector<Capa> get_capas();
};

void Red_Neuronal::configuracion(){
    for(int i=0; i<renglones; i++){
        cout<<"Capa: "<<i<<" N° de neuronas: "<<capas[i].get_activacion().size()<<endl;
    }
}
void Red_Neuronal::clasificar(vector<double> x, double objetivo){
    propagacion(x);

    vector<double> prediccion=capas[renglones-1].get_activacion();

    if(prediccion[0] >=0.5){
        prediccion[0]=1;
    }else{
        prediccion[0]=0;
    }

  //  cout<<"prediccion: "<<prediccion<<" etiqueta: "<<objetivo<<endl;
    if(prediccion[0]==objetivo){
        accuracy++;
    }

}

void Red_Neuronal::carga_pesosr(int ncapa, int nneruona, int npeso, double valor){
    capas[ncapa].cargar_pesosc(nneruona, npeso, valor);
}

void Red_Neuronal::cargar_biasr(int ncapa, int nneurona, double valor){
    capas[ncapa].cargar_biasc(nneurona, valor);
}
void Red_Neuronal::guardar_pesos(vector<int> ncapas, int elementos){
    ofstream guardar("pesos.txt");
    ofstream guardarb("bias.txt");

    //primera capa
    for(int j=0; j<ncapas[0]; j++){
        for(int k=0; k<elementos; k++){
            guardar<<0<<" "<<j<<" "<<k<<" "<<capas[0].get_neurona(j).get_pesos()[k]<<endl;
        }
         guardarb<<0<<" "<<j<<" "<<capas[0].get_neurona(j).get_b()<<endl;
    }
    //demas capas
    for(int i=1; i<ncapas.size(); i++){
        for(int j=0; j<ncapas[i]; j++){
            for(int k=0; k<capas[i-1].get_activacion().size(); k++){
                guardar<<i<<" "<<j<<" "<<k<<" "<<capas[i].get_neurona(j).get_pesos()[k]<<endl;
            }
            guardarb<<i<<" "<<j<<" "<<capas[i].get_neurona(j).get_b()<<endl;

        }
    }
    guardar.close();
    guardarb.close();

    //para el bias;
    capas[1].get_neurona(1).get_b();

}

void Red_Neuronal::actualiza_peso(int ncapa, int nneurona, int npeso, double valor){
    capas[ncapa].modifica_peso(nneurona, npeso, valor);

}
vector<Capa> Red_Neuronal::get_capas(){
    return capas;
}

Red_Neuronal :: Red_Neuronal(vector<int> n_capas, int n_entrada, double _lr){
    renglones=n_capas.size();
    Capa entrada(n_capas[0], n_entrada);
    capas.push_back(entrada);
    for(int i=1; i<n_capas.size(); i++){
        Capa aux(n_capas[i], n_capas[i-1]);
        capas.push_back(aux);
    }
    lr=_lr;
    accuracy=0;

}

void Red_Neuronal ::show(int n){
    if(n>=0 && n<renglones){
        capas[n].show();
    }else{
        cout<<"posicion no valida"<<endl;
    }

}

void Red_Neuronal::propagacion(vector<double> x){
    for(int i=0; i<renglones; i++){
        if(i==0){
            capas[i].calcula_pesos(x);
            capas[i].activacion();
        }else{
            capas[i].calcula_pesos(capas[i-1].get_activacion());
            capas[i].activacion();
        }
    }
}

void Red_Neuronal::propagacion_atras(double objetivo, vector<double> x){
    //calculo del error

    vector<double> aux;
    aux=capas[renglones-1].get_activacion();
    double error=0;
    for(int i=0; i<aux.size(); i++){
        error+=(aux[i]-objetivo)*(aux[i]-objetivo);
    }
    cout<<"error: "<<error<<endl;

    vector<vector<double> > deltas;
    int pos=0;
    vector<vector<double> > W;
    //ciclo que empieza en la ultima capa y va hasta la primer capa
    for(int l=renglones-1; l>=0; l-- ){
        vector<double> temp, aux1;
        aux1=capas[l].get_activacion();
        if(l==renglones-1){
            for(int i=0; i<aux1.size(); i++){//ciclo que va hasta el numero de neuronas en la capa
                temp.push_back(d_costo(aux[i], objetivo)*d_sigma(aux[i]));
                deltas.push_back(temp);
            }
        }else{
         //  cout<<"tamano delta: "<<pos-1<<" "<<deltas[pos-1].size()<<endl;
            vector<double> aux2;
            aux2.assign(capas[l].get_activacion().size(),0);
            //cout<<"size aux2: "<<aux2.size()<<endl;
            for(int k=0; k<deltas[pos-1].size(); k++){
                for(int i=0; i<aux2.size(); i++){
                    aux2[i]+=deltas[pos-1][k]*W[k][i];
                  // cout<<"hola"<<endl;
                }
            }


            for(int i=0; i<aux2.size(); i++){
                aux2[i]*=d_sigma(capas[l].get_activacion()[i]);
               // cout<<aux2[i]<<" ";
            }

           // cout<<endl;
            deltas.push_back(aux2);



        }
        W.clear();

        for(int i=0; i<capas[l].get_activacion().size(); i++){
            W.push_back(capas[l].get_neurona(i).get_pesos());
        }

        //descenso de gradiente

        //promedio de los deltas de la capa en la que vamos.
        double media=0;
        for(int i=0; i<deltas[pos].size(); i++){
            media+=deltas[pos][i];
        }
        media/=deltas[pos].size();

        for(int i=0; i<capas[l].get_activacion().size();i++){
            capas[l].modifica_bias(i,media*lr);
        }


       if(l==0){
            for(int k=0; k<capas[l].get_activacion().size(); k++){
                for(int i=0; i<x.size(); i++){
                    capas[l].modifica_peso(k,i,deltas[pos][k]*x[i]*lr);
                }
            }
        }else{
            for(int k=0; k<capas[l].get_activacion().size(); k++){
                for(int i=0; i<capas[l-1].get_activacion().size(); i++){
                    capas[l].modifica_peso(k,i,deltas[pos][k]*capas[l-1].get_activacion()[i]*lr);//get_neurona(k).modi_pesos(i,deltas[pos][k]*x[i]*lr);
                }
            }

        }
        pos++;




    }

}


int main(){
    //perdón, intenté organizar el código en diferentes archivos pero se me acabó el tiempo :(
    srand(2);
    vector<int> ncapas;
    vector<vector<double> > pesos;
    vector<vector<double> >bias;
    vector<vector<double> > datos;
    vector<double> etiquetas;

   //////////aqui empieza la parte de entrenamiento
    datos=cargar_datos("datos.txt", etiquetas);

    ncapas.push_back(8);
    ncapas.push_back(16);
    ncapas.push_back(1);

   Red_Neuronal entrenamiento(ncapas, 4, 0.5);


    for(int i=0; i<80; i++){
        entrenamiento.propagacion(datos[i]);
        entrenamiento.propagacion_atras(etiquetas[i], datos[i]);
    }
    entrenamiento.guardar_pesos(ncapas, 4);

    pesos=cargar_pesos("pesos.txt");
    bias=cargar_bias("bias.txt");


    //aqui empieza la parte de clasificacion
    Red_Neuronal prueba(ncapas, 4, 0.5);

    for(int i=0; i<pesos.size(); i++){
        prueba.carga_pesosr(pesos[i][0], pesos[i][1], pesos[i][2], pesos[i][3]);
    }

    for(int i=0; i<bias.size(); i++){
        prueba.cargar_biasr(bias[i][0], bias[i][1], bias[i][2]);
    }

    for(int i=0; i<datos.size(); i++){
        prueba.clasificar(datos[i], etiquetas[i]);
    }
    cout<<"Porcentaje de clasificacion: "<<(prueba.accuracy/100)*100<<"%"<<endl;

    prueba.configuracion();

    return 0;
}
vector<vector<double> > cargar_pesos(string nombre){
    fstream abrir(nombre);
    vector<vector<double> > datos;
    double ncapa, nneurona, npeso, valor;
    while(!abrir.eof()){
        vector<double> aux;
        abrir>>ncapa;
        abrir>>nneurona;
        abrir>>npeso;
        if(!(abrir>>valor)){
            continue;
        }


        aux.push_back(ncapa);
        aux.push_back(nneurona);
        aux.push_back(npeso);
        aux.push_back(valor);
        datos.push_back(aux);
    }
    return datos;
}

vector<vector<double> > cargar_bias(string nombre){
    fstream abrir(nombre);
    vector<vector<double> > datos;
    double ncapa, nneurona, valor;
    while(!abrir.eof()){
        vector<double> aux;
        abrir>>ncapa;
        abrir>>nneurona;

        if(!(abrir>>valor)){
            continue;
        }

        aux.push_back(ncapa);
        aux.push_back(nneurona);
        aux.push_back(valor);
        datos.push_back(aux);
    }
    return datos;
}




vector<vector<double> > cargar_datos(string nombre, vector<double> &etiquetas){
    fstream abrir(nombre);
    vector<vector<double> > datos;

double x1, x2, x3, x4, ve;
    while(!abrir.eof()){
        vector<double> aux;
        abrir >> x1;
        abrir >> x2;
        abrir>> x3;
        abrir>>x4;
        if(!(abrir>>ve)){
            continue;
        }
        aux.push_back(x1);
        aux.push_back(x2);
        aux.push_back(x3);
        aux.push_back(x4);
        datos.push_back(aux);
        etiquetas.push_back(ve);
    }
    return datos;

}

double sigma(double x){
    return 1/(1+exp(-x));
}

double d_sigma(double x){
    return x*(1-x);
}

double costo(double x, double objetivo){
    return (x-objetivo)*(x-objetivo);
}

double d_costo(double x, double objetivo){
    return 2*(x-objetivo);
}
