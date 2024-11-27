#include <iostream>
#include "tads/HashLibro.cpp"
using namespace std;


int main()
{

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
            Par<string, bool> libro = biblioteca.buscar(id);

            if(libro.primero == ""){

                cout<<"libro_no_encontrado"<<'\n';

            } else {

                cout<<libro.primero<<" ";

                if(libro.segundo){
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
    
    return 0;
}