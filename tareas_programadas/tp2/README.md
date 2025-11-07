# Proyecto Programado 2 - Curso Análisis de Algoritmos

**Estudiante:** Jean Aguilar Mena B70134
**Curso:** Análisis de Algoritmos y Estructuras de Datos  
**Proyecto:** Programado 2

---

## 📌 Descripción General

El objetivo de este proyecto es implementar algunas de las estructuras de datos estudiadas en el curso, con el propósito de realizar experimentos de rendimiento sobre sus operaciones principales. Posteriormente, se analizarán los resultados obtenidos para **comparar la eficiencia teórica de las estructuras de datos** con los tiempos observados de forma empírica.

La idea es desarrollar en el estudiante la capacidad de evaluar el comportamiento real de diferentes estructuras, reflexionar sobre sus resultados y justificar si estos coinciden con lo esperado según la teoría.

---

## 🧠 Estructuras de Datos Implementadas

Las estructuras que se implementan y evalúan en este proyecto son:

| Estructura                              | Nombre                            |
| --------------------------------------- | --------------------------------- |
| Lista Simplemente Enlazada              | _Singly Linked List_              |
| Árbol de Búsqueda Binaria               | _Binary Search Tree (BST)_        |
| Árbol Rojinegro                         | _Red-Black Tree (RBT)_            |
| Tabla Hash con Encadenamiento           | _Hash Table with Chaining_        |
| Tabla Hash con Direccionamiento Abierto | _Hash Table with Open Addressing_ |

Cada estructura fue implementada desde cero, sin uso de bibliotecas externas que resolvieran directamente su funcionamiento, siguiendo la plantilla base brindada por el profesor.

---

## 🧪 Metodología Experimental

Para cada estructura de datos se realizarán pruebas de inserción, búsqueda y eliminación siguiendo el patrón descrito a continuación:

### 🔹 Inserción

- Se insertan **1,000,000 elementos** utilizando dos escenarios:
  1. **Inserción aleatoria**
  2. **Inserción en orden**
- Se registra el tiempo total de ejecución.

### 🔹 Búsqueda

- Se realizan **10,000 búsquedas** de elementos existentes.
- Se ejecutan tanto después de una inserción aleatoria como después de una inserción ordenada.
- Se mide el tiempo y se comparan los resultados.

### 🔹 Eliminación

- Se eliminan **10,000 elementos** que existen en la estructura.
- Se toman tiempos tanto para el caso aleatorio como para el caso ordenado.

> ✅ **Cada prueba se ejecuta 3 veces** y se utiliza el promedio para evitar sesgos y fluctuaciones en los tiempos.

---

## 📈 Lineamientos para el Análisis de Resultados

El informe debe incluir un análisis acompañado de gráficos, considerando los siguientes puntos:

### 1️⃣ Validación de Resultados vs Teoría

Identificar en cada gráfico si el comportamiento observado corresponde con la complejidad teórica esperada para cada estructura.

### 2️⃣ Comparación de Búsquedas

- Comparar los tiempos entre búsquedas con llaves aleatorias y ordenadas.
- Identificar qué estructuras tuvieron resultados significativamente mejores.
- Destacar aquellas que tomaron **la mitad del tiempo o menos** para realizar las búsquedas.
- Argumentar si estos resultados tienen sentido según la teoría.

### 3️⃣ Comparación de Eliminaciones

- Comparar los tiempos de eliminación con llaves aleatorias y ordenadas.
- Detectar si alguna estructura fue particularmente más eficiente.
- Señalar estructuras que tardaron **la mitad o menos** del tiempo que las restantes.
- Justificar si esto coincide con lo esperado teóricamente.

---

## 🚀 Ejecución del Proyecto

Para compilar y ejecutar el programa se utiliza `make`.

```bash
# Compilar el proyecto
make

# Ejecutar el proyecto
make run
```
