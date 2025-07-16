#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
// Estructura
struct personas {
	char nombre[20], apellido[30], cedula[10];
	int edad;
	float coeficiente_int;
};
void Crear();
const char *nombre_Archivo = "ListadePersonas.dat";
int main() {
	Crear();
	return 0;

}
void Crear(){
	FILE *archivo = fopen(nombre_Archivo, "a+b");
	char respuesta;
	personas persona;
	do {
	fflush(stdin);
	cout << "Desea ingresar una nueva persona? (s/n): ";
	cin >> respuesta;
	cout << "Ingrese el nombre(s/n): "; cin.getline(persona.nombre, 20);
	cout << "Ingrese el apellido(s/n): "; cin.getline(persona.apellido, 30);
	cout << "Ingrese la cedula(s/n): "; cin.getline(persona.cedula, 10);
	cout << "Ingrese la edad(s/n): "; cin >> persona.edad;
	cout << "Ingrese el coeficiente intelectual(s/n): "; cin >> persona.coeficiente_int;
	cin.ignore(); // Limpiar el buffer de entrada


	fwrite(&persona, sizeof(personas), 1, archivo);
	} while (respuesta == 's' || respuesta == 'S');

	fclose(archivo);
}