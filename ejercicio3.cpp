#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include <C:\Users\lauta\OneDrive - Facultad de Ingenieria - Universidad ORT Uruguay\Documentos\Algoritmos 2\Obli-Alg2\tads\HeapMueble.cpp>

using namespace std;

int main() {
    int n;
    cin >> n;  
    HashMueble* objetos = new HashMueble(n);

    while (n--) {
        int id;
        int price;
        cin >> id >> price;
        objetos->ADD(id, price);
    }

    int k;
    cin >> k;
    objetos->GetKCheapest(k);

    delete objetos;
}


