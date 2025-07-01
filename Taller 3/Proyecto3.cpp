#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

class Publicacion {
    private:
    string titulo;
    string autor;
    int anioPublicacion;

    public:
    Publicacion(string t, string a, int anio) : titulo(t), autor(a), anioPublicacion(anio) {
        
    }
};




int main(){
 int opcion; 

 do {
    cout << "Menu de opciones:" << endl;
    cout << "1. Agregar nueva publicacion" << endl;
    cout << "2. Mostrar todas las publicaciones" << endl;
    cout << "3. Buscar publicacion por titulo" << endl;
    cout << "4. Eliminar publicacion" << endl;
    cout << "5. Mostrar estadisticas" << endl;
    cout << "6. Salir del programa" << endl;
    cout << "Seleccione una opcion: ";
    cin >> opcion;

    switch(opcion) {
        case 1:
          
            break;
        case 2:
          
            break;
        case 3:
           
            break;
        case 4:
          
            break;
        case 5:
            cout << "Saliendo del programa." << endl;
            break;
        default:
            cout << "Opción no válida, intente de nuevo." << endl;
    }  
}}