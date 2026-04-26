#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string.h>
#include <cstring>
using namespace std;
int position = 0;
class Alumno
{        
    public:
    void Capturar();
    void Mostrar();
    void Buscar_Codigo(int);
    void Modificar_Promedio(int);
    void Modificar_Carrera();
    void Eliminar_Codigo(int);
    private:
    char nombre[10];
    char AP[10];
    char AM[10];
    char carrera[15];
    int codigo;
    float promedio;
}x;
void Alumno::Capturar()
{
    cout<<"\nNombre: "<< endl;
    cin >> x.nombre;
    cout<<"\nApellido Paterno: "<< endl;
    cin >> x.AP;
    cout<<"\nApellido Materno: "<< endl;
    cin >> x.AM;
    cout<<"\nCarrera: "<< endl;
    cin >> x.carrera;
    cout<<"\nCodigo: "<< endl;
    cin >> x.codigo;
    cout<<"\nPromedio: "<< endl;
    cin >> x.promedio;
    ofstream Alum("Alumnos.txt",ios::app);
    Alum.write((char*) &x, sizeof(x));
    Alum.close();
}
void Alumno::Mostrar()
{
    fstream Alum("Alumnos.txt",ios::in|ios::out);
    if (!Alum.good())
    {
        cout<<"\nArchivo Dañado"<<endl;
    }
    else{
        while (!Alum.eof())
        {
            Alum.read((char*) &x, sizeof(x));
            if (Alum.eof())
            {
                break;
            }
            cout<<"Nombre: "<<x.nombre<<" "<<x.AP<<" "<<x.AM <<endl;
            cout<<"Codigo: "<<x.codigo<<endl;
            cout<<"Carrera: "<<x.carrera<<endl;
            cout<<"Promedio: "<<x.promedio<<endl;
            cout<<"------------------------------"<<endl;
        }
    }
    Alum.close();
    
}
void Alumno::Buscar_Codigo(int){
    int num;
    bool encontrado;
        do
        {
            encontrado = false;
            cout<<"\nIngresa el Código del Alumno a Buscar: "<< endl;
            cin >> num;
            ifstream Alum("Alumnos.txt", ios::binary | ios::in);
            while (Alum.read((char*)&x, sizeof(x))) {
                if (x.codigo == num) {
                    cout << "\n--- REGISTRO ENCONTRADO ---" << endl;
                    cout << "Nombre: " << x.nombre << " " << x.AP << " " << x.AM << endl;
                    cout << "Carrera: " << x.carrera << endl;
                    cout << "Promedio: " << x.promedio << endl;
                    cout << "---------------------------" << endl;
                    encontrado = true;
                    break;
                }
            }
            Alum.close();

            if (!encontrado) {
                cout << "Error: El código " << num << " no existe en la base de datos." << endl;
                cout << "Prueba con otro código existente." << endl;
            }
        } while (!encontrado);
    
}
void Alumno::Modificar_Promedio(int) {
    int cod_buscado;
    bool encontrado;
    long pos;
    do {
        encontrado = false;
        cout << "\nIngresa el Código del alumno para modificar su promedio: ";
        cin >> cod_buscado;
        fstream Alum("Alumnos.txt", ios::binary | ios::in | ios::out);
        if (!Alum) {
            cout << "Error: No se pudo abrir el archivo." << endl;
            return;
        }
        while (Alum.read((char*)&x, sizeof(x))) {
            if (x.codigo == cod_buscado) {
                encontrado = true;
                cout << "\nRegistro encontrado:" << endl;
                cout << "Alumno: " << x.nombre << " | Promedio actual: " << x.promedio << endl;
                cout << "Ingresa el NUEVO promedio del alumno: ";
                cin >> x.promedio;
                pos = (long)Alum.tellg() - sizeof(x);
                Alum.seekp(pos, ios::beg);
                Alum.write((char*)&x, sizeof(x));
                cout << "\nPromedio actualizado!" << endl;
                break; 
            }
        }

        Alum.close();
        if (!encontrado) 
        {
            cout << "Error: El código [" << cod_buscado << "] no existe." << endl;
        }
    } while (!encontrado);
}
void Alumno::Modificar_Carrera(){
    int cod_buscado;
    bool encontrado;
    long pos;
    do {
        encontrado = false;
        cout << "\nIngresa el Código del alumno para modificar su promedio: ";
        cin >> cod_buscado;
        fstream Alum("Alumnos.txt", ios::binary | ios::in | ios::out);
        if (!Alum) {
            cout << "Error: No se pudo abrir el archivo." << endl;
            return;
        }
        while (Alum.read((char*)&x, sizeof(x))) {
            if (x.codigo == cod_buscado) {
                encontrado = true;
                cout << "\nRegistro encontrado:" << endl;
                cout << "Alumno: " << x.nombre << " | Promedio actual: " << x.promedio << endl;
                cout << "Ingresa la NUEVA carrera del alumno: ";
                cin >> x.carrera;
                pos = (long)Alum.tellg() - sizeof(x);
                Alum.seekp(pos, ios::beg);
                Alum.write((char*)&x, sizeof(x));
                cout << "\nCarrera actualizada!" << endl;
                break; 
            }
        }

        Alum.close();
        if (!encontrado) 
        {
            cout << "Error: El código [" << cod_buscado << "] no existe." << endl;
        }
    } while (!encontrado);
}
void Alumno::Eliminar_Codigo(int){
    int cod_buscado;
    int decision;
    bool encontrado;
    do {
        encontrado = false;
        cout << "\nIngresa el Código del alumno para eliminarlo: ";
        cin >> cod_buscado;
        ifstream Alum("Alumnos.txt", ios::binary | ios::in);
        ofstream Temp("Auxiliar.txt", ios::binary | ios::out);
        if (!Alum) {
            cout << "Error: No se pudo abrir el archivo." << endl;
            return;
        }
        while (Alum.read((char*)&x, sizeof(x))) {
            if (x.codigo == cod_buscado) {
                encontrado = true;
                cout << "\nRegistro encontrado:" << endl;
                cout << "Alumno: " << x.nombre << " " << x.AP << endl;
                cout << "Seguro de la Eliminacion?\n1. SI\n2. NO\nOPCION: ";
                cin >> decision;
                if (decision == 1) {
                    cout << "\nRegistro eliminado correctamente." << endl;
                } else {
                    Temp.write((char*)&x, sizeof(x));
                    cout << "\nOperación cancelada." << endl;
                }
            } else {
                Temp.write((char*)&x, sizeof(x));
            }
        }
        Alum.close();
        Temp.close();
        remove("Alumnos.txt");
        rename("Auxiliar.txt", "Alumnos.txt");
        if (!encontrado) {
            cout << "Error: El código [" << cod_buscado << "] no existe." << endl;
        }
    } while (!encontrado);
}
int main() {
    int opc;
    do {
        cout <<"HELLOOOOOOOO"<<endl;
        cout <<"MENU"<<endl;
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
            x.Capturar();
            break;
        case 2:
            x.Mostrar();
            break;
        case 3: 
            x.Buscar_Codigo(0);
            break;
        case 4: 
            x.Modificar_Promedio(0);
            break;
        case 5:
            x.Modificar_Carrera();
            break;
        case 6:
            x.Eliminar_Codigo(0);
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