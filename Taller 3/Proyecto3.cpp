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
    string fechaPublicacion;  
    string ciudad;            
public:
    Periodico(string t, string a, int anio, string fecha, string c)
        : Publicacion(t, a, anio), fechaPublicacion(fecha), ciudad(c) {}
    void mostrar() const override {
        cout << "Tipo: Periódico\nTítulo: " << getTitulo()
             << "\nAutor: " << getAutor()
             << "\nAño: " << getAnioPublicacion()
             << "\nFecha de Publicación: " << fechaPublicacion
             << "\nCiudad: " << ciudad << endl;
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
    string titulo, autor, fecha, ciudad;

    do {
        cout << "\n=== TIPOS DE PUBLICACIÓN ===\n";
        cout << "1. Libro\n2. Revista\n3. Periódico\n4. Volver al menú principal\nSeleccione el tipo: ";
        cin >> tipo;
        limpiarBuffer();

        if (tipo == 4) return nullptr;

        cout << "Título: "; getline(cin, titulo);
        cout << "Autor: "; getline(cin, autor);
        cout << "Año (1500-2025): "; cin >> anio;
        limpiarBuffer();

        if (!validarTexto(titulo) || !validarTexto(autor) || !validarAnio(anio)) {
            cout << "Datos inválidos.\n";
            continue;
        }

        if (tipo == 1) {
            cout << "Número de páginas: "; cin >> numero;
            if (!validarNumeroPositivo(numero)) return nullptr;
            return new Libro(titulo, autor, anio, numero);
        } else if (tipo == 2) {
            cout << "Número de edición: "; cin >> numero;
            if (!validarNumeroPositivo(numero)) return nullptr;
            return new Revista(titulo, autor, anio, numero);
        } else if (tipo == 3) {
            cout << "Fecha de publicación (ej: 04-07-2025): "; getline(cin, fecha);
            cout << "Ciudad de publicación: "; getline(cin, ciudad);
            if (!validarTexto(fecha) || !validarTexto(ciudad)) return nullptr;
            return new Periodico(titulo, autor, anio, fecha, ciudad);
        } else {
            cout << "Opción inválida.\n";
        }
    } while (true);
}
void mostrarCatalogo(Publicacion** catalogo, int total) {
    if (total == 0) {
        cout << "No hay publicaciones.\n";
        return;
    }
    for (int i = 0; i < total; ++i) {
        cout << "\n[" << i + 1 << "] ";
        catalogo[i]->mostrar();
    }
}
void buscarTitulo(Publicacion** catalogo, int total) {
    string buscar;
    cout << "\nIngrese el título a buscar: ";
    limpiarBuffer();
    getline(cin, buscar);
    bool encontrado = false;

    for (int i = 0; i < total; ++i) {
        if (catalogo[i]->getTitulo().find(buscar) != string::npos) {
            catalogo[i]->mostrar();
            encontrado = true;
        }
    }
    if (!encontrado) cout << "No se encontraron coincidencias.\n";
}


void eliminarPublicacion(Publicacion**& catalogo, int& total) {
    if (total == 0) { cout << "No hay publicaciones.\n"; return; }
    mostrarCatalogo(catalogo, total);
    int i;
    cout << "\nSeleccione el número a eliminar: "; cin >> i;
    if (i < 1 || i > total) { cout << "Índice inválido.\n"; return; }
    delete catalogo[i - 1];
    for (int j = i - 1; j < total - 1; ++j) catalogo[j] = catalogo[j + 1];
    total--;
    cout << "Eliminado.\n";
}
void mostrarEstadisticas(Publicacion** catalogo, int total) {
    int libros = 0, revistas = 0, periodicos = 0;
    if (total == 0) { cout << "No hay publicaciones.\n"; return; }
    int minAnio = catalogo[0]->getAnioPublicacion();
    int maxAnio = catalogo[0]->getAnioPublicacion();

    for (int i = 0; i < total; ++i) {
        if (dynamic_cast<Libro*>(catalogo[i])) libros++;
        else if (dynamic_cast<Revista*>(catalogo[i])) revistas++;
        else if (dynamic_cast<Periodico*>(catalogo[i])) periodicos++;

        int anio = catalogo[i]->getAnioPublicacion();
        if (anio < minAnio) minAnio = anio;
        if (anio > maxAnio) maxAnio = anio;
    }

    cout << "\nEstadísticas:\n";
    cout << "Total: " << total << "\nLibros: " << libros << "\nRevistas: " << revistas << "\nPeriódicos: " << periodicos << endl;
    cout << "Más antigua: " << minAnio << "\nMás reciente: " << maxAnio << endl;
}

void liberarMemoria(Publicacion** catalogo, int total) {
    for (int i = 0; i < total; ++i) delete catalogo[i];
    delete[] catalogo;
}

int main() {
    int capacidad = 5, total = 0;
    Publicacion** catalogo = new Publicacion*[capacidad];
    int opcion;

    do {
        cout << "\n===== SISTEMA DE GESTIÓN DE BIBLIOTECA =====\n";
        cout << "1. Agregar nueva publicación\n2. Mostrar todas las publicaciones\n";
        cout << "3. Buscar publicación por título\n4. Eliminar publicación\n";
        cout << "5. Mostrar estadísticas\n6. Salir del programa\nOpción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                if (total == capacidad)
                    redimensionar(catalogo, capacidad, capacidad + 5);
                Publicacion* pub = crearPublicacion();
                if (pub != nullptr)
                    catalogo[total++] = pub;
                break;
            }
            case 2:
                mostrarCatalogo(catalogo, total);
                break;
            case 3:
                buscarTitulo(catalogo, total);
                break;
            case 4:
                eliminarPublicacion(catalogo, total);
                break;
            case 5:
                mostrarEstadisticas(catalogo, total);
                break;
            case 6:
                liberarMemoria(catalogo, total);
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 6);

    return 0;
}
