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
                    hash[hashPos]->price = price;
                    return;
                }
                hashPos = abs(hash1(id) + j * hash2(id)) % largeArray;
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
            sink(0);
        }

        Node* extractMin() {
            return heap[0];
        }

        void sink(int index) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index;

            // Comparar con el hijo izquierdo
            if (left < heapSize && heap[left]->price < heap[smallest]->price) {
                smallest = left;
            }

            // Comparar con el hijo derecho
            if (right < heapSize && heap[right]->price < heap[smallest]->price) {
                smallest = right;
            }

            // Si el elemento más pequeño no es el actual, intercambia y repite el proceso
            if (smallest != index) {
                swap(heap[index], heap[smallest]);
                sink(smallest);  // Recursivamente hundir el nodo
            }
        }

        void floats(int index) {
            int parent = (index - 1) / 2;

            if (index > 0 && heap[index]->price < heap[parent]->price) {
                swap(heap[index], heap[parent]);
                floats(parent);  // Recurre para verificar más arriba en el heap
            }
        }

        int parent(int i) {
            return (i - 1) / 2;
        }

        void swap(Node*& a, Node*& b) {
            Node* aux = a;
            a = b;
            b = aux;
        }
};
