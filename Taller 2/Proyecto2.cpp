#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const char* FILE_NAME = "productos.dat";

struct Producto {
    int codigo;
    char nombre[30];
    float precio;
    int stock;
    char categoria[20];
    bool activo;
};

int main () { 

    
}