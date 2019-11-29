#include <iostream>
#include <vector>
#include <cairo.h>
#include <fstream>
#include<cmath>

using namespace std;

double FIND_MAX(vector< pair<double, double> > coordenadas,char bandera);
double FIND_MIN(vector< pair<double, double> > coordenadas,char bandera);
double Ecuacion_recta(double eje, double origen, double max, double min, double valor);
void graficar_cairo(vector< pair<double, double> > coordenadas, vector< pair<double, double> > simplificado);

int main(){
   vector< pair<double, double> > coordenadas;
    ifstream abrir("simplificadoslp.txt");
    double x, y;
    pair<double, double> aux;
    while(!abrir.eof()){
        abrir >> x;
        abrir >> y;
        aux.first=x;
        aux.second=y;
        coordenadas.push_back(aux);
    }
    aux.first=coordenadas[0].first;
    aux.second=coordenadas[0].second;
    coordenadas.push_back(aux);
    abrir.close();

    graficar_cairo(coordenadas, coordenadas);





    return 0;
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
    cairo_pattern_add_color_stop_rgb(pat, 0,0.9,0.9,0.9);
    cairo_pattern_add_color_stop_rgb(pat, 1,0.6,0.6,0.6);
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



    cairo_surface_write_to_png(surface, "cuadro.png");
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
}
