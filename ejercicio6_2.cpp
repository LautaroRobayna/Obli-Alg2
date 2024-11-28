#include <string>
#include <iostream>
#include "tads/Par.cpp"
#include "tads/ListImp2.cpp"
#include "tads/MinHeap.cpp"

using namespace std;
Par<ListImp<int>, ListImp<int>> dijkstra(int n, int src, ListImp<Par<int, int>>* G) {
    const int INF = 1e9;

    // Arreglos para distancias y padres
    int* dist = new int[n + 1];
    int* parent = new int[n + 1];
    bool* inHeap = new bool[n + 1];

    // Inicializamos distancias y padres
    for (int i = 0; i <= n; i++) {
        dist[i] = INF;
        parent[i] = -1;
        inHeap[i] = false;
    }

    dist[src] = 0;

    // Creamos el MinHeap
    MinHeap heap(n + 1);
    heap.insert(src, dist[src]);
    inHeap[src] = true;

    while (!heap.isEmpty()) {
        Nodo* current = heap.extractMin();
        if (current == nullptr) break;
        int u = current->key;
        int d = current->value;
        delete current; // Liberamos el nodo extraído

        inHeap[u] = false;

        // Si la distancia en el heap es mayor, ignoramos el nodo
        if (d > dist[u]) continue;

        // Recorremos los vecinos de u
        ListImp<Par<int, int>>& adj = G[u];
        for (int i = 0; i < adj.getSize(); i++) {
            Par<int, int> edge = adj.get(i);
            int v = edge.primero;
            int weight = edge.segundo;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                if (!inHeap[v]) {
                    heap.insert(v, dist[v]);
                    inHeap[v] = true;
                } else {
                    // Actualizar el valor en el heap
                    heap.decreaseKey(v, dist[v]);
                }
            }
        }
    }

    // Convertimos los arreglos a ListImp<int> antes de devolverlos
    ListImp<int> distList;
    ListImp<int> parentList;
    for (int i = 0; i <= n; i++) {
        distList.insert(dist[i]);
        parentList.insert(parent[i]);
    }

    // Liberamos la memoria de los arreglos
    delete[] dist;
    delete[] parent;
    delete[] inHeap;

    return {distList, parentList};
}





ListImp<int> reconstruct_path(int start, int finish, ListImp<int> parent) {
    ListImp<int> path;
    int current = finish;

    while (current != -1) {
        path.insertAt(0, current);
        current = parent.get(current);
    }

    if (path.getSize() == 0 || path.get(0) != start) {
        return ListImp<int>();
    }

    return path;
}

void duplicarValor(ListImp<Par<int,int>>* G, int a, int b){
    int pos = 0;
    while(G[a].get(pos).primero != b ) pos++;

    G[a].set(pos, {b, G[a].get(pos).segundo*2});

}

void duplicar(ListImp<Par<int,int>>* G, ListImp<int> &camino){
    for(int i = 1; i < camino.getSize(); i++){
        duplicarValor(G, camino.get(i-1), camino.get(i));
        duplicarValor(G, camino.get(i), camino.get(i-1));
    }
}

void restaurarValor(ListImp<Par<int,int>>* G, int a, int b){
    int pos = 0;
    while(G[a].get(pos).primero != b ) pos++;

    G[a].set(pos, {b, G[a].get(pos).segundo/2});

}

void restaurar(ListImp<Par<int,int>>* G, ListImp<int> &camino){
    for(int i = 1; i < camino.getSize(); i++){
        restaurarValor(G, camino.get(i-1), camino.get(i));
        restaurarValor(G, camino.get(i), camino.get(i-1));
    }
}

void imprimirCamino(ListImp<int>& path, string* ciudades) {
    cout << ciudades[path.get(0)];
    for (int i = 1; i < path.getSize(); i++) {
        cout << " -> " << ciudades[path.get(i)];
    }
}

