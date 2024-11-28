#include <iostream>
using namespace std;

class HeapMcOrt {
    public:
        class Nodo {
            public:
                int id;
                int prioridad;
                bool paraLlevar;
                string items;
                Nodo(int id, int prioridad, bool paraLlevar, string items) : id(id), prioridad(prioridad), paraLlevar(paraLlevar), items(items) {}
        };

        HeapMcOrt(int cantPedidos) {
            this->cant = 0;
            this->largoMax = cantPedidos;
            this->heap = new Nodo*[largoMax](); 
        }

        ~HeapMcOrt() {
            for (int i = 0; i < cant; i++) {
                delete heap[i];
            }
            delete[] heap;
        }

        void I(int id, int prioridad, bool paraLlevar, string items) {
            if (cant < largoMax) {
                Insertar(id, prioridad, paraLlevar, items);
            }
        }

        void E(int id) {
            Eliminar(id);
        }

        void C(int id) {
            CambiarPedido(id);
        }

        void M() {
            MostrarOrdenado();
        }

    private:
        Nodo** heap;
        int cant;
        int largoMax;

        void Insertar(int id, int prioridad, bool paraLlevar, string items) {
            heap[cant] = new Nodo(id, prioridad, paraLlevar, items);
            cant++;
            flotar(cant - 1);
        }

        void Eliminar(int id) {
            int pos = -1;
            for (int i = 0; i < cant; i++) {
                if (heap[i]->id == id) {
                    pos = i;
                    break;
                }
            }
            if (pos == -1) return;

            delete heap[pos];
            heap[pos] = heap[cant - 1];
            cant--;
            
            if (pos < cant) {
                flotar(pos);
                hundir(pos);
            }
        }

        int padre(int pos) {
            return (pos - 1) / 2;
        }

        int hijoIzq(int pos) {
            return 2 * pos + 1;
        }

        int hijoDer(int pos) {
            return 2 * pos + 2;
        }

        void intercambiar(int a, int b) {
            Nodo* temp = heap[a];
            heap[a] = heap[b];
            heap[b] = temp;
        }

        bool tienePrioridad(Nodo* a, Nodo* b) {
            if (a->prioridad < b->prioridad) return true;
            if (a->prioridad > b->prioridad) return false;
            
            if (a->paraLlevar && !b->paraLlevar) return true;
            if (!a->paraLlevar && b->paraLlevar) return false;
            
            return a->id < b->id;
        }

        void flotar(int pos) {
            while (pos > 0) {
                int p = padre(pos);
                if (tienePrioridad(heap[pos], heap[p])) {
                    intercambiar(pos, p);
                    pos = p;
                } else {
                    break;
                }
            }
        }

        void hundir(int pos) {
            while (true) {
                int izq = hijoIzq(pos);
                int der = hijoDer(pos);
                int menor = pos;

                if (izq < cant && tienePrioridad(heap[izq], heap[menor])) {
                    menor = izq;
                }
                if (der < cant && tienePrioridad(heap[der], heap[menor])) {
                    menor = der;
                }

                if (menor == pos) break;

                intercambiar(pos, menor);
                pos = menor;
            }
        }

        void CambiarPedido(int id) {
            for (int i = 0; i < cant; i++) {
                if (heap[i]->id == id) {
                    heap[i]->paraLlevar = !heap[i]->paraLlevar;
                    flotar(i);
                    hundir(i);
                    break;
                }
            }
        }

        void MostrarOrdenado() {
            Nodo** heapTemp = new Nodo*[cant];
            int cantTemp = cant;
            
            for (int i = 0; i < cant; i++) {
                heapTemp[i] = new Nodo(heap[i]->id, heap[i]->prioridad, 
                                     heap[i]->paraLlevar, heap[i]->items);
            }
            
            while (cantTemp > 0) {
                cout << heapTemp[0]->id << " " << heapTemp[0]->prioridad << " "
                     << (heapTemp[0]->paraLlevar ? "true" : "false") << " "
                     << heapTemp[0]->items << endl;
                
                delete heapTemp[0];
                heapTemp[0] = heapTemp[cantTemp - 1];
                cantTemp--;
                
                int pos = 0;
                while (true) {
                    int izq = 2 * pos + 1;
                    int der = 2 * pos + 2;
                    int menor = pos;
                    
                    if (izq < cantTemp && tienePrioridad(heapTemp[izq], heapTemp[menor])) {
                        menor = izq;
                    }
                    if (der < cantTemp && tienePrioridad(heapTemp[der], heapTemp[menor])) {
                        menor = der;
                    }
                    
                    if (menor == pos) break;
                    
                    Nodo* temp = heapTemp[pos];
                    heapTemp[pos] = heapTemp[menor];
                    heapTemp[menor] = temp;
                    pos = menor;
                }
            }
            
            delete[] heapTemp;
        }
};