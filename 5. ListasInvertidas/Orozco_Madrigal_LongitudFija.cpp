#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
using namespace std;
class Alumno {
public:
    void Capturar();
    void Mostrar();
    void Buscar_Codigo();
    void Buscar_por_Carrera();
    void Modificar_Promedio();
    void Modificar_Carrera();
    void Eliminar_Codigo();
private:
    char nombre[10];
    char AP[10];
    char AM[10];
    char carrera[15];
    int codigo;
    float promedio;
    long sig; 
} x;
struct IndiceCarrera {
    char nombreCarrera[15];
    long primeraPos;
};

void Alumno::Capturar() {
    cout << "\nNombre: "; cin >> x.nombre;
    cout << "Apellido Paterno: "; cin >> x.AP;
    cout << "Apellido Materno: "; cin >> x.AM;
    cout << "Carrera: "; cin >> x.carrera;
    cout << "Codigo: "; cin >> x.codigo;
    cout << "Promedio: "; cin >> x.promedio;
    x.sig = -1;
    fstream Ind("Carreras.txt", ios::binary | ios::in | ios::out);
    if (!Ind) Ind.open("Carreras.txt", ios::binary | ios::out); 
    IndiceCarrera ic;
    bool existeCarrera = false;
    long posIndice = 0;
    while (Ind.read((char*)&ic, sizeof(ic))) {
        if (strcmp(ic.nombreCarrera, x.carrera) == 0) {
            existeCarrera = true;
            break;
        }
        posIndice += sizeof(ic);
    }

    ofstream Alum("Alumnos.txt", ios::binary | ios::app);
    long nuevaPos = Alum.tellp();

    if (existeCarrera) {
         x.sig = ic.primeraPos;
        ic.primeraPos = nuevaPos;
        Ind.seekp(posIndice, ios::beg);
        Ind.write((char*)&ic, sizeof(ic));
    } else {
        strcpy(ic.nombreCarrera, x.carrera);
        ic.primeraPos = nuevaPos;
        Ind.clear();
        Ind.seekp(0, ios::end);
        Ind.write((char*)&ic, sizeof(ic));
    }
    
    Alum.write((char*)&x, sizeof(x));
    Alum.close();
    Ind.close();
}

void Alumno::Buscar_por_Carrera() {
    char carreraBuscada[15];
    cout << "Ingrese la carrera a consultar: ";
    cin >> carreraBuscada;

    ifstream Ind("Carreras.txt", ios::binary);
    IndiceCarrera ic;
    long posLista = -1;

    while (Ind.read((char*)&ic, sizeof(ic))) {
        if (strcmp(ic.nombreCarrera, carreraBuscada) == 0) {
            posLista = ic.primeraPos;
            break;
        }
    }
    Ind.close();

    if (posLista == -1) {
        cout << "No hay alumnos en esa carrera." << endl;
        return;
    }

    ifstream Alum("Alumnos.txt", ios::binary);
    cout << "\nAlumnos en " << carreraBuscada << ":" << endl;
    while (posLista != -1) {
        Alum.seekg(posLista, ios::beg);
        Alum.read((char*)&x, sizeof(x));
        
        cout << "- " << x.nombre << " " << x.AP << " (Cod: " << x.codigo << ")" << endl;
        posLista = x.sig;
    }
    Alum.close();
}
void Alumno::Mostrar() {
    ifstream Alum("Alumnos.txt", ios::binary);
    if (!Alum) { cout << "Archivo vacío." << endl; return; }
    while (Alum.read((char*)&x, sizeof(x))) {
        cout << "Nombre: " << x.nombre << " " << x.AP << " | Carrera: " << x.carrera << " | Sig: " << x.sig << endl;
    }
    Alum.close();
}

int main() {
    int opc;
    do {
        cout << "\n--- MENU LISTAS INVERTIDAS ---" << endl;
        cout << "1. CAPTURAR\n2. MOSTRAR TODO\n3. BUSCAR POR CARRERA (LISTA INVERTIDA)\n4. SALIR\nOPCION: ";
        cin >> opc;
        switch (opc) {
            case 1: x.Capturar(); break;
            case 2: x.Mostrar(); break;
            case 3: x.Buscar_por_Carrera(); break;
            case 4: break;
        }
    } while (opc != 4);
    return 0;
}