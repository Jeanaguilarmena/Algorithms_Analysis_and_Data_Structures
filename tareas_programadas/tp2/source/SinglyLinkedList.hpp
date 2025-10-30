/*
 Credits
 Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 Modified by: Prof. Allan Berrocal, Universidad de Costa Rica
*/
#include <iostream>
#pragma once
template <typename DataType>
class SLList;

template <typename DataType>
class SLListNode {
 public:
  friend class SLList<DataType>;

  SLListNode();

  SLListNode(const DataType& value, SLListNode<DataType>* next = nullptr);

  ~SLListNode();

  DataType getKey() const;

  SLListNode<DataType>* getNext() const;

  void setKey(DataType key);

  void setNext(SLListNode<DataType>* newNode);

 private:
  DataType key;

  SLListNode<DataType>* next;
};

template <typename DataType>
class SLList {
 public:
  // SLList() = default;
  SLList();

  // ~SLList() {};
  ~SLList();

  void insert(const DataType& value);

  SLListNode<DataType>* search(const DataType& value) const;

  void remove(const DataType& value);

  SLListNode<DataType>* getNil() const;

  void printList() const;
  
 private:
  SLListNode<DataType>* nil;

};

//Implementación de SLListNode
template <typename DataType>
SLListNode<DataType>::SLListNode() : key(DataType()), next(nullptr) {}

template <typename DataType>
SLListNode<DataType>::SLListNode(const DataType& value, SLListNode<DataType>* next) : key(value), next(next) {}

template <typename DataType>
SLListNode<DataType>::~SLListNode() {}

template <typename DataType>
DataType SLListNode<DataType>::getKey() const {
  return key;
}

template <typename DataType>
SLListNode<DataType>* SLListNode<DataType>::getNext() const {
  return next;
}

template <typename DataType>
void SLListNode<DataType>::setKey(DataType key) {
  this->key = key;
}

template <typename DataType>
void SLListNode<DataType>::setNext(SLListNode<DataType>* newNode) {
  this->next = newNode;
}

//Implementación de SLList con centinela
template <typename DataType>
SLList<DataType>::SLList() {
  nil = new SLListNode<DataType>();
  nil->setNext(nullptr);
}

//No permite insertar elementos duplicados e inserta al inicio de la lista
template <typename DataType>
// void SLList<DataType>::insert(const DataType& value) {
//   if (!search(value)) {
//     SLListNode<DataType>* newNode = new SLListNode<DataType>(value, nil->getNext());
//     nil->setNext(newNode);
//   }
// }

void SLList<DataType>::insert(const DataType& value) {
    SLListNode<DataType>* newNode = new SLListNode<DataType>(value, nil->getNext());
    nil->setNext(newNode);
  
}

template <typename DataType>
SLListNode<DataType>* SLList<DataType>::search(const DataType& value) const {
  SLListNode<DataType>* current = nil->getNext();
  while (current) {
    if (current->getKey() == value) {
      return current;
    }
    current = current->getNext();
  }
  return nullptr;
}

template <typename DataType>
void SLList<DataType>::remove(const DataType& value) {
  SLListNode<DataType>* current = nil;
  while (current->getNext()) {
    if (current->getNext()->getKey() == value) {
      SLListNode<DataType>* nodeToDelete = current->getNext();
      current->setNext(nodeToDelete->getNext());
      delete nodeToDelete;
      return;
    }
    current = current->getNext();
  }
}

template <typename DataType>
SLListNode<DataType>* SLList<DataType>::getNil() const {
  return nil;
}

template <typename DataType>
SLList<DataType>::~SLList() {
  SLListNode<DataType>* current = nil;
  while (current) {
    SLListNode<DataType>* nodeToDelete = current;
    current = current->getNext();
    delete nodeToDelete;
  }
}

template <typename DataType>
void SLList<DataType>::printList() const {
  SLListNode<DataType>* current = nil->getNext();
  while (current) {
    std::cout << current->getKey() << " -> ";
    current = current->getNext();
  }
  std::cout << "nullptr" << std::endl;
}

