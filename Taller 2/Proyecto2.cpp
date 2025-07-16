#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const char* ARCHIVO = "Productos.dat";
struct Producto {
    int codigo;
    char nombre[30];
    float precio;
    int stock;
    char categoria[20];
    bool activo;
};
void MostrarMenu(){
    cout << "\n --Menu de Productos--\n" << endl;
    cout << "1. Agregar producto" << endl;
    cout << "2. Modificar producto" << endl;
    cout << "3. Eliminar producto" << endl;
    cout << "4. Listar productos" << endl;
    cout << "5. Buscar producto" << endl;
    cout << "6. Buscar por categoria" << endl;
    cout << "7. Salir" << endl;
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
    while (archivo.read((char*)&p, sizeof(Producto))) {
        if (p.activo) {
            cout << "Codigo: " << p.codigo << ", Nombre: " << p.nombre << ", Precio: " << p.precio << ", Stock: " << p.stock << ", Categoria: " << p.categoria << endl;
        }
    }
}

void BuscarProducto(){
int codigo; 
cout <<"-Buscando Productos-\n";
cout << "\nIngrese el codigo del producto que desea buscar: "; cin >> codigo;
ifstream archivo(ARCHIVO, ios::binary);
Producto p;
bool encontrado = false;
while (archivo.read ((char*)&p, sizeof(Producto))) {
    if (p.activo && p.codigo ==codigo){
        cout << "Nombre: "<<p.nombre << endl;
        cout << "Precio: $"<<p.precio <<endl;
        cout << "Stock: "<<p.stock <<endl; 
        encontrado=true;
        break;
   }}
if(!encontrado){
    cout << "\nProducto no encontrado.\n";
}
}
void ModificarProducto(){
int codigo;
cout << "Codigo: "; cin >> codigo;

fstream archivo(ARCHIVO, ios::binary | ios::in | ios::out);
Producto p;
bool encontrado = false;

while(archivo.read((char*)&p, sizeof(Producto))){
    if (p.activo && p.codigo == codigo) {
        cout << "Nuevo nombre ("<< p.nombre << " ):";
        cin.ignore();
        cin.getline(p.nombre, 30);

        cout << "Nuevo precio (" << p.precio << "):";
        cin >> p.precio;
         
        archivo.seekp(-sizeof(Producto), ios::cur);
        archivo.write((char*)&p, sizeof(Producto));

        cout << "Producto Modificado\n";
        encontrado = true;
        break;
    }
}
if (!encontrado) {
    cout << "Producto no encontrado.\n";
}

}
void EliminarProducto(){
    int codigo;
    cout << "\n -Eliminando Producto- \n";
    cout << "Codigo: "; cin >> codigo;
    
    fstream archivo(ARCHIVO, ios::binary | ios::in | ios::out);
    Producto p;
    bool encontrado = false;

    while(archivo.read((char*)&p, sizeof(Producto))){
        if(p.activo && p.codigo == codigo) {
            p.activo = false;
            
            archivo.seekp(-sizeof(Producto), ios::cur);
            archivo.write((char*)&p, sizeof(Producto));

            cout << "\nProducto Eliminado\n";
            encontrado = true;
            break;
        }
    }
    if (!encontrado) {
        cout <<"Producto no encontrado";
    }
}
void mostrarPorCategoria() {
    char categoria[20];
    cout << "Ingrese categoria: ";
    cin.ignore();
    cin.getline(categoria, 20);

    ifstream archivo(ARCHIVO, ios::binary);
    Producto p;
    bool encontrados = false;

    while (archivo.read((char*)&p, sizeof(Producto))) {
        if (p.activo && strcmp(p.categoria, categoria) == 0) {
            cout << "Codigo: " << p.codigo << " Nombre: " << p.nombre << endl;
            encontrados = true;
        }
    }

    if (!encontrados) cout << "No hay productos en esta categoria.\n";
}

int main () {
    int opcion;
    do { 
        MostrarMenu();
        cin >> opcion;
        switch (opcion) {
            case 1:
                agregarProducto();
                break;
            case 2:
                ModificarProducto();
                break;
            case 3:
                EliminarProducto();
                break;
            case 4:
                mostrarProductos();
                break;
            case 5:
                BuscarProducto();
                break;
            case 6: mostrarPorCategoria();
            break;
            case 7:
                cout << "Saliendo del programa.\n";
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcion != 7);
    
}