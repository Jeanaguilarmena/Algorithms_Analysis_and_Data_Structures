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
  size_t size;

  std::vector<DataType> table;
};
