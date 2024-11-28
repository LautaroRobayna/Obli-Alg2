#include <iostream>
using namespace std;

class Nodo {
public:
    int key;    // Clave del nodo (identificador)
    int value;  // Valor asociado (distancia, costo, etc.)
    Nodo(int key, int value) : key(key), value(value) {}
};

class MinHeap {
public:
    int capacity;
    int size;
    Nodo** heap;

    MinHeap(int capacity) : capacity(capacity), size(0) {
        heap = new Nodo*[capacity];
        for (int i = 0; i < capacity; i++) {
            heap[i] = nullptr;
        }
    }

    ~MinHeap() {
        for (int i = 0; i < size; i++) {
            delete heap[i];
        }
        delete[] heap;
    }

    int leftChild(int pos) { return 2 * pos + 1; }
    int rightChild(int pos) { return 2 * pos + 2; }
    int parent(int pos) { return (pos - 1) / 2; }

    void swap(int pos1, int pos2) {
        Nodo* temp = heap[pos1];
        heap[pos1] = heap[pos2];
        heap[pos2] = temp;
    }

    void insert(int key, int value) {
        if (size >= capacity) {
            cout << "Heap está lleno\n";
            return;
        }
        Nodo* newNode = new Nodo(key, value);
        heap[size] = newNode;
        int current = size;
        size++;
        while (current > 0 && heap[current]->value < heap[parent(current)]->value) {
            swap(current, parent(current));
            current = parent(current);
        }
    }

    Nodo* extractMin() {
        if (size == 0) return nullptr;
        Nodo* minNode = heap[0];
        heap[0] = heap[size - 1];
        size--;
        sinkDown(0);
        return minNode;
    }

    void sinkDown(int pos) {
        int smallest = pos;
        int left = leftChild(pos);
        int right = rightChild(pos);

        if (left < size && heap[left]->value < heap[smallest]->value)
            smallest = left;
        if (right < size && heap[right]->value < heap[smallest]->value)
            smallest = right;

        if (smallest != pos) {
            swap(pos, smallest);
            sinkDown(smallest);
        }
    }
};
