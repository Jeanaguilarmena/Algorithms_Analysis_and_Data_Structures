/*
 Credits
 Modified by: Prof. Allan Berrocal, Universidad de Costa Rica
 */

#pragma once
#include <cstdint>
#include <vector>

template <typename DataType>

class OpenAddressHashTable {
 public:
  OpenAddressHashTable(size_t size) {};

  ~OpenAddressHashTable() {};

  void insert(const DataType& value);

  size_t search(const DataType& value) const;

  void remove(const DataType& value);

  size_t getSize() const;

 private:
 enum State { EMPTY, OCCUPIED, DELETED };
 //aca agrego algun metodo auxiliar si es necesario
  size_t size;

  std::vector<DataType> table;
  std::vector<State> state;
  size_t count;

  //Metodos auxiliares
  uint32_t keyFromValue(const DataType& value) const;
  size_t hashFunction(uint32_t key) const;
  size_t probe(size_t h, size_t i) const;
};

// Implementation

template <typename DataType>
OpenAddressHashTable<DataType>::OpenAddressHashTable(size_t size) {
  this->size = size;
  table.resize(size);
  state.resize(size, EMPTY);
  count = 0;
}

template <typename DataType>
OpenAddressHashTable<DataType>::~OpenAddressHashTable() {}

template <typename DataType>
uint32_t OpenAddressHashTable<DataType>::keyFromValue(const DataType& value) const {
  return (uint32_t)value;
}

template <typename DataType>
size_t OpenAddressHashTable<DataType>::hashFunction(uint32_t key) const {
  // Método Middle-Squared + Secuencia de Weyl
  const unsigned long long WEYL = 0xB5AD4ECEDA1CE2A9ULL;
  unsigned long long k = (unsigned long long)key;

  k = k * k;         // Elevar al cuadrado
  k = k + WEYL;      // Sumar secuencia Weyl

  // Extraer los 20 bits del centro
  unsigned long long middle = (k >> 22) & ((1ULL << 20) - 1);

  // Reducir por el tamaño de la tabla
  return (size_t)(middle % size);
}

template <typename DataType>
size_t OpenAddressHashTable<DataType>::probe(size_t h, size_t i) const {
  // Sondeo cuadrático: (h + i + i^2) mod size
  return (h + i + i * i) % size;
}

template <typename DataType>
void OpenAddressHashTable<DataType>::insert(const DataType& value) {
  if (count == size) return;  // tabla llena, no hace nada

  uint32_t key = keyFromValue(value);
  size_t h = hashFunction(key);
  int firstDeleted = -1;

  for (size_t i = 0; i < size; i++) {
    size_t pos = probe(h, i);

    if (state[pos] == EMPTY) {
      if (firstDeleted != -1) pos = firstDeleted;
      table[pos] = value;
      state[pos] = OCCUPIED;
      count++;
      return;
    }

    if (state[pos] == DELETED && firstDeleted == -1) {
      firstDeleted = (int)pos;
    }

    if (state[pos] == OCCUPIED && table[pos] == value) {
      return;  // ya existe, no insertar duplicado
    }
  }

  if (firstDeleted != -1) {
    table[firstDeleted] = value;
    state[firstDeleted] = OCCUPIED;
    count++;
  }
}

template <typename DataType>
size_t OpenAddressHashTable<DataType>::search(const DataType& value) const {
  uint32_t key = keyFromValue(value);
  size_t h = hashFunction(key);

  for (size_t i = 0; i < size; i++) {
    size_t pos = probe(h, i);

    if (state[pos] == EMPTY) {
      return (size_t)-1;  // no encontrado
    }

    if (state[pos] == OCCUPIED && table[pos] == value) {
      return pos;
    }
  }
  return (size_t)-1;
}

template <typename DataType>
void OpenAddressHashTable<DataType>::remove(const DataType& value) {
  size_t pos = search(value);

  if (pos != (size_t)-1) {
    state[pos] = DELETED;  // eliminación lógica
    count--;
  }
}

template <typename DataType>
size_t OpenAddressHashTable<DataType>::getSize() const {
  return count;
}