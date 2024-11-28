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
        Node(T element, Node *next, Node *previous) : element(element), next(next), previous(previous) {}
    };

    Node *head;
    Node *tail;
    int size;

public:
    ListImp() : head(NULL), tail(NULL), size(0) {}

    // Constructor de copia
    ListImp(const ListImp<T>& other) : head(NULL), tail(NULL), size(0) {
        Node* current = other.head;
        while (current != NULL) {
            insert(current->element);
            current = current->next;
        }
    }

    // Operador de asignación
    ListImp<T>& operator=(const ListImp<T>& other) {
        if (this != &other) {
            clear();
            Node* current = other.head;
            while (current != NULL) {
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

    void clear() {
        Node* current = head;
        while (current != NULL) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = tail = NULL;
        size = 0;
    }

    // Resto de métodos (insert, insertAt, get, set, etc.)
    // ...

    // Inserta un elemento al final de la lista
    void insert(T element)
    {
        Node *newNode = new Node(element, NULL, tail);
        if (isEmpty())
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    // Inserta un elemento en una posición específica
    void insertAt(int index, T element)
    {
        assert(index >= 0 && index <= size);
        Node *newNode = new Node(element, NULL, NULL);
        if (index == 0)
        {
            if (head != NULL)
            {
                newNode->next = head;
                head->previous = newNode;
            }
            head = newNode;
            if (tail == NULL) // Si la lista estaba vacía
            {
                tail = newNode;
            }
        }
        else if (index == size)
        {
            tail->next = newNode;
            newNode->previous = tail;
            tail = newNode;
        }
        else
        {
            Node *current = head;
            for (int i = 0; i < index; i++)
            {
                current = current->next;
            }
            newNode->next = current;
            newNode->previous = current->previous;
            if (current->previous != NULL)
            {
                current->previous->next = newNode;
            }
            current->previous = newNode;
        }
        size++;
    }

    // Modifica el elemento en una posición específica
    void set(int index, T element) {
        assert(index >= 0 && index < size);
        Node *current = head;
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }
        current->element = element;
    }

    // Verifica si la lista está vacía
    bool isEmpty()
    {
        return head == NULL;
    }

    // Obtiene el elemento en una posición específica
    T& get(int index)
    {
        assert(index >= 0 && index < size);
        Node *current = head;
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }
        return current->element;
    }

    // Devuelve el tamaño de la lista
    int getSize()
    {
        return size;
    }

    // Otros métodos si es necesario...
};

#endif
