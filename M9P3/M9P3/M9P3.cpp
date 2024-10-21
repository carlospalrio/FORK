#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h> // Para CreateThread y WaitForSingleObject

using namespace std; // Usamos el espacio de nombres estándar

vector<string> listaNombres; // Arreglo global para almacenar nombres

// Añadir un nombre al arreglo global
void insertarNombre(const string& nombre) {
    listaNombres.push_back(nombre);
}

// Mostrar un nombre aleatorio del arreglo global
void elegirNombreAleatorio() {
    if (!listaNombres.empty()) {
        int indice = rand() % listaNombres.size(); // Elegir un índice al azar
        cout << "Bienvenido, " << listaNombres[indice] << "!" << endl;
    }
    else {
        cout << "El arreglo esta vacio." << endl;
    }
}

// Simulación del código del proceso "hijo"
void procesoHijo(int numProceso) {
    string nombre;
    cout << "Introduce un nombre para el proceso " << numProceso << ": ";
    cin >> nombre;

    // Añadir el nombre al arreglo global
    insertarNombre(nombre);

    // Mostrar un nombre elegido aleatoriamente
    elegirNombreAleatorio();
}

int main() {
    int numProcesos;
    cout << "Cuantos procesos deseas crear?: ";
    cin >> numProcesos;

    srand(time(0)); // Inicializar generador de números aleatorios

    // Crear los procesos de manera simulada utilizando hilos
    for (int i = 0; i < numProcesos; ++i) {
        HANDLE hilo = CreateThread(
            NULL, // No usar atributos de seguridad especiales
            0,    // Usar el tamaño de pila predeterminado
            (LPTHREAD_START_ROUTINE)procesoHijo, // Función que ejecuta el proceso "hijo"
            (LPVOID)(i + 1), // El número del proceso se pasa como argumento
            0,    // Iniciar el hilo inmediatamente
            NULL  // No se requiere el ID del hilo
        );

        if (hilo == NULL) {
            cerr << "No se pudo crear el proceso " << i + 1 << endl;
            return 1;
        }

        // Esperar a que el hilo termine su ejecución
        WaitForSingleObject(hilo, INFINITE);

        // Cerrar el manejador del hilo para liberar recursos
        CloseHandle(hilo);
    }

    // Al final, mostrar todos los nombres almacenados en el arreglo
    cout << "\nLista de nombres guardados:" << endl;
    for (const auto& nombre : listaNombres) {
        cout << nombre << endl;
    }

    return 0;
}
