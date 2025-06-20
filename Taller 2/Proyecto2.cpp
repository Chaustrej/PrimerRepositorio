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
void MostrarMenu(){
    cout << "Menu de Productos" << endl;
    cout << "1. Agregar producto" << endl;
    cout << "2. Modificar producto" << endl;
    cout << "3. Eliminar producto" << endl;
    cout << "4. Listar productos" << endl;
    cout << "5. Buscar producto" << endl;
    cout << "6. Salir" << endl;
    cout << "Seleccione una opcion: ";
}
void agregarProducto(){
    Producto p;
    cout << "\n-Agregar Producto-\n";
    cout << "Ingrese codigo: "; cin >> p.codigo;
    cout << "Ingrese nombre: "; cin.ignore(); cin.getline(p.nombre, 30);
    cout << "Ingrese precio: "; cin >> p.precio;
    cout << "Ingrese stock: "; cin >> p.stock;
    cout << "Ingrese categoria: "; cin.ignore(); cin.getline(p.categoria, 20);
    p.activo = true;

    ofstream archivo(ARCHIVO, ios::binary | ios::app);
    archivo.write(reinterpret_cast<char*>(&p), sizeof(Producto));
    cout << "Producto agregado exitosamente.\n";
}
void mostrarProductos(){
    ifstream archivo(ARCHIVO, ios::binary);
    if (!archivo) {
        cout << "No hay productos registrados\n";
        return;
    }
    Producto p;
    cout << "\n-Lista de Productos-\n";
    while (archivo.read(char*>(&p), sizeof(Producto))) {
        if (p.activo) {
            cout << "Codigo: " << p.codigo << ", Nombre: " << p.nombre 
                 << ", Precio: " << p.precio << ", Stock: " << p.stock 
                 << ", Categoria: " << p.categoria << endl;
        }
    }
}

void BuscarProducto(){
}
void ModificarProducto(){
}
void EliminarProducto(){
}

int main () { 
int opcion;
    
}