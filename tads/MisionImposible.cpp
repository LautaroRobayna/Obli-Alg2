#include <iostream>
#include <fstream>
#include "../tads/ListImp.cpp"
#define INF 99999
using namespace std;

template<class T1, class T2>
class Par {
    public:
        T1 elem1;
        T2 elem2;

        Par(T1 elem1, T2 elem2): elem1(elem1), elem2(elem2) {}
};

class Arista {
    public:
        int costo;
        bool existe;

        Arista() : costo(0), existe(false) {}
};

class Grafo {
private:
    int** vertices;          // Array de punteros a enteros para los vértices
    Arista*** matAdy;        // Matriz de adyacencia
    int tope;               // Capacidad máxima del grafo
    int cantVertices;       // Cantidad actual de vértices

    int primerHueco() {
        for (int i = 1; i < tope; i++) {
            if(!vertices[i]) {
                return i;
            }
        }
        return -1;
    }

    int posVertice(int v) {
        for (int i = 0; i < tope; i++) {
            if(vertices[i] != nullptr && *vertices[i] == v) {
                return i;
            }
        }
        return -1;
    }

    int ObtenerPosSinIncidencias(int* cantIncidencias, bool* vis) {
        for (int i = 1; i < tope; i++) {
            if(vertices[i] && cantIncidencias[i] == 0 && !vis[i]) {
                return i;
            }
        }
        return -1;
    }

    int posMasCercanoNoVis(int* dist, bool* vis) {
        int posMin = -1;
        int min = INF;
        for (int i = 0; i < tope; i++) {
            if(vertices[i] && !vis[i] && dist[i] < min) {
                min = dist[i];
                posMin = i;
            }
        }
        return posMin;
    }

public:
    Grafo(int tope, bool esDirigido = true) {
        this->tope = tope;
        this->cantVertices = 0;
        
        // Inicializar array de vértices
        this->vertices = new int*[tope]();  // () inicializa todo en nullptr
        
        // Inicializar matriz de adyacencia
        this->matAdy = new Arista**[tope];
        for (int i = 0; i < tope; i++) {
            this->matAdy[i] = new Arista*[tope];
        }

        if(esDirigido) {
            // Para grafo dirigido, inicializar toda la matriz
            for (int i = 0; i < tope; i++) {
                for (int j = 0; j < tope; j++) {
                    this->matAdy[i][j] = new Arista();
                }
            }
        } else {
            // Para grafo no dirigido, inicializar solo la mitad y compartir punteros
            for (int i = 0; i < tope; i++) {
                for (int j = i; j < tope; j++) {
                    Arista* arista = new Arista();
                    this->matAdy[i][j] = arista;
                    this->matAdy[j][i] = arista;  // Misma arista en ambas direcciones
                }
            }
        }
    }

    void AgregarVertice(int v) {
        if (posVertice(v) == -1) {  // Verificar que el vértice no exista
            int pos = primerHueco();
            if (pos != -1) {
                vertices[pos] = new int(v);
                cantVertices++;
            }
        }
    }

    bool getExisteArista(int i, int j) {
        return matAdy[i][j]->existe;
    }

    void AgregarArista(int vOri, int vDes, int costo) {
        int posO = posVertice(vOri);
        int posD = posVertice(vDes);
        
        if (posO != -1 && posD != -1) {
            matAdy[posO][posD]->costo = costo;
            matAdy[posO][posD]->existe = true;
        } else {
            cout << "Error: Vértice no encontrado" << endl;
        }
    }
    

    int* getVertice(int indice) {
        return vertices[indice];  
    }

    ListImp<int>* OrdenTopologico(){
        int*cantIncidencias = new int[tope]();
        bool*vis=new bool[tope]();
        ListImp<int>* res = new ListImp<int>();
        for (int j = 1; j < tope; j++)
        {
            for (int i = 1; i < tope; i++)
            {
                if(matAdy[i][j]->existe){
                    cantIncidencias[j]++;
                }
            }
        }
        int verticesRestantes = cantVertices;
        while(verticesRestantes > 0){
            int pos = ObtenerPosSinIncidencias(cantIncidencias, vis);
            if(pos == -1){
                cout << "NOOOOOO! CICLOOOO!" << endl;
                break;
            } else {
                res->insert(*vertices[pos]);
                vis[pos]=true;
                for (int j = 0; j < tope; j++)
                {
                    if(matAdy[pos][j]->existe){
                        cantIncidencias[j]--;
                    }
                }
            }
            verticesRestantes--;
        }    
        return res;        
    }

