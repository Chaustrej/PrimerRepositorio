#include <iostream>
#include <string>
#include <limits>
#include <locale>
using namespace std;
class Publicacion {
private:
    string titulo;
    string autor;
    int anioPublicacion;

public:
    Publicacion(string t, string a, int anio): titulo(t), autor(a), anioPublicacion(anio) {}
    virtual void mostrar() const = 0;
    string getTitulo() const { return titulo; }
    string getAutor() const { return autor; }
    int getAnioPublicacion() const { return anioPublicacion; }
    virtual ~Publicacion() {}
};
class Libro : public Publicacion {
private:
    int numeroPaginas;
public:
    Libro(string t, string a, int anio, int paginas)
        : Publicacion(t, a, anio), numeroPaginas(paginas) {}

    void mostrar() const override {
        cout << "Tipo: Libro\nTítulo: " << getTitulo()
             << "\nAutor: " << getAutor()
             << "\nAño: " << getAnioPublicacion()
             << "\nPáginas: " << numeroPaginas << endl;
    }
};
class Revista : public Publicacion {
private:
    int numeroEdicion;
public:
    Revista(string t, string a, int anio, int edicion)
        : Publicacion(t, a, anio), numeroEdicion(edicion) {}

    void mostrar() const override {
        cout << "Tipo: Revista\nTítulo: " << getTitulo()
             << "\nAutor: " << getAutor()
             << "\nAño: " << getAnioPublicacion()
             << "\nEdición: " << numeroEdicion << endl;
    }
};
class Periodico : public Publicacion {
private:
    string frecuencia;
public:
    Periodico(string t, string a, int anio, string freq)
        : Publicacion(t, a, anio), frecuencia(freq) {}
    void mostrar() const override {
        cout << "Tipo: Periódico\nTítulo: " << getTitulo()
             << "\nAutor: " << getAutor()
             << "\nAño: " << getAnioPublicacion()
             << "\nFrecuencia: " << frecuencia << endl;
    }
};

// funciones de validación
bool validarTexto(const string& texto) { return !texto.empty();}
bool validarAnio(int anio) {return anio >= 1800 && anio <= 2025;}
bool validarNumeroPositivo(int num) {return num > 0;}
void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void redimensionar(Publicacion**& arreglo, int& capacidad, int nuevoTamano) {
    Publicacion** nuevo = new Publicacion*[nuevoTamano];
    for (int i = 0; i < capacidad; i++) {
        nuevo[i] = arreglo[i];
    }
    delete[] arreglo;
    arreglo = nuevo;
    capacidad = nuevoTamano;
}
Publicacion* crearPublicacion() {
    int tipo, anio, numero;
    string titulo, autor, frecuencia;
    cout << "\nSeleccione tipo de publicación:\n";
    cout << "1. Libro\n2. Revista\n3. Periódico\nOpción: ";
    cin >> tipo;
    limpiarBuffer();
    cout << "Ingrese el título: ";
    getline(cin, titulo);
    if (!validarTexto(titulo)) return nullptr;
    cout << "Ingrese el autor: ";
    getline(cin, autor);
    if (!validarTexto(autor)) return nullptr;
    cout << "Ingrese el año de publicación (1500-2025): ";
    cin >> anio;
    if (!validarAnio(anio)) return nullptr;
    if (tipo == 1) {
        cout << "Número de páginas: ";
        cin >> numero;
        if (!validarNumeroPositivo(numero)) return nullptr;
        return new Libro(titulo, autor, anio, numero);
    } else if (tipo == 2) {
        cout << "Número de edición: ";
        cin >> numero;
        if (!validarNumeroPositivo(numero)) return nullptr;
        return new Revista(titulo, autor, anio, numero);
    } else if (tipo == 3) {
        limpiarBuffer();
        cout << "Frecuencia (Diario, Semanal, etc.): ";
        getline(cin, frecuencia);
        if (!validarTexto(frecuencia)) return nullptr;
        return new Periodico(titulo, autor, anio, frecuencia);
    } else {
        cout << "Tipo inválido.\n";
        return nullptr; }}

        void mostrarCatalogo(Publicacion** catalogo, int total) {
    if (total == 0) {
        cout << "No hay publicaciones registradas.\n";
        return;
    }
    for (int i = 0; i < total; ++i) {
        cout << "\n[" << i + 1 << "] ";
        catalogo[i]->mostrar();
    }
}
void eliminarPublicacion(Publicacion**& catalogo, int& total) {
    if (total == 0) {
        cout << "No hay publicaciones.\n";
        return;
    }

    mostrarCatalogo(catalogo, total);
    int indice;
    cout << "\nSeleccione el número a eliminar: ";
    cin >> indice;

    if (indice < 1 || indice > total) {
        cout << "Índice inválido.\n";
        return;
    }

    delete catalogo[indice - 1];
    for (int i = indice - 1; i < total - 1; ++i) {
        catalogo[i] = catalogo[i + 1];
    }
    total--;
    cout << "Publicación eliminada.\n";
}

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
    }  while(opcion != 5);  
}
}