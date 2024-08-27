#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <regex>
#include <chrono>

#if defined( unix ) && !defined(__ANDROID__)
    #include <stdio_ext.h>
#endif

#define MONTO_CORTE 10000 // Nuestro delimitador para avisar cuando se recomiende un corte de caja

using namespace std;
using namespace chrono;

struct Cliente
{
    int numero_movimiento;
    string nombre;
    string apellidos;
    string cuenta;
    string movimiento;
    double monto_movimiento;

    Cliente *siguiente;
};

static void iniciar_movimiento(Cliente *&, long long int &);
static void apliar_nodos(Cliente *&);
static void mostrar_movimientos(Cliente *&);
static void hacer_corte(Cliente *&);

static bool validar_numero_movimiento( Cliente *&, const int & );

static void limpiar_buffer_STDIN();
static void limpiar_pantalla();
static void pausar_terminal();
static void mostrar_mensaje_error();

int main()
{
    int opcion;
    long long int fondo_caja;
    bool entrada_invalida;
    Cliente *cabeza_lista = nullptr;

    #if defined( _WIN32 ) || defined( _WIN64 )

        setlocale(LC_CTYPE, "es_MX");

    #elif defined( unix ) && !defined(__ANDROID__)

        setlocale(LC_CTYPE, "es_MX.UTF-8");

    #endif

    do
    {
        limpiar_pantalla();

        cout << "Con cuánto dinero desea fondear la caja el día de hoy?: $";
        limpiar_buffer_STDIN();
        cin >> fondo_caja;

        entrada_invalida = cin.fail();

        if ( entrada_invalida )
        {
            cin.clear();
            mostrar_mensaje_error();
        }
        else if( fondo_caja < 300000LL )
            {
                cout << "La caja debe tener más de $300,000 para iniciar operaciones. . ." << endl;
                pausar_terminal();
            }
        
    } while ( entrada_invalida );
    

    do
    {
        do
        {
            //limpiar_pantalla();

            cout << "\t\t=================================================================\n" << endl;
            cout << "\t\t\t\tMENÚ DE BANCO\n\n" << endl;
            cout << "\t\t\t\t1. Ingresar Movimiento Bancario" << endl;
            cout << "\t\t\t\t2. Mostrar Movimientos Bancarios" << endl;
            cout << "\t\t\t\t3. Generar Corte de Caja" << endl;
            cout << "\t\t\t\t4. Salir\n" << endl;
            cout << "\t\t=================================================================\n" << endl;
            cout << "\t\t\t\tSelecciona una opción: ";

            limpiar_buffer_STDIN();

            cin >> opcion;
            entrada_invalida = cin.fail();

            if (entrada_invalida)
            {
                cin.clear();
                mostrar_mensaje_error();
            }
            else if( opcion < 1 || opcion > 4 )

                    mostrar_mensaje_error();
            
        } while (entrada_invalida || (opcion < 1 || opcion > 4));

        //limpiar_pantalla();

        switch ( opcion )
        {
            case 1:

                if( fondo_caja <= MONTO_CORTE )
                {
                    cout << "La caja cuenta con $" << fondo_caja << " se recomienda hacer corte de caja. . ." << endl;
                    pausar_terminal();
                }

                iniciar_movimiento( cabeza_lista, fondo_caja );

            break;

            case 2:
                if ( cabeza_lista != nullptr )

                    mostrar_movimientos(cabeza_lista);

                else

                    cout << "\t\t\tNo hay movimientos bancarios registrados.\n" << endl;

                
            break;

            case 3:
                if ( cabeza_lista != nullptr )

                    hacer_corte(cabeza_lista);

                else

                    cout << "\t\t\tNo hay movimientos bancarios registrados.\n" << endl;

                
            break;

            case 4:
                cout << "Saliendo del programa. . . ." << endl;
                seconds(5);
            break;
        
        }
        
    } while ( opcion != 4 );
    
    return EXIT_SUCCESS;
}

