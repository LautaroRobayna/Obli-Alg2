#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
const ll INF = numeric_limits<ll>::max();  // Infinito, para representar distancias no alcanzadas

vector<vector<ll>> G;  // Grafo representado como matriz de adyacencia

pair<vector<ll>, vector<int>> dijkstra(int n, int src) {
    vector<ll> dist(n + 1, INF);  // Distancias inicializadas a infinito
    vector<int> pred(n + 1, -1); // Predecesores para reconstruir el camino
    vector<bool> visited(n + 1, false); // Para marcar nodos visitados
    dist[src] = 0;  // La distancia al nodo de origen es 0

    for (int i = 1; i <= n; i++) {
        ll u = -1;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (u == -1 || dist[u] == INF) break;  // No quedan nodos alcanzables
        visited[u] = true;

        for (int v = 1; v <= n; v++) {
            if (G[u][v] != INF && dist[u] + G[u][v] < dist[v]) {
                dist[v] = dist[u] + G[u][v];
                pred[v] = u;
            }
        }
    }

    return {dist, pred};
}

void duplicar(vector<int> path) {
    if (path.empty()) return;  // Verificar que el camino no esté vacío
    for (int i = 1; i < path.size(); i++) {
        G[path[i-1]][path[i]] *= 2;
        G[path[i]][path[i-1]] *= 2;
    }
}

void restaurar(vector<int> path) {
    if (path.empty()) return;  // Verificar que el camino no esté vacío
    for (int i = 1; i < path.size(); i++) {
        G[path[i-1]][path[i]] /= 2;
        G[path[i]][path[i-1]] /= 2;
    }
}

vector<int> reconstruct_path(int src, int dest, const vector<int>& pred) {
    vector<int> path;
    for (int at = dest; at != -1; at = pred[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    if (path[0] != src) path.clear();  // Si el destino no es alcanzable
    return path;
}

void imprimirCamino(vector<int>& path, string* ciudades) {
    if (path.empty()) {
        cout << "No hay camino\n";
        return;
    }
    cout << ciudades[path[0]];
    for (int i = 1; i < path.size(); i++) {
        cout << " -> " << ciudades[path[i]];
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

    G.assign(n + 1, vector<ll>(n + 1, INF));
    for (int i = 1; i <= n; i++) {
        G[i][i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int a, b, v;
        cin >> a >> b >> v;
        G[a][b] = v;
        G[b][a] = v;
    }

    vector<vector<ll>> dist(6);
    vector<vector<int>> pred(6);
    vector<vector<int>> path(6);

    ll cam1 = 0; 
    ll cam2 = 0;

    // Primer Dijkstra
    tie(dist[0], pred[0]) = dijkstra(n, S);
    path[0] = reconstruct_path(S, E, pred[0]);
    duplicar(path[0]);

    // Segundo Dijkstra
    tie(dist[1], pred[1]) = dijkstra(n, E);
    path[1] = reconstruct_path(E, T, pred[1]);
    duplicar(path[1]);

    // Tercer Dijkstra
    tie(dist[2], pred[2]) = dijkstra(n, T);
    path[2] = reconstruct_path(T, P, pred[2]);

    restaurar(path[0]);
    restaurar(path[1]);

    // Cuarto Dijkstra
    tie(dist[3], pred[3]) = dijkstra(n, S);
    path[3] = reconstruct_path(S, T, pred[3]);
    duplicar(path[3]);

    // Quinto Dijkstra
    tie(dist[4], pred[4]) = dijkstra(n, T);
    path[4] = reconstruct_path(T, E, pred[4]);
    duplicar(path[4]);

    // Sexto Dijkstra
    tie(dist[5], pred[5]) = dijkstra(n, E);
    path[5] = reconstruct_path(E, P, pred[5]);

    cam1 = dist[0][E] + dist[1][T] + dist[2][P];
    cam2 = dist[3][T] + dist[4][E] + dist[5][P];

    if (cam1 <= cam2) {
        cout << "BE11, la mejor ruta es Desactivar la Entidad, buscar equipo y punto de extraccion con un costo de " << cam1 << '\n';
        cout << "La otra opcion tiene un costo de " << cam2 << '\n';
        cout << "Paso 1: ";
        imprimirCamino(path[0], ciudades);
        cout << " -> Desactivar la Entidad" << '\n';
        cout << "Paso 2: ";
        imprimirCamino(path[1], ciudades);
        cout << " -> Buscar equipo" << '\n';
        cout << "Paso 3: ";
        imprimirCamino(path[2], ciudades);
        cout << " -> Ir a Punto de extraccion" << '\n';
    } else {
        cout << "BE11, la mejor ruta es buscar equipo, Desactivar la Entidad y punto de extraccion con un costo de " << cam2 << '\n';
        cout << "La otra opcion tiene un costo de " << cam1 << '\n';
        cout << "Paso 1: ";
        imprimirCamino(path[3], ciudades);
        cout << " -> Buscar equipo" << '\n';
        cout << "Paso 2: ";
        imprimirCamino(path[4], ciudades);
        cout << " -> Desactivar la Entidad" << '\n';
        cout << "Paso 3: ";
        imprimirCamino(path[5], ciudades);
        cout << " -> Ir a Punto de extraccion" << '\n';
    }

    delete[] ciudades;
    return 0;
}
