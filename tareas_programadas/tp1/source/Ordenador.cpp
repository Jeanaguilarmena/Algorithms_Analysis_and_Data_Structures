#include "Ordenador.hpp"
#include <cstdint>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>

//METODOS PRIVADOS

void Ordenador::mergeSortAux(std::uint32_t *A, std::uint32_t left, std::uint32_t right) const {
    if (left < right) {
        std::uint32_t mid = left + (right - left) / 2;
        mergeSortAux(A, left, mid);
        mergeSortAux(A, mid + 1, right);
        merge(A, left, mid, right);
    }
}

void Ordenador::merge(std::uint32_t *A, std::uint32_t left, std::uint32_t mid, std::uint32_t right) const {
    //Esto lo hago para tener los tamaños de los subarreglos
    std::uint32_t n1 = mid - left + 1;
    std::uint32_t n2 = right - mid;

    //Acá creo 2 vectores temporales
    std::vector<std::uint32_t> L(n1), R(n2);
    //Acá copio los datos a los vectores temporales
    for (std::uint32_t i = 0; i < n1; i++) {
        L[i] = A[left + i];
    }
    for (std::uint32_t j = 0; j < n2; j++) {
        R[j] = A[mid + 1 + j];
    }
    // Acá hago la mezcla de los dos vectores temporales
    std::uint32_t i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            A[k++] = L[i++];
        } else {
            A[k++] = R[j++];
        }
    }
    //Estos 2 ciclos son por si quedó algun numero en alguno de los sub arreglos
    while (i < n1) {
        A[k++] = L[i++];
    }
    while (j < n2) {
        A[k++] = R[j++];
    }
}

// ===============================
// AUXILIARES HEAPSORT
// ===============================
void Ordenador::heapify(std::uint32_t *A, std::uint32_t n, std::uint32_t i) const {
    std::uint32_t largest = i; // inicializar el mayor como raíz
    std::uint32_t left = 2 * i + 1; // hijo izquierdo
    std::uint32_t right = 2 * i + 2; // hijo derecho


    //Aca lo que hago es ver cual es el mayor entre la raiz y los hijos
    if (left < n && A[left] > A[largest]) {
        largest = left;
    }
    if (right < n && A[right] > A[largest]) {
        largest = right;
    }

    // Si el mayor no es la raíz, entonces lo intercambio y vuelvo a llamar a heapify de manera recursiva
    if (largest != i) {
        std::swap(A[i], A[largest]);
        heapify(A, n, largest);
    }
}

// ===============================
// AUXILIARES QUICKSORT
// ===============================
void Ordenador::quickSortAux(std::uint32_t *A, std::uint32_t low, std::uint32_t high) const {
    //caso base es cuando low >= high
    if (low < high) {
        //Se hace este llamado para obtener el pivote del arreglo original
        std::uint32_t pi = partition(A, low, high);
        // Se hacen llamados recursivos a quicksort para las dos mitades del arreglo
        if (pi > 0) quickSortAux(A, low, pi - 1); // cuidado underflow
        quickSortAux(A, pi + 1, high);
    }
}

std::uint32_t Ordenador::partition(std::uint32_t *A, std::uint32_t low, std::uint32_t high) const {
    //En esta implementación estoy eligiendo el último elemento como pivote
    std::uint32_t pivot = A[high];
    //En este caso i lo pongo como signed porque puede ser negativo y marca la frontera de los menores al pivote
    std::int32_t i = low - 1;

    // Recorro el arreglo moviendo los que son menores al pivote a la izquierda
    for (std::uint32_t j = low; j < high; j++) {
        if (A[j] <= pivot) {
            i++;
            std::swap(A[i], A[j]);
        }
    }
    // Finalmente coloco el pivote en su posición correcta
    std::swap(A[i + 1], A[high]);
    //Acá retorno la posición del pivote
    return i + 1;
}

// ===============================
// AUXILIARES RADIX SORT (RESIDUOS)
// ===============================
void Ordenador::countingSortByDigit(std::uint32_t *A, std::uint32_t n, std::uint32_t r, std::uint32_t shift) const {
    std::uint32_t k = 1u << r;
    std::vector<std::uint32_t> output(n);
    std::vector<std::uint32_t> count(k, 0);

    // Contar ocurrencias de los r bits
    for (std::uint32_t i = 0; i < n; i++) {
        std::uint32_t digit = (A[i] >> shift) & (k - 1);
        count[digit]++;
    }

    // Acumulado
    for (std::uint32_t i = 1; i < k; i++)
        count[i] += count[i - 1];

    // Ordenar establemente
    for (std::int32_t i = n - 1; i >= 0; i--) {
        std::uint32_t digit = (A[i] >> shift) & (k - 1);
        output[--count[digit]] = A[i];
    }

    // Copiar al arreglo original
    for (std::uint32_t i = 0; i < n; i++)
        A[i] = output[i];
}


