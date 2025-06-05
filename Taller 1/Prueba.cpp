#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Persona {
    char nombre[50];
    char apellido[50];
    char cedula[20];
    int edad;
    float coeficiente_int;
};

const string ARCHIVO = "ListadePersonas.dat";

// Prototipos de las funciones 
void agregarPersona(); 
void buscarPorCedula();
void listarPersonas();
void buscarPorEdad();
void eliminarPersona();
void editarPersona();
void mostrarMayores();
void mostrarMenu();
Persona* leerArchivo(int* cantidad); 
void escribirArchivo(Persona* personas, int cantidad);
void liberarMemoria(Persona* personas);

int main() {
    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore(); 
        switch(opcion) {
            case 1:
                agregarPersona();
                break;
            case 2:
                buscarPorCedula();
                break;
            case 3:
                listarPersonas();
                break;
            case 4:
                buscarPorEdad();
                break;
            case 5:
                eliminarPersona();
                break;
            case 6:
                editarPersona();
                break;
            case 7:
                mostrarMayores();
                break;
            case 8:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "La opcion no es valida. Intente de nuevo." << endl;
        }
    } while(opcion != 8);

    return 0;
}

void mostrarMenu() {
    cout << "\nMENU DE OPCIONES" << endl;
    cout << "1) Agregar persona" << endl;
    cout << "2) Buscar persona por cedula" << endl;
    cout << "3) Listar todas las personas" << endl;
    cout << "4) Buscar personas por edad" << endl;
    cout << "5) Eliminar persona" << endl;
    cout << "6) Editar persona" << endl;
    cout << "7) Mostrar persona(s) de mayor edad" << endl;
    cout << "8) Salir" << endl;
    cout << "Seleccione una opcion: ";
}

Persona* leerArchivo(int* cantidad) {
    ifstream archivo(ARCHIVO, ios::binary | ios::ate);
    *cantidad = 0;
    Persona* personas = nullptr;

    if(archivo.is_open()) {
        streampos size = archivo.tellg();
        *cantidad = size / sizeof(Persona);
        personas = new Persona[*cantidad];
        
        archivo.seekg(0, ios::beg);
        archivo.read((char*)personas, size);
        archivo.close();
    }

    return personas;
}

void escribirArchivo(Persona* personas, int cantidad) {
    ofstream archivo(ARCHIVO, ios::binary);

    if(archivo.is_open()) {
        archivo.write((const char*)personas, cantidad * sizeof(Persona));
        archivo.close();
    }
}

void liberarMemoria(Persona* personas) {
    delete[] personas;
}

void agregarPersona() {
    Persona nueva;
    cout << "\nAgregar Una Nueva Persona" << endl;
    cout << "Nombre: ";
    cin.getline(nueva.nombre, 50);
    cout << "Apellido: ";
    cin.getline(nueva.apellido, 50);
    cout << "Cedula: ";
    cin.getline(nueva.cedula, 20);
    cout << "Edad: ";
    cin >> nueva.edad;
    cout << "Coeficiente intelectual: ";
    cin >> nueva.coeficiente_int;
    cin.ignore();

    int cantidad;
    Persona* personas = leerArchivo(&cantidad);
    
    Persona* nuevasPersonas = new Persona[cantidad + 1];
    
    for(int i = 0; i < cantidad; i++) {
        nuevasPersonas[i] = personas[i];
    }
    
    nuevasPersonas[cantidad] = nueva;
    escribirArchivo(nuevasPersonas, cantidad + 1);

    liberarMemoria(personas);
    liberarMemoria(nuevasPersonas);

    cout << "Persona agregada!" << endl;
}

void buscarPorCedula() {
    char cedula[20];
    cout << "\nBuscar por cedula" << endl;
    cout << "Ingrese la cedula a buscar: ";
    cin.getline(cedula, 20);

    int cantidad;
    Persona* personas = leerArchivo(&cantidad);
    bool encontrado = false;

    for(int i = 0; i < cantidad; i++) {
        if(strcmp(personas[i].cedula, cedula) == 0) {
            cout << "\nPersona encontrada:" << endl;
            cout << "Nombre: " << personas[i].nombre << endl;
            cout << "Apellido: " << personas[i].apellido << endl;
            cout << "Cedula: " << personas[i].cedula << endl;
            cout << "Edad: " << personas[i].edad << endl;
            cout << "Coeficiente intelectual: " << personas[i].coeficiente_int << endl;
            encontrado = true;
            break;
        }
    }

    if(!encontrado) {
        cout << "No se encontro ninguna persona con esa cedula." << endl;
    }

    liberarMemoria(personas);
}

void listarPersonas() {
    int cantidad;
    Persona* personas = leerArchivo(&cantidad);

    if(cantidad == 0) {
        cout << "\nNo hay personas registradas." << endl;
        liberarMemoria(personas);
        return;
    }

    cout << "\nLista de Personas (" << cantidad << ")" << endl;
    cout << "--------------------------------------------------" << endl;
    for(int i = 0; i < cantidad; i++) {
        cout << "Nombre: " << personas[i].nombre << endl;
        cout << "Apellido: " << personas[i].apellido << endl;
        cout << "Cedula: " << personas[i].cedula << endl;
        cout << "Edad: " << personas[i].edad << endl;
        cout << "Coeficiente intelectual: " << personas[i].coeficiente_int << endl;
        cout << "--------------------------------------------------" << endl;
    }

    liberarMemoria(personas);
}

