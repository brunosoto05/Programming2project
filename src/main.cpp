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

    for (int i = 0; i < totalRepuestos; i++) {
        if (repuestos[i].modeloCompatibilidad == modelo && repuestos[i].anioCompatibilidad == anio) {
            mostrarDatosRepuesto(repuestos[i]);
            return;
        }
    }
    cout << "No se encontró ningún repuesto con ese modelo y año.\n";
}

// Funciones para guardar cambios en los archivos CSV
void guardarDatosVehiculos() {
    ofstream archivo(RUTA_VEHICULOS);
    archivo << "Modelo,Marca,Placa,Color,AñoFabricacion,Kilometraje,Rentado,PrecioPorDia,CedulaCliente,FechaEntrega\n";
    for (int i = 0; i < totalVehiculos; i++) {
        archivo << vehiculos[i].modelo << ',' << vehiculos[i].marca << ',' << vehiculos[i].placa << ','
                << vehiculos[i].color << ',' << vehiculos[i].anioFabricacion << ',' << vehiculos[i].kilometraje << ','
                << (vehiculos[i].rentado ? "true" : "false") << ',' << vehiculos[i].precioPorDia << ','
                << vehiculos[i].cedulaCliente << ',' << vehiculos[i].fechaEntrega << '\n';
    }
    archivo.close();
}

void guardarDatosClientes() {
    ofstream archivo(RUTA_CLIENTES);
    archivo << "Cedula,Nombre,Apellido,Email,VehiculosRentados,Direccion,Activo\n";
    for (int i = 0; i < totalClientes; i++) {
        archivo << clientes[i].cedula << ',' << clientes[i].nombre << ',' << clientes[i].apellido << ','
                << clientes[i].email << ',' << clientes[i].vehiculosRentados << ',' << clientes[i].direccion << ','
                << (clientes[i].activo ? "true" : "false") << '\n';
    }
    archivo.close();
}

void guardarDatosRepuestos() {
    ofstream archivo(RUTA_REPUESTOS);
    archivo << "Modelo,Marca,Nombre,ModeloCompatibilidad,AnioCompatibilidad,Precio,Existencias\n";
    for (int i = 0; i < totalRepuestos; i++) {
        archivo << repuestos[i].modelo << ',' << repuestos[i].marca << ',' << repuestos[i].nombre << ','
                << repuestos[i].modeloCompatibilidad << ',' << repuestos[i].anioCompatibilidad << ','
                << repuestos[i].precio << ',' << repuestos[i].existencias << '\n';
    }
    archivo.close();
}

void guardarCambios() {
    guardarDatosVehiculos();
    guardarDatosClientes();
    guardarDatosRepuestos();
}

// Función para obtener la fecha y hora actual
string obtenerFechaHoraActual() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    stringstream fechaHora;
    fechaHora << 1900 + ltm->tm_year << "-"
              << 1 + ltm->tm_mon << "-"
              << ltm->tm_mday << " "
              << ltm->tm_hour << ":"
              << ltm->tm_min << ":"
              << ltm->tm_sec;
    
    return fechaHora.str();
}

// Funciones para asignar/quitar vehículos y vender repuestos
void asignarVehiculoACliente() {
    string placa, cedula;
    cout << "Ingrese la placa del vehículo a asignar: ";
    cin >> placa;
    cout << "Ingrese la cédula del cliente: ";
    cin >> cedula;

    for (int i = 0; i < totalVehiculos; i++) {
        if (vehiculos[i].placa == placa && !vehiculos[i].rentado) {
            for (int j = 0; j < totalClientes; j++) {
                if (clientes[j].cedula == cedula && clientes[j].activo) {
                    vehiculos[i].rentado = true;
                    vehiculos[i].cedulaCliente = cedula;
                    vehiculos[i].fechaEntrega = obtenerFechaHoraActual(); // Asignar la fecha y hora actual
                    clientes[j].vehiculosRentados++;
                    cout << "Vehículo asignado correctamente. Fecha de entrega registrada: " << vehiculos[i].fechaEntrega << endl;
                    return;
                }
            }
            cout << "Cliente no encontrado o no está activo.\n";
            return;
        }
    }
    cout << "Vehículo no encontrado o ya está rentado.\n";
}

void quitarVehiculoDeCliente() {
    string placa;
    cout << "Ingrese la placa del vehículo a quitar: ";
    cin >> placa;

    for (int i = 0; i < totalVehiculos; i++) {
        if (vehiculos[i].placa == placa && vehiculos[i].rentado) {
            string cedulaCliente = vehiculos[i].cedulaCliente;
            vehiculos[i].rentado = false;
            vehiculos[i].cedulaCliente = "";
            vehiculos[i].fechaEntrega = ""; // Limpiar la fecha de entrega al quitar el vehículo
            for (int j = 0; j < totalClientes; j++) {
                if (clientes[j].cedula == cedulaCliente) {
                    clientes[j].vehiculosRentados--;
                    cout << "Vehículo quitado correctamente.\n";
                    return;
                }
            }
        }
    }
    cout << "Vehículo no encontrado o no está rentado.\n";
}

void venderRepuesto() {
    string modelo;
    int anio;
    int cantidad;
    cout<< "Ingrese el modelo del repuesto: ";
    cin>> modelo;
    cout << "Ingrese el año de compatibilidad: ";
    cin >> anio;
    cout << "Ingrese la cantidad a vender: ";
    cin >> cantidad;

    for (int i = 0; i < totalRepuestos; i++) {
        if (repuestos[i].modeloCompatibilidad == modelo && repuestos[i].anioCompatibilidad == anio) {
            if (repuestos[i].existencias >= cantidad) {
                repuestos[i].existencias -= cantidad;
                cout << "Repuesto vendido correctamente. Existencias restantes: " << repuestos[i].existencias << endl;
                return;
            } else {
                cout << "No hay suficientes existencias para esa cantidad.\n";
                return;
            }
        }
    }
    cout << "Repuesto no encontrado.\n";
}
