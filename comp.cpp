#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip> // Para std::hex

using namespace std;

// Función para limpiar caracteres invisibles e innecesarios
string cleanString(const string& str) {
    string result;
    for (char ch : str) {
        // Eliminar el retorno de carro (\x0D)
        if (ch != '\r') {
            // Mantener caracteres imprimibles y espacios
            if (isprint(static_cast<unsigned char>(ch)) || isspace(static_cast<unsigned char>(ch))) {
                result += ch;
            }
        }
    }
    return result;
}

// Función para mostrar caracteres en formato hexadecimal
void printHex(const string& str) {
    for (unsigned char ch : str) {
        cout << "\\x" << hex << setw(2) << setfill('0') << static_cast<int>(ch);
    }
    cout << endl;
}

// Función para comparar dos archivos y encontrar diferencias
void compareFiles(const string& file1, const string& file2) {
    ifstream f1(file1);
    ifstream f2(file2);

    if (!f1.is_open()) {
        cerr << "Error opening file: " << file1 << endl;
        return;
    }
    if (!f2.is_open()) {
        cerr << "Error opening file: " << file2 << endl;
        return;
    }

    stringstream buffer1, buffer2;
    buffer1 << f1.rdbuf();
    buffer2 << f2.rdbuf();

    string content1 = cleanString(buffer1.str());
    string content2 = cleanString(buffer2.str());

    if (content1 != content2) {
        // Encontrar y mostrar la línea donde los archivos difieren
        istringstream s1(content1);
        istringstream s2(content2);
        string line1, line2;
        int lineNumber = 1;

        while (getline(s1, line1) && getline(s2, line2)) {
            if (line1 != line2) {
                cout << "Difference found on line " << lineNumber << ":\n";
                cout << "File 1: ";
                printHex(line1);
                cout << "File 2: ";
                printHex(line2);
                return;
            }
            lineNumber++;
        }

        // Si un archivo tiene más líneas que el otro
        while (getline(s1, line1)) {
            cout << "File 1 has extra line " << lineNumber << ": ";
            printHex(line1);
            lineNumber++;
        }
        while (getline(s2, line2)) {
            cout << "File 2 has extra line " << lineNumber << ": ";
            printHex(line2);
            lineNumber++;
        }
    } else {
        cout << "Si" << endl; // Los archivos son idénticos
    }
}

int main() {
    string file1 = "out.txt"; // Archivo a comparar
    string file2 = ".//tests//ejercicio2//1000000.out.txt"; // Archivo contra el cual comparar

    compareFiles(file1, file2);

    return 0;
}
