#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>

using namespace std;

constexpr char RUTA_VEHICULOS[] = "bin/vehiculos.csv";
constexpr char RUTA_CLIENTES[] = "bin/clientes.csv";
constexpr char RUTA_REPUESTOS[] = "bin/repuestos.csv";

constexpr int LIMITE_VEHICULOS = 100;
constexpr int LIMITE_CLIENTES = 100;
constexpr int LIMITE_REPUESTOS = 100;

struct Vehiculo {
    string modelo, marca, placa, color, cedulaCliente, fechaEntrega;
    int anioFabricacion;
    float kilometraje, precioPorDia;
    bool rentado;
};

struct Cliente {
    string cedula, nombre, apellido, email, direccion;
    int vehiculosRentados;
    bool activo;
};

struct Repuesto {
    string modelo, marca, nombre, modeloCompatibilidad;
    int anioCompatibilidad, existencias;
    float precio;
};

Vehiculo vehiculos[LIMITE_VEHICULOS];
Cliente clientes[LIMITE_CLIENTES];
Repuesto repuestos[LIMITE_REPUESTOS];
int totalVehiculos = 0;
int totalClientes = 0;
int totalRepuestos = 0;

// Funciones para cargar datos
int cargarDatosVehiculos();
int cargarDatosClientes();
int cargarDatosRepuestos();

// Funciones para mostrar datos
void mostrarDatosVehiculo(const Vehiculo &v);
void mostrarDatosCliente(const Cliente &c);
void mostrarDatosRepuesto(const Repuesto &r);

// Nuevas funciones para consultas individuales
void consultarVehiculoPorPlaca();
void consultarClientePorCedula();
void consultarRepuestoPorModeloAnio();

// Funciones para guardar cambios en los archivos CSV
void guardarDatosVehiculos();
void guardarDatosClientes();
void guardarDatosRepuestos();
void guardarCambios(); // Llama a las tres anteriores

// Funciones para asignar/quitar vehículos y vender repuestos
void asignarVehiculoACliente();
void quitarVehiculoDeCliente();
void venderRepuesto();

// Función para obtener la fecha y hora actual
string obtenerFechaHoraActual();

int main() {
    totalVehiculos = cargarDatosVehiculos();
    totalClientes = cargarDatosClientes();
    totalRepuestos = cargarDatosRepuestos();

    char opcion;
    do {
        cout << "Menú principal:\n"
             << "1. Consultar Vehículos\n"
             << "2. Consultar Clientes\n"
             << "3. Consultar Repuestos\n"
             << "4. Consultar Vehículo por Placa\n"
             << "5. Consultar Cliente por Cédula\n"
             << "6. Consultar Repuesto por Modelo y Año\n"
             << "7. Asignar Vehículo a Cliente\n"
             << "8. Quitar Vehículo de Cliente\n"
             << "9. Vender Repuesto\n"
             << "S. Guardar Cambios\n"
             << "X. Salir\nOpción: ";
        cin >> opcion;

        switch (opcion) {
        case '1':
            for (int i = 0; i < totalVehiculos; i++) mostrarDatosVehiculo(vehiculos[i]);
            break;
        case '2':
            for (int i = 0; i < totalClientes; i++) mostrarDatosCliente(clientes[i]);
            break;
        case '3':
            for (int i = 0; i < totalRepuestos; i++) mostrarDatosRepuesto(repuestos[i]);
            break;
        case '4':
            consultarVehiculoPorPlaca();
            break;
        case '5':
            consultarClientePorCedula();
            break;
        case '6':
            consultarRepuestoPorModeloAnio();
            break;
        case '7':
            asignarVehiculoACliente();
            break;
        case '8':
            quitarVehiculoDeCliente();
            break;
        case '9':
            venderRepuesto();
            break;
        case 'S':
        case 's':
            guardarCambios();
            cout << "Cambios guardados correctamente.\n";
            break;
        case 'X':
        case 'x':
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opción inválida, intente de nuevo.\n";
        }
    } while (opcion != 'X' && opcion != 'x');

    return 0;
}

// Funciones de carga de datos
int cargarDatosVehiculos() {
    ifstream archivo(RUTA_VEHICULOS);
    string linea;
    getline(archivo, linea); // Omitir encabezado

}