    pair<int, ListImp<int>> Dijkstra(int origen, int destino) {
        int posOrigen = posVertice(origen);
        int posDestino = posVertice(destino);
        
        if (posOrigen == -1 || posDestino == -1) {
            return {INF, ListImp<int>()};
        }

        int* dist = new int[tope];
        bool* vis = new bool[tope]();
        int* prev = new int[tope];
        
        // Inicialización
        for (int i = 0; i < tope; i++) {
            dist[i] = INF;
            prev[i] = -1;
        }
        dist[posOrigen] = 0;

        // Algoritmo de Dijkstra
        for (int count = 0; count < cantVertices; count++) {
            // Encontrar el vértice no visitado con la menor distancia
            int u = -1;
            int minDist = INF;
            for (int i = 0; i < tope; i++) {
                if (!vis[i] && vertices[i] && dist[i] < minDist) {
                    minDist = dist[i];
                    u = i;
                }
            }
            
            if (u == -1 || u == posDestino) break;
            
            vis[u] = true;

            // Actualizar distancias
            for (int v = 0; v < tope; v++) {
                if (vertices[v] && matAdy[u][v]->existe && !vis[v]) {
                    int alt = dist[u] + matAdy[u][v]->costo;
                    if (alt < dist[v]) {
                        dist[v] = alt;
                        prev[v] = u;
                    }
                }
            }
        }

        // Construir el camino
        ListImp<int> camino;
        if (dist[posDestino] != INF) {
            int at = posDestino;
            while (at != -1) {
                camino.insert(*vertices[at]);
                at = prev[at];
            }
            camino.reverse();
        }

        int costoTotal = dist[posDestino];
        
        delete[] dist;
        delete[] vis;
        delete[] prev;

        return {costoTotal, camino};
    }

    ~Grafo() {
        // Liberar memoria de la matriz de adyacencia
        for (int i = 0; i < tope; i++) {
            for (int j = 0; j < tope; j++) {
                delete matAdy[i][j];
            }
            delete[] matAdy[i];
        }
        delete[] matAdy;

        // Liberar memoria de los vértices
        for (int i = 0; i < tope; i++) {
            delete vertices[i];
        }
        delete[] vertices;
    }
};

class OrgMisiones {
public:
    class Mision {
    public:
        int idMision;  // Cambié 'id' por 'idMision' para consistencia
        string nombre;
        int idCiudad;
        ListImp<int>* dependencias;

        Mision(int id, string nombre, int idCiudad, ListImp<int>* dependencias)
    : idMision(id), nombre(nombre), idCiudad(idCiudad), dependencias(dependencias) {}

    };

    class Ciudad {
    public:
        int id;
        string nombre;

        Ciudad(int id, string nombre) : id(id), nombre(nombre) {}
    };

    OrgMisiones(int cantMisiones, int cantCiudades, int o) {
        grafoMisiones = new Grafo(cantMisiones + 1);  // +1 porque los IDs empiezan en 1
        grafoCiudades = new Grafo(cantCiudades + 1, false);
        misiones = new Mision*[cantMisiones + 1]();  
        ciudades = new Ciudad*[cantCiudades + 1]();  
        ciudadInicial = o;

        // Inicializar los vértices en ambos grafos
        for(int i = 1; i <= cantMisiones; i++) {
            grafoMisiones->AgregarVertice(i);
        }
        for(int i = 1; i <= cantCiudades; i++) {
            grafoCiudades->AgregarVertice(i);
        }
    }

    void imprimirMatrizAdyacencia(int cantMisiones) {
        for (int i = 1; i <= cantMisiones; i++) {
            for (int j = 1; j <= cantMisiones; j++) {
                cout << (grafoMisiones->getExisteArista(i, j) ? 1 : 0) << " ";
            }
            cout << endl;
        }
    }

    void agregarMision(Mision* m) {
        misiones[m->idMision] = m;
        
        for (int i = 0; i < m->dependencias->getSize(); i++) {
            int idDep = m->dependencias->get(i);
            if(idDep != 0) {
                grafoMisiones->AgregarArista(m->idMision, idDep, 1);
            }
        }
    }

    void agregarCiudad(int idCiudad, string nombre) {
        ciudades[idCiudad] = new Ciudad(idCiudad, nombre);
    }

    void agregarRuta(int idCiudadOri, int idCiudadDes, int tiempo) {
        grafoCiudades->AgregarArista(idCiudadOri, idCiudadDes, tiempo);
    }

    void resolver() {
        ListImp<int>* ordenMisiones = grafoMisiones->OrdenTopologico();
        int ciudadActual = ciudadInicial;
        int tiempoTotal = 0;

        cout << "Ciudad inicial: " << ciudades[ciudadInicial]->nombre << endl;

      for(int i = 0; i < ordenMisiones->getSize(); i++) {
            int idMisionActual = ordenMisiones->get(i);
            Mision* misionActual = misiones[idMisionActual];
            
            auto resultado = grafoCiudades->Dijkstra(ciudadActual, misionActual->idCiudad);
            int costo = resultado.first;
            ListImp<int>& camino = resultado.second;

            imprimirCamino(camino, misionActual, costo);

            tiempoTotal += costo;
            ciudadActual = misionActual->idCiudad;
        }

        cout << "Misiones ejecutadas con exito." << endl;
        cout << "Tiempo total de viaje: " << tiempoTotal << endl;

        delete ordenMisiones;
    }

private:
    Grafo* grafoMisiones;
    Grafo* grafoCiudades;
    Mision** misiones;
    Ciudad** ciudades;
    int ciudadInicial;

    void imprimirCamino(ListImp<int>& camino, Mision* mision, int costo) {
        bool primero = true;
        for(int i = 0; i < camino.getSize(); i++) {
            if(!primero) cout << " -> ";
            cout << ciudades[camino.get(i)]->nombre;
            primero = false;
        }
        cout << " -> Mision: " << mision->nombre 
             << " - " << ciudades[mision->idCiudad]->nombre 
             << " - Tiempo de viaje: " << costo << endl;
    }
};
