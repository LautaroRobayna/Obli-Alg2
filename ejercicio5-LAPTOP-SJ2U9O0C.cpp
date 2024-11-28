#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "../tads/MisionImposible.cpp"
#include "../tads/ListImp.cpp"

using namespace std;

int main() {
    int m;
    cin >> m;
    cout << "Total misiones leídas: " << m << endl;

    ListImp<OrgMisiones::Mision*> listaMisiones;

    for (int i = 0; i < m; i++) {
        string nombre;
        int idMision, idCiudad;
        ListImp<int>* dependientes = new ListImp<int>();

        // Debug: mostrar estado de entrada antes de leer
        cout << "Estado de entrada antes de leer misión:" << endl;
        char next = cin.peek();
        cout << "Próximo carácter: '" << next << "'" << endl;

        cin >> idMision >> nombre >> idCiudad;
        
        cout << "Misión leída - ID: " << idMision 
             << ", Nombre: " << nombre 
             << ", Ciudad: " << idCiudad << endl;

        // Lectura de dependencias con debug detallado
        int dep;
        cout << "Leyendo dependencias:" << endl;
        while (true) {
            cin >> dep;
            
            // Debug de cada lectura
            cout << "Dependencia leída: " << dep 
                 << ", Estado de cin: " 
                 << (cin.fail() ? "FAIL" : "OK") 
                 << endl;
            
            if (dep == 0) break;
            
            if (dep < 1 || dep > 200) {
                cout << "Error: ID de misión dependiente inválido" << endl;
                delete dependientes;
                return 1;
            }
            dependientes->insert(dep);
        }
        
        // Imprimir dependencias
        cout << "Dependencias para la misión " << nombre << ": ";
        for (int j = 0; j < dependientes->getSize(); j++) {
            cout << dependientes->get(j) << " ";
        }
        cout << endl;
        
        OrgMisiones::Mision* mision = new OrgMisiones::Mision(idMision, nombre, idCiudad, dependientes);
        listaMisiones.insert(mision);
    }

    int c, o;
    cin >> c >> o;
    int cantCiudades = c;

    OrgMisiones* org = new OrgMisiones(cantMisiones, cantCiudades, o);

    for (int i = 1; i <= ListaMisiones.getSize(); i++) {
        Mision m = ListaMisiones->get(i);
        org->agregarMision(m->id, m->name, m->cityId, m->dependencies);
    }

    while (c--)
    {
        int idCiudad;
        string nombre;
        cin >> idCiudad >> nombre;
        org->agregarCiudad(idCiudad, nombre);
    }

    int e;
    cin >> e;
    while (e--)
    {
        int idCiudadOri, idCiudadDes, tiempo;
        cin >> idCiudadOri >> idCiudadDes >> tiempo;
        org->agregarRuta(idCiudadOri, idCiudadDes, tiempo);
    }

    org->resolver();

    return 0;
}