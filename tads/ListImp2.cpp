#ifndef LIST_IMP
#define LIST_IMP

#include <cassert>

template <class T>
class ListImp
{
private:
    // Clase interna (Node) para la lista doblemente enlazada
    class Node
    {
    public:
        T element;
        Node *next;
        Node *previous;
        Node(const T& element, Node *next = nullptr, Node *previous = nullptr) : element(element), next(next), previous(previous) {}
    };

    Node *head;
    Node *tail;
    int size;

public:
    // Constructor por defecto
    ListImp() : head(nullptr), tail(nullptr), size(0) {}

    // Constructor de copia
    ListImp(const ListImp<T>& other) : head(nullptr), tail(nullptr), size(0) {
        Node* current = other.head;
        while (current != nullptr) {
            insert(current->element);
            current = current->next;
        }
    }

    // Operador de asignación
    ListImp<T>& operator=(const ListImp<T>& other) {
        if (this != &other) {
            clear();
            Node* current = other.head;
            while (current != nullptr) {
                insert(current->element);
                current = current->next;
            }
        }
        return *this;
    }

    // Destructor
    ~ListImp() {
        clear();
    }

    // Limpia la lista
    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = tail = nullptr;
        size = 0;
    }

    // Verifica si la lista está vacía
    bool isEmpty() const {
        return head == nullptr;
    }

    // Devuelve el tamaño de la lista
    int getSize() const {
        return size;
    }

    // Inserta un elemento al final de la lista
    void insert(const T& element) {
        Node* newNode = new Node(element, nullptr, tail);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    // Inserta un elemento en una posición específica
    void insertAt(int index, const T& element) {
        assert(index >= 0 && index <= size);
        if (index == size) {
            insert(element);
            return;
        }
        Node* newNode = new Node(element);
        if (index == 0) {
            newNode->next = head;
            if (head != nullptr) {
                head->previous = newNode;
            }
            head = newNode;
            if (tail == nullptr) {
                tail = newNode;
            }
        } else {
            Node* current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
            newNode->next = current;
            newNode->previous = current->previous;
            if (current->previous != nullptr) {
                current->previous->next = newNode;
            }
            current->previous = newNode;
        }
        size++;
    }

    // Modifica el elemento en una posición específica
    void set(int index, const T& element) {
        assert(index >= 0 && index < size);
        Node* current = getNodeAt(index);
        current->element = element;
    }

    // Obtiene el elemento en una posición específica
    T& get(int index) {
        assert(index >= 0 && index < size);
        Node* current = getNodeAt(index);
        return current->element;
    }

    // Obtiene el elemento en una posición específica (constante)
    const T& get(int index) const {
        assert(index >= 0 && index < size);
        Node* current = getNodeAt(index);
        return current->element;
    }

private:
    // Método auxiliar para obtener el nodo en una posición específica
    Node* getNodeAt(int index) const {
        assert(index >= 0 && index < size);
        Node* current;
        if (index < size / 2) {
            current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
        } else {
            current = tail;
            for (int i = size - 1; i > index; i--) {
                current = current->previous;
            }
        }
        return current;
    }
};

#endif
