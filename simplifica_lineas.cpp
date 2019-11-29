#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cairo.h>

using namespace std;

double area_h(pair<double, double> x, pair<double, double> x0, pair<double, double> x1);
double distancia(pair<double,double> x1, pair<double,double> x2);
void simplificacion(const char *nombre_archivo, const char *nombre_guardado, double tole);
double area_metrica(vector<pair<double,double> >x);
double FIND_MAX(vector< pair<double, double> > coordenadas,char bandera);
double FIND_MIN(vector< pair<double, double> > coordenadas,char bandera);
double Ecuacion_recta(double eje, double origen, double max, double min, double valor);
void graficar_cairo(vector< pair<double, double> > coordenadas, vector< pair<double, double> > simplificado);

int main(int argc, char *argv[]){
    double tolerancia;
    tolerancia=atof(argv[3]);
    simplificacion(argv[1], argv[2], tolerancia);

    return 0;
}

double area_h(pair<double, double> x, pair<double, double> x0, pair<double, double> x1){
    double a, b, c, area, s;
    a= distancia(x,x1);
    b=distancia(x0, x1);
    c=distancia(x1,x);
    s=(a+b+c)/2;
    area=sqrt(s*(s-a)*(s-b)*(s-c));
    return area;
}

double distancia(pair<double,double> x1, pair<double,double> x2){
    double dist;
    dist=sqrt((x2.first-x1.first)*(x2.first-x1.first)+(x2.second-x1.second)*(x2.second-x1.second));
    return dist;
}

void simplificacion(const char *nombre_archivo, const char *nombre_guardado, double tole){
    ifstream abrir(nombre_archivo);
    ofstream guardar(nombre_guardado);

    vector< pair<double, double> > coordenadas, coordenadas2;

    vector <pair<double, double> >::iterator it, it2;


    double x, y, tam_ini, tam_fin;

    while(!abrir.eof()){
        pair<double, double> aux;
        abrir >> x;
        abrir >> y;
        aux.first=x;
        aux.second=y;
        coordenadas.push_back(aux);
        coordenadas2.push_back(aux);
    }
    tam_ini=coordenadas.size();
    double area_i=area_metrica(coordenadas);
    double a_min=tole+1, area;
    int contador=0;

    while(1){
        a_min=area_h(coordenadas[static_cast<int>(coordenadas.size()-1)], coordenadas[0], coordenadas[1]);

        int pos_min=0;
        for(int i=1; i<static_cast<int>(coordenadas.size()); i++){
            if(i!= static_cast<int> (coordenadas.size()-1)){
                area=area_h(coordenadas[i-1], coordenadas[i], coordenadas[i+1]);
                //cout<<area<<" ";
            }else {
                area=area_h(coordenadas[0], coordenadas[i], coordenadas[i-1]);
            }

            if(area<a_min){
                a_min=area;
                pos_min=i;
            }
        }
        if(a_min<tole){
            coordenadas.erase(coordenadas.begin()+pos_min);
        }else{
            break;
        }

        contador++;
    }
    cout<<endl;
    cout<<"Numero de puntos quitados: "<<contador<<endl;

    coordenadas.push_back(coordenadas[0]);

    for(it=coordenadas.begin(); it!=coordenadas.end(); it++){
        guardar<<it->first << " "<<it->second<<endl;
    }
    tam_fin=coordenadas.size();
    double area_f=area_metrica(coordenadas);

    cout<<"Porcentaje de compresión: "<<100-(tam_fin/tam_ini)*100<<"%"<<endl;
    cout<<"Jaccard: "<<2*(area_f)/(area_f+area_i)<<endl;

    graficar_cairo(coordenadas2, coordenadas);


    abrir.close();
    guardar.close();
}

double area_metrica(vector <pair<double,double> >x){
    double area1=0, area2=0, areat;
    for(int i=0; i<x.size()-1; i++){
        area1+=x[i].first*x[i+1].second;
        area2+=x[i].second*x[i+1].first;
    }
    areat=fabs(area1-area2)/2;
    return areat;
}

