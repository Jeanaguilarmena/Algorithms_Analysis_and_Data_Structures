#include "Ordenador.hpp"
#include <cstdint>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>

//METODOS PRIVADOS
//La documentación de cada método está en el .hpp

//==============================
// AUXILIARES MERGESORT
//==============================

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

    std::vector<std::uint32_t> L(n1), R(n2);

    for (std::uint32_t i = 0; i < n1; i++) {
        L[i] = A[left + i];
    }
    for (std::uint32_t j = 0; j < n2; j++) {
        R[j] = A[mid + 1 + j];
    }

    std::uint32_t i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            A[k++] = L[i++];
        } else {
            A[k++] = R[j++];
        }
    }
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
    std::uint32_t largest = i; 
    std::uint32_t left = 2 * i + 1; 
    std::uint32_t right = 2 * i + 2; 

    if (left < n && A[left] > A[largest]) {
        largest = left;
    }
    if (right < n && A[right] > A[largest]) {
        largest = right;
    }

    if (largest != i) {
        std::swap(A[i], A[largest]);
        heapify(A, n, largest);
    }
}

// ===============================
// AUXILIARES QUICKSORT
// ===============================

void Ordenador::quickSortAux(std::uint32_t *A, std::uint32_t low, std::uint32_t high) const {
    if (low < high) {
        std::uint32_t pi = partition(A, low, high);
        if (pi > 0) quickSortAux(A, low, pi - 1); 
        quickSortAux(A, pi + 1, high);
    }
}

std::uint32_t Ordenador::partition(std::uint32_t *A, std::uint32_t low, std::uint32_t high) const {

    // ===============================
    // ACÁ PONGO LAS OPCIONES DE PIVOTE, POR DEFECTO MANTENGO LA VERSIÓN ESTÁNDAR
    // ===============================

    // 1) Último elemento como pivote (versión estándar)
    std::uint32_t pivot = A[high];

    // 2) Pivote aleatorio
    // std::uint32_t randIndex = low + (std::rand() % (high - low + 1));
    // std::swap(A[randIndex], A[high]);
    // std::uint32_t pivot = A[high];

    // 3) Media de tres (primero, medio y último)
    // std::uint32_t mid = low + (high - low) / 2;
    // if (A[low] > A[mid]) std::swap(A[low], A[mid]);
    // if (A[low] > A[high]) std::swap(A[low], A[high]);
    // if (A[mid] > A[high]) std::swap(A[mid], A[high]);
    // std::swap(A[mid], A[high]);
    // std::uint32_t pivot = A[high];
    std::int32_t i = low - 1;

    for (std::uint32_t j = low; j < high; j++) {
        if (A[j] <= pivot) {
            i++;
            std::swap(A[i], A[j]);
        }
    }
    std::swap(A[i + 1], A[high]);
    return i + 1;
}

// ===============================
// AUXILIARES RADIX SORT (RESIDUOS)
// ===============================
void Ordenador::countingSortByDigit(std::uint32_t *A, std::uint32_t n, std::uint32_t r, std::uint32_t shift) const {
    std::uint32_t k = 1u << r;
    std::vector<std::uint32_t> output(n);
    std::vector<std::uint32_t> count(k, 0);

    for (std::uint32_t i = 0; i < n; i++) {
        std::uint32_t digit = (A[i] >> shift) & (k - 1);
        count[digit]++;
    }

    for (std::uint32_t i = 1; i < k; i++)
        count[i] += count[i - 1];

    for (std::int32_t i = n - 1; i >= 0; i--) {
        std::uint32_t digit = (A[i] >> shift) & (k - 1);
        output[--count[digit]] = A[i];
    }

    for (std::uint32_t i = 0; i < n; i++)
        A[i] = output[i];
}


//METODOS PUBLICOS

    // ===============================
    // ORDENAMIENTO POR SELECCIÓN
    // ===============================

    void Ordenador::ordenamientoPorSeleccion(std::uint32_t *A, std::uint32_t n) const {
  
        for (std::uint32_t i = 0; i < n - 1; i++) {
            std::uint32_t minIdx = i;
            for (std::uint32_t j = i + 1; j < n; j++) {
                if (A[j] < A[minIdx]) {
                    minIdx = j;
                }
            }
            std::swap(A[i], A[minIdx]);
        }
    }

    // ===============================
    // ORDENAMIENTO POR INSERCIÓN
    // ===============================

    void Ordenador::ordenamientoPorInserccion(std::uint32_t *A, std::uint32_t n) const {
  
        for (std::uint32_t i = 1; i < n; i++) {
            std::uint32_t key = A[i];
            std::int32_t j = i - 1; 
            while (j >= 0 && A[j] > key) {
                A[j + 1] = A[j];
                j--;
            }
            A[j + 1] = key;
        }
    }

    // ===============================
    // ORDENAMIENTO POR MEZCLA (MERGESORT)
    // ===============================

    void Ordenador::ordenamientoPorMezcla(std::uint32_t *A, std::uint32_t n) const {
        mergeSortAux(A, 0, n - 1);
    }

    // ===============================
    // ORDENAMIENTO POR MONTÍCULOS (HEAPSORT)
    // ===============================

    void Ordenador::ordenamientoPorMonticulos(std::uint32_t *A, std::uint32_t n) const {
        for (std::int32_t i = n / 2 - 1; i >= 0; i--) {
            heapify(A, n, i);
        }
        for (std::int32_t i = n - 1; i > 0; i--) {
            std::swap(A[0], A[i]);
            heapify(A, i, 0);
        }
    }

    // ===============================
    // ORDENAMIENTO RÁPIDO (QUICKSORT)
    // ===============================

    void Ordenador::ordenamientoRapido(std::uint32_t *A, std::uint32_t n) const {
        quickSortAux(A, 0, n - 1);
    }
  

    // ===============================
    // ORDENAMIENTO POR RESIDUOS (RADIX SORT)
    // ===============================

    void Ordenador::ordenamientoPorResiduos(std::uint32_t *A, std::uint32_t n) const {

        //Generar el r aplicando la fórmula
        // std::uint32_t r = static_cast<std::uint32_t>(std::floor(std::log2(n))); 

        std::uint32_t maxVal = A[0];
        for (std::uint32_t i = 1; i < n; i++)
            if (A[i] > maxVal) maxVal = A[i];
    
        std::uint32_t r = 16; //Acá cambio el valor de r para probar
        cout << "r= " << r;
    
        std::uint32_t b = 32; 
        std::uint32_t d = (b + r - 1) / r;
    
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

