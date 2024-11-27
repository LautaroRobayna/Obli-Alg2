#include <iostream>
#include "../funciones/enteros.cpp"
using namespace std;

class NodoLibro {

public:
    
    int id;
    int altura;
    string titulo;
    bool habilitado;
    NodoLibro* izq;
    NodoLibro* der;
    NodoLibro(int id, string titulo) {
        this->id = id;
        this->titulo = titulo;
        this->altura = 1;
        habilitado = true;
        this->izq = NULL;
        this->der = NULL;
    }
};
class AVLLibro {

public:

    NodoLibro* raiz;
    int cantidadLibros;
    int habilitados;
    int desabilitados;

    AVLLibro(){
        raiz = NULL;
        cantidadLibros = 0;
        habilitados = 0;
        desabilitados = 0;
    }

    int altura(NodoLibro* nodo){
        return nodo ? nodo->altura : 0;
    }

    void actualizarAltura(NodoLibro* nodo){
        if(nodo){
            nodo->altura = 1 + max(altura(nodo->izq), altura(nodo->der));
        }
    }

    void insertar(int id, string titulo){
        insertar(raiz, id, titulo);
    }

    int calcularBalance(NodoLibro* nodo){
        return nodo? altura(nodo->izq) - altura(nodo->der) : 0;
    }

    void insertar(NodoLibro* &nodo, int id, string titulo){

        if(!nodo){

            nodo = new NodoLibro(id, titulo);
            habilitados++;
            cantidadLibros++;
            return;

        } else if(id == nodo->id){

            nodo->titulo = titulo;
            if(!nodo->habilitado){
                habilitados++;
                desabilitados--;
            }
            nodo->habilitado = true;
            return;

        } 
        
        if(id < nodo->id){

            insertar(nodo->izq, id, titulo);

        } else {

            insertar(nodo->der, id, titulo);
        } 
        
        actualizarAltura(nodo);

        int balance = calcularBalance(nodo);

        if(balance > 1){
            if(id < nodo->izq->id){
                rotacionLL(nodo);
            } else {
                rotacionRR(nodo->izq);
                rotacionLL(nodo);
            }
            
        } else if(balance < -1){
            if(id > nodo->der->id){
                rotacionRR(nodo);
            } else {
                rotacionLL(nodo->der);
                rotacionRR(nodo);
            }
        }
    }

    void rotacionLL(NodoLibro* &nodo) {
        NodoLibro* temp = nodo->izq;
        nodo->izq = temp->der;
        temp->der = nodo;

        actualizarAltura(nodo);
        actualizarAltura(temp);

        nodo = temp;
    }
    void rotacionRR(NodoLibro* &nodo){
        NodoLibro* temp = nodo->der;
        nodo->der = temp->izq;
        temp->izq = nodo;

        actualizarAltura(nodo);
        actualizarAltura(temp);

        nodo = temp;
    }

    NodoLibro* buscar(int id){
        return buscar(raiz, id);
    }

    NodoLibro* buscar(NodoLibro* nodo, int id){
        if(!nodo || nodo->id == id){
            return nodo;
        }

        if(id < nodo->id){
            return buscar(nodo->izq, id);
        } else {
            return buscar(nodo->der, id);
        }
    }

    void desabilitar(int id){
        NodoLibro* nodo = buscar(id);
        if(nodo){
            if(nodo->habilitado){
                habilitados--;
                desabilitados++;
            } else {
                habilitados++;
                desabilitados--;
            }
            nodo->habilitado = !nodo->habilitado;
        }
    }
};
