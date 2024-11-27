#include <iostream>
#include "../funciones/enteros.cpp"
#include "Par.cpp"
using namespace std;


class HashLibro {

    public: 
    class NodoHash{
        public:
            int id;
            string titulo; 
            bool habilitado;
            
            NodoHash() {
                id = -1;
                titulo = "";
                habilitado = false;
            }

            NodoHash(int id, string titulo){
                this->id = id;
                this->titulo = titulo;
                habilitado = true;
            }
        };

        NodoHash** lista;
        int largo;
        int cantidad;
        int habilitados;
        int desabilitados;


       int hash1(int k) {
            string key = to_string(k);
            long long h = 0;
            for (int i = 0; i < key.length(); i++)
                h = ((31 * h)%largo + int(key[i]))%largo;
            return (h + largo)%largo;
        }

        

        int hash2(int k) {

            string key = to_string(k);
            long long h = 0;
            for (int i = 0; i < key.length(); i++)
                h = ((37 * h)%largo + int(key[i]))%largo;
            return (h+largo)%largo;
        }

        HashLibro(int n){
            if(n < 28){
                largo = 53;  
            } else {
                n = primoSup(2*n);
                largo = n;
            }
            lista = new NodoHash*[largo];
            for (int i = 0; i < largo; i++) {
                lista[i] = NULL;  // Inicializa cada posición a NULL
            }
            cantidad = 0;
            habilitados = 0;
            desabilitados = 0;
        };

        void insertar(int id, string nombre){
            NodoHash* libro = new NodoHash(id, nombre);
            int h1 = hash1(id);
            int h2 = hash2(id);
            int pos = h1;
            int i = 0;
            while(lista[pos] != NULL){
                if(lista[pos]->id == id) {
                    lista[pos]->titulo = nombre;
                    if(!lista[pos]->habilitado){
                        lista[pos]->habilitado = true;
                        habilitados++;
                        desabilitados--;
                    }
                    return;
                }
                i++;
                pos = (h1 + (h2*i)%largo )% largo;
            }
            lista[pos] = libro;
            cantidad++;
            habilitados++;
        }

        bool toggle(int id){
            
            int h1 = hash1(id);
            int h2 = hash2(id);
            int pos = h1;
            int i = 0;
            while(lista[pos] != NULL){
                if(lista[pos]->id == id){
                    if(lista[pos]->habilitado){
                        habilitados--;
                        desabilitados++;
                    } else {
                        desabilitados--;
                        habilitados++;
                    }
                    lista[pos]->habilitado = !lista[pos]->habilitado;
                    return true;
                }
                i++;
                pos = ( h1 + (i*h2)%largo ) % largo;
            }
            return false;
        }
        
        
        Par<string, bool> buscar(int id){

            int h1 = hash1(id);
            int h2 = hash2(id);
            int pos = h1;
            int i = 0;
            while(lista[pos]!= NULL){
                if(lista[pos]->id == id){
                    return {lista[pos]->titulo, lista[pos]->habilitado};
                }
                i++;
                pos = ( h1 + (i*h2)%largo ) % largo;
            }
            return {"",false};
        }


};
