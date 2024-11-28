#include <iostream>
#include <string>
#include "tads/HeapMcOrt.cpp"

using namespace std;

int main() {
    int n, o;
    cin >> n >> o;  
    HeapMcOrt* cola = new HeapMcOrt(n);

    while (o--) {
        char op;
        cin >> op;
        if (op == 'I') {
            int id;
            int prioridad;
            string paraLlevarStr; 
            string items;
            cin >> id >> prioridad >> paraLlevarStr >> items;
            bool paraLlevar = (paraLlevarStr == "true");
            cola->I(id, prioridad, paraLlevar, items);
        } else if (op == 'E') {
            int id;
            cin >> id;
            cola->E(id);
        } else if (op == 'C') {
            int id;
            cin >> id;
            cola->C(id);
        }
    }

    cola->M();

    delete cola;
    return 0;
}