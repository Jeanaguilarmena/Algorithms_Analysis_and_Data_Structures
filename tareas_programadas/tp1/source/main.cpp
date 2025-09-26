#include <iostream>  
using namespace std;
#include <random>    
#include <vector>    
#include <cstdint>  
#include <fstream>    
#include "Ordenador.hpp" 
#include <chrono>     


/**
 * @brief Genera un arreglo con números aleatorios en el rango [1, maxValue].
 * 
 * @param size     Tamaño del arreglo a generar.
 * @param maxValue Valor máximo posible de los números generados.
 * @return std::vector<uint32_t> Arreglo con números aleatorios.
 */
std::vector<std::uint32_t> generarArrayRandom(std::uint32_t size, std::uint32_t maxValue) {
    std::vector<std::uint32_t> array(size);

    // Semilla para generación de números aleatorios
    std::random_device rd;
    std::mt19937 gen(rd());  
    std::uniform_int_distribution<std::uint32_t> dis(1, maxValue);

    // Llenar el arreglo con números aleatorios
    for (std::uint32_t i = 0; i < size; ++i) {
        array[i] = dis(gen);
    }
    return array;
}


/**
 * @brief Guarda un arreglo en un archivo de texto.
 * 
 * @param arr      Arreglo a guardar.
 * @param filename Nombre del archivo de salida.
 */
void guardarArrayTXT(const vector<uint32_t>& arr, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error al abrir el archivo para escribir: " << filename << endl;
        return;
    }
    for (size_t i = 0; i < arr.size(); i++) {
        file << arr[i];
        if (i + 1 < arr.size()) file << " "; // Espacio entre números
    }
}


/**
 * @brief Carga un arreglo desde un archivo de texto.
 * 
 * @param filename Nombre del archivo de entrada.
 * @return std::vector<uint32_t> Arreglo leído desde el archivo.
 */
vector<uint32_t> cargarArrayTXT(const string& filename) {
    ifstream file(filename);
    vector<uint32_t> arr;
    uint32_t val;

    if (!file) {
        cerr << "Error al abrir el archivo para leer: " << filename << endl;
        return arr; 
    }

    while (file >> val) {
        arr.push_back(val);
    }
    return arr;
}


int main() {
    Ordenador algoritmos = Ordenador();

    vector<uint32_t> array = cargarArrayTXT("array4.txt");

    auto start = chrono::high_resolution_clock::now();

    algoritmos.ordenamientoPorResiduos(array.data(), array.size());

    auto end = chrono::high_resolution_clock::now();


    auto duracion    = chrono::duration_cast<chrono::microseconds>(end - start).count();
    auto duracion_ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    auto duracion_s  = chrono::duration_cast<chrono::seconds>(end - start).count();
    
    cout << endl << "=============================================================" << endl;
    cout << "                REPORTE DE ORDENAMIENTO" << endl;
    cout << "=============================================================" << endl;
    cout << left << setw(35) << "Algoritmo:" << "Ordenamiento por Residuos" << endl;
    cout << left << setw(35) << "Longitud del array:" << array.size() << " elementos" << endl;
    cout << left << setw(35) << "Rango de numeros:" << "1 - 10000" << endl;
    cout << left << setw(35) << "Duración total:" << duracion << " microsegundos" << endl;
    cout << left << setw(35) << "Duración total:" << duracion_ms << " milisegundos" << endl;
    cout << left << setw(35) << "Duración total:" << duracion_s << " segundos" << endl;
    cout << "=============================================================" << endl << endl; 
  
    
    // OPCIONAL:
    // Generar un arreglo aleatorio grande y guardarlo en archivo:
    // std::vector<uint32_t> array1 = generarArrayRandom(1000000, 1000000);
    // guardarArrayTXT(array1, "array4.txt");
    
    return 0;
}
