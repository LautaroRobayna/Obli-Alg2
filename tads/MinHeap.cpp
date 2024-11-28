class Nodo {
public:
    int key;    // Clave del nodo (identificador)
    int value;  // Valor asociado (distancia, costo, etc.)
    Nodo(int key, int value) : key(key), value(value) {}
};

class MinHeap {
private:
    Nodo** heap;       // Array de punteros a Nodo
    int capacity;
    int size;
    int* position;     // Array para almacenar la posición de cada nodo en el heap

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return (2 * i + 1); }
    int rightChild(int i) { return (2 * i + 2); }

    void swap(int i, int j) {
        // Actualizamos las posiciones en el array position
        position[heap[i]->key] = j;
        position[heap[j]->key] = i;

        // Intercambiamos los nodos en el heap
        Nodo* temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    void heapifyUp(int i) {
        while (i != 0 && heap[parent(i)]->value > heap[i]->value) {
            swap(i, parent(i));
            i = parent(i);
        }
    }

    void heapifyDown(int i) {
        int smallest = i;
        int l = leftChild(i);
        int r = rightChild(i);

        if (l < size && heap[l]->value < heap[smallest]->value)
            smallest = l;
        if (r < size && heap[r]->value < heap[smallest]->value)
            smallest = r;

        if (smallest != i) {
            swap(i, smallest);
            heapifyDown(smallest);
        }
    }

public:
    MinHeap(int capacity) : capacity(capacity), size(0) {
        heap = new Nodo*[capacity];
        position = new int[capacity];
        for (int i = 0; i < capacity; i++) {
            heap[i] = nullptr;
            position[i] = -1;
        }
    }

    ~MinHeap() {
        // Liberamos todos los nodos restantes en el heap
        for (int i = 0; i < size; i++) {
            delete heap[i];
        }
        delete[] heap;
        delete[] position;
    }

    void insert(int key, int value) {
        if (size >= capacity) {
            // Si el heap está lleno, no insertamos
            return;
        }
        Nodo* newNode = new Nodo(key, value);
        heap[size] = newNode;
        position[key] = size;
        heapifyUp(size);
        size++;
    }

    Nodo* extractMin() {
        if (size <= 0) {
            return nullptr; // Heap vacío
        }
        Nodo* root = heap[0];

        // Actualizamos la posición
        position[root->key] = -1;

        heap[0] = heap[size - 1];
        position[heap[0]->key] = 0;
        size--;
        heapifyDown(0);
        return root;
    }

    bool isEmpty() {
        return size == 0;
    }

    void decreaseKey(int key, int newValue) {
        int i = position[key];
        if (i == -1) return; // El nodo no está en el heap

        heap[i]->value = newValue;
        heapifyUp(i);
    }
};
