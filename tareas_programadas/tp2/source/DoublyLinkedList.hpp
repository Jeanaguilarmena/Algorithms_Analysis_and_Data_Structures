/*
 Credits
 Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 Modified by: Prof. Allan Berrocal, Universidad de Costa Rica
 */

#pragma once
template <typename DataType>
class DLList;

template <typename DataType>
class DLListNode {
 public:
  friend class DLList<DataType>;

  DLListNode() = default;

  DLListNode(const DataType& value, DLListNode<DataType>* next = nullptr,
             DLListNode<DataType>* prev = nullptr);

  ~DLListNode() {};

  DataType getKey() const;

  DLListNode<DataType>* getPrev() const;

  DLListNode<DataType>* getNext() const;

  void setKey(DataType key);

  void setPrev(DLListNode<DataType>* prev);

  void setNext(DLListNode<DataType>* next);

 private:
  DataType key;

  DLListNode<DataType>* next;

  DLListNode<DataType>* prev;
};

template <typename DataType>
class DLList {
 public:
  DLList() = default;

  ~DLList() {};

  void insert(const DataType& value);

  DLListNode<DataType>* search(const DataType& value) const;

  void remove(const DataType& value);

  void remove(DLListNode<DataType>* node);

  DLListNode<DataType>* getNil() const;

 private:
  DLListNode<DataType>* nil;
};


// Implementación de DLList con nodo centinela
template <typename DataType>
DLListNode<DataType>::DLListNode(const DataType& value, DLListNode<DataType>* next, DLListNode<DataType>* prev)
    : key(value), next(next), prev(prev) {}

// Getters
template <typename DataType>
DataType DLListNode<DataType>::getKey() const {
    return key;
}

template <typename DataType>
DLListNode<DataType>* DLListNode<DataType>::getNext() const {
    return next;
}

template <typename DataType>
DLListNode<DataType>* DLListNode<DataType>::getPrev() const {
    return prev;
}

// Setters
template <typename DataType>
void DLListNode<DataType>::setKey(DataType key) {
    this->key = key;
}

template <typename DataType>
void DLListNode<DataType>::setNext(DLListNode<DataType>* next) {
    this->next = next;
}

template <typename DataType>
void DLListNode<DataType>::setPrev(DLListNode<DataType>* prev) {
    this->prev = prev;
}

// ------------------ DLList ------------------

// Constructor de la lista: crea el nodo centinela
template <typename DataType>
DLList<DataType>::DLList() {
    nil = new DLListNode<DataType>();
    nil->setNext(nullptr);
    nil->setPrev(nullptr);
}

// Destructor: elimina todos los nodos
template <typename DataType>
DLList<DataType>::~DLList() {
    DLListNode<DataType>* current = nil;
    while (current) {
        DLListNode<DataType>* nodeToDelete = current;
        current = current->getNext();
        delete nodeToDelete;
    }
}

// Insertar al inicio (no permite duplicados)
template <typename DataType>
void DLList<DataType>::insert(const DataType& value) {
    if (!search(value)) {
        DLListNode<DataType>* first = nil->getNext();
        DLListNode<DataType>* newNode = new DLListNode<DataType>(value, first, nil);
        nil->setNext(newNode);
        if (first) {
            first->setPrev(newNode);
        }
    }
}

// Buscar nodo por valor
template <typename DataType>
DLListNode<DataType>* DLList<DataType>::search(const DataType& value) const {
    DLListNode<DataType>* current = nil->getNext();
    while (current) {
        if (current->getKey() == value) {
            return current;
        }
        current = current->getNext();
    }
    return nullptr;
}

// Eliminar por valor
template <typename DataType>
void DLList<DataType>::remove(const DataType& value) {
    DLListNode<DataType>* node = search(value);
    if (node) {
        remove(node);
    }
}

// Eliminar por nodo
template <typename DataType>
void DLList<DataType>::remove(DLListNode<DataType>* node) {
    if (!node) return;

    DLListNode<DataType>* prevNode = node->getPrev();
    DLListNode<DataType>* nextNode = node->getNext();

    if (prevNode) prevNode->setNext(nextNode);
    if (nextNode) nextNode->setPrev(prevNode);

    delete node;
}

// Obtener el nodo centinela
template <typename DataType>
DLListNode<DataType>* DLList<DataType>::getNil() const {
    return nil;
}
