#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/ListImp.cpp"
#include "funciones/enteros.cpp"

using namespace std;


bool sePuede(int altura, int largo, int valor, int** mat){
    if(altura == 0 && largo == 0) return true;
    if(altura == 0 && largo == 1) return mat[0][0] != valor;
    if(largo == 0) return mat[altura-1][0] != valor && mat[altura-1][1] != valor;
    return  mat[altura-1][0] != valor && mat[altura-1][1] != valor && mat[altura][0] != valor;
}

void back(int pos, int n, int &mejorCantidad, int** matriz, ListImp<int>* flores, int &valorAcumulado){

    if(pos >= n*2){

        mejorCantidad = max(mejorCantidad, valorAcumulado);

    } else {

        int altura = pos/2;
        int largo = pos%2;
        
        back(pos + 1, n, mejorCantidad, matriz, flores,valorAcumulado); // no poner flores
        for(int i = 0; i < flores[altura].getSize(); i++){
            if(sePuede(altura,largo, flores[altura].get(i), matriz)){
                matriz[altura][largo] = flores[altura].get(i);
                valorAcumulado += (n+1-largo)/2;
                back(pos + 1, n, mejorCantidad, matriz, flores, valorAcumulado);
                valorAcumulado -= (n+1-largo)/2;
                matriz[altura][largo] = 0;
            }
        }
    }

}

int main()
{
    int n,k; cin>>n>>k;

    ListImp<int>* flores = new ListImp<int>[n];
    for(int i = 1; i <= k; i++){
        string nombre; cin>>nombre;
        int col; cin>>col;
        if(col == -1){
            for(int j = 0; j < n; j++){
                flores[j].insert(i);
            }
        } else {
            flores[col].insert(i);
        }
    }

    int** matriz = new int*[n];
    for(int i = 0; i < n; i++){
        matriz[i] = new int[2];
        matriz[i][0] = 0;
        matriz[i][1] = 0;
    }

    int mejorCantidad = 0;
    int valorAcumulado = 0;
    back(0,n,mejorCantidad,matriz,flores,valorAcumulado);

    cout<<mejorCantidad<<'\n';

    return 0;
}