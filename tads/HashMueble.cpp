#include <iostream>
#include "../funciones/enteros.cpp"
using namespace std;

class NodoH {
    public:
    int id;
    int pos;
    NodoH(int id, int pos){
        this->id = id;
        this->pos = pos;
    }
};

class HashMueble{
public:

    int largo;
    NodoH** hash;

    HashMueble(int n){
        this->largo = primoSup(n*2+1);
        this->hash = new NodoH*[largo]; 
        for (int i = 0; i < largo; ++i) {
            hash[i] = nullptr;
        }
    }

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
        return ((h == 0) ? 1 : h);
    }

    NodoH* buscar(int id){

        int h1 = hash1(id);
        int h2 = hash2(id);
        int pos = h1;
        int i = 1;

        while(hash[pos] && hash[pos]->id != id){
            pos = (pos + ((i++)*h2)%largo)%largo;
        }

        return hash[pos];
    }

    bool esta(int id) {
        return (buscar(id) != nullptr);
    }
    int valor(int id){
        NodoH* nodo = buscar(id);
        return (nodo? nodo->pos: -1);
    }

    void insertar(int id, int lugar) {
    NodoH* nodo = buscar(id);
    if (nodo) {
        nodo->pos = lugar;  // Si ya existe, solo actualiza la posición.
        return;  // Evita insertar de nuevo.
    }

    int h1 = hash1(id);
    int h2 = hash2(id);
    int pos = h1;
    int i = 1;

    while (hash[pos]) {
        pos = (pos + ((i++) * h2) % largo) % largo;
    }

    hash[pos] = new NodoH(id, lugar);
}

};