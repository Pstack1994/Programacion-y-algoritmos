#ifndef CONVEXHULL
#define CONVEXHULL
using namespace std;

using namespace std;

typedef pair<double, double> punto;
int distancia(punto p1, punto p2, punto p3);
punto encuentra_inicio(vector<punto>);
double producto_cruz(punto, punto, punto);
void imprime_puntos(vector<punto>);
bool orden(const punto&p1, const punto &p2);
vector<punto>datos_aleatorios(int n);
vector<punto> Marcha_Jarvis(vector<punto>);
vector<punto> cargar_datos(string);
typedef struct imagen{
    char formato[3];// p2
    char comentario[1];//comentario
    int nmax;// nivel maximo de intensidad
    int m;
    int n;
    vector <vector<int> > intensidad;
}imagen;

int pos_punto_inicial(vector<punto>);
void intercambia_puntos(punto &p1, punto &p2);
int producto_cruz_g(punto p1, punto p2, punto p3);
int distancia_g(punto p1, punto p2);
bool ordena_por_angulo(const punto &p1, const punto &p2);
void imprime_puntos(vector<punto>);
bool orientacion(punto p1, punto p2, punto p3);
vector<punto>Graham(vector<punto> puntos);
vector<punto> abrir_imagen(const char *nombre);

//punto p;

#endif
