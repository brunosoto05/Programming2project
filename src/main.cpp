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

    int total = 0;
    while (getline(archivo, linea) && total < LIMITE_VEHICULOS) {
        stringstream ss(linea);
        Vehiculo v;
        string rentado;

        getline(ss, v.modelo, ',');
        getline(ss, v.marca, ',');
        getline(ss, v.placa, ',');
        getline(ss, v.color, ',');
        ss >> v.anioFabricacion;
        ss.ignore();
        ss >> v.kilometraje;
        ss.ignore();
        getline(ss, rentado, ',');
        v.rentado = (rentado == "true");
        ss >> v.precioPorDia;
        ss.ignore();
        getline(ss, v.cedulaCliente, ',');
        getline(ss, v.fechaEntrega);

        vehiculos[total++] = v;
    }
    archivo.close();
    return total;
}

int cargarDatosClientes() {
    ifstream archivo(RUTA_CLIENTES);
    string linea;
    getline(archivo, linea); // Omitir encabezado

    int total = 0;
    while (getline(archivo, linea) && total < LIMITE_CLIENTES) {
        stringstream ss(linea);
        Cliente c;

        getline(ss, c.cedula, ',');
        getline(ss, c.nombre, ',');
        getline(ss, c.apellido, ',');
        getline(ss, c.email, ',');
        ss >> c.vehiculosRentados;
        ss.ignore();
        getline(ss, c.direccion, ',');
        string activo;
        getline(ss, activo);
        c.activo = (activo == "true");

        clientes[total++] = c;
    }
    archivo.close();
    return total;
}

int cargarDatosRepuestos() {
    ifstream archivo(RUTA_REPUESTOS);
    string linea;
    getline(archivo, linea); // Omitir encabezado

    int total = 0;
    while (getline(archivo, linea) && total < LIMITE_REPUESTOS) {
        stringstream ss(linea);
        Repuesto r;

        getline(ss, r.modelo, ',');
        getline(ss, r.marca, ',');
        getline(ss, r.nombre, ',');
        getline(ss, r.modeloCompatibilidad, ',');
        ss >> r.anioCompatibilidad;
        ss.ignore();
        ss >> r.precio;
        ss.ignore();
        ss >> r.existencias;

        repuestos[total++] = r;
    }
    archivo.close();
    return total;
}

// Funciones para mostrar datos
void mostrarDatosVehiculo(const Vehiculo &v) {
    cout << "Modelo: " << v.modelo << ", Marca: " << v.marca << ", Placa: " << v.placa
         << ", Color: " << v.color << ", Año: " << v.anioFabricacion << ", Kilometraje: " << v.kilometraje
         << ", Rentado: " << (v.rentado ? "Sí" : "No") << ", Precio por día: $" << v.precioPorDia
         << ", Cedula cliente: " << v.cedulaCliente << ", Fecha entrega: " << v.fechaEntrega << endl;
}

void mostrarDatosCliente(const Cliente &c) {
    cout << "Cedula: " << c.cedula << ", Nombre: " << c.nombre << " " << c.apellido
         << ", Email: " << c.email << ", Vehículos rentados: " << c.vehiculosRentados
         << ", Dirección: " << c.direccion << ", Activo: " << (c.activo ? "Sí" : "No") << endl;
}

void mostrarDatosRepuesto(const Repuesto &r) {
    cout << "Modelo: " << r.modelo << ", Marca: " << r.marca << ", Nombre: " << r.nombre
         << ", Modelo compatible: " << r.modeloCompatibilidad << ", Año compatible: " << r.anioCompatibilidad
         << ", Precio: $" << r.precio << ", Existencias: " << r.existencias << endl;
}

// Funciones para consultas individuales
void consultarVehiculoPorPlaca() {
    string placa;
    cout << "Ingrese la placa del vehículo: ";
    cin >> placa;

    for (int i = 0; i < totalVehiculos; i++) {
        if (vehiculos[i].placa == placa) {
            mostrarDatosVehiculo(vehiculos[i]);
            return;
        }
    }
    cout << "No se encontró ningún vehículo con esa placa.\n";
}

void consultarClientePorCedula() {
    string cedula;
    cout << "Ingrese la cédula del cliente: ";
    cin >> cedula;

    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i].cedula == cedula) {
            mostrarDatosCliente(clientes[i]);
            return;
        }
    }
    cout << "No se encontró ningún cliente con esa cédula.\n";
}

void consultarRepuestoPorModeloAnio() {
    string modelo;
    int anio;
    cout << "Ingrese el modelo del repuesto: ";
    cin >> modelo;
    cout << "Ingrese el año de compatibilidad: ";
    cin >> anio;

    