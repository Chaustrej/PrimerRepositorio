#include <iostream>
#include <string>
using namespace std;

const int maximo_Personas = 200;

class Persona {
   public:
    string nombre, apellido, cedula;
    int edad;
    float coeficiente_int;
    Persona() {}; 
    Persona(string nom, string ape, string ced, int ed, float coef) 
     : nombre(nom), apellido(ape), cedula(ced), edad(ed), coeficiente_int(coef) {}
    void mostrar() const {
        cout << "Nombre: " << nombre << " " << apellido
             << "\nCedula: " << cedula
             << "\nEdad: " << edad
             << "\nCoeficiente Intelectual: " << coeficiente_int << endl;
    }
};

class Crud : public Persona {
    private:
        Persona personas[maximo_Personas];
        int cantidad=0;
    public:
    void agregarPersonas() {
      if (cantidad >= maximo_Personas) {
            cout << "Lista llena. No se pueden agregar más personas.\n";
            return;
        }
        string nom, ape, ced;
        int ed;
        float coeficiente_int;

        cout << "Nombre: "; cin >> nom;
        cout << "Apellido: "; cin >> ape;
        cout << "Edad: "; cin >> ed;
        cout << "Cedula: "; cin >> ced;
        cout << "Coeficiente: "; cin >> coeficiente_int;

        personas[cantidad] = Persona(nom, ape, ced, ed, coeficiente_int);
        cantidad++;
        cout << "Persona agregada.\n";
    }
    void listarPersonas() {
        if (cantidad == 0) {
            cout << "No hay personas.\n";
            return;
        }

        for (int i = 0; i < cantidad; i++) {
            personas[i].mostrar();
        }
    }
    void buscarPorEdad() {
        int edadBuscada;
        cout << "Edad a buscar: ";
        cin >> edadBuscada;
        bool encontrada = false;

        for (int i = 0; i < cantidad; i++) {
            if (personas[i].edad == edadBuscada) {
                personas[i].mostrar();
                encontrada = true;
            }
        }

        if (!encontrada) {
            cout << "No se encontro a las personas con esas edades.\n";
        }
    }
    void eliminarPersona() {
        string cedulaBuscada;
        cout << "Ponga el numero de cedula de la persona que desee eliminar: ";
        cin >> cedulaBuscada;

        for (int i = 0; i < cantidad; i++) {
            if (personas[i].cedula == cedulaBuscada) {
                // Mover los elementos hacia atrás
                for (int j = i; j < cantidad - 1; j++) {
                    personas[j] = personas[j + 1];
                }
                cantidad--;
                cout << "Persona eliminada.\n";
                return;
            }
        }
        cout << "Persona no encontrada.\n"; }
    void editarPersona() {
        string cedulaBuscada;
        cout << "Cedula a editar: ";
        cin >> cedulaBuscada;

        for (int i = 0; i < cantidad; i++) {
            if (personas[i].cedula == cedulaBuscada) {
                cout << "Nuevo nombre: "; cin >> personas[i].nombre;
                cout << "Nuevo apellido: "; cin >> personas[i].apellido;
                cout << "Nueva edad: "; cin >> personas[i].edad;
                cout << "Nuevo coeficiente: "; cin >> personas[i].coeficiente_int;
                cout << "Datos actualizados.\n";
                return;
            }
        }
    cout << "Persona no encontrada.\n";
    }
     void mostrarPersonasdeMayorEdad() {
        if (cantidad == 0) {
            cout << "No hay personas.\n";
            return;
        }

        int mayorEdad = personas[0].edad;
        for (int i = 1; i < cantidad; i++) {
            if (personas[i].edad > mayorEdad) {
                mayorEdad = personas[i].edad;
            }
        }

        cout << "Persona(s) con mayor edad (" << mayorEdad << " anos):\n";
        for (int i = 0; i < cantidad; i++) {
            if (personas[i].edad == mayorEdad) {
                personas[i].mostrar();
            }
        }
    }
}; 

int main(){
    Crud crud;
    int opcion;

    do {
        cout << "\n=== MENU DE PERSONAS ===\n";
        cout << "1. Agregar persona\n2. Listar personas\n3. Buscar por edad\n";
        cout << "4. Eliminar persona\n5. Editar persona\n6. Mostrar personas de mayor edad\n7. Salir\nOpcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                crud.agregarPersonas();
                break;
            case 2:
                crud.listarPersonas();
                break;
            case 3:
                crud.buscarPorEdad();
                break;
            case 4:
                crud.eliminarPersona();
                break;
            case 5:
                crud.editarPersona();
                break;
            case 6:
                crud.mostrarPersonasdeMayorEdad();
                break;
            case 7:
                cout << "Saliendo del programa.\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }
    } while (opcion != 7);

    return 0;
}