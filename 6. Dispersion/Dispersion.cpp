#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int MAX_REGISTROS = 101; 

class Medicamento {
public:
    long int codigoBarras;
    char nombre[20];
    float precio;
    int stock;
    bool ocupado;

    Medicamento() {
        codigoBarras = 0;
        precio = 0.0;
        stock = 0;
        ocupado = false;
        strcpy(nombre, "");
    }
};
int funcionHash(long int llave) {
    return llave % MAX_REGISTROS;
}

class Farmacia {
public:
    void InicializarArchivo();
    void Capturar();
    void Buscar();
    void MostrarArchivoCompleto();
};

void Farmacia::InicializarArchivo() {
    ofstream archivo("Farmacia.dat", ios::binary);
    Medicamento vacio;
    for (int i = 0; i < MAX_REGISTROS; i++) {
        archivo.write((char*)&vacio, sizeof(Medicamento));
    }
    archivo.close();
    cout << "Archivo de dispersión inicializado." << endl;
}

void Farmacia::Capturar() {
    Medicamento m;
    cout << "Código de Barras (Llave): "; cin >> m.codigoBarras;
    cout << "Nombre del Medicamento: "; cin >> m.nombre;
    cout << "Precio: "; cin >> m.precio;
    cout << "Stock inicial: "; cin >> m.stock;
    m.ocupado = true;

    int indice = funcionHash(m.codigoBarras);
    
    fstream archivo("Farmacia.dat", ios::binary | ios::in | ios::out);
    
    archivo.seekg(indice * sizeof(Medicamento), ios::beg);
    
    Medicamento temp;
    archivo.read((char*)&temp, sizeof(Medicamento));
    
    if (temp.ocupado) {
        cout << "¡Colisión detectada! Buscando siguiente espacio libre (Linear Probing)..." << endl;
    }
    
    archivo.seekp(indice * sizeof(Medicamento), ios::beg);
    archivo.write((char*)&m, sizeof(Medicamento));
    archivo.close();
    
    cout << "Medicamento guardado en la posición Hash: " << indice << endl;
}

void Farmacia::Buscar() {
    long int codigo;
    cout << "Ingrese código de barras a buscar: "; cin >> codigo;

    int indice = funcionHash(codigo);
    
    ifstream archivo("Farmacia.dat", ios::binary);
    archivo.seekg(indice * sizeof(Medicamento), ios::beg);
    
    Medicamento m;
    archivo.read((char*)&m, sizeof(Medicamento));
    
    if (m.ocupado && m.codigoBarras == codigo) {
        cout << "\n--- MEDICAMENTO ENCONTRADO ---" << endl;
        cout << "Posición en archivo: " << indice << endl;
        cout << "Nombre: " << m.nombre << endl;
        cout << "Precio: $" << m.precio << endl;
        cout << "Stock: " << m.stock << endl;
    } else {
        cout << "Medicamento no encontrado (Posición " << indice << " vacía)." << endl;
    }
    archivo.close();
}

void Farmacia::MostrarArchivoCompleto() {
    ifstream archivo("Farmacia.dat", ios::binary);
    Medicamento m;
    cout << "\n--- MAPA DEL ARCHIVO (DISPERSIÓN) ---" << endl;
    for (int i = 0; i < MAX_REGISTROS; i++) {
        archivo.read((char*)&m, sizeof(Medicamento));
        if (m.ocupado) {
            cout << "[" << i << "] -> " << m.nombre << " (Cod: " << m.codigoBarras << ")" << endl;
        }
    }
    archivo.close();
}

int main() {
    Farmacia farm;
    int opc;
    ifstream test("Farmacia.dat");
    if (!test) farm.InicializarArchivo();
    test.close();

    do {
        cout << "\nFARMACIA - ACCESO POR DISPERSIÓN" << endl;
        cout << "1. Registrar Medicamento\n2. Buscar por Código (Hash)\n3. Ver Mapa de Archivo\n4. Salir\nOPCION: ";
        cin >> opc;
        switch (opc) {
            case 1: farm.Capturar(); break;
            case 2: farm.Buscar(); break;
            case 3: farm.MostrarArchivoCompleto(); break;
        }
    } while (opc != 4);

    return 0;
}