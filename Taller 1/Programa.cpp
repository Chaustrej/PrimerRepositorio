#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

// Prototipos de funciones
string Minuscula(const string& palabra);
string Marcarr(const string& LasPalabras, const string& Laslineas, int& Eltiempo);

// Variables globales
int contador = 0; // Contador de palabras encontradas

int main() {
    string LasPalabras, Laslineas, continuar;

    cout << "Aqui se encuentra el buscador de palabras\n";
    cin.ignore();

    do {
        ifstream archivo("Archivo.txt");
        if (!archivo) {
            cout << "Error: archivo 'Archivo.txt' no encontrado. Verifique bien si se encuentra cerca.\n";
            return 1;
        }

        do {
            cout << "\nPor favor coloque las palabras que se va a buscar: ";
            getline(cin, LasPalabras);
        } while (LasPalabras.empty());

        cout << "\nEl resultado sería:\n";

        int total = 0, Laslineas_num = 1;
        bool encontrado = false;

        while (getline(archivo, Laslineas)) {
            int Eltiempo = 0;
            string LineaMarcadaColor = Marcarr(LasPalabras, Laslineas, Eltiempo);

            if (Eltiempo > 0) {
                cout << Laslineas_num << ": " << LineaMarcadaColor << endl;
                total += Eltiempo;
                encontrado = true;
            }
            Laslineas_num++;
        }

        archivo.close();
        if (encontrado) {
            cout << "\nEste sería el número de encontrados: " << total << endl;
        } else {
            cout << "No se ha encontrado la palabra.\n";
        }

        do {
            cout << "\n¿Desea buscar otra palabra? (s/n): ";
            getline(cin, continuar);
            continuar = Minuscula(continuar);
        } while (continuar != "s" && continuar != "n");

    } while (continuar == "s");

    cout << "Esto es todo por ahora\n";
    return 0;
}

// Convierte una cadena a minúsculas
string Minuscula(const string& palabra) {
    string resultado = palabra;
    transform(resultado.begin(), resultado.end(), resultado.begin(), ::tolower);
    return resultado;
}

// Marca las palabras encontradas en la línea y devuelve la línea modificada
string Marcarr(const string& LasPalabras, const string& Laslineas, int &Eltiempo) {
    string resultado = "";
    string lineaMinima = Minuscula(Laslineas);
    string palabraMinima = Minuscula(LasPalabras);
    size_t pos = 0, Encontro;
    Eltiempo = 0; // Inicializa el contador local

    while ((Encontro = lineaMinima.find(palabraMinima, pos)) != string::npos) {
    
        resultado += Laslineas.substr(pos, Encontro - pos);
        resultado += "033[32m" + Laslineas.substr(Encontro, LasPalabras.length()) + "033[0m"; // Resalta la palabra encontrada en verde
        Eltiempo++; // Incrementa el contador local
        pos = Encontro + LasPalabras.length();
    }
    resultado += Laslineas.substr(pos);
    return resultado;
}
