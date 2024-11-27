#include <iostream>
using namespace std;
class NodoMueble{
    public:
    int precio;
    int id;
    NodoMueble(int id, int precio){
        this->id = id;
        this->precio = precio;
    }
};
int const oo = 9999999;
class HeapMuebles{
public:
    

    int largo;
    int cantidad;
    NodoMueble** heap;

    HeapMuebles(int n){
        this->largo = n;
        this->cantidad = 0;
        this->heap = new NodoMueble*[largo];
        for(int i = 0; i < n; i++){
            heap[i] = nullptr;
        }
    };

    int hijoIzq(int pos){
        return pos*2 + 1;
    }
    int hijoDer(int pos){
        return pos*2 + 2;
    }
    int padre(int pos){
        return (pos-1)/2;
    }

    void intercambiar(int pos1, int pos2) {
        if (pos1 < 0 || pos2 < 0 || pos1 >= cantidad || pos2 >= cantidad) {
            cout << "Error: intercambio fuera de límites" << '\n';
            return;
        }

        NodoMueble* temp = heap[pos1];
        heap[pos1] = heap[pos2];
        heap[pos2] = temp;
    }

    bool esMenor(int pos1, int pos2){
        if(precioS(pos1) < precioS(pos2)){
            return true;
        } else if (precioS(pos1) == precioS(pos2) && (precioS(pos1) != oo)){
            return heap[pos1]->id > heap[pos2]->id;
        }
        return false;
    }

    void flotar(int pos){
        int miPadre = padre(pos);
        if(pos > 0 && esMenor(pos, miPadre)){
            intercambiar(pos, miPadre);
            flotar(miPadre);
        }
    }

    int precioS(int pos){
        return (pos < cantidad? heap[pos]->precio : oo);
    }

    void hundir(int pos){
        int hIzq = hijoIzq(pos); 
        int hDer = hijoDer(pos);
        
        if(min(precioS(hIzq),precioS(hDer)) < precioS(pos)){
            if(esMenor(hIzq,hDer)){
                intercambiar(pos, hIzq);
                hundir(hIzq);
            } else {
                intercambiar(pos, hDer);
                hundir(hDer);
            }
        }
    }

    void eliminarUltimo(){
        if(cantidad > 0){
            cantidad--;
            delete heap[cantidad];
            heap[cantidad] = nullptr;
        }
    }

    int top(){
        return (cantidad? heap[0]->id : -1);
    }

    void pop(){
        if(cantidad > 0){
            intercambiar(0, cantidad-1);
            eliminarUltimo();
            hundir(0);
        }
    }

    void insertar(int id, int precioNuevo){
       
        cantidad++;
        heap[cantidad-1] = new NodoMueble(id,precioNuevo);
        flotar(cantidad-1);
        
    }


};