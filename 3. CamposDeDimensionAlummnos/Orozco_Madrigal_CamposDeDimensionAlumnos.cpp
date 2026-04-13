#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <cstring>
using namespace std;
class alumno
{        
    public:
    void capturar();
    void mostrar();
    void buscar_Codigo(int);
    void modificar_Promedio(int);
    void modificar_Carrera();
    void eliminar_Codigo(int);
    char nombre[10];
    char carrera[15];
    int codigo;
    float prom;
}x;
void alumno::capturar()
{
    int a, b, c, d;
    cout<<endl<<"\n Captura el Codigo del alumno: ";
    cin>>x.codigo;
    a = sizeof(int);
    cout<<endl<<"\n Captura el Nombre del alumno: ";
    cin>>x.nombre;
    b=strlen(x.nombre);
    cout<<endl<<"\n Captura la carrera del alumno: ";
    cin>>carrera;
    c=strlen(x.carrera);
    cout<<endl<<"\n Captura el promedio del alumno: ";
    cin>>x.prom;
    d = sizeof(float);
    ofstream Alum("alumnos.txt", ios::app | ios::binary);
    Alum.write((char*) &a, sizeof(int));
    Alum.write((char*)&x.codigo,a);
    Alum.write((char*) &b, sizeof(int));
    Alum.write((char*) &x.nombre,b);
    Alum.write((char*) &c, sizeof(int));
    Alum.write((char*)&x.carrera,c);
    Alum.write((char*) &d, sizeof(int));
    Alum.write((char*) &x.prom,d);
    Alum.close();
}

void alumno::mostrar()
{
    int a, b, c, d;
    fstream Alum("alumnos.txt", ios::in | ios::out | ios::binary);
    if (!Alum.good())
        cout<<endl<<"\n ARCHIVO DAÑADO ";
    else
    {
        while(!Alum.eof())
        {
            Alum.read((char*)&a, sizeof(int));
            if (Alum.eof()) break;
            Alum.read((char*)&x.codigo, a);
            Alum.read((char*)&b, sizeof(int));
            Alum.read((char*)&x.nombre, b);
            x.nombre[b] = '\0';
            Alum.read((char*)&c, sizeof(int));
            Alum.read((char*)&x.carrera, c);
            x.carrera[c] = '\0';
            Alum.read((char*)&d, sizeof(int));
            Alum.read((char*)&x.prom, d);
            cout << "\n tamaño del nombre: " << b << endl;
            cout << "\n Codigo del alumno: " << x.codigo;
            cout << "\n Nombre del alumno: " << x.nombre;
            cout << "\n Carrera del alumno: " << x.carrera;
            cout << "\n Promedio del alumno: " << x.prom;
            cout << "\n***********************";
        }
    }
    Alum.close();
}

void alumno::buscar_Codigo(int buscado) {
    int a, b, c, d;
    bool encontrado = false;
    cout << "\nIngresa el Codigo a buscar: ";
    cin >> buscado;

    ifstream Alum("alumnos.txt", ios::binary);
    if (!Alum) { cout << "\nError al abrir archivo"; return; }

    while (Alum.read((char*)&a, sizeof(int))) {
        Alum.read((char*)&x.codigo, a);
        Alum.read((char*)&b, sizeof(int));
        Alum.read((char*)&x.nombre, b);
        x.nombre[b] = '\0';
        Alum.read((char*)&c, sizeof(int));
        Alum.read((char*)&x.carrera, c);
        x.carrera[c] = '\0';
        Alum.read((char*)&d, sizeof(int));
        Alum.read((char*)&x.prom, d);

        if (x.codigo == buscado) {
            cout << "\n--- ALUMNO ENCONTRADO ---";
            cout << "\nNombre: " << x.nombre << "\nCarrera: " << x.carrera << "\nPromedio: " << x.prom << endl;
            encontrado = true;
            break;
        }
    }
    if (!encontrado) cout << "\nEl codigo no existe.";
    Alum.close();
}

void alumno::modificar_Promedio(int buscado) {
    int a, b, c, d;
    bool encontrado = false;
    cout << "\nCodigo del alumno a modificar promedio: ";
    cin >> buscado;

    ifstream Alum("alumnos.txt", ios::binary);
    ofstream Temp("temp.txt", ios::binary);

    while (Alum.read((char*)&a, sizeof(int))) {
        Alum.read((char*)&x.codigo, a);
        Alum.read((char*)&b, sizeof(int));
        Alum.read((char*)&x.nombre, b);
        x.nombre[b] = '\0';
        Alum.read((char*)&c, sizeof(int));
        Alum.read((char*)&x.carrera, c);
        x.carrera[c] = '\0';
        Alum.read((char*)&d, sizeof(int));
        Alum.read((char*)&x.prom, d);

        if (x.codigo == buscado) {
            cout << "\nAlumno: " << x.nombre << " | Promedio actual: " << x.prom;
            cout << "\nNuevo promedio: "; cin >> x.prom;
            encontrado = true;
        }
        Temp.write((char*)&a, sizeof(int)); Temp.write((char*)&x.codigo, a);
        Temp.write((char*)&b, sizeof(int)); Temp.write((char*)&x.nombre, b);
        Temp.write((char*)&c, sizeof(int)); Temp.write((char*)&x.carrera, c);
        Temp.write((char*)&d, sizeof(int)); Temp.write((char*)&x.prom, d);
    }
    Alum.close(); Temp.close();
    remove("alumnos.txt"); rename("temp.txt", "alumnos.txt");
    if (encontrado) cout << "\nPromedio actualizado.";
    else cout << "\nNo se encontro el codigo.";
}

