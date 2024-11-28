#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>
#include "ListImp.cpp"

using namespace std;

struct Ciudad {
    int x, y, p;
};

// Me la dio Claude, es para poder comparar ciudades
bool operator==(const Ciudad& a, const Ciudad& b) {
    return a.x == b.x && a.y == b.y && a.p == b.p;
}

bool compararPorX(const Ciudad& a, const Ciudad& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool compararPorY(const Ciudad& a, const Ciudad& b) {
    return a.y < b.y;
}

// Calcular la distancia efectiva entre dos ciudades
double distanciaEfectiva(const Ciudad& a, const Ciudad& b) {
    double distanciaEuclidiana = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
    double ajustePoblacion = abs(a.p - b.p) / (double)max(a.p, b.p);
    return distanciaEuclidiana + ajustePoblacion;
}

// Divide & Conquer para encontrar la distancia efectiva mínima
pair<Ciudad, Ciudad> encontrarDistanciaMinima(Ciudad ciudades[], int izq, int der) {
    // Caso base: si hay 2 o 3 ciudades
    if (der - izq <= 3) {
        pair<Ciudad, Ciudad> mejorPar;
        double mejorDistancia = numeric_limits<double>::max();
        
        for (int i = izq; i <= der; ++i) {
            for (int j = i + 1; j <= der; ++j) {
                double dist = distanciaEfectiva(ciudades[i], ciudades[j]);
                
                if (dist < mejorDistancia || 
                    (dist == mejorDistancia && 
                     (ciudades[i].p + ciudades[j].p > 
                      mejorPar.first.p + mejorPar.second.p))) {
                    mejorDistancia = dist;
                    mejorPar = {ciudades[i], ciudades[j]};
                }
            }
        }
        return mejorPar;
    }

    // Dividir en dos mitades
    int mid = (izq + der) / 2;
    int xMedio = ciudades[mid].x;

    // Resolver recursivamente en ambas mitades
    auto parIzq = encontrarDistanciaMinima(ciudades, izq, mid);
    auto parDer = encontrarDistanciaMinima(ciudades, mid + 1, der);

    double distIzq = distanciaEfectiva(parIzq.first, parIzq.second);
    double distDer = distanciaEfectiva(parDer.first, parDer.second);
    
    pair<Ciudad, Ciudad> mejorPar;
    double mejorDistancia;
    
    if (distIzq < distDer || 
        (distIzq == distDer && 
         (parIzq.first.p + parIzq.second.p > parDer.first.p + parDer.second.p))) {
        mejorPar = parIzq;
        mejorDistancia = distIzq;
    } else {
        mejorPar = parDer;
        mejorDistancia = distDer;
    }

    // Combinar - crear banda central con la lista implementada
    ListImp<Ciudad> bandaCentral;
    
    for (int i = izq; i <= der; ++i) {
        if (abs(ciudades[i].x - xMedio) < mejorDistancia) {
            bandaCentral.insert(ciudades[i]);
        }
    }

    // Convertir la lista a un array para poder ordenar por Y
    Ciudad* bandaCentralArray = new Ciudad[bandaCentral.getSize()];
    for (int i = 0; i < bandaCentral.getSize(); ++i) {
        bandaCentralArray[i] = bandaCentral.get(i);
    }

    // Ordenar banda central por Y
    sort(bandaCentralArray, bandaCentralArray + bandaCentral.getSize(), compararPorY);

    // Comparar pares en la banda central
    for (int i = 0; i < bandaCentral.getSize(); ++i) {
        for (int j = i + 1; j < bandaCentral.getSize() && 
             (bandaCentralArray[j].y - bandaCentralArray[i].y) < mejorDistancia; ++j) {
            
            double dist = distanciaEfectiva(bandaCentralArray[i], bandaCentralArray[j]);
            
            if (dist < mejorDistancia || 
                (dist == mejorDistancia && 
                 (bandaCentralArray[i].p + bandaCentralArray[j].p > 
                  mejorPar.first.p + mejorPar.second.p))) {
                mejorDistancia = dist;
                mejorPar = {bandaCentralArray[i], bandaCentralArray[j]};
            }
        }
    }

    // Liberar memoria
    delete[] bandaCentralArray;

    return mejorPar;
}