//METODOS PUBLICOS

// ===============================
    // ORDENAMIENTO POR SELECCIÓN
    // ===============================
    void Ordenador::ordenamientoPorSeleccion(std::uint32_t *A, std::uint32_t n) const {
        //Recorro el arreglo n-1 veces
        for (std::uint32_t i = 0; i < n - 1; i++) {
            //Acá marco i como el índice del mínimo
            std::uint32_t minIdx = i;
            //Busco si hay algun elemento menor que A[i] en el resto del arreglo y si lo hay actualizo minIdx
            for (std::uint32_t j = i + 1; j < n; j++) {
                if (A[j] < A[minIdx]) {
                    minIdx = j;
                }
            }
            //Acá cambio el elemento en la posición i por el mínimo encontrado
            std::swap(A[i], A[minIdx]);
        }
        // for (int i = 0; i < n; ++i) {
        //     cout << A[i] << " ";
        // }
    }

    // ===============================
    // ORDENAMIENTO POR INSERCIÓN
    // ===============================
    void Ordenador::ordenamientoPorInserccion(std::uint32_t *A, std::uint32_t n) const {
        //Recorro el arreglo desde el segundo elemento
        for (std::uint32_t i = 1; i < n; i++) {
            //Pongo el elemento de la posición i como el key
            std::uint32_t key = A[i];
            //Pongo j al indice del elemento anterior a i
            std::int32_t j = i - 1; // signed porque puede ser negativo
            //Reviso que j sea menor o igual a 0 y si es mayor que key, lo muevo una posición a la derecha
            while (j >= 0 && A[j] > key) {
                A[j + 1] = A[j];
                j--;
            }
            //Pongo el key en la posición correcta
            A[j + 1] = key;
        }
        // for (int i = 0; i < n; ++i) {
        //     cout << A[i] << " ";
        // }
    }

    // ===============================
    // ORDENAMIENTO POR MEZCLA (MERGESORT)
    // ===============================
    void Ordenador::ordenamientoPorMezcla(std::uint32_t *A, std::uint32_t n) const {
        mergeSortAux(A, 0, n - 1);
        // for (int i = 0; i < n; ++i) {
        //     cout << A[i] << " ";
        // }
    }

    // ===============================
    // ORDENAMIENTO POR MONTÍCULOS (HEAPSORT)
    // ===============================
    void Ordenador::ordenamientoPorMonticulos(std::uint32_t *A, std::uint32_t n) const {
        // construir heap máximo
        for (std::int32_t i = n / 2 - 1; i >= 0; i--) {
            heapify(A, n, i);
        }
        // extraer elementos
        for (std::int32_t i = n - 1; i > 0; i--) {
            std::swap(A[0], A[i]);
            heapify(A, i, 0);
        }
        // for (int i = 0; i < n; ++i) {
        //     cout << A[i] << " ";
        // }
    }

    // ===============================
    // ORDENAMIENTO RÁPIDO (QUICKSORT)
    // ===============================
    void Ordenador::ordenamientoRapido(std::uint32_t *A, std::uint32_t n) const {
        quickSortAux(A, 0, n - 1);
        // for (int i = 0; i < n; ++i) {
        //     cout << A[i] << " ";
        // }
    }
  

    // ===============================
    // ORDENAMIENTO POR RESIDUOS (RADIX SORT)
    // ===============================
    void Ordenador::ordenamientoPorResiduos(std::uint32_t *A, std::uint32_t n) const {

        //Voy a comentarlo por ahora
        // std::uint32_t r = static_cast<std::uint32_t>(std::floor(std::log2(n))); // Generar el r aplicando la formula

        std::uint32_t maxVal = A[0];
        for (std::uint32_t i = 1; i < n; i++)
            if (A[i] > maxVal) maxVal = A[i];
    
        std::uint32_t r = 16; //Acá cambio el valor de r para probar
        cout << "r= " << r;
    
        std::uint32_t b = 32; 
        std::uint32_t d = (b + r - 1) / r; // Le aplico la formula para calcular el d
    
        for (std::uint32_t i = 0; i < d; i++) {
            std::uint32_t shift = i * r;
            countingSortByDigit(A, n, r, shift);
        }
    }
    
    /**
     * @brief Retorna un std::string con los datos de la tarea.
     * 
     * Este método devuelve una cadena de texto que contiene el carné, nombre y tarea.
     * 
     * @return std::string Una cadena de texto con los datos de la tarea.
     */

    string Ordenador::ImprimirDatosDeTarea() const {
        string message = "Carné: B70134, Nombre: Jean Aguilar Mena, Tarea 1.";
        return message;
    }

