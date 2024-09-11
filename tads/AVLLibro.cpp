#include <iostream>
#include "C:/Users/lauta/OneDrive - Facultad de Ingenieria - Universidad ORT Uruguay/Documentos/Algoritmos 2/Obli-Alg2/funciones/enteros.cpp"
using namespace std;
// Usé este como guia, tambien usé el de la ppt. https://github.com/Ekan5h/AVLtree/blob/master/AVL.cpp

class AVLLibro {
public:
    class Nodo {
    public:
        int id;
        string titulo;
        bool habilitado;
        bool estadoAnterior;
        bool nuevo;
        int altura;
        Nodo* izq;
        Nodo* der;

        Nodo(int id, string titulo) : id(id), titulo(titulo), habilitado(true), estadoAnterior(false), nuevo(true), altura(1), izq(NULL), der(NULL) {}
    };

    Nodo* raiz = NULL;
    int cantidad = 0;
    int habilitados = 0;

    void ADD(int id, const string& titulo) {
        Nodo* insertado = insertar(raiz, id, titulo);
        if (insertado->nuevo) cantidad++;

        if (!insertado->estadoAnterior) habilitados++;
    }

    void FIND(int id) {
        Nodo* resultado = buscar(raiz, id);  
        if (resultado == NULL) {
            cout << "libro_no_encontrado" << endl;
        } else {
            if (resultado->habilitado) {
                cout << resultado->titulo << " H" << endl;
            } else {
                cout << "libro_no_encontrado" << endl;
                cout << resultado->titulo << " D" << endl;
            }
        }
    }


    void TOGGLE(int id) {
        Nodo* resultado = habilitarDeshabilitar(raiz, id);
        if (resultado == NULL) {
            cout << "libro_no_encontrado" << endl;
        } else {
            if (resultado->estadoAnterior) {
                habilitados--;
            } else {
                habilitados++;
            }
        }
    }

    void COUNT(){
        cout << cantidad << " " << habilitados << " " << (cantidad - habilitados) << endl;
    }

private:
    Nodo* insertar(Nodo* nodo, int id, const string& titulo) {
        if (nodo == NULL) return new Nodo(id, titulo);

        if (id < nodo->id) {
            nodo->izq = insertar(nodo->izq, id, titulo);
        } else if (id > nodo->id) {
            nodo->der = insertar(nodo->der, id, titulo);
        } else {
            nodo->titulo = titulo;
            nodo->estadoAnterior = nodo->habilitado;
            nodo->habilitado = true;
            nodo->nuevo = false;
        }

        nodo->altura = 1 + max(altura(nodo->izq), altura(nodo->der));

        int balance = getBalance(nodo);
        if (balance > 1 && id < nodo->izq->id) {
            return rotacionDer(nodo);
        }
        if (balance < -1 && id > nodo->der->id) {
            return rotacionIzq(nodo);
        }
        if (balance > 1 && id > nodo->izq->id) {
            nodo->izq = rotacionIzq(nodo->izq);
            return rotacionDer(nodo);
        }
        if (balance < -1 && id < nodo->der->id) {
            nodo->der = rotacionDer(nodo->der);
            return rotacionIzq(nodo);
        }

        return nodo;
    }

    int altura(Nodo* nodo) {
        if (nodo == NULL)
            return 0;
        return nodo->altura;
    }

    int getBalance(Nodo* nodo) {
        if (nodo == NULL)
            return 0;
        return altura(nodo->izq) - altura(nodo->der);
    }

    Nodo* rotacionIzq(Nodo* nodo) {
        Nodo* nuevaRaiz = nodo->der;
        Nodo* temp = nuevaRaiz->izq;
        nuevaRaiz->izq = nodo;
        nodo->der = temp;

        nodo->altura = max(altura(nodo->izq), altura(nodo->der)) + 1;
        nuevaRaiz->altura = max(altura(nuevaRaiz->izq), altura(nuevaRaiz->der)) + 1;

        return nuevaRaiz;
    }

    Nodo* rotacionDer(Nodo* nodo) {
        Nodo* nuevaRaiz = nodo->izq;
        Nodo* temp = nuevaRaiz->der;
        nuevaRaiz->der = nodo;
        nodo->izq = temp;

        nodo->altura = max(altura(nodo->izq), altura(nodo->der)) + 1;
        nuevaRaiz->altura = max(altura(nuevaRaiz->izq), altura(nuevaRaiz->der)) + 1;

        return nuevaRaiz;
    }

    Nodo* buscar(Nodo* nodo, int id){
        if(nodo == NULL) return NULL;

        if (id < nodo->id) {
            return buscar(nodo->izq, id);
        } else if (id > nodo->id) {
            return buscar(nodo->der, id);
        } else {
            return nodo;
        }
    }

    Nodo* habilitarDeshabilitar(Nodo* nodo, int id){
        if(nodo == NULL) return NULL;

        if (id < nodo->id) {
            return habilitarDeshabilitar(nodo->izq, id);
        } else if (id > nodo->id) {
            return habilitarDeshabilitar(nodo->der, id);
        } else {
            nodo->estadoAnterior = nodo->habilitado;
            nodo->habilitado = !nodo->habilitado;
            return nodo;
        }
    }
};