int main() {
    int n;
    cin >> n;
    string *ciudades = new string[n + 1];
    for (int i = 1; i <= n; i++) {
        int id;
        cin >> id;
        string nombre;
        cin >> nombre;
        ciudades[id] = nombre;
    }

    int S, E, T, P, m;
    cin >> S >> E >> T >> P >> m;

    ListImp<Par<int,int>>* G = new ListImp<Par<int,int>>[n+1];

    for(int i = 0; i < m; i++){
        int a,b,v; cin>>a>>b>>v;
        G[a].insert({b,v});
        G[b].insert({a,v});
    }

    ListImp<int>* distancias = new ListImp<int>[6];
    ListImp<int>* anterior = new ListImp<int>[6];
    ListImp<int>* caminos = new ListImp<int>[6];

    int camino1 = 0; int camino2 = 0;

    Par<ListImp<int>,ListImp<int>> resultado = dijkstra(n, S, G);
    distancias[0] = resultado.primero;
    anterior[0] = resultado.segundo;
    caminos[0] = reconstruct_path(S,E,anterior[0]);
    duplicar(G,caminos[0]);


    resultado = dijkstra(n, E, G);
    distancias[1] = resultado.primero;
    anterior[1] = resultado.segundo;
    caminos[1] = reconstruct_path(E,T,anterior[1]);
    duplicar(G,caminos[1]);

    resultado = dijkstra(n, T, G);
    distancias[2] = resultado.primero;
    anterior[2] = resultado.segundo;
    caminos[2] = reconstruct_path(T,P,anterior[2]);

    restaurar(G,caminos[1]);
    restaurar(G,caminos[0]);

    
    resultado = dijkstra(n, S, G);
    distancias[3] = resultado.primero;
    anterior[3] = resultado.segundo;
    caminos[3] = reconstruct_path(S,T,anterior[3]);
    duplicar(G,caminos[3]);

    resultado = dijkstra(n, T, G);
    distancias[4] = resultado.primero;
    anterior[4] = resultado.segundo;
    caminos[4] = reconstruct_path(T,E,anterior[4]);
    duplicar(G,caminos[4]);

    resultado = dijkstra(n, E, G);
    distancias[5] = resultado.primero;
    anterior[5] = resultado.segundo;
    caminos[5] = reconstruct_path(E,P,anterior[5]);
    
    camino1 = distancias[0].get(E) + distancias[1].get(T) + distancias[2].get(P);
    camino2 = distancias[3].get(T) + distancias[4].get(E) + distancias[5].get(P);
    
    
    if (camino1 <= camino2) {
        cout << "BE11, la mejor ruta es Desactivar la Entidad, buscar equipo y punto de extraccion con un costo de " << camino1<< '\n';
        cout << "La otra opcion tiene un costo de " << camino2 << '\n';
        cout << "Paso 1: ";
        imprimirCamino(caminos[0], ciudades);
        cout << " -> Desactivar la Entidad" << '\n';
        cout << "Paso 2: ";
        imprimirCamino(caminos[1], ciudades);
        cout << " -> Buscar equipo" << '\n';
        cout << "Paso 3: ";
        imprimirCamino(caminos[2], ciudades);
        cout << " -> Ir a Punto de extraccion" << '\n';
    } else {
        cout << "BE11, la mejor ruta es buscar equipo, Desactivar la Entidad y punto de extraccion con un costo de " << camino2 << '\n';
        cout << "La otra opcion tiene un costo de " << camino1 << '\n';
        cout << "Paso 1: ";
        imprimirCamino(caminos[3], ciudades);
        cout << " -> Buscar equipo" << '\n';
        cout << "Paso 2: ";
        imprimirCamino(caminos[4], ciudades);
        cout << " -> Desactivar la Entidad" << '\n';
        cout << "Paso 3: ";
        imprimirCamino(caminos[5], ciudades);
        cout << " -> Ir a Punto de extraccion" << '\n';
    }

    delete[] ciudades;
    
    return 0;
}
