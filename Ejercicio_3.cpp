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

        string getStatus() const
        {
            return status;
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

        void setStatus(string &nuevo_status)
        {
            status = nuevo_status;
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

        void modificar_nodo_paciente( Lista *&pacientes, string &dato_nuevo, const int &opcion, const long int &codigo )
        {
            Lista *auxiliar = pacientes;

            while ((auxiliar != nullptr) && (auxiliar->codigo != codigo))

                auxiliar = auxiliar->siguiente;

            switch ( opcion )
            {
                case 1:

                    auxiliar->nombre = dato_nuevo;

                    break;

                case 2:

                    auxiliar->apellidos = dato_nuevo;

                    break;

                case 3:

                    auxiliar->direccion = dato_nuevo;

                    break;

            }


        }

        void eliminar_nodo_paciente(Lista *pacientes, string &_nombre)
        {
            Lista *auxiliar = pacientes;
            Lista *anterior = nullptr;

            while ((auxiliar != nullptr) && (auxiliar->nombre != _nombre))
            {
                anterior = auxiliar;
                auxiliar = auxiliar->siguiente;
                
            }

            if (anterior == nullptr) // Es el primer nodo
            {
                pacientes = pacientes->siguiente;
                delete auxiliar;
            }
            else  // Es el ultimo nodo
            {
                anterior->siguiente = auxiliar->siguiente;
                delete auxiliar;
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
static void dar_baja_paciente( Lista *& );
static void pagar_adeudo(Lista *&);
static bool verificar_codigo(Lista *&,  long int );
static bool comprobar_existencia_paciente( Lista *&, string *, long int *, const int * );

static bool buscar_pacientes_activos( Lista *& );
static bool buscar_pacientes_alta( Lista *& );

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

        limpiar_pantalla();
        
        switch ( opcion )
        {
            case 1:

                dar_alta_pacientes( lista_pacientes );

            break;

            case 2:

                if ( lista_pacientes != nullptr )

                    modificar_datos_pacientes( lista_pacientes );

                else

                    cout << "No hay datos a modificar porque no hay pacientes registrados. . . ." << endl;

                
            break;

            case 3:

                if ( lista_pacientes != nullptr )

                    lista_pacientes->mostrar_datos_paciente( lista_pacientes );

                else

                    cout << "No hay pacientes registrados en el hospital. . . ." << endl;


            break;

            case 4:
                if ( buscar_pacientes_activos( lista_pacientes ) )

                    pagar_adeudo( lista_pacientes );

                else

                    cout << "No hay pacientes activos en el hospital. . . ." << endl;

            break;

            case 5:
                if ( buscar_pacientes_alta( lista_pacientes ) )

                    dar_baja_paciente( lista_pacientes );

                else

                    cout << "No hay pacientes dados de alta los cuales eliminar del sistema. . . ." << endl;

                
            break;

            case 6:
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
    regex patron_direccion("Calle ([a-zA-Z. ]+) #([0-9]{1,4}) Colonia ([a-zA-Z ]+), ([A-Za-z ]+), ([A-Za-z ]+)");
    regex patron_nombres("([a-zA-Z]+)");
    regex patron_apellidos("([a-zA-Z]+)? ([a-zA-Z]+)");

    string nombre, apellidos, direccion;
    bool expresion_valida, paciente_existente;

    int opcion_dato;
    long int codigo_paciente;

    do
    {
        limpiar_pantalla();
        cout << "Ingrese el codigo del paciente que desea modificar: ";
        limpiar_buffer_STDIN();
        cin >> codigo_paciente;

        paciente_existente = comprobar_existencia_paciente( _pacientes, nullptr, &codigo_paciente, nullptr  );

        if ( !paciente_existente )
        {
            mostrar_mensaje_error();
            pausar_terminal();
        }

    } while ( !paciente_existente );
    

    do
    {
        limpiar_pantalla();
        cout << "Que dato desea modificar?" << endl;
        cout << "1. Nombre" << endl;
        cout << "2. Apellidos" << endl;
        cout << "3. Direccion" << endl;
        cout << "4. Salir" << endl;
        cout << "Opcion: ";
        limpiar_buffer_STDIN();
        cin >> opcion_dato;

        if ( opcion_dato < 1 || opcion_dato > 4 )

            mostrar_mensaje_error();

    } while ( opcion_dato < 1 || opcion_dato > 4 );

    switch ( opcion_dato ) 
    {
        case 1:
            do
            {
                limpiar_pantalla();
                cout << "Nombre del paciente: ";
                limpiar_buffer_STDIN();
                getline(cin, nombre);

                expresion_valida = regex_search( nombre, patron_nombres );

                if ( !expresion_valida )

                    mostrar_mensaje_error();

            } while ( !expresion_valida );

            _pacientes->modificar_nodo_paciente(_pacientes, nombre, opcion_dato, codigo_paciente);
            
        break;

        case 2:
            do
            {
                limpiar_pantalla();
                cout << "Apellidos del paciente: ";
                limpiar_buffer_STDIN();
                getline(cin, apellidos);

                expresion_valida = regex_search(apellidos, patron_apellidos);

                if ( !expresion_valida )

                    mostrar_mensaje_error();

            } while ( !expresion_valida );

            _pacientes->modificar_nodo_paciente(_pacientes, apellidos, opcion_dato, codigo_paciente);
            
        break;

        case 3:
            do
            {
                limpiar_pantalla();
                cout << "Direccion del paciente: ";
                limpiar_buffer_STDIN();
                getline(cin, direccion);

                expresion_valida = regex_search(direccion, patron_direccion);

                if ( !expresion_valida )

                    mostrar_mensaje_error();

            } while ( !expresion_valida );

            _pacientes->modificar_nodo_paciente(_pacientes, direccion, opcion_dato, codigo_paciente);
            
        break;
    }

    if ( opcion_dato != 4 )

        cout << "Los cambios se han guardado correctamente!" << endl;

}

static void dar_baja_paciente( Lista *&_pacientes )
{
    regex patron_nombres("([a-zA-Z]+)");
    string nombre_paciente;
    bool expresion_valida;
    const int bandera_nombre = 1;

    do
    {
        cout << "Escribe el nombre del paciente a dar de baja: ";
        limpiar_buffer_STDIN();
        getline(cin, nombre_paciente);
        expresion_valida = regex_search(nombre_paciente, patron_nombres);

        if ( !expresion_valida )

            mostrar_mensaje_error();

    } while( !expresion_valida );
    
    if ( comprobar_existencia_paciente( _pacientes, &nombre_paciente, nullptr, &bandera_nombre) )
    {
        Lista *auxiliar = _pacientes;

        while (auxiliar->nombre != nombre_paciente)

            auxiliar = auxiliar->getSiguiente();

        _pacientes->eliminar_nodo_paciente( _pacientes, auxiliar->nombre );
    }
    else

        cout << "No se encontro el paciente con ese nombre, OPERACION CANCELADA . . . ." << endl;

}

static bool comprobar_existencia_paciente( Lista *&_pacientes, string *_nombre_paciente, long int *codigo ,const int *opcion_nombre )
{
    Lista *auxiliar = _pacientes;

    if (opcion_nombre != nullptr ) // Buscar al paciente por su nombre
    {
        while (auxiliar != nullptr)
        {
            if (auxiliar->nombre == *_nombre_paciente)

                return true;

            auxiliar = auxiliar->getSiguiente();
        }
        
    }
    else // Buscar al paciente por su codigo unico
    {
        while (auxiliar != nullptr)
        {
            if (auxiliar->getCodigo() == *codigo)

                return true;

            auxiliar = auxiliar->getSiguiente();
        }
    }

    return false;
}

static void pagar_adeudo( Lista *&_pacientes )
{
    regex patron_nombres("([a-zA-Z]+)");
    string nombre_paciente;
    bool expresion_valida;
    const int bandera_nombre = 1;

    do
    {
        cout << "Escribe el nombre del paciente al que quieres pagar el adeudo: ";
        limpiar_buffer_STDIN();
        getline(cin, nombre_paciente);
        expresion_valida = regex_search(nombre_paciente, patron_nombres);

        if (!expresion_valida )

            mostrar_mensaje_error();

    } while (!expresion_valida );

    if ( comprobar_existencia_paciente( _pacientes, &nombre_paciente, nullptr, &bandera_nombre) )
    {
        Lista *auxiliar = _pacientes;

        while (auxiliar->nombre != nombre_paciente)
        {
            auxiliar = auxiliar->getSiguiente();
        }

        double adeudo_nuevo = 0;
        string status_nuevo = "Alta";

        auxiliar->setAdeudo(adeudo_nuevo);
        auxiliar->setStatus(status_nuevo);
    }

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

static bool buscar_pacientes_activos( Lista *&_pacientes )
{
    Lista *auxiliar = _pacientes;

    if (auxiliar != nullptr)
    {
        while (auxiliar!= nullptr)
        {
            if (auxiliar->getStatus() == "Activo")

                return true;

            auxiliar = auxiliar->getSiguiente();
        }
    }

    return false;

}

static bool buscar_pacientes_alta( Lista *&_pacientes )
{
    Lista *auxiliar = _pacientes;

    if (auxiliar != nullptr)
    {
        while (auxiliar!= nullptr)
        {
            if (auxiliar->getStatus() == "Alta")

                return true;

            auxiliar = auxiliar->getSiguiente();
        }
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
