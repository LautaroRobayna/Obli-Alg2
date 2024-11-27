#include <string>
#include <iostream>
#include "funciones/enteros.cpp"
#include "tads/Par.cpp"

using namespace std;
typedef long long ll;

bool divisionPosible(ll n, ll k, ll *lista, ll valorMaximo){
    ll usados = 1;
    ll valorActual = 0;
    for(int i = 0 ; i < n; i++){
        if(valorActual + lista[i] > valorMaximo){
            usados++;
            valorActual = lista[i];
        } else {
            valorActual += lista[i];
        }
    }

    return usados <= k;
}

int main()
{
    ll n, k; cin>>n;
    ll sumaTotal = 0;
    ll* lista = new ll[n];

    ll bajo = 0;
    ll alto = 0;
    for(int i = 0; i < n; i++){
        cin>>lista[i];
        sumaTotal += lista[i];
        bajo = max(lista[i], bajo);
    }
    alto = sumaTotal;
    cin>>k;
    ll resultado = alto;

    while(bajo <= alto){
        ll mid = (bajo+alto)/2;
        if(divisionPosible(n,k,lista,mid)){
            resultado = mid;
            alto = mid - 1;
        } else {
            bajo = mid + 1;
        }
    }

    ll acumulado = 0;
    ll estudianteN = 0;
    int* acum = new int[k];

    for(int i = 0; i < k; i++){
        acum[i] = 0;
    }

    Par<int,int>* indx = new Par<int,int>[k];
    indx[0].primero = 1;

    for(int i = 1; i <= n; i++){
        if(acum[estudianteN] + lista[i-1] > resultado){
            indx[estudianteN].segundo = i-1;
            estudianteN++;
            indx[estudianteN].primero = i;
            acum[estudianteN] += lista[i-1];
        } else {
            acum[estudianteN] += lista[i-1];
        }
    }

    indx[estudianteN].segundo = n;

    for(int i = 0; i < k; i++){
        if(acum[i] == 0)
            break;

        cout<<acum[i]<<" "<<indx[i].primero<<" "<<indx[i].segundo<<'\n';
    }

    cout<<resultado<<'\n';

    return 0;
}