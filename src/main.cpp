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

