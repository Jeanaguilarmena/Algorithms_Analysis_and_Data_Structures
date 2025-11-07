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
  private:
    BSTreeNode<DataType>* buildBalancedTree(long long start, long long end, BSTreeNode<DataType>* parent);
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
  root = nullptr;
}


template <typename DataType>
void BSTree<DataType>::insert(const DataType &value) {
  BSTreeNode<DataType>* newNode = new BSTreeNode<DataType>(value);
  BSTreeNode<DataType>* parent = nullptr;
  BSTreeNode<DataType>* current = root;

  while (current) {
    parent = current;
    if (value == current->getKey()) {
      delete newNode;  
      return;
    } else if (value < current->getKey()) {
      current = current->getLeft();
    } else {
      current = current->getRight();
    }
  }

  newNode->setParent(parent);

  if (!parent) {  
    root = newNode;
  } else if (value < parent->getKey()) {
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
  if (n == 0) { root = nullptr; return; }
  root = buildBalancedTree(0LL, static_cast<long long>(n) - 1LL, nullptr);
}

template <typename DataType>
BSTreeNode<DataType>* BSTree<DataType>::buildBalancedTree(long long start, long long end, BSTreeNode<DataType>* parent) {
    if (start > end) return nullptr;

    long long mid = start + (end - start) / 2; 
    BSTreeNode<DataType>* node = new BSTreeNode<DataType>(static_cast<DataType>(mid));
    node->setParent(parent);

    node->setLeft(buildBalancedTree(start, mid - 1, node));
    node->setRight(buildBalancedTree(mid + 1, end, node));

    return node;
}




#include <stack>

template <typename DataType>
void BSTree<DataType>::inorderWalk(BSTreeNode<DataType>* rootOfSubTree) const {
  std::stack<BSTreeNode<DataType>*> stack;
  BSTreeNode<DataType>* current = rootOfSubTree;

  while (current != nullptr || !stack.empty()) {
    while (current != nullptr) {
      stack.push(current);
      current = current->getLeft();
    }

    current = stack.top();
    stack.pop();
    std::cout << current->getKey() << " ";

    current = current->getRight();
  }
}

template <typename DataType>
void BSTree<DataType>::preorderWalk(BSTreeNode<DataType>* rootOfSubTree) const {
  if (!rootOfSubTree) return;

  std::stack<BSTreeNode<DataType>*> stack;
  stack.push(rootOfSubTree);

  while (!stack.empty()) {
    BSTreeNode<DataType>* current = stack.top();
    stack.pop();

    std::cout << current->getKey() << " ";

    if (current->getRight())
      stack.push(current->getRight());
    if (current->getLeft())
      stack.push(current->getLeft());
  }
}

template <typename DataType>
void BSTree<DataType>::postorderWalk(BSTreeNode<DataType>* rootOfSubTree) const {
  if (!rootOfSubTree) return;

  std::stack<BSTreeNode<DataType>*> stack1, stack2;
  stack1.push(rootOfSubTree);

  while (!stack1.empty()) {
    BSTreeNode<DataType>* current = stack1.top();
    stack1.pop();
    stack2.push(current);

    if (current->getLeft())
      stack1.push(current->getLeft());
    if (current->getRight())
      stack1.push(current->getRight());
  }

  while (!stack2.empty()) {
    std::cout << stack2.top()->getKey() << " ";
    stack2.pop();
  }
}


template <typename DataType> 
void BSTree<DataType>::remove(const DataType &value) {
  BSTreeNode<DataType> *nodeToDelete = search(root, value);
  if (!nodeToDelete) return;  

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
