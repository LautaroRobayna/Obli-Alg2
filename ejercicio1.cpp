#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "C:/Users/lauta/OneDrive - Facultad de Ingenieria - Universidad ORT Uruguay/Documentos/Algoritmos 2/Obli-Alg2/tads/AVLLibro.cpp"

using namespace std;

int main() {
    int N;
    cin >> N;  // Leer el número de operaciones
    AVLLibro arbol;  // Crear una instancia de AVLLibro

    for (int i = 0; i < N; ++i) {
        string operacion;
        cin >> operacion;

        if (operacion == "ADD") {
            int id;
            string titulo;
            cin >> id >> titulo;
            arbol.ADD(id, titulo);
        } 
        else if (operacion == "FIND") {
            int id;
            cin >> id;
            arbol.FIND(id);
        } 
        else if (operacion == "TOGGLE") {
            int id;
            cin >> id;
            arbol.TOGGLE(id);
        } 
        else if (operacion == "COUNT") {
            arbol.COUNT();
        }
    }

    return 0;
}


