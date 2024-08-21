/* 
    EQUIPO 5

    INTEGRANTES:

    - Diego Leonardo Alejo Cantu
    - Axel Gabriel Gutierrez Ruano
    - Diego Alonso Villanueva Garcia

 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <clocale>
#include <string>
#include <new>
#include <chrono>

#ifdef unix
    #include <stdio_ext.h>
    #include <regex>
#endif

using namespace std;
using namespace chrono;

class Lista
{
    public:
        string nombre;
        string apellidos;

        Lista(string _nombre = "", string _apellidos = "", long int _codigo = 0L, string _direccion = "", string _status = "",double _adeudo = 0.0L,  Lista *_siguiente = nullptr)
        : nombre(_nombre), apellidos(_apellidos), codigo(_codigo), direccion(_direccion), status(_status), adeudo(_adeudo), siguiente(_siguiente)
        {}; // Constructor de objetos

    // ================================================================ SETTERS Y GETTERS ================================================================
        long int getCodigo() const
        {
            return codigo;
        }

        string getDireccion() const
        {
            return direccion;
        }

        double getAdeudo() const
        {
            return adeudo;
        }

        Lista *getSiguiente() const
        {
            return siguiente;
        }

        void setCodigo(int &nuevo_codigo)
        {
            codigo = nuevo_codigo;
        }

        void setDireccion(string &nueva_direccion)
        {
            direccion = nueva_direccion;
        }

        void setAdeudo(double &nuevo_adeudo)
        {
            adeudo = nuevo_adeudo;
        }

        void setSiguiente(Lista *nueva_siguiente)
        {
            siguiente = nueva_siguiente;
        }

        // ================================================================================================================================


        void insertar_nodo_paciente(Lista *&pacientes, string &nombre, string &apellidos, int codigo, string &direccion, string &status, double adeudo)
        {
            Lista *nuevo_nodo_paciente = new Lista( nombre, apellidos, codigo, direccion, status, adeudo); // Se crea un nuevo objeto

            if (pacientes == nullptr) // Si la lista está vacía

                pacientes = nuevo_nodo_paciente;

            else // Si la lista ya tiene nodos
            {
                Lista *auxiliar = pacientes;

                while (auxiliar->siguiente != nullptr)

                    auxiliar = auxiliar->siguiente;

                auxiliar->siguiente = nuevo_nodo_paciente;
            }
        }

        void mostrar_datos_paciente(Lista *pacientes)
        {
            Lista *auxiliar = pacientes;

            cout << "================================================" << endl;
            while (auxiliar != nullptr)
            {
                cout << "\nNombre: " << auxiliar->nombre << endl;
                cout << "\nApellidos: " << auxiliar->apellidos << endl;
                cout << "\nCódigo: " << auxiliar->codigo << endl;
                cout << "\nDirección: " << auxiliar->direccion << endl;
                cout << "\nAdeudo: $" << auxiliar->adeudo << endl;
                cout << "\nStatus: " << auxiliar->status << endl;
                cout << "================================================" << endl;

                auxiliar =  auxiliar->siguiente;
            }
            


        }

        void eliminar_nodo_paciente(Lista *pacientes)
        {
            Lista *auxiliar = pacientes;

            while (auxiliar != nullptr)
            {
                
            }
        }

    private:
        long int codigo;
        string direccion;
        string status;
        double adeudo;
        Lista *siguiente;
};

static void dar_alta_pacientes(Lista *&);
static void modificar_datos_pacientes(Lista *&);
static void pagar_adeudo(Lista *&);
static bool verificar_codigo(Lista *&,  long int );

static void limpiar_buffer_STDIN();
static void limpiar_pantalla();
static void pausar_terminal();
static void mostrar_mensaje_error();

int main()
{   
    int opcion;
    Lista *lista_pacientes = nullptr;

    do
    {
        limpiar_pantalla();

        do
        {
            limpiar_pantalla();

            cout << "=================================================================" << endl;
            cout << "MENU DE HOSPITAL\n\n" << endl;
            cout << "1. Alta Pacientes" << endl;
            cout << "2. Modificacion de datos de paciente" << endl;
            cout << "3. Mostrar Pacientes" << endl;
            cout << "4. Pagar adeudo" << endl;
            cout << "5. Eliminar Paciente" << endl;
            cout << "6. Salir" << endl;
            cout << "=================================================================" << endl;
            cout << "Selecciona una opcion: ";

            limpiar_buffer_STDIN();

            cin >> opcion;

            if ( opcion < 1 || opcion > 6 )

                mostrar_mensaje_error();

            
        } while ( opcion < 1 || opcion > 6 );
        
        switch ( opcion )
        {
            case 1:

                dar_alta_pacientes( lista_pacientes );

            break;

            case 2:

                modificar_datos_pacientes( lista_pacientes );

            break;

            case 3:

                if ( lista_pacientes != nullptr )

                    lista_pacientes->mostrar_datos_paciente( lista_pacientes );

                else

                    cout << "No hay pacientes registrados en el hospital. . . ." << endl;


            break;

            case 4:
            break;

            case 5:
            break;

            case 6:
                limpiar_pantalla();
                cout << "Saliendo del programa. . . ." << endl;
                milliseconds(2500);
            break;
        }

        if (opcion != 6)

            pausar_terminal();
        
    } while( opcion != 6);

    return EXIT_SUCCESS;
}

static void dar_alta_pacientes(Lista *&_pacientes)
{
    regex patron_direccion("Calle ([a-zA-Z. ]+) #([0-9]{1,4}) Colonia ([a-zA-Z ]+), ([A-Za-z ]+), ([A-Za-z ]+)");
    regex patron_nombres("([a-zA-Z]+)");
    regex patron_apellidos("([a-zA-Z]+)? ([a-zA-Z]+)");

    string nombre, apellidos, direccion, status;
    long int codigo;
    double adeudo;
    bool expresion_valida, codigo_valido = true;

    do
    {
        limpiar_pantalla();
        cout << "Nombre del paciente: ";
        limpiar_buffer_STDIN();
        getline(cin, nombre);

        expresion_valida = regex_search(nombre, patron_nombres);

        if ( !expresion_valida )
        {
            mostrar_mensaje_error();
            pausar_terminal();
        }

    } while (!expresion_valida);

    do
    {
        limpiar_pantalla();
        cout << "Apellidos del paciente: ";
        limpiar_buffer_STDIN();
        getline(cin, apellidos);

        expresion_valida = regex_search(apellidos, patron_apellidos);

        if ( !expresion_valida )
        {
            mostrar_mensaje_error();
            pausar_terminal();
        }

    } while (!expresion_valida);

    do
    {
        limpiar_pantalla();
        cout << "Direccion del paciente: ";
        limpiar_buffer_STDIN();
        getline(cin, direccion);

        expresion_valida = regex_search(direccion, patron_direccion);

        if ( !expresion_valida )
        {
            mostrar_mensaje_error();
            pausar_terminal();
        }

    } while (!expresion_valida);

    do
    {
        limpiar_pantalla();
        
        srand(time(nullptr));
        codigo = rand();

        codigo_valido = verificar_codigo(_pacientes, codigo);

        if (!codigo_valido)
        {
            mostrar_mensaje_error();
            pausar_terminal();
        }
        else
        {
            cout << "Codigo del paciente: " << codigo << " generado exitosamente!" << endl;
            pausar_terminal();
        }
        
    } while (!codigo_valido);
    
    do
    {
        limpiar_pantalla();
        cout << "Adeudo del paciente: $";
        limpiar_buffer_STDIN();
        cin >> adeudo;

        if (adeudo <= 0)
        {
            mostrar_mensaje_error();
            pausar_terminal();
        }
    } while (adeudo <= 0);

    status = "Activo";

    _pacientes->insertar_nodo_paciente(_pacientes, nombre, apellidos, codigo, direccion, status, adeudo);
}

static void modificar_datos_pacientes(Lista *&_pacientes)
{


}

static bool verificar_codigo(Lista *&_pacientes, long int _codigo_recibido)
{
    Lista *auxiliar = _pacientes;

    if (auxiliar != nullptr)
    {
        while (auxiliar != nullptr)
        {
            if (auxiliar->getCodigo() == _codigo_recibido)

                return false;

            auxiliar = auxiliar->getSiguiente();
        }
    }

    return true;
}

static void limpiar_buffer_STDIN()
{
    #if defined(_WIN32) || defined(_WIN64)
        rewind(stdin);
    #elif defined(unix)
        __fpurge(stdin);
    #endif


}

static void limpiar_pantalla()
{
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #elif defined(unix)
        system("clear");
    #endif


}


static void pausar_terminal()
{
    #if defined(_WIN32) || defined(_WIN64)
        system("pause")
    #elif defined(unix)
        cout << "Presione ENTER para continuar. . . ." << endl;
        limpiar_buffer_STDIN();
        cin.get();
        limpiar_pantalla();
    #endif


}

static void mostrar_mensaje_error()
{
    cerr << "ERROR DE CAMPO, ingrese otro valor válido. . . ." << endl ;
    limpiar_buffer_STDIN();
    cin.get();
}
