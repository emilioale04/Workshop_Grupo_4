#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream> 
#include "../lib/global.h"
#include <windows.h>
#include <cctype>

using namespace std;

struct provincia
{
    unsigned int iIncremental;
    char sNombre[50];
    int iPoblacion;
    float fTemperatura;
    char lstPlatoTipico[100];
};

vector <provincia> lstProvincia;
const string pathfilebinary = "./resorce/database/delivery.dat";

void leerArchivoBinario();
void escribirArchivoBinario();
void presentarProvincias();      
void buscarProv();
void buscarProvAv();  
void presentarProvincia(provincia p);
void agregarProvincia();
void eliminarProvincia();
void numerarProvinciaId();        
int menu();
void presentarAcercaDe();
bool validariDato(string str);
int validarfDato(string cadena);
string tolowerStr(string str);
void segmentarCadena( const string  str, const char delim,  vector <string> &lst ); 


int main()
{   
    setColor(BLACK, WHITE);
    leerArchivoBinario();

    system("cls");
    do{
        switch (menu())
        {
            case AGREGAR:
                system("cls");
                agregarProvincia();
                break;
            case PRESENTAR:
                system("cls");
                presentarProvincias();
                cout<<endl;
                system("pause");
                break;
            case BUSCAR:
                system("cls");
                buscarProv();
                cout<<endl;
                system("pause");
                break;
            case BUSQUEDA_AVANZADA:
                system("cls");
                buscarProvAv();
                cout<<endl;
                system("pause");
                break;
            case GUARDAR:
                system("cls");
                escribirArchivoBinario();
                break;
            case ELIMINAR:
                system("cls");
                eliminarProvincia();
                cout<<endl;
                system("pause");
                break;    
            case SALIR:
                system("cls");
                cout << "bye bye...";
                cout<<endl;
                exit(0);
            case ACERCA_DE:
                system("cls");
                presentarAcercaDe();
                cout<<endl;
                system("pause");
                break;
            default:
                system("cls");
                cout << "Seleccion no valida \n";
                cout<<endl;
                system("pause");
                break;
        }
    }while (true);
} 

void leerArchivoBinario()
{
    ifstream rf(pathfilebinary, ios::in | ios::binary);
    cout << "Abrir archivo:" << pathfilebinary << endl;
    if(!rf) 
    {
        cout << " <+> Error al abrir el archivo binario <+> " << endl << endl;
        system("pause");
    } 
    provincia tp[1];
    while(rf.read((char *) &tp[0], sizeof(provincia)))
        lstProvincia.push_back(tp[0]);
    rf.close();
}

void escribirArchivoBinario()
{
    ofstream f(pathfilebinary, ios::out | ios_base::binary );
    cout << endl << "Escribir archivo: " << pathfilebinary << endl;
    if(f.good())
    {
        for (auto &&prov : lstProvincia)
            f.write((char *) &prov, sizeof(provincia));
    }
    f.close();
}

bool validariDato(string str)
{
    for (char const &c : str) {
        if (isdigit(c) == 0) return false;
    }
    return true;
}

int validarfDato(string cadena) {
    int longitud = cadena.length();
    // Quitar espacios, saltos de línea, etcétera
    while (longitud > 0 && isspace(cadena[longitud - 1]))
        longitud--;
    if (longitud <= 0) return 0;
    int i;
    int haEncontradoElPunto = 0;
    for (i = 0; i < longitud; ++i) {
        // En caso de que sea un guión, y que no esté al inicio, no es válido
        if (cadena[i] == '-' && i > 0) {
            return 0;
        }
        // El punto solo puede aparecer una vez
        if (cadena[i] == '.') {
            // Si ya lo ha encontrado antes, entonces no es válido
            if (haEncontradoElPunto) {
                return 0;
            } else {

                haEncontradoElPunto = 1;
            }
        }
        // Si no es dígito, tampoco es válido
        if (!isdigit(cadena[i]) && cadena[i] != '-' && cadena[i] != '.') {
            return 0;
        }
    }
    return 1;
}


