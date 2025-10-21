/*
 Credits
 Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 Modified by: Prof. Allan Berrocal, Universidad de Costa Rica
 */

#pragma once
#include <cstddef>

template <typename DataType>
class BSTree;

template <typename DataType>
class BSTreeNode {
 public:
  friend class BSTree<DataType>;
  BSTreeNode() = default;


  BSTreeNode(const DataType &value, BSTreeNode<DataType> *parent = nullptr,
             BSTreeNode<DataType> *left = nullptr,
             BSTreeNode<DataType> *right = nullptr);

  ~BSTreeNode();

  DataType getKey() const;

  BSTreeNode<DataType> *getParent() const;

  BSTreeNode<DataType> *getLeft() const;

  BSTreeNode<DataType> *getRight() const;

  void setParent(BSTreeNode<DataType> *parent);

  void setLeft(BSTreeNode<DataType> *left);

  void setRight(BSTreeNode<DataType> *right);

 private:
  DataType key;

  BSTreeNode<DataType> *parent = nullptr;

  BSTreeNode<DataType> *left = nullptr;

  BSTreeNode<DataType> *right = nullptr;
};

template <typename DataType>
class BSTree {
 public:
 //Preguntar al profe si puedo eliminar el default
  BSTree();

  ~BSTree() {};

  void insert(const DataType &value);

  void remove(const DataType &value);

  void inorderWalk(BSTreeNode<DataType> *rootOfSubtree) const;

  void preorderWalk(BSTreeNode<DataType> *rootOfSubtree) const;

  void postorderWalk(BSTreeNode<DataType> *rootOfSubtree) const;

  BSTreeNode<DataType> *search(const BSTreeNode<DataType> *rootOfSubtree,
                               const DataType &value) const;

  BSTreeNode<DataType> *getMinimum(
      const BSTreeNode<DataType> *rootOfSubtree) const;

  BSTreeNode<DataType> *getMaximum(
      const BSTreeNode<DataType> *rootOfSubtree) const;

  BSTreeNode<DataType> *getSuccessor(const BSTreeNode<DataType> *node) const;

  BSTreeNode<DataType> *getRoot() const;

  void fastInsert(size_t n);
  
 private:
  BSTreeNode<DataType> *root;
  void transplant(BSTreeNode<DataType> *u, BSTreeNode<DataType> *v);
};


//Implementacion del BSTNode
template <typename DataType>
BSTreeNode<DataType>::BSTreeNode(const DataType &value,
                                 BSTreeNode<DataType> *parent,
                                 BSTreeNode<DataType> *left,
                                 BSTreeNode<DataType> *right)
    : key(value), parent(parent), left(left), right(right) {}

template <typename DataType>
BSTreeNode<DataType>::~BSTreeNode() {}

template <typename DataType>
DataType BSTreeNode<DataType>::getKey() const {
  return this->key;
}

template <typename DataType>
BSTreeNode<DataType>* BSTreeNode<DataType>::getParent() const {
  return this->parent;
}

template <typename DataType>
BSTreeNode<DataType>* BSTreeNode<DataType>::getLeft() const {
  return this->left;
}

template <typename DataType>
BSTreeNode<DataType>* BSTreeNode<DataType>::getRight() const {
  return this->right;
}

template <typename DataType>
void BSTreeNode<DataType>::setParent(BSTreeNode<DataType>* parent) {
  this->parent = parent;
}

template <typename DataType>
void BSTreeNode<DataType>::setLeft(BSTreeNode<DataType>* left) {
  this->left = left;
}

template <typename DataType>
void BSTreeNode<DataType>::setRight(BSTreeNode<DataType>* right) {
  this->right = right;
}

//Implementación del BSTree

template <typename DataType>
BSTree<DataType>::BSTree() {
  nil = new RBTreeNode<DataType>();  
  nil->setColor(BLACK);              
  nil->setLeft(nil);
  nil->setRight(nil);
  nil->setParent(nil);
  root = nil;                        
}


//No permite insertar elementos duplicados
template <typename DataType>
void BSTree<DataType>::insert(const DataType &value) {
  BSTreeNode<DataType>* newNode = new BSTreeNode<DataType>(value);
  BSTreeNode<DataType>* parent = nullptr;
  BSTreeNode<DataType>* current = root;

  while(current) {
    parent = current;
    if (value == current->key) {
      delete newNode;
      return;
    } else if (value < current->value) {
      current = current->left;
    } else {
      current = current->right;
    }
    newNode->setParent(parent);
  }
  if (!parent) {
    root = newNode;
  } else if (value < newNode->getKey()){
    parent->setLeft(newNode);
  } else {
    parent->setRight(newNode);
  }
}

