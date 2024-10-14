#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/HashLibro.cpp"
#include <chrono> // Para std::chrono
using namespace std;


int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    // Capturar el tiempo de inicio
    auto start = chrono::high_resolution_clock::now();
    int t; cin>>t;
    HashLibro biblioteca(t);

    
    while(t--){

        string comando; cin>>comando;
        if(comando == "ADD"){
            int id; cin>>id;
            string nombre; cin>>nombre;
            biblioteca.insertar(id,nombre);
        } else if(comando == "FIND"){
            int id; cin>>id;
            pair<string, bool> libro = biblioteca.buscar(id);
            if(libro.first == ""){
                cout<<"libro_no_encontrado"<<'\n';
            } else {
                cout<<libro.first<<" ";
                if(libro.second){
                    cout<<"H"<<'\n';
                } else {
                    cout<<"D"<<'\n';
                }
            }
        } else if(comando == "TOGGLE"){
            int id; cin>>id;
            if(!biblioteca.toggle(id)){
                cout<<"libro_no_encontrado"<<'\n';
            }
        } else {
            cout<<biblioteca.cantidad<<" "<<biblioteca.habilitados<<" "<<biblioteca.desabilitados<<'\n';
        }
        
    }
    // Capturar el tiempo de finalización
    auto end = chrono::high_resolution_clock::now();

    // Calcular la duración en segundos
    chrono::duration<double> duration = end - start;
    
    // Mostrar la duración
    //cout << "Tiempo de ejecución: " << duration.count() << " s" << endl;   
    
    return 0;
}