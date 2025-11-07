/*
 Credits
 Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 Modified by: Prof. Allan Berrocal, Universidad de Costa Rica
 */

#pragma once
#include <cstdint>
#include <vector>
#include "DoublyLinkedList.hpp"

template <typename DataType>

class ChainedHashTable {
 public:
  // ChainedHashTable(size_t size) {}; // Cambie el constructor, para agregar la definición
  ChainedHashTable(size_t size);

  // ~ChainedHashTable() {};
  ~ChainedHashTable(); // Cambie el destructor, para agregar la definición

  void insert(const DataType& value);

  DLListNode<DataType>* search(const DataType& value) const;

  void remove(const DataType& value);

  size_t getSize() const;
  size_t getCollisionCount() const;
  void resetCollisionCount();

 private:
  size_t size;
  size_t count;
  std::vector<DLList<DataType>> table;
  size_t collisionCount;

  //Metodos auxiliares
  uint32_t keyFromValue(const DataType& value) const;
  size_t hashFunction(uint32_t key) const;
};

// Implementation

template <typename DataType>
ChainedHashTable<DataType>::ChainedHashTable(size_t size) {
  this->size = size;
  table.resize(size);
  count = 0;
  collisionCount = 0;
}

template <typename DataType>
ChainedHashTable<DataType>::~ChainedHashTable() {}


template <typename DataType>
uint32_t ChainedHashTable<DataType>::keyFromValue(const DataType& value) const {
  return (uint32_t)value;
}

template <typename DataType>
size_t ChainedHashTable<DataType>::hashFunction(uint32_t key) const {
  return key % size;
}

template <typename DataType>
void ChainedHashTable<DataType>::insert(const DataType& value) {
  uint32_t key = keyFromValue(value);
  size_t index = hashFunction(key);

  if (!table[index].isEmpty()) {
    collisionCount++;
  }

  if (!table[index].search(value)) {
    table[index].insert(value);
    count++;
  }
}

template <typename DataType>
DLListNode<DataType>* ChainedHashTable<DataType>::search(const DataType& value) const {
  uint32_t key = keyFromValue(value);
  size_t index = hashFunction(key);

  if (table[index].size() > 1) {
    const_cast<ChainedHashTable<DataType>*>(this)->collisionCount++;
  } 

  return table[index].search(value);  
}

template <typename DataType>
void ChainedHashTable<DataType>::remove(const DataType& value) {
  uint32_t key = keyFromValue(value);
  size_t index = hashFunction(key);

  if (table[index].size() > 1) {
    collisionCount++;
  }

  DLListNode<DataType>* node = table[index].search(value);
  if (node) {
    table[index].remove(node);
    count--;
  }
}

template <typename DataType>
size_t ChainedHashTable<DataType>::getSize() const {
  return count;
}

template <typename DataType>
size_t ChainedHashTable<DataType>::getCollisionCount() const {
  return collisionCount;
}

template <typename DataType>
void ChainedHashTable<DataType>::resetCollisionCount() {
  collisionCount = 0;
}
