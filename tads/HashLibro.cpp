#include <iostream>
#include "../funciones/enteros.cpp"
using namespace std;


class HashLibro {

    public: 
    class NodoHash{
        public:
            int id;
            string titulo; 
            bool habilitado;
            bool susuki;
            NodoHash() {
            id = -1;
            titulo = "";
            habilitado = false;
            susuki = false;
        }

            NodoHash(int id, string titulo){
                this->id = id;
                this->titulo = titulo;
                habilitado = true;
                susuki = true;
            }
        };

        NodoHash* lista;
        int largo;
        int cantidad;
        int habilitados;
        int desabilitados;


        int hash1(int key) {
            key = ((key >> 16) ^ key) * 0x45d9f3b;
            key = ((key >> 16) ^ key) * 0x45d9f3b;
            key = (key >> 16) ^ key;
            return key % largo;
        }

        int hash2(int key) {
            key = ((key >> 16) ^ key) * 0x119de1f3;
            key = ((key >> 16) ^ key) * 0x119de1f3;
            key = (key >> 16) ^ key;
            return (key % largo) | 1; 
        }

        HashLibro(int n){
            if(n < 28){
                lista = new NodoHash[53];
                largo = 53;  
            } else {
                n = primoSup(2*n);
                lista = new NodoHash[n];
                largo = n;
            }
            cantidad = 0;
            habilitados = 0;
            desabilitados = 0;
        };

        void insertar(int id, string nombre){
            NodoHash libro(id, nombre);
            int h1 = hash1(id);
            int h2 = hash2(id);
            int pos = h1;
            int i = 0;
            while(lista[pos].susuki){
                if(lista[pos].id == id) {
                    lista[pos].titulo = nombre;
                    if(!lista[pos].habilitado){
                        lista[pos].habilitado = true;
                        habilitados++;
                        desabilitados--;
                    }
                    return;
                }
                i++;
                pos = (h1 + h2*i )% largo;
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
            while(lista[pos].susuki){
                if(lista[pos].id == id){
                    if(lista[pos].habilitado){
                        habilitados--;
                        desabilitados++;
                    } else {
                        desabilitados--;
                        habilitados++;
                    }
                    lista[pos].habilitado = !lista[pos].habilitado;
                    return true;
                }
                i++;
                pos = ( h1 + i*h2 ) % largo;
            }
            return false;
        }

        
        pair<string, bool> buscar(int id){

            int h1 = hash1(id);
            int h2 = hash2(id);
            int pos = h1;
            int i = 0;
            while(lista[pos].susuki){
                if(lista[pos].id == id){
                    return {lista[pos].titulo, lista[pos].habilitado};
                }
                i++;
                pos = ( h1 + i*h2 ) % largo;
            }
            return {"",false};
        }


};
