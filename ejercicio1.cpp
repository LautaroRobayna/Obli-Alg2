#include <iostream>
#include "tads/AVLLibro.cpp"

using namespace std;

int main() {

    int n; cin>>n;
    AVLLibro libreria;

    while(n--){
        string comando; cin>>comando;
        if(comando == "ADD"){

            int id; string titulo; cin>>id>>titulo;

            libreria.insertar(id, titulo);

        } else if(comando == "FIND"){

            int id; cin>>id;
            NodoLibro* nodo = libreria.buscar(id);

            if(nodo){
                cout<<nodo->titulo<<(nodo->habilitado? " H\n" : " D\n");
            } else {
                cout<<"libro_no_encontrado"<<'\n';
            }

        } else if(comando == "TOGGLE"){

            int id; cin>>id;
            NodoLibro* nodo = libreria.buscar(id);

            if(nodo){
                libreria.desabilitar(id);
            } else {
                cout<<"libro_no_encontrado"<<'\n';
            }

        } else { //comando == "COUNT"

            cout<<libreria.cantidadLibros<<" "<<libreria.habilitados<<" "<<libreria.desabilitados<<'\n';
            
        }
    }

    return 0;
}
