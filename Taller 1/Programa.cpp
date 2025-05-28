#include <iostream>
#include <conio.h>
#include <windows.h> // funcion que sirve para las funciones de la consola
#include <string> 
#include <fstream>

using namespace std;

// Definire las funciones que usare en el programa
void CambiarColor(int color) { 
    // Cambia el color del texto en la consola, usare esto para resaltar las letras de busquedad 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
int main() { 



}