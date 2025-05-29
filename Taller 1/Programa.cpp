#include <iostream>
#include <conio.h>
#include <string> 
#include <fstream>
#include <algorithm>

void ();
using namespace std;
// prototipo de funciones
string Minuscula();
string Marcarr(const string& LasPalabras, const string& Laslineas, int& Eltiempo);
// Definire las funciones que usare en el programa
 // Variables globales
int contador = 0; // Contador de palabras encontradas
int main() { 
string LasPalabras, Laslineas, continuar;

    string palabra, linea, continuar;
    
    cout << "Aqui se encuentra el buscador de palabras\n";
    cin.ignore();
    
    do {
        ifstream archivo("Archivo.txt");
        if (!archivo) {
            cout << "Error: archivo 'Archivo.txt' no encontrado verifique bien si se encuentra cerca\n";
            return 1;
        }
        
        do {
            cout << "\nPorfavor coloque las palabras que se va a buscar: ";
            getline(cin, palabra);
        } while (palabra.empty());
        
        cout << "\nEl resultado seria:\n";
        
        int total = 0, Laslineas_num = 1;
        bool encontrado = false;
        
        while (getline(archivo, Laslineas)) {
            int Eltiempo = 0;
            string LineaMarcadaColor = Marcarr(Laslineas, LasPalabras, Eltiempo);
            
            if (Eltiempo> 0) {
                cout << Laslineas_num << ": " << LineaMarcadaColor << endl;
                total += Eltiempo;
                encontrado = true;
            }
           Laslineas_num++;
        }
        
        archivo.close();
        


}

}
//// Convierte una cadena a minúsculas
string Minuscula(string palabra) {
    // Convierte una cadena a minúsculas
    transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);
    return palabra;
}
// Marca las palabras encontradas en la línea y devuelve la línea modificada
string Marcarr(const string& LasPalabras, const string& Laslineas, int& Eltiempo) {
        string resultado = "";
    string lineaMinima = Minuscula(Laslineas);
    string palabraMinima = Minuscula(LasPalabras);
    size_t pos = 0, Encontro;
    
    while ((Encontro = lineaMinima.find(palabraMinima, pos)) != string::npos) {
        resultado += Laslineas.substr(pos, Encontro - pos);
        resultado += "\033[31m" + Laslineas.substr(Encontro, LasPalabras.length()) + "\033[0m";
        contador++;
        pos = Encontro + LasPalabras.length();
    }
    resultado += Laslineas.substr(pos);
    return resultado;

}   