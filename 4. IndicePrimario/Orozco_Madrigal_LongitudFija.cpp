#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
using namespace std;
class Alumno {
public:
    void Capturar();
    void Mostrar();
    void Buscar();
private:
    char nombre[10];
    char AP[10];
    char AM[10];
    char carrera[15];
    int codigo;
    float promedio;
} x;

struct Indice {
    int llave;
    long int posicion;
};

void Alumno::Capturar() {
    cout << "\n--- CAPTURAR ALUMNO ---" << endl;
    cout << "Nombre: "; cin >> x.nombre;
    cout << "Apellido Paterno: "; cin >> x.AP;
    cout << "Apellido Materno: "; cin >> x.AM;
    cout << "Carrera: "; cin >> x.carrera;
    cout << "Codigo: "; cin >> x.codigo;
    cout << "Promedio: "; cin >> x.promedio;
    ofstream Alum("Alumnos.txt", ios::app | ios::binary);
    Alum.seekp(0, ios::end);
    long int pos = Alum.tellp(); 
    Alum.write((char*)&x, sizeof(x));
    Alum.close();
    ofstream Ind("Indice.txt", ios::app);
    Ind << x.codigo << " " << pos << endl;
    Ind.close();
    cout << "Registro guardado e indexado con éxito.\n";
}

void Alumno::Mostrar() {
    ifstream Alum("Alumnos.txt", ios::binary);
    if (!Alum.good()) {
        cout << "\nArchivo no encontrado." << endl;
        return;
    }
    cout << "\n--- LISTA DE ALUMNOS ---" << endl;
    while (Alum.read((char*)&x, sizeof(x))) {
        cout << "Nombre: " << x.nombre << " " << x.AP << " " << x.AM << endl;
        cout << "Codigo: " << x.codigo << " | Carrera: " << x.carrera << " | Prom: " << x.promedio << endl;
        cout << "-----------------------------------" << endl;
    }
    Alum.close();
}
void Alumno::Buscar() {
    int codigoBusqueda;
    int codigoIndice;
    long int posIndice;
    bool encontrado = false;
    cout << "\nIngresa el Código del Alumno a Buscar: ";
    cin >> codigoBusqueda;
    ifstream Ind("Indice.txt");
    if (!Ind) {
        cout << "El índice no existe." << endl;
        return;
    }

    while (Ind >> codigoIndice >> posIndice) {
        if (codigoIndice == codigoBusqueda) {
            ifstream Alum("Alumnos.txt", ios::binary);
            Alum.seekg(posIndice, ios::beg);
            Alum.read((char*)&x, sizeof(x));
            cout << "\n--- REGISTRO ENCONTRADO (Vía Índice) ---" << endl;
            cout << "Nombre: " << x.nombre << " " << x.AP << " " << x.AM << endl;
            cout << "Carrera: " << x.carrera << " | Promedio: " << x.promedio << endl;
            cout << "Ubicación física en archivo: " << posIndice << " bytes." << endl;
            cout << "----------------------------------------" << endl;
            encontrado = true;
            Alum.close();
            break;
        }
    }
    Ind.close();

    if (!encontrado) {
        cout << "Error: El código " << codigoBusqueda << " no existe." << endl;
    }
}
int main() {
    int opc;
    do {
        cout << "\n*** SISTEMA DE ALUMNOS ***" << endl;
        cout << "1. CAPTURAR" << endl;
        cout << "2. MOSTRAR" << endl;
        cout << "3. BUSCAR" << endl;
        cout << "4. SALIR" << endl;
        cout << "OPCIÓN: ";
        cin >> opc;

        switch (opc) {
            case 1: x.Capturar(); break;
            case 2: x.Mostrar(); break;
            case 3: x.Buscar(); break;
            case 4: cout << "Saliendo..." << endl; break;
            default: cout << "Opción inválida." << endl;
        }
    } while (opc != 4);

    return 0;
}