void buscarPorEdad() {
    int edad;
    cout << "\nBuscar por la Edad" << endl;
    cout << "Ingrese la edad a buscar: ";
    cin >> edad;
    cin.ignore();

    int cantidad;
    Persona* personas = leerArchivo(&cantidad);
    int encontrados = 0;

    cout << "\nPersonas con Edad " << edad << endl;
    cout << "--------------------------------------------------" << endl;
    for(int i = 0; i < cantidad; i++) {
        if(personas[i].edad == edad) {
            cout << "Nombre: " << personas[i].nombre << endl;
            cout << "Apellido: " << personas[i].apellido << endl;
            cout << "Cedula: " << personas[i].cedula << endl;
            cout << "Edad: " << personas[i].edad << endl;
            cout << "Coeficiente intelectual: " << personas[i].coeficiente_int << endl;
            cout << "-------------------" << endl;
            encontrados++;
        }
    }

    if(encontrados == 0) {
        cout << "No se encontraron personas con esa edad." << endl;
    } else {
        cout << "Total encontrados: " << encontrados << endl;
    }

    liberarMemoria(personas);
}

void eliminarPersona() {
    char cedula[20];
    cout << "\nEliminar Persona" << endl;
    cout << "Ingrese la cedula de la persona a eliminar: ";
    cin.getline(cedula, 20);

    int cantidad;
    Persona* personas = leerArchivo(&cantidad);
    bool encontrado = false;
    int indiceEliminar = -1;

    for(int i = 0; i < cantidad; i++) {
        if(strcmp(personas[i].cedula, cedula) == 0) {
            cout << "\nEliminando a:" << endl;
            cout << "Nombre: " << personas[i].nombre << " " << personas[i].apellido << endl;
            cout << "Cedula: " << personas[i].cedula << endl;
            indiceEliminar = i;
            encontrado = true;
            break;
        }
    }

    if(encontrado) {
        Persona* nuevasPersonas = new Persona[cantidad - 1];
        
        for(int i = 0, j = 0; i < cantidad; i++) {
            if(i != indiceEliminar) {
                nuevasPersonas[j++] = personas[i];
            }
        }
        
        escribirArchivo(nuevasPersonas, cantidad - 1);
        liberarMemoria(nuevasPersonas);
        cout << "Persona eliminada exitosamente!" << endl;
    } else {
        cout << "No se encontro ninguna persona con esa cedula." << endl;
    }

    liberarMemoria(personas);
}

void editarPersona() {
    char cedula[20];
    cout << "\nEditar Persona" << endl;
    cout << "Ingrese la cedula de la persona a editar: ";
    cin.getline(cedula, 20);

    int cantidad;
    Persona* personas = leerArchivo(&cantidad);
    bool encontrado = false;

    for(int i = 0; i < cantidad; i++) {
        if(strcmp(personas[i].cedula, cedula) == 0) {
            cout << "\nEditando a:" << endl;
            cout << "Nombre actual: " << personas[i].nombre << endl;
            cout << "Nuevo nombre (dejar vacio para mantener): ";
            char nombre[50];
            cin.getline(nombre, 50);
            if(strlen(nombre) > 0) {
                strcpy(personas[i].nombre, nombre);
            }

            cout << "Apellido actual: " << personas[i].apellido << endl;
            cout << "Nuevo apellido (dejar vacio para mantener): ";
            char apellido[50];
            cin.getline(apellido, 50);
            if(strlen(apellido) > 0) {
                strcpy(personas[i].apellido, apellido);
            }

            cout << "Edad actual: " << personas[i].edad << endl;
            cout << "Nueva edad (ingrese -1 para mantener): ";
            int edad;
            cin >> edad;
            cin.ignore();
            if(edad != -1) {
                personas[i].edad = edad;
            }

            cout << "Coeficiente intelectual actual: " << personas[i].coeficiente_int << endl;
            cout << "Nuevo coeficiente intelectual (ingrese -1 para mantener): ";
            float ci;
            cin >> ci;
            cin.ignore();
            if(ci != -1) {
                personas[i].coeficiente_int = ci;
            }

            encontrado = true;
            break;
        }
    }

    if(encontrado) {
        escribirArchivo(personas, cantidad);
        cout << "Persona editada exitosamente!" << endl;
    } else {
        cout << "No se encontro ninguna persona con esa cedula." << endl;
    }

    liberarMemoria(personas);
}

void mostrarMayores() {
    int cantidad;
    Persona* personas = leerArchivo(&cantidad);

    if(cantidad == 0) {
        cout << "\nNo hay personas registradas." << endl;
        liberarMemoria(personas);
        return;
    }

    int maxEdad = personas[0].edad;
    for(int i = 1; i < cantidad; i++) {
        if(personas[i].edad > maxEdad) {
            maxEdad = personas[i].edad;
        }
    }

    cout << "\nPersona(S) de Mayor Edad (" << maxEdad << " años)" << endl;
    cout << "--------------------------------------------------" << endl;
    for(int i = 0; i < cantidad; i++) {
        if(personas[i].edad == maxEdad) {
            cout << "Nombre: " << personas[i].nombre << endl;
            cout << "Apellido: " << personas[i].apellido << endl;
            cout << "Cedula: " << personas[i].cedula << endl;
            cout << "Edad: " << personas[i].edad << endl;
            cout << "Coeficiente intelectual: " << personas[i].coeficiente_int << endl;
            cout << "--------------------------------------------------" << endl;
        }
    }

    liberarMemoria(personas);
}