void alumno::modificar_Carrera() {
    int a, b, c, d, buscado;
    bool encontrado = false;
    cout << "\nCodigo del alumno a modificar carrera: ";
    cin >> buscado;

    ifstream Alum("alumnos.txt", ios::binary);
    ofstream Temp("temp.txt", ios::binary);

    while (Alum.read((char*)&a, sizeof(int))) {
        Alum.read((char*)&x.codigo, a);
        Alum.read((char*)&b, sizeof(int));
        Alum.read((char*)&x.nombre, b);
        x.nombre[b] = '\0';
        Alum.read((char*)&c, sizeof(int));
        Alum.read((char*)&x.carrera, c);
        x.carrera[c] = '\0';
        Alum.read((char*)&d, sizeof(int));
        Alum.read((char*)&x.prom, d);

        if (x.codigo == buscado) {
            cout << "\nAlumno: " << x.nombre << " | Carrera actual: " << x.carrera;
            cout << "\nNueva carrera: "; cin >> x.carrera;
            c = strlen(x.carrera);
            encontrado = true;
        }
        Temp.write((char*)&a, sizeof(int)); Temp.write((char*)&x.codigo, a);
        Temp.write((char*)&b, sizeof(int)); Temp.write((char*)&x.nombre, b);
        Temp.write((char*)&c, sizeof(int)); Temp.write((char*)&x.carrera, c);
        Temp.write((char*)&d, sizeof(int)); Temp.write((char*)&x.prom, d);
    }
    Alum.close(); Temp.close();
    remove("alumnos.txt"); rename("temp.txt", "alumnos.txt");
    if (encontrado) cout << "\nCarrera actualizada.";
}

void alumno::eliminar_Codigo(int buscado) {
    int a, b, c, d;
    bool encontrado = false;
    cout << "\nCodigo del alumno a eliminar: ";
    cin >> buscado;

    ifstream Alum("alumnos.txt", ios::binary);
    ofstream Temp("temp.txt", ios::binary);

    while (Alum.read((char*)&a, sizeof(int))) {
        Alum.read((char*)&x.codigo, a);
        Alum.read((char*)&b, sizeof(int));
        Alum.read((char*)&x.nombre, b);
        x.nombre[b] = '\0';
        Alum.read((char*)&c, sizeof(int));
        Alum.read((char*)&x.carrera, c);
        x.carrera[c] = '\0';
        Alum.read((char*)&d, sizeof(int));
        Alum.read((char*)&x.prom, d);

        if (x.codigo == buscado) {
            cout << "\nAlumno " << x.nombre << " eliminado.";
            encontrado = true;
        } else {
            Temp.write((char*)&a, sizeof(int)); Temp.write((char*)&x.codigo, a);
            Temp.write((char*)&b, sizeof(int)); Temp.write((char*)&x.nombre, b);
            Temp.write((char*)&c, sizeof(int)); Temp.write((char*)&x.carrera, c);
            Temp.write((char*)&d, sizeof(int)); Temp.write((char*)&x.prom, d);
        }
    }
    Alum.close(); Temp.close();
    remove("alumnos.txt"); rename("temp.txt", "alumnos.txt");
    if (!encontrado) cout << "\nCodigo no encontrado.";
}

int main() {
    int opc;
    do {
        cout <<"\nMENU"<<endl;
        cout <<"1. CAPTURAR\n"
            <<"2. MOSTRAR\n"
            <<"3. BUSCAR CÓDIGO\n"
            <<"4. MODIFICAR PROMEDIO\n"
            <<"5. MODIFICAR CARRERA\n"
            <<"6. ELIMINAR CODIGO\n"
            <<"7. SALIR\n"<<endl;
        cout<<"OPCIÓN: "<<endl;
        cin>>opc;
        switch (opc)
        {
        case 1:
            x.capturar();
            break;
        case 2:
            x.mostrar();
            break;
        case 3: 
            x.buscar_Codigo(0);
            break;
        case 4: 
            x.modificar_Promedio(0);
            break;
        case 5:
            x.modificar_Carrera();
            break;
        case 6:
            x.eliminar_Codigo(0);
            break;
        case 7:
            cout<<"SALIENDO DEL SISTEMA"<<endl;
            break;
        default:
            cout<<"OPCION NO ENCONTRADA, INTENTA CON ALGUNA DEL MENU...\n"<< endl;
            break;
        }
    } while (opc != 7);
    return 0;
}