void agregarProvincia()
{
    string valor;
    string str;
    do
    {   
        setColor(BLACK, LGREEN);
        fflush(stdin);
        struct provincia prov;
        cout <<endl << "-- Ingresar datos de provincia  -- " << endl ;

        setColor(BLACK, WHITE);
        cout <<"<+> Nombre: ";
        cin.getline(prov.sNombre, 50, '\n');

        for (auto &&provincia : lstProvincia)
        {   
            if (tolowerStr(prov.sNombre) == tolowerStr(provincia.sNombre))
            {
                cout <<"La provincia " <<prov.sNombre << " ya existe..."<< endl;
                goto again; 

            }
        }
        prov.iIncremental = lstProvincia.size()+1; 

        cout <<"<+> Poblacion: ";
        getline(cin, valor);
        validariDato(valor);
        while(validariDato(valor)==false){
            setColor(BLACK, RED);
            cout <<"NO ha ingresado un numero entero, intente nuevamente..."<<endl;
            setColor(BLACK, WHITE);
            cout <<"<+> Poblacion: ";
            getline(cin, valor);
        }
        prov.iPoblacion= stoi(valor);

        fflush(stdin);
        
        cout <<"<+> Temperatura: ";
        getline(cin, valor);
        validarfDato(valor);
        while(validarfDato(valor)==0){
            setColor(BLACK, RED);
            cout <<"NO ha ingresado un numero, intente nuevamente..."<<endl;
            setColor(BLACK, WHITE);
            cout <<"<+> Temperatura: ";
            getline(cin, valor);
        }
        prov.fTemperatura = stof(valor);

        fflush(stdin);

        cout <<"<+> PlatoTipico (separados por coma): ";
        cin.getline(prov.lstPlatoTipico, 100, '\n');

        fflush(stdin);
        
        lstProvincia.push_back(prov);

        again:
        setColor(BLACK, LRED);
        cout << "Deseas salir (s): " ;
        cin >> str;
        str = tolowerStr(str);

    } while (!(str == "s"));
}

void buscarProv()
{   
    setColor(BLACK, LGREEN);
    cout << "------ Buscar Provincia -------" << endl;
    setColor(BLACK, WHITE);
    bool encontrado = false;

    string prov;

    cout <<"Ingresa el Nombre de la provincia: ";
    
    getline(cin, prov);

    for (auto &&provincia : lstProvincia)
    {
        if (tolowerStr(provincia.sNombre) == tolowerStr(prov))
        {
            presentarProvincia(provincia);
            encontrado = true;
        }
    }
    if (!encontrado)
    {
        setColor(BLACK, LRED);
        cout <<"No se encontro la provincia..." << endl; 
    }

}

void presentarProvincia(provincia p)
{   
    cout<<"Id: "        << p.iIncremental<<endl;
    cout<<"Nombre: "        << p.sNombre<<endl;
    cout<<"Poblacion: "     << p.iPoblacion<<endl;
    cout<<"Temperatura: "   << p.fTemperatura<<endl;
    cout<<"Platos Tipicos: "   << p.lstPlatoTipico<<endl;

    vector <string> lstPlatoTipico; 
    segmentarCadena (p.lstPlatoTipico, ',', lstPlatoTipico); 
    for (const auto &pt: lstPlatoTipico)  
        cout <<"\t" << pt << endl ;  
}

void presentarProvincias(){
    setColor(BLACK, LGREEN);
    cout<<endl<<"-------    Provincias   ----------"<<endl;
    setColor(BLACK, WHITE);
    for(auto &&prov : lstProvincia)
        presentarProvincia(prov);
}

int menu()
{
    int eleccion;
    system("cls");
    do
    {
        setColor(BLACK, YELLOW);
        cout << endl
        << "()---Provincias del Ecuador---()\n"         << endl
        << "Ingresa una opcion: \n"                  << endl;
        cout<< endl
        << AGREGAR                  << " | Agregar provincias               |"  << endl;
        setColor(BLACK, LBLUE);
        cout
        << PRESENTAR                << " | Presentar provincias             |"  << endl
        << BUSCAR                   << " | Busqueda de provincias           |"  << endl
        << BUSQUEDA_AVANZADA        << " | Busqueda avanzada de provincias  |"  << endl;
        setColor(BLACK, RED);
        cout
        << GUARDAR                  << " | Guardar provincias               |"  << endl
        << ELIMINAR                 << " | Eliminar provincias              |"  << endl
        << ACERCA_DE                << " | Acerca de                        |"  << endl
        << SALIR                    << " | Salir del sistema                |"  << endl;
        setColor(BLACK, WHITE);
        cout<< "\nSu seleccion: ";
        cin >> eleccion;
        cin.clear();
        fflush(stdin);
    }while (eleccion < 0 || eleccion > 7); 
    return eleccion;
}

string tolowerStr(string str)  
{
    for (int x=0; x < str.length(); x++)
        str[x] = tolower(str[x]);
    return str;
}

void segmentarCadena( const string  str, const char delim,  vector<string> &outlst )  
{  
    string strDiv;  
    stringstream s(str);  
    while ( getline (s, strDiv, delim) )  
        outlst.push_back(strDiv);  
}

