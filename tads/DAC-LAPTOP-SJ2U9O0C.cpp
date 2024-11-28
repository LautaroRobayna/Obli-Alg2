#include <iostream>
#include "../tads/ListImp.cpp"
using namespace std;

class Comunicaciones {
    public:
        class Ciudad {
            public:
                int x;
                int y;
                int p;
                Ciudad(int x, int y, int p) : x(x), y(y), p(p){}
        };

        Comunicaciones(int cantCiudades) {
            this->cantCiudades = cantCiudades;
            this->arrayCiudades = new Ciudad*[this->cantCiudades]();
        }
        
        void agregarCiudad(int x, int y, int p, int n){
            Ciudad* c = new Ciudad(x,y,p);
            this->arrayCiudades[n] = c;
        }

        void minDist(){
            
        }

    private:
        int cantCiudades;
        Ciudad** arrayCiudades;

};


