#include <iostream>
#include <vector>

using namespace std;


vector<vector<int> > inicializa(int n, vector<pair<int, int> >reinas_iniciales){
    vector<vector<int> > tablero;
    for(int i=0; i<n; i++){
        vector<int> aux;
        aux.assign(8,0);
        tablero.push_back(aux);
    }
    for(int i=0; i<reinas_iniciales.size(); i++){
        tablero[reinas_iniciales[i].first][reinas_iniciales[i].second]=1;
    }

    return tablero;
}
void imprime_tablero(vector<vector<int> > tablero){
    for(int i=0; i< tablero.size(); i++){
        for(int j=0; j<tablero.size(); j++){
            cout<<tablero[i][j]<<" ";
        }
        cout<<endl;
    }
}

int main(){
    vector<vector<int> > tablero;
    vector<pair<int, int> > reinas_iniciales;
    int n=8;
    reinas_iniciales.push_back(make_pair(2,3));
    reinas_iniciales.push_back(make_pair(5,7));

    tablero=inicializa(n, reinas_iniciales);

    //poder insertar?
   for(int i=0; i<8; i++){
       for(int j=0; j<8; j++){
           bool es_seguro=true;
           if(i== reinas_iniciales[0].first || i== reinas_iniciales[1].first ||  j== reinas_iniciales[0].second || j== reinas_iniciales[1].second
           || i+j== reinas_iniciales[0].first +  reinas_iniciales[0].second || i+j== reinas_iniciales[1].first +  reinas_iniciales[1].second
           || i-j== reinas_iniciales[0].first -  reinas_iniciales[0].second || i-j== reinas_iniciales[1].first -  reinas_iniciales[1].second){
               es_seguro=false;
           }
       }
    }

    return 0;
}


        for (col = 0; col < n; col++) {
            boolean foundSafe = true;

            //check if this row and col is not under attack from any previous queen.
            for (int queen = 0; queen < row; queen++) {
                if (positions[queen].col == col || positions[queen].row - positions[queen].col == row - col ||
                        positions[queen].row + positions[queen].col == row + col) {
                    foundSafe = false;
                    break;
                }
            }
            if (foundSafe) {
                positions[row] = new Position(row, col);
                if (solveNQueenOneSolutionUtil(n, row + 1, positions)) {
                    return true;
                }
            }
        }
        return false;
    }