double FIND_MAX(vector< pair<double, double> > coordenadas,char bandera){
    vector< pair<double, double> > :: iterator it;
    double max_x, max_y;

        max_x=coordenadas[0].first;
        max_y=coordenadas[0].second;


   for(it=coordenadas.begin(); it!=coordenadas.end(); it++){
        if(it->first > max_x){
            max_x=it->first;
        }

        if(it->second>max_y){
            max_y=it->second;
        }

    }

    if(bandera=='x'){
        return max_x;
    }else if(bandera=='y'){
        return max_y;
    }
    return 0;
}


double FIND_MIN(vector< pair<double, double> > coordenadas,char bandera){
    vector< pair<double, double> > :: iterator it;
    double min_x, min_y;

        min_x=coordenadas[0].first;
        min_y=coordenadas[0].second;


   for(it=coordenadas.begin(); it!=coordenadas.end(); it++){
        if(it->first < min_x){
            min_x=it->first;
        }

        if(it->second < min_y){
            min_y=it->second;
        }

    }

    if(bandera=='x'){
        return min_x;
    }else if(bandera=='y'){
        return min_y;
    }
    return 0;
}

double Ecuacion_recta(double eje, double origen, double max, double min, double valor){
    double p;
    p=(eje-origen)*(valor-min)/(max-min) + origen;
    return p;
}

void graficar_cairo(vector< pair<double, double> > coordenadas, vector< pair<double, double> > simplificado){
    double width=800;
    double height=800;
    cairo_surface_t *surface;
    cairo_t *cr;
    surface=cairo_image_surface_create(CAIRO_FORMAT_ARGB32,800,800);
    cr= cairo_create(surface);

    cairo_pattern_t *pat;
    pat=cairo_pattern_create_linear(width/2,0,width/2,height);
    //cairo_pattern_add_color_stop_rgb(pat, 0,0.9,0.9,0.9);
    cairo_pattern_add_color_stop_rgb(pat, 1,1,1,1);
    cairo_rectangle(cr,0,0,width,height);
    cairo_set_source(cr,pat);
    cairo_fill(cr);

    double xmax=FIND_MAX(coordenadas, 'x');
    double ymax= FIND_MAX(coordenadas,'y');
    double xmin=FIND_MIN(coordenadas, 'x');
    double ymin= FIND_MIN(coordenadas,'y');



    double ejex= width-(width/8);
    double ejey=height/8;
    double origenx= width/8;
    double origeny= height-(height/8);

    double xaux;
    double yaux;
    for(int i=0; i<coordenadas.size(); i++){
        double valx= Ecuacion_recta(ejex, origenx, xmax, xmin, coordenadas[i].first);
        double valy= Ecuacion_recta(ejey, origeny, ymax, ymin, coordenadas[i].second);
        if(i>=1){
            cairo_set_source_rgba(cr,0,0,1,1);
            cairo_set_line_width(cr,6);
            cairo_move_to(cr,xaux,yaux);
            cairo_line_to(cr,valx,valy);
            cairo_stroke(cr);
        }
        xaux=valx;
        yaux=valy;
    }

    for(int i=0; i<simplificado.size(); i++){
        double valx= Ecuacion_recta(ejex, origenx, xmax, xmin, simplificado[i].first);
        double valy= Ecuacion_recta(ejey, origeny, ymax, ymin, simplificado[i].second);
        if(i>=1){
            cairo_set_source_rgba(cr,1,0,0,0.8);
            cairo_set_line_width(cr,2);
            cairo_move_to(cr,xaux,yaux);
            cairo_line_to(cr,valx,valy);
            cairo_stroke(cr);
        }
        xaux=valx;
        yaux=valy;
    }



    cairo_surface_write_to_png(surface, "RESULTADO.png");
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
}