static void iniciar_movimiento(Cliente *&lista_clientes, long long int &fondo)
{
    bool numero_invalido, expresion_valida, entrada_invalida;
    regex patron_movimiento("(Deposito|Retiro)");
    regex patron_nombre_apellidos("([a-zA-ZÁ-Ý\u00f1\u00d1]+)? ([a-zA-ZÁ-Ý\u00f1\u00d1]+)");
    regex patron_cuenta("[0-9]{1,8}");

    do
    {
        cout << "Se le va a generar un numero de movimiento. . . " << endl;
        seconds(5);
        
        srand(time(nullptr));
        lista_clientes->numero_movimiento = rand();

        numero_invalido = validar_numero_movimiento(lista_clientes, lista_clientes->numero_movimiento);

        if ( numero_invalido )
        {
            //limpiar_pantalla();
            cout << "Espere un momento por favor. . . ." << endl;
            seconds(10);
        }

    } while ( numero_invalido );

    do
    {
        //limpiar_pantalla();
        cout << "Nombre: ";
        limpiar_buffer_STDIN();
        getline(cin, lista_clientes->nombre);

        expresion_valida = regex_search(lista_clientes->nombre, patron_nombre_apellidos);

        if ( !expresion_valida )

            mostrar_mensaje_error();


    } while (!expresion_valida);

    do
    {
        //limpiar_pantalla();
        cout << "Apellidos: ";
        limpiar_buffer_STDIN();
        getline(cin, lista_clientes->apellidos);

        expresion_valida = regex_search(lista_clientes->apellidos, patron_nombre_apellidos);

        if ( !expresion_valida )

            mostrar_mensaje_error();


    } while (!expresion_valida);

    do
    {
        // limpiar_pantalla();

        cout << "Ingrese su número de cuenta: ";
        limpiar_buffer_STDIN();
        getline(cin, lista_clientes->cuenta);

        expresion_valida = regex_search(lista_clientes->cuenta, patron_cuenta);
        
        if ( !expresion_valida )

            mostrar_mensaje_error();

    } while ( !expresion_valida );

    do
    {
        //limpiar_pantalla();

        cout << "Qué tipo de movimiento hará en nuestro banco? (Deposito|Retiro): ";
        limpiar_buffer_STDIN();
        getline(cin, lista_clientes->movimiento);

        expresion_valida = regex_search(lista_clientes->movimiento, patron_movimiento);

        if ( !expresion_valida )

            mostrar_mensaje_error();
        
    } while ( !expresion_valida );

    do
    {
        // limpiar_pantalla();

        cout << "Monto del movimiento: $";
        limpiar_buffer_STDIN();
        cin >> lista_clientes->monto_movimiento;
        entrada_invalida = cin.fail();
        
        if ( entrada_invalida || lista_clientes->monto_movimiento <= 0 )
        {
            cin.clear();
            mostrar_mensaje_error();
        }
        else if ( lista_clientes->monto_movimiento > 50000 && lista_clientes->movimiento == "Retiro")
            {
                //limpiar_pantalla();
                cout << "No puedes retirar más de los $50,000 permitidos, favor de pasar a gerencia. . .";
                pausar_terminal();
            }

    } while(( entrada_invalida || lista_clientes->monto_movimiento <= 0 ) || ( lista_clientes->monto_movimiento > 50000 && lista_clientes->movimiento == "Retiro" ) );

    if ( lista_clientes->movimiento == "Deposito" )

        fondo += lista_clientes->monto_movimiento;

    else

        fondo -= lista_clientes->monto_movimiento;


    apliar_nodos(lista_clientes);

    //limpiar_pantalla();
    cout << "OPERACIÓN REALIZADA CON ÉXITO!" << endl;
    cout << "Regresando al menú. . . ." << endl;
    seconds(5);
}

static void apliar_nodos(Cliente *&lista_clientes)
{
    Cliente *nuevo_nodo = new Cliente();

    nuevo_nodo->nombre = lista_clientes->nombre;
    nuevo_nodo->apellidos = lista_clientes->apellidos;
    nuevo_nodo->cuenta = lista_clientes->cuenta;
    nuevo_nodo->movimiento = lista_clientes->movimiento;
    nuevo_nodo->monto_movimiento = lista_clientes->monto_movimiento;
    nuevo_nodo->numero_movimiento = lista_clientes->numero_movimiento;

    nuevo_nodo->siguiente = nullptr;
    
    if ( lista_clientes == nullptr )

        lista_clientes = nuevo_nodo;

    else
    {
        Cliente *auxiliar = lista_clientes;

        while (auxiliar->siguiente!= nullptr)

            auxiliar = auxiliar->siguiente;

        auxiliar->siguiente = nuevo_nodo;
    }
}

static void mostrar_movimientos(Cliente *&lista_clientes)
{
    Cliente *auxiliar = lista_clientes;

    cout << "\t\t+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=" << endl;

    while ( auxiliar != nullptr )
    {
        cout << "\t\t\tMovimiento número: " << auxiliar->numero_movimiento << endl;
        cout << "\t\t\tNombre y Apellidos: " << auxiliar->nombre << " " << auxiliar->apellidos << endl;
        cout << "\t\t\tCuenta: " << auxiliar->cuenta << endl;
        cout << "\t\t\tTipo de Movimiento: " << auxiliar->movimiento << endl;
        cout << "\t\t\tMonto: $" << auxiliar->monto_movimiento << endl;
        cout << "\n\t\t+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=" << endl;
    }
    
    
}

static void hacer_corte(Cliente *&lista_clientes)
{
    
}

static bool validar_numero_movimiento( Cliente *&lista_clientes, const int &numero )
{
    Cliente *auxiliar = lista_clientes;

    while (auxiliar != nullptr)
    {
        if (auxiliar->numero_movimiento == numero)

            return true;

        auxiliar = auxiliar->siguiente;
    }

    return false;

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
        system("pause");
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