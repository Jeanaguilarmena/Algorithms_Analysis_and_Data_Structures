#pragma once
#include <cstdint>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

/**
 * @brief Clase que implementa distintos algoritmos de ordenamiento.
 * 
 * La clase Ordenador cuenta con algoritmos clásicos de ordenamiento
 * (selección, inserción, mezcla, montículos, rápido y por residuos),
 * además de métodos auxiliares privados que apoyan su implementación.
 * 
 * @authors 
 * - Prof. Arturo Camacho, ECCI-Universidad de Costa Rica
 * - Modificado por Prof. Allan Berrocal, ECCI-Universidad de Costa Rica
 */
class Ordenador {
private:
    // ===============================
    // AUXILIARES MERGESORT
    // ===============================

    /**
     * @brief Método auxiliar de MergeSort que divide el arreglo y ordena recursivamente.
     * 
     * @param A Arreglo a ordenar.
     * @param left Índice inicial del subarreglo.
     * @param right Índice final del subarreglo.
     */
    void mergeSortAux(std::uint32_t *A, std::uint32_t left, std::uint32_t right) const;

    /**
     * @brief Mezcla dos subarreglos ordenados en uno solo.
     * 
     * @param A Arreglo a ordenar.
     * @param left Índice inicial del subarreglo izquierdo.
     * @param mid Índice medio del arreglo.
     * @param right Índice final del subarreglo derecho.
     */
    void merge(std::uint32_t *A, std::uint32_t left, std::uint32_t mid, std::uint32_t right) const;

    // ===============================
    // AUXILIARES HEAPSORT
    // ===============================

    /**
     * @brief Ajusta un subárbol para mantener la propiedad de heap máximo.
     * 
     * @param A Arreglo que representa el heap.
     * @param n Tamaño del heap.
     * @param i Índice del nodo a ajustar.
     */
    void heapify(std::uint32_t *A, std::uint32_t n, std::uint32_t i) const;

    // ===============================
    // AUXILIARES QUICKSORT
    // ===============================

    /**
     * @brief Método auxiliar de QuickSort que ordena recursivamente.
     * 
     * @param A Arreglo a ordenar.
     * @param low Índice inicial del subarreglo.
     * @param high Índice final del subarreglo.
     */
    void quickSortAux(std::uint32_t *A, std::uint32_t low, std::uint32_t high) const;

    /**
     * @brief Función de partición para QuickSort.
     * 
     * @param A Arreglo a ordenar.
     * @param low Índice inicial.
     * @param high Índice final.
     * @return std::uint32_t Índice del pivote después de la partición.
     */
    std::uint32_t partition(std::uint32_t *A, std::uint32_t low, std::uint32_t high) const;

    // ===============================
    // AUXILIARES RADIX SORT
    // ===============================

    /**
     * @brief Aplica Counting Sort a un dígito específico (para Radix Sort).
     * 
     * @param A Arreglo a ordenar.
     * @param n Tamaño del arreglo.
     * @param r Cantidad de bits usados por dígito.
     * @param shift Desplazamiento de bits para el dígito actual.
     */
    void countingSortByDigit(std::uint32_t *A, std::uint32_t n, std::uint32_t r, std::uint32_t shift) const;

public:
    /// Constructor por defecto.
    Ordenador() = default;

    /// Destructor por defecto.
    ~Ordenador() = default;

    /**
     * @brief Ordena un arreglo usando Selección.
     * 
     * @param A Arreglo a ordenar.
     * @param n Tamaño del arreglo.
     */
    void ordenamientoPorSeleccion(std::uint32_t *A, std::uint32_t n) const;

    /**
     * @brief Ordena un arreglo usando Inserción.
     * 
     * @param A Arreglo a ordenar.
     * @param n Tamaño del arreglo.
     */
    void ordenamientoPorInserccion(std::uint32_t *A, std::uint32_t n) const;

    /**
     * @brief Ordena un arreglo usando MergeSort.
     * 
     * @param A Arreglo a ordenar.
     * @param n Tamaño del arreglo.
     */
    void ordenamientoPorMezcla(std::uint32_t *A, std::uint32_t n) const;

    /**
     * @brief Ordena un arreglo usando HeapSort.
     * 
     * @param A Arreglo a ordenar.
     * @param n Tamaño del arreglo.
     */
    void ordenamientoPorMonticulos(std::uint32_t *A, std::uint32_t n) const;

    /**
     * @brief Ordena un arreglo usando QuickSort.
     * 
     * @param A Arreglo a ordenar.
     * @param n Tamaño del arreglo.
     */
    void ordenamientoRapido(std::uint32_t *A, std::uint32_t n) const;

    /**
     * @brief Ordena un arreglo usando Radix Sort (por residuos).
     * 
     * @param A Arreglo a ordenar.
     * @param n Tamaño del arreglo.
     */
    void ordenamientoPorResiduos(std::uint32_t *A, std::uint32_t n) const;

    /**
     * @brief Retorna un std::string con los datos de la tarea.
     * 
     * @return string Cadena con carné, nombre y tarea.
     */
    string ImprimirDatosDeTarea() const;
};
