#include <iostream>
#include "../funciones/enteros.cpp"
using namespace std;

class HashBook {
    public:
        class Node {
            public:
                int id;
                string title;
                bool available;
                bool dirty;
                Node(int id, string title) : id(id), title(title), available(true), dirty(false){}
        };

        HashBook(int maxAmount) {
            this->amount = 0;
            this->maxAmount = maxAmount;
            this->available = 0;
            this->largeArray = primoSup(maxAmount*2);
            this->hash = new Node*[this->largeArray]();
            this->hashF = hashF;
            this->hashF2 = hashF2;
        }

        void ADD(int id, string title){
            this->Insert(id, title);
        }

        void TOGGLE(int id){
            this->HabilitarDeshabilitar(id);
        }

        void FIND(int id){
            Node* book = Search(id);
            if(book){
                if(book->available){
                    cout << book->title << " H" << endl;
                }
                else{
                    cout << book->title << " D" << endl;
                }
            }
            else{
                cout << "libro_no_encontrado" << endl;
            }
        }

        void COUNT(){
            int unavailable = this->amount - this->available;
            cout << this->amount << " " << this->available << " " << unavailable;
        }
        
           

    private:
        Node** hash;
        int amount;
        int largeArray;
        int maxAmount;
        int available;
        int(*hashF);
        int(*hashF2);

        
        int hash1(int id) {
        int h = 0;
        h = 31 * id ;
        return h;
        }

        //Funcion dada por chatGPT
        int hash2(int id) {
        int h = 0;
        h = 33 * id; // Un número primo diferente (33) al usado en fHash
        return h % (largeArray - 1) + 1; // Asegura que el desplazamiento sea siempre positivo y no sea cero
        }

        void Insert(int id, string title){
            int hashPos = abs(hash1(id)) % largeArray;
            int j = 0;
            while(hash[hashPos] && !hash[hashPos]->dirty){
                j++;
                if(hash[hashPos]->id == id){
                    hash[hashPos]->title = title;
                    if(!hash[hashPos]->available){
                        hash[hashPos]->available = true;
                    }
                    return;
                }
                hashPos = abs(hash1(id) + j * hash2(id)) % largeArray;
            }
            if(hash[hashPos]){
                delete hash[hashPos];
            }
            hash[hashPos] = new Node(id, title);
            amount++;
            available++;
        }

        void HabilitarDeshabilitar(int id){
            int hashPos = abs(hash1(id)) % largeArray;
            int j = 0;
            if(!hash[hashPos] || hash[hashPos]->dirty){
                cout << "book_no_encontrado" << endl;
            }
            while(hash[hashPos] && !hash[hashPos]->dirty){
                j++;
                if(hash[hashPos]->id == id){
                    if(hash[hashPos]->available){
                        hash[hashPos]->available = false;
                        available--;
                    }else{
                        hash[hashPos]->available = true;
                        available++;
                    }
                    return;
                }
                hashPos = abs(hash1(id) + j * hash2(id)) % largeArray;
            }
        }

        Node* Search(int id){
            int hashPos = abs(hash1(id)) % largeArray;
            int j = 0;
            while(hash[hashPos] && !hash[hashPos]->dirty){
                j++;
                if(hash[hashPos]->id == id){
                    return hash[hashPos];
                }
                hashPos = abs(hash1(id) + j * hash2(id)) % largeArray;
            }
            return NULL;
        }

};