template <typename DataType>
BSTreeNode<DataType> *BSTree<DataType>::search(
    const BSTreeNode<DataType>* node, const DataType &value) const {
      while (node && value != node->getKey()) {
        if (value < node->getKey()) {
          node = node->getLeft();
        } else {
          node = node->getRight();
        }
      }
      return const_cast<BSTreeNode<DataType>*>(node);
    }

template <typename DataType>
BSTreeNode<DataType>* BSTree<DataType>::getMinimum(const BSTreeNode<DataType>* node) const {
  while (node && node->getLeft()) {
    node = node->getLeft();
  }
  return const_cast<BSTreeNode<DataType>*>(node);
}


template <typename DataType>
BSTreeNode<DataType>* BSTree<DataType>::getMaximum(const BSTreeNode<DataType>* node) const {
  while (node && node->getRight()) {
    node = node->getRight();
  }
  return const_cast<BSTreeNode<DataType>*>(node);
}

template <typename DataType>
BSTreeNode<DataType>* BSTree<DataType>::getSuccessor(const BSTreeNode<DataType>* node) const {
  if (node->getRight()) {
    return getMinimum(node->getRight());
  }
  BSTreeNode<DataType>* parent = node->getParent();
  while (parent && node == parent->getRight()) {
    node = parent;
    parent = parent->getParent();
  }
  return parent;
}

template <typename DataType>
BSTreeNode<DataType> *BSTree<DataType>::getRoot() const {
  return root;
}

template <typename DataType>
void BSTree<DataType>::fastInsert(size_t n) {
  for (size_t i = 1; 1 <= n; i++) {
    insert(static_cast<DataType>(i));
  }
}

template <typename DataType>
void BSTree<DataType>::inorderWalk(BSTreeNode<DataType>* rootOfSubTree) const {
  if (rootOfSubTree) {
    inorderWalk(rootOfSubTree->getLeft());
    std::cout << rootOfSubTree->getKey() << " ";
    inorderWalk(rootOfSubTree->getRight());
  }
}

template <typename DataType>
void BSTree<DataType>::preorderWalk(BSTreeNode<DataType>* rootOfSubTree) const {
  if (rootOfSubTree) {
    std::cout << rootOfSubTree->getKey() << " ";
    preorderWalk(rootOfSubTree->getLeft());
    preorderWalk(rootOfSubTree->getRight());
  }
}

template <typename DataType>
void BSTree<DataType>::postorderWalk(BSTreeNode<DataType>* rootOfSubTree) const {
  if (rootOfSubTree) {
    postorderWalk(rootOfSubTree->getLeft());
    postorderWalk(rootOfSubTree->getRight());
    std::cout << rootOfSubTree->getKey() << " ";
  }
}

template <typename DataType> 
void BSTree<DataType>::remove(const DataType &value) {
  BSTreeNode<DataType> *nodeToDelete = search(root, value);
  if (!nodeToDelete) return;  // no existe

  if (nodeToDelete->getLeft() == nullptr)
    transplant(nodeToDelete, nodeToDelete->getRight());
  else if (nodeToDelete->getRight() == nullptr)
    transplant(nodeToDelete, nodeToDelete->getLeft());
  else {
    BSTreeNode<DataType> *successor = getMinimum(nodeToDelete->getRight());
    if (successor->getParent() != nodeToDelete) {
      transplant(successor, successor->getRight());
      successor->setRight(nodeToDelete->getRight());
      if (successor->getRight())
        successor->getRight()->setParent(successor);
    }
    transplant(nodeToDelete, successor);
    successor->setLeft(nodeToDelete->getLeft());
    if (successor->getLeft())
      successor->getLeft()->setParent(successor);
  }
  delete nodeToDelete;
}

template <typename DataType>
void BSTree<DataType>::transplant(BSTreeNode<DataType> *u,
                                  BSTreeNode<DataType> *v) {
  if (u->getParent() == nullptr)
    root = v;
  else if (u == u->getParent()->getLeft())
    u->getParent()->setLeft(v);
  else
    u->getParent()->setRight(v);
  if (v != nullptr)
    v->setParent(u->getParent());
}
