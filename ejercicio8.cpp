#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/DAC.cpp"

// Para este ejercicio me apoyé en este video: https://www.youtube.com/watch?v=6u_hWxbOc7E&t=338s

int main() {
    int n;
    cin >> n;

    // Crear array dinámicamente con el tamaño n
    Ciudad* ciudades = new Ciudad[n];
    
    for (int i = 0; i < n; ++i) {
        cin >> ciudades[i].x >> ciudades[i].y >> ciudades[i].p;
    }

    // Ordenar por X usando quicksort nativo
    sort(ciudades, ciudades + n, compararPorX);

    auto resultado = encontrarDistanciaMinima(ciudades, 0, n - 1);

    Ciudad c1 = resultado.first, c2 = resultado.second;
    if (c1.x > c2.x || (c1.x == c2.x && c1.y > c2.y)) {
        swap(c1, c2);
    }

    cout << c1.x << " " << c1.y << " " << c1.p << "\n";
    cout << c2.x << " " << c2.y << " " << c2.p << "\n";

    // Liberar memoria
    delete[] ciudades;

    return 0;
}