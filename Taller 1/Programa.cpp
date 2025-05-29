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


}

string Minuscula(string palabra) {
    // Convierte una cadena a minúsculas
    transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);
    return palabra;
}

string Marcarr(const string& LasPalabras, const string& Laslineas, int& Eltiempo) {
        string resultado = "";
    string lineaMin = Minuscula(Laslineas);
    string palabraMin = Minuscula(LasPalabras);
    size_t pos = 0, Encontro;
    
    while ((Encontro = lineaMin.find(palabraMin, pos)) != string::npos) {
        resultado += Laslineas.substr(pos, Encontro - pos);
        resultado += "\033[31m" + Laslineas.substr(Encontro, LasPalabras.length()) + "\033[0m";
        contador++;
        pos = Encontro + LasPalabras.length();
    }
    resultado += Laslineas.substr(pos);
    return resultado;

}