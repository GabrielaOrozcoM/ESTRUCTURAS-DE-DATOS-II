#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <cstdlib>
using namespace std;
class Cliente
{
    public:
    string codigo;
    string nombre;
    string telefono;
    string saldo;
    void capturar();
    void mostrar();
    void buscar (string codigo);
    void modificar (string);
    void eliminar (string codigo);
};

void Cliente::capturar()
{
    cout << "Codigo: ";
    fflush(stdin);
    getline (cin, codigo);
    cout << "Nombre: ";
    fflush(stdin);
    getline (cin, nombre);
    cout << "Telefono: ";
    fflush(stdin);
    getline (cin, telefono);
    cout << "Saldo: ";
    fflush(stdin);
    getline (cin, saldo);
    ofstream archivo ("clientes.txt", ios:: app);
    archivo << codigo <<'|'<< nombre << '|'<< telefono <<'|'<< saldo << endl;
    archivo.close();
}
void Cliente:: mostrar()
{
    fstream archivo ("clientes.txt", ios::in|ios::out);
    if(!archivo.good())
    {
        cout << "(!) Error al abrir el archivo." << endl;
        return;
    }
    else
    {
        string tmp;
        int i=0;
        system("cls");
        cout << endl << "Lista de clientes" << endl;
        while(!archivo.eof())
        { 
            i++;
            cout<<"\n Cliente num. "<<i<<endl;
            getline(archivo, tmp, '|');
            if (archivo.eof()) { break; }
            cout << "Codigo: \t" << tmp << endl;
            getline (archivo, tmp, '|');
            cout << "Nombre: \t" << tmp << endl;
            getline (archivo, tmp, '|');
            cout << "Telefono: \t" << tmp << endl;
            getline (archivo, tmp, '\n');
            cout << "Saldo: \t" << tmp << endl;
        }
        cout << endl;
    }
}
void Cliente::buscar(string cod_buscado) {
    ifstream archivo("clientes.txt");
    string c, n, t, s;
    bool encontrado = false;
    if (!archivo.is_open()) return;
    while (getline(archivo, c, '|')) {
        getline(archivo, n, '|');
        getline(archivo, t, '|');
        getline(archivo, s, '\n');
        if (c == cod_buscado) {
            cout << "\n--- CLIENTE ENCONTRADO ---" << endl;
            cout << "Codigo: " << c << "\nNombre: " << n << "\nTel: " << t << "\nSaldo: " << s << endl;
            encontrado = true;
            break;
        }
    }
    if (!encontrado) cout << "\n(!) Cliente no registrado." << endl;
    archivo.close();
}
void Cliente::modificar(string cod_buscado) {
    ifstream archivo("clientes.txt");
    ofstream temporal("temp.txt");
    string c, n, t, s, nuevo_saldo;
    bool encontrado = false;
    while (getline(archivo, c, '|')) {
        getline(archivo, n, '|');
        getline(archivo, t, '|');
        getline(archivo, s, '\n');
        if (c == cod_buscado) {
            encontrado = true;
            cout << "Cliente: " << n << " | Saldo actual: " << s << endl;
            cout << "Ingresa el nuevo saldo: ";
            cin >> nuevo_saldo;
            temporal << c << '|' << n << '|' << t << '|' << nuevo_saldo << endl;
        } else {
            temporal << c << '|' << n << '|' << t << '|' << s << endl;
        }
    }
    archivo.close();
    temporal.close();
    remove("clientes.txt");
    rename("temp.txt", "clientes.txt");
    if (encontrado) cout << "Saldo actualizado." << endl;
    else cout << "No se encontro el codigo." << endl;
}
void Cliente::eliminar(string cod_buscado) {
    ifstream archivo("clientes.txt");
    ofstream temporal("temp.txt");
    string c, n, t, s;
    bool encontrado = false;

    while (getline(archivo, c, '|')) {
        getline(archivo, n, '|');
        getline(archivo, t, '|');
        getline(archivo, s, '\n');

        if (c == cod_buscado) {
            encontrado = true;
            cout << "Cliente " << n << " eliminado." << endl;
        } else {
            temporal << c << '|' << n << '|' << t << '|' << s << endl;
        }
    }
    archivo.close();
    temporal.close();
    remove("clientes.txt");
    rename("temp.txt", "clientes.txt");
}

int main() 
{
    int opc;
    Cliente cli;
    string buscar_cod;
    do 
    {
        cout << "\nMENU - CLIENTES" << endl;
        cout << "1. CAPTURAR\n"
            <<"2. MOSTRAR\n"
            <<"3. BUSCAR CODIGO\n"
            <<"4. MODIFICAR SALDO\n"
            <<"5. ELIMINAR CODIGO\n"
            <<"6. SALIR" << endl;
        cout << "OPCION: ";
        cin >> opc;
        switch (opc) 
        {
            case 1:
                cli.capturar();
                break;
            case 2:
                cli.mostrar();
                break;
            case 3:
                cout << "Codigo a buscar: "; cin >> buscar_cod;
                cli.buscar(buscar_cod);
                break;
            case 4:
                cout << "Codigo para modificar saldo: "; cin >> buscar_cod;
                cli.modificar(buscar_cod);
                break;
            case 5:
                cout << "Codigo a eliminar: "; cin >> buscar_cod;
                cli.eliminar(buscar_cod);
                break;
            case 6:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout<<"Opcion no encontrada...";
                break;
        }
    } while (opc != 6);
    return 0;
}