void buscarProvAv()
{
    cout << "------ Busqueda Avanzada de Provincias -------" << endl;
    
    bool encontrado = false;

    char prov[50];

    int cont = 0;
    setColor(BLACK, LGREEN);
    cout <<"Ingresa el nombre para la busqueda avanzada: ";
    
    setColor(BLACK, WHITE);
    cin.getline(prov, 50, '\n');

    for (auto &&provincia : lstProvincia)
    {   

        string prov1 = tolowerStr(prov);

        string prov2 = tolowerStr(provincia.sNombre);

        for (int j = 0; j < prov2.length(); j++)
            if(prov1[j] == prov2[j])
                cont++;

        if (cont >= 3){
            presentarProvincia(provincia);
            break;
        }
    }
    if (cont <= 2)
    {
        setColor(BLACK, LRED);
        cout <<"No se encontro similares a " << prov << endl;
    }
}

void eliminarProvincia()
{   
    setColor(BLACK, RED);
    cout << "------ Eliminar Provincia -------" << endl;

    setColor(BLACK, WHITE);
    
    bool encontrado = false;

    char prov[50];

    int pos = 0;

    cout <<"Ingresa el nombre de la provincia a eliminar: ";
    
    cin.getline(prov, 50, '\n');

    for (auto &&provincia : lstProvincia)
    {   
        if (tolowerStr(prov) == tolowerStr(provincia.sNombre))
        {
            cout <<"Se elimino: " <<provincia.sNombre<< endl; 
            lstProvincia.erase(lstProvincia.begin()+pos);
            encontrado = true;

        }
        pos++;
    }
    if (!encontrado)
    {
        setColor(BLACK, RED);
        cout <<"No se encontro la provincia a eliminar..." << endl;
    }
    numerarProvinciaId();

}

void numerarProvinciaId(){
    for(int i = 0; i < lstProvincia.size(); i++){
        lstProvincia[i].iIncremental = i+1;
    }
}

void presentarAcercaDe(){
    setColor(BLACK, LBLUE);
    cout << "------ Acerca de -------" << endl << endl;

    setColor(BLACK, LBLUE);
    cout << "------ Authors -------" << endl;
    cout << endl;
    setColor(BLACK, CYAN);
    cout <<"> alejandro.alvarez@epn.edu.ec ";
    setColor(BLACK, WHITE);
    cout << "Alejandro Alvarez" << endl;
    setColor(BLACK, CYAN);
    cout <<"> emilio.armas@epn.edu.ec ";
    setColor(BLACK, WHITE);
    cout << "Emilio Armas" << endl;
    setColor(BLACK, CYAN);
    cout <<"> jose.defaz@epn.edu.ec ";
    setColor(BLACK, WHITE);
    cout << "Jose Defaz" << endl;
    setColor(BLACK, CYAN);
    cout <<"> mercedes.martinez@epn.edu.ec ";
    setColor(BLACK, WHITE);
    cout << "Mercedes Martinez" << endl;
    setColor(BLACK, CYAN);
    cout <<"> alexander.pinto@epn.edu.ec ";
    setColor(BLACK, WHITE);
    cout << "Fernando Pinto" << endl;
    setColor(BLACK, CYAN);
    cout <<"> luis.villa@epn.edu.ec ";
    setColor(BLACK, WHITE);
    cout << "Luis Villa" << endl << endl;

    setColor(BLACK, LBLUE);
    cout << "By 2022";

    setColor(BLACK, WHITE);
}

/* 

En los archivos binarios los datos no se almacenan los numeros como cadenas de caracteres, si no que se almacenan de la misma manera en la que se almacena en memoria, por lo que este contenido no puede ser visualizado mediante un editor de textos.
ifstream (ios::in | ios::binary): clase de operacion de lectura de archivos, en este caso de archivos binarios.
ofstream (ios::out | ios::binary): clase de operacion de escritura de archivos, en este caso de archivos binarios.
'Nombre_de_Fichero'.seekg(): permite buscar cierta posicion en un archivo si el fichero es de lectura, seek indica que se realiza una busqueda en el archivo y g proviene de 'get' el cual indica lectura
'Nombre_de_Fichero'.seekp(): busca una porsicion si el fichero de escritura, la letra p proviene de 'put' el cual indica escritura.
En .seekg(), .seekp() se debe indicar la cantidad de espacios que se desea saltar(en bytes), y desde que posicion usando las siguientes funciones:
ios::beg: indica el principio del fichero.
ios::cur: indica la posicion actual del fichero.
ios::end: indica el final del fichero.
Para conocer la posicion en la que nos encontramos dentro de un fichero se usa:
.tellg(): en caso de que el fichero sea de lectura.
.tellp(): en caso de que el fichero sea de escritura.
Si se usan las funciones anteriores al final del fichero, se puede saber la longitud(bytes) de cierto fichero.
'Nombre_de_Fichero'.read(bloque, tamaño): Lee un bloque de informacion del fichero. 
'Nombre_de_Fichero'.write(bloque, tamaño): Escribe un bloque de informacion en el fichero. 


>> agregar color 0,1

*/