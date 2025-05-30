#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <limits>
#include <locale>

using namespace std;

// Prototipos
string Minuscula(const string& palabra);
string Marcarr(const string& LasPalabras, const string& Laslineas, int& Eltiempo);

int main() {
    setlocale(LC_ALL, "");

    string LasPalabras, Laslineas, continuar;

    cout << "--Aqui se encuentra el buscador de palabras-- \n";

    do {
        // Mostrar contenido del archivo SIN numerar
        {
            ifstream mostrar("archivo.txt");
            if (mostrar.is_open()) {
                cout << "\nContenido del archivo:\n";
                while (getline(mostrar, Laslineas)) {
                    cout << Laslineas << endl;  // Aquí quito el número de línea
                }
                mostrar.close();
            } else {
                cout << "No se pudo abrir el archivo 'archivo.txt'. Verifique si existo...\n";
                return 1;
            }
        }

        do {
            cout << "\nPor favor coloque las palabras que se va a buscar: ";
            getline(cin, LasPalabras);
        } while (LasPalabras.empty());

        ifstream archivo("archivo.txt");
        if (!archivo.is_open()) {
            cout << "No se pudo abrir el archivo para buscar.\n";
            return 1;
        }

        cout << "\n El resultado seria: \n";

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
            cout << "\nEste seria el numero de encontrados, los colocamos en orden : " << total << endl;
        } else {
            cout << "No se ha encontrado la palabra que usted coloco intente de nuevo.\n";
        }

        do {
            cout << " Desea buscar otra palabra? (s/n): ";
            getline(cin, continuar);
            continuar = Minuscula(continuar);
        } while (continuar != "s" && continuar != "n");

    } while (continuar == "s");

    cout << "\n Esto es todo por ahora gracias por usarme\n";
    return 0;
}

string Minuscula(const string& palabra) {
    string resultado = palabra;
    transform(resultado.begin(), resultado.end(), resultado.begin(), ::tolower);
    return resultado;
}

string Marcarr(const string& LasPalabras, const string& Laslineas, int &Eltiempo) {
    string resultado = "";
    string lineaMinima = Minuscula(Laslineas);
    string palabraMinima = Minuscula(LasPalabras);
    size_t pos = 0, Encontro;
    Eltiempo = 0;

    while ((Encontro = lineaMinima.find(palabraMinima, pos)) != string::npos) {
        resultado += Laslineas.substr(pos, Encontro - pos);
        resultado += "\033[32m" + Laslineas.substr(Encontro, LasPalabras.length()) + "\033[0m";
        Eltiempo++;
        pos = Encontro + LasPalabras.length();
    }
    resultado += Laslineas.substr(pos);
    return resultado;
}
