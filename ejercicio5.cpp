#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/MisionImposible.cpp"
#include "tads/ListImp.cpp"

using namespace std;

int main() {
    int m;
    cin >> m;

    ListImp<OrgMisiones::Mision*> listaMisiones;
    
    for (int i = 0; i < m; i++) {
        string nombre;
        int idMision, idCiudad;
        ListImp<int>* dependientes = new ListImp<int>();

        cin >> idMision >> nombre >> idCiudad;

        int dep;
        while (true) {
            cin >> dep;
            if (dep == 0) break;
            dependientes->insert(dep);
        }

        OrgMisiones::Mision* mision = new OrgMisiones::Mision(idMision, nombre, idCiudad, dependientes);
        listaMisiones.insert(mision);
    }


        int cantCiudades, o;
        cin >> cantCiudades >> o;

        OrgMisiones* org = new OrgMisiones(m, cantCiudades, o);

        // Agregar misiones al organizador
        for (int i = 0; i < listaMisiones.getSize(); i++) {
            OrgMisiones::Mision* m = listaMisiones.get(i);
            org->agregarMision(m);
        }

        // Leer ciudades
        while (cantCiudades--) {
            int idCiudad;
            string nombre;
            cin >> idCiudad >> nombre;
            if (idCiudad < 1 || idCiudad > 50) {
                cout << "Error: ID de ciudad inválido" << endl;
                return 1;
            }
            org->agregarCiudad(idCiudad, nombre);
        }

        // Leer rutas
        int e;
        cin >> e;

        while (e--) {
            int idCiudadOri, idCiudadDes, tiempo;
            cin >> idCiudadOri >> idCiudadDes >> tiempo;
            org->agregarRuta(idCiudadOri, idCiudadDes, tiempo);
        }

        // Resolver y liberar memoria
        org->resolver();
        
        // Limpieza de memoria
        for (int i = 0; i < listaMisiones.getSize(); i++) {
            OrgMisiones::Mision* m = listaMisiones.get(i);
            delete m;
        }
        delete org;

        return 0;
}