#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const char* ARCHIVO = "personas.dat";

class Persona {
private:
    char nombre[30], apellido[30], cedula[15];
    int edad;
    float coeficiente_int;
    bool activo;

public:
    Persona() {
        strcpy(nombre, "");
        strcpy(apellido, "");
        edad = 0;
        strcpy(cedula, "");
        coeficiente_int = 0;
        activo = true;
    }

    void ingresarDatos() {
        cout << "Nombre: "; cin.ignore(); cin.getline(nombre, 30);
        cout << "Apellido: "; cin.getline(apellido, 30);
        cout << "Edad: "; cin >> edad;
        cout << "Cedula: "; cin.ignore(); cin.getline(cedula, 15);
        cout << "Coeficiente intelectual: "; cin >> coeficiente_int;
        activo = true;
    }

    void mostrar() const {
        cout << "Nombre: " << nombre
             << ", Apellido: " << apellido
             << ", Edad: " << edad
             << ", Cedula: " << cedula
             << ", Coeficiente: " << coeficiente_int << endl;
    }

    bool esActiva() const {
        return activo;
    }

    const char* getCedula() const {
        return cedula;
    }

    int getEdad() const {
        return edad;
    }

    void modificar() {
        cout << "Nuevo nombre: "; cin.ignore(); cin.getline(nombre, 30);
        cout << "Nuevo apellido: "; cin.getline(apellido, 30);
        cout << "Nueva edad: "; cin >> edad;
        cout << "Nuevo coeficiente: "; cin >> coeficiente_int;
    }

    void desactivar() {
        activo = false;
    }
};

class CrudPersonas {
public:
    void agregarPersona() {
        Persona p;
        p.ingresarDatos();
        ofstream archivo(ARCHIVO, ios::binary | ios::app);
        archivo.write((char*)&p, sizeof(Persona));
        archivo.close();
        cout << "Persona agregada.\n";
    }

    void listarPersonas() {
        ifstream archivo(ARCHIVO, ios::binary);
        Persona p;
        cout << "\n- Lista de personas -\n";
        while (archivo.read((char*)&p, sizeof(Persona))) {
            if (p.esActiva()) {
                p.mostrar();
            }
        }
        archivo.close();
    }

    void buscarPorCedula() {
        char cedula[15];
        cout << "Ingrese cedula: "; cin.ignore(); cin.getline(cedula, 15);
        ifstream archivo(ARCHIVO, ios::binary);
        Persona p;
        bool encontrado = false;

        while (archivo.read((char*)&p, sizeof(Persona))) {
            if (p.esActiva() && strcmp(p.getCedula(), cedula) == 0) {
                p.mostrar();
                encontrado = true;
                break;
            }
        }
        archivo.close();
        if (!encontrado)
            cout << "Persona no encontrada.\n";
    }

    void modificarPersona() {
        char cedula[15];
        cout << "Ingrese cedula de la persona a modificar: ";
        cin.ignore();
        cin.getline(cedula, 15);

        fstream archivo(ARCHIVO, ios::binary | ios::in | ios::out);
        Persona p;
        bool encontrado = false;

        while (archivo.read((char*)&p, sizeof(Persona))) {
            if (p.esActiva() && strcmp(p.getCedula(), cedula) == 0) {
                cout << "Modificando persona:\n";
                p.mostrar();
                p.modificar();
                archivo.seekp(-sizeof(Persona), ios::cur);
                archivo.write((char*)&p, sizeof(Persona));
                cout << "Persona modificada.\n";
                encontrado = true;
                break;
            }
        }
        archivo.close();
        if (!encontrado)
            cout << "Persona no encontrada.\n";
    }

    void eliminarPersona() {
        char cedula[15];
        cout << "Ingrese cedula de la persona a eliminar: ";
        cin.ignore();
        cin.getline(cedula, 15);

        fstream archivo(ARCHIVO, ios::binary | ios::in | ios::out);
        Persona p;
        bool eliminado = false;

        while (archivo.read((char*)&p, sizeof(Persona))) {
            if (p.esActiva() && strcmp(p.getCedula(), cedula) == 0) {
                p.desactivar();
                archivo.seekp(-sizeof(Persona), ios::cur);
                archivo.write((char*)&p, sizeof(Persona));
                cout << "Persona eliminada.\n";
                eliminado = true;
                break;
            }
        }
        archivo.close();
        if (!eliminado)
            cout << "Persona no encontrada.\n";
    }

    void mostrarMayorEdad() {
        ifstream archivo(ARCHIVO, ios::binary);
        Persona p;
        int mayorEdad = -1;

        while (archivo.read((char*)&p, sizeof(Persona))) {
            if (p.esActiva() && p.getEdad() > mayorEdad) {
                mayorEdad = p.getEdad();
            }
        }

        archivo.clear();
        archivo.seekg(0);
        bool encontrado = false;
        cout << "\n-Personas con mayor edad (" << mayorEdad << " anos):\n";
        while (archivo.read((char*)&p, sizeof(Persona))) {
            if (p.esActiva() && p.getEdad() == mayorEdad) {
                p.mostrar();
                encontrado = true;
            }
        }

        archivo.close();
        if (!encontrado)
            cout << "No hay personas registradas.\n";
    }
};

void mostrarMenu() {
    cout << "\n--- MENU DE PERSONAS ---\n";
    cout << "1. Agregar persona\n";
    cout << "2. Modificar persona\n";
    cout << "3. Eliminar persona\n";
    cout << "4. Listar personas\n";
    cout << "5. Buscar por cedula\n";
    cout << "6. Mostrar persona(s) de mayor edad\n";
    cout << "7. Salir\n";
    cout << "Seleccione una opcion: ";
}

int main() {
    CrudPersonas crud;
    int opcion;

    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1: crud.agregarPersona(); break;
            case 2: crud.modificarPersona(); break;
            case 3: crud.eliminarPersona(); break;
            case 4: crud.listarPersonas(); break;
            case 5: crud.buscarPorCedula(); break;
            case 6: crud.mostrarMayorEdad(); break;
            case 7: cout << "Saliendo...\n"; break;
            default: cout << "Opcion invalida.\n";
        }

    } while (opcion != 7);

    return 0;
}
