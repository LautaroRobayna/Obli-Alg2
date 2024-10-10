#include <iostream>
#include "C:\Users\lauta\OneDrive - Facultad de Ingenieria - Universidad ORT Uruguay\Documentos\Algoritmos 2\Obli-Alg2\funciones\enteros.cpp"
using namespace std;

class HashMueble {
    public:
        class Node {
            public:
                int id;
                int price;
                bool available;
                bool dirty;
                Node(int id, int price) : id(id), price(price), available(true), dirty(false) {}
        };

        HashMueble(int maxAmount) {
            this->amount = 0;
            this->maxAmount = maxAmount;
            this->largeArray = primoSup(maxAmount * 2);
            this->hash = new Node*[this->largeArray]();
            this->heap = new Node*[maxAmount]();  // Para el heap de objetos más baratos
            this->heapSize = 0;
        }

        // Agregar un objeto y actualizar tanto el hash como el heap
        void ADD(int id, int price) {
            Insert(id, price);
        }

        // Obtener los K objetos más baratos
        void GetKCheapest(int k) {
            for (int i = 0; i < k; i++) {
                if (heapSize == 0) break; // Si no hay más elementos en el heap
                Node* cheapest = extractMin(); // Obtener el más barato del heap
                cout << cheapest->id << endl;
                deleteMin();  
            }
        }

    private:
        Node** hash;
        Node** heap;
        int largeArray;
        int maxAmount;
        int amount;
        int heapSize;

        int hash1(int id) {
            return id % largeArray;
        }

        int hash2(int id) {
            return (id * 7) % largeArray;
        }

        void Insert(int id, int price) {
            int hashPos = abs(hash1(id)) % largeArray;
            int j = 0;
            while (hash[hashPos] && !hash[hashPos]->dirty) {
                j++;
                if (hash[hashPos]->id == id && hash[hashPos]->price > price) {
                    // Actualiza el precio si ya existe el objeto en el hash
                    hash[hashPos]->price = price;
                    return;
                }
                hashPos = abs(hash1(id) + j * hash2(id)) % largeArray;
            }
            if (hash[hashPos]) {
                delete hash[hashPos];
            }
            hash[hashPos] = new Node(id, price);
            amount++;
            insertHeap(hash[hashPos]);
        }

        void insertHeap(Node* obj) {
            heap[heapSize++] = obj;
            floats(heapSize - 1);
        }

        void deleteMin() {
            Node* toDelete = heap[0];
            heap[0] = heap[--heapSize];
            heap[heapSize] = NULL;
            delete toDelete;
            sink(0);
        }

        Node* extractMin() {
            return heap[0];
        }

        void sink(int i) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;

            if (left < heapSize){
                smallest = left;
                if (right < heapSize && heap[right]->price < heap[smallest]->price){
                    smallest = right;
                }
                if (heap[smallest]->price < heap[i]->price || heap[smallest]->price == heap[i]->price && heap[smallest]->id < heap[i]->id){ 
                    swap(i, smallest);
                    sink(smallest);
                }
            }
        }

        void floats(int i){
            int par = parent(i);
            if(i > 0 && (heap[par]->price > heap[i]->price || 
                          (heap[par]->price == heap[i]->price && heap[par]->id < heap[i]->id))){
                swap(i, par);
                floats(par);
            }
        }

        int parent(int i) {
            return (i - 1) / 2;
        }

        void swap(int a, int b){
            Node* aux = heap[a];
            heap[a] = heap[b];
            heap[b] = aux;
        }
};
