#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

int n;
int k;
int** mat;
int res = 0;
int total = 0;
int* indices;
int** valores;
int* sumar;
int sinRes = 0;

bool sePuede(int altura, int largo, int valor){
    if(altura == 0 && largo == 0) return true;
    if(altura == 0 && largo == 1) return mat[0][0] != valor;
    if(largo == 0) return mat[altura-1][0] != valor && mat[altura-1][1] != valor;
    return  mat[altura-1][0] != valor && mat[altura-1][1] != valor && mat[altura][0] != valor;
}

void back(int pos){

    if(pos >= n*2){
        total = max(total, res);
    } else {
        int altura = pos/2;
        int largo = pos%2;
        if(indices[altura] < sinRes + 2){
            back(pos + 1);
            for(int i = 0; i < indices[altura]; i++){
                if(sePuede(altura,largo, valores[altura][i])){
                    mat[altura][largo] = valores[altura][i];
                    res += sumar[largo];
                    back(pos + 1);
                    res -= sumar[largo];
                    mat[altura][largo] = 0;
                }
            }
        } else {
            res += n;
            back(pos +2);
            res -= n;
        }
        
    }

}

int main()
{
    cin>>n>>k;
    sumar = new int[2];
    sumar[0] = (n+1)/2;
    sumar[1] = (n)/2;
    int* indxs = new int[n];
    for(int i = 0 ; i< n; i++){
        indxs[i] = 0;
    }

    for(int i = 0 ; i < k; i++){
        string nombre; cin>>nombre;
        int fila; cin>>fila;
        if(fila == -1){
            sinRes++;
        } else {
            indxs[fila]++;
        }
    }
    valores = new int*[n];
    indices = new int[n];
    int nuevo = sinRes+1;
    for(int i = 0; i < n; i++){
        valores[i] = new int[sinRes + indxs[i]];
        indices[i] = sinRes + indxs[i];
    }
    for(int i = 0; i<n; i++){
        for(int j = 0; j < sinRes + indxs[i]; j++){
            if(j < sinRes){
                valores[i][j] = j + 1;
            }  else {
                valores[i][j] = nuevo++;
            } 
        }
    }

    mat = new int*[n];
    for(int i = 0; i < n; i++){
        mat[i] = new int[2];
        mat[i][0] = 0;
        mat[i][1] = 0;
    }

    back(0);

    cout<<total<<'\n';

    return 0;
}