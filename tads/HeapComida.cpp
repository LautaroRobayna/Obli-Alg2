#include <string>
using namespace std;
class NodoComida {
    public:

    int id;
    int prioridad;
    bool paraLlevar;
    string nombre;

    NodoComida(int id, int prioridad, bool paraLlevar, string nombre){
        this->id = id;
        this->prioridad = prioridad;
        this->paraLlevar = paraLlevar;
        this->nombre = nombre;
    };

};

class HeapComida {
    public:

    int largo;
    int cantidad;
    NodoComida** heap;

    HeapComida(int n){
        this->largo = n;
        this->cantidad = 0;
        this-> heap = new NodoComida*[n];
        for(int i = 0 ; i < n; i++){
            heap[i] = nullptr;
        }
    };

    void insertar(int id, int prioridad, bool paraLlevar){
        cantidad++;
        NodoComida nodo(id){
            
        }
    }


};