#include <cstdint>
#pragma once
using namespace std;
#include <cstdint>
#include <vector>
#include <algorithm>
#include <iostream>

/*
Credits
Author: Prof. Arturo Camacho, ECCI-Universidad de Costa Rica
 
Modified by: Prof. Allan Berrocal, ECCI-Universidad de Costa Rica
*/

class Ordenador {
    private:
    // ===============================
    // AUXILIARES MERGESORT
    // ===============================
    void mergeSortAux(std::uint32_t *A, std::uint32_t left, std::uint32_t right) const;

    void merge(std::uint32_t *A, std::uint32_t left, std::uint32_t mid, std::uint32_t right) const;

    // ===============================
    // AUXILIARES HEAPSORT
    // ===============================
    void heapify(std::uint32_t *A, std::uint32_t n, std::uint32_t i) const;

    // ===============================
    // AUXILIARES QUICKSORT
    // ===============================
    void quickSortAux(std::uint32_t *A, std::uint32_t low, std::uint32_t high) const;

    std::uint32_t partition(std::uint32_t *A, std::uint32_t low, std::uint32_t high) const;

    // ===============================
    // AUXILIARES RADIX SORT (RESIDUOS)
    // ===============================
   void countingSortByDigit(std::uint32_t *A, std::uint32_t n, std::uint32_t r, std::uint32_t shift) const;


    public:
    Ordenador() = default;
    ~Ordenador() = default;
    /* Nota:
     - Si no planea implementar algunos de los métodos de ordenamiento, no los borre.
     - Simplemente déjelos con el cuerpo vacío para evitar errores de compilación, ya
       que se ejecutará el mismo main para todas las tareas.
     - Recuerde hacer uso de programación defensiva y documentar los métodos con formato Doxygen, por ejemplo.
     - No cambié la firma de los métodos de la clase Ordenador.
     - No lance excepciones para el manejo de errores.
       Ante un error, basta con que el método no modifique el arreglo original y que no cause la caída del programa.
    */ 

    void ordenamientoPorSeleccion(std::uint32_t *A, std::uint32_t n) const;
    void ordenamientoPorInserccion(std::uint32_t *A, std::uint32_t n) const;
    void ordenamientoPorMezcla(std::uint32_t *A, std::uint32_t n) const;
    void ordenamientoPorMonticulos(std::uint32_t *A, std::uint32_t n) const;
    void ordenamientoRapido(std::uint32_t *A, std::uint32_t n) const;
    void ordenamientoPorResiduos(std::uint32_t *A, std::uint32_t n) const;
    string ImprimirDatosDeTarea() const;

    /**
     * @brief Retorna un std::string con los datos de la tarea.
     * 
     * Este método devuelve una cadena de texto que contiene el carné, nombre y tarea.
     * 
     * @return std::string Una cadena de texto con los datos de la tarea.
     */
    constexpr const char* imprimirDatosDeTarea() const {
      return "Carné: 12345, Nombre: ABC, Tarea 1";
    } 

};
