# Proyecto Programado 1 - Curso Análisis de Algoritmos

**Estudiante:** Jean Aguilar Mena  
**Curso:** Análisis de Algoritmos  
**Proyecto:** Programado 1

---

## Descripción del proyecto

El objetivo de este proyecto fue implementar y experimentar con distintos algoritmos de ordenamiento vistos en el curso, para analizar su comportamiento tanto teórico como práctico. Los algoritmos desarrollados incluyen:

- Selection Sort
- Insertion Sort
- Merge Sort
- Heap Sort
- Quick Sort
- Radix Sort

La meta principal fue que el estudiante pudiera **comparar la eficiencia teórica de cada algoritmo con la eficiencia observada en los experimentos**, identificar fortalezas y limitaciones prácticas, y reflexionar sobre los factores que afectan su desempeño en diferentes escenarios.

Para ello, se trabajó con arreglos de distintos tamaños, desde **1,000 hasta 1,000,000 de elementos**, generando números pseudoaleatorios para garantizar condiciones consistentes entre los distintos algoritmos. Los resultados de cada experimento se documentan en un **reporte de investigación** que incluye planteamiento del problema, diseño experimental, análisis de resultados y conclusiones.

---

## Estructura del proyecto

El proyecto está organizado en tres archivos principales:

1. **`Ordenador.hpp`**:  
   Define la clase `Ordenador` con los métodos públicos para cada algoritmo de ordenamiento y sus métodos auxiliares privados. También contiene documentación detallada de cada función.

2. **`Ordenador.cpp`**:  
   Implementa todos los métodos definidos en el `.hpp`, incluyendo algoritmos y funciones auxiliares como partición para QuickSort, heapify para HeapSort, merge para MergeSort y counting sort para Radix Sort.

3. **`main.cpp`**:
   - Crea una instancia de la clase `Ordenador`.
   - Incluye funciones para:
     - Generar arreglos aleatorios (`generarArrayRandom`).
     - Guardar y cargar arreglos desde archivos `.txt` (`guardarArrayTXT` y `cargarArrayTXT`).
   - Contiene una sección inicial opcional para generar y guardar los arreglos antes de ejecutar los algoritmos. Esta sección **debe ejecutarse primero** para asegurar que todos los algoritmos trabajen sobre los mismos datos. Posteriormente, se comenta esta sección y se ejecuta la prueba de los algoritmos para obtener los resultados.

---

## Uso del proyecto

1. **Compilación:**  
   El proyecto incluye un `Makefile`. Para compilar, ejecutar:
   ```bash
   make
   ```
2. **Ejecución:**
   Esto genera un archivo ejecutable que se llama programa, por lo que para correrlo sería:
   ```
   ./programa
   ```
