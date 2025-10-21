/*
 Credits
 Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 Modified by: Prof. Allan Berrocal, Universidad de Costa Rica
*/

#pragma once

enum colors { RED, BLACK };

template <typename DataType>
class RBTree;

template <typename DataType>
class RBTreeNode {
 public:
  friend class RBTree<DataType>;

  RBTreeNode() = default;

  RBTreeNode(const DataType &value, RBTreeNode<DataType> *parent = nullptr,
             RBTreeNode<DataType> *left = nullptr,
             RBTreeNode<DataType> *right = nullptr, enum colors c = RED);

  ~RBTreeNode();

  DataType getKey() const;

  RBTreeNode<DataType> *getParent() const;

  RBTreeNode<DataType> *getLeft() const;

  RBTreeNode<DataType> *getRight() const;

  void setKey(DataType key);

  void setParent(RBTreeNode<DataType> *parent);

  void setLeft(RBTreeNode<DataType> *left);

  void setRight(RBTreeNode<DataType> *right);

  void setColor(enum colors newColor);

 private:
  DataType key;

  RBTreeNode<DataType> *parent;

  RBTreeNode<DataType> *left;

  RBTreeNode<DataType> *right;

  enum colors color;
};


template <typename DataType>
class RBTree {
 public:
 //Preguntar al profe si se puede quitar el default
  // RBTree() = default;

  RBTree();

  ~RBTree() {}

  void insert(const DataType &value);

  void remove(const DataType &value);

  RBTreeNode<DataType> *search(const RBTreeNode<DataType> *rootOfSubtree,
                               const DataType &value) const;

  RBTreeNode<DataType> *getMinimum(
      const RBTreeNode<DataType> *rootOfSubtree) const;

  RBTreeNode<DataType> *getMaximum(
      const RBTreeNode<DataType> *rootOfSubtree) const;

  RBTreeNode<DataType> *getSuccessor(const RBTreeNode<DataType> *node) const;

  RBTreeNode<DataType> *getRoot() const;

  RBTreeNode<DataType> *getNil() const;


 private:
  RBTreeNode<DataType> *root;

  RBTreeNode<DataType> *nil;

  //METODOS AUXILIARES ARBOL ROJINEGRO
  void insertFixup(RBTreeNode<DataType>* z);
  void rightRotate(RBTreeNode<DataType>* y);
  void leftRotate(RBTreeNode<DataType>* x);
  void deleteFixup(RBTreeNode<DataType>* x);
  void transplant(RBTreeNode<DataType>* u, RBTreeNode<DataType>* v);
};


//Implementación de RBTreeNode
template <typename DataType>
RBTreeNode<DataType>::RBTreeNode(const DataType &value, RBTreeNode<DataType> *parent,
                                 RBTreeNode<DataType> *left,
                                 RBTreeNode<DataType> *right, enum colors c)
    : key(value), parent(parent), left(left), right(right), color(c) {}

template <typename DataType>
RBTreeNode<DataType>::~RBTreeNode() {}

template <typename DataType>
DataType RBTreeNode<DataType>::getKey() const {
  return key;
}

template <typename DataType>
RBTreeNode<DataType> *RBTreeNode<DataType>::getParent() const {
  return this->parent;
}

template <typename DataType>
RBTreeNode<DataType> *RBTreeNode<DataType>::getLeft() const {
  return this->left;
}

template <typename DataType>
RBTreeNode<DataType> *RBTreeNode<DataType>::getRight() const {
  return this->right;
}

template <typename DataType>
void RBTreeNode<DataType>::setParent(RBTreeNode<DataType>* parent) {
  this->parent = parent;
}

template <typename DataType>
void RBTreeNode<DataType>::setLeft(RBTreeNode<DataType>* left) {
  this->left = left;
}

template <typename DataType>
void RBTreeNode<DataType>::setRight(RBTreeNode<DataType>* right) {
  this->right = right;
}

template <typename DataType>
void RBTreeNode<DataType>::setColor(enum colors newColor) {
  this->color = newColor;
}

template <typename DataType>
void RBTreeNode<DataType>::setKey(DataType key) {
  this->key = key;
}

// Implementación de RBTree

template <typename DataType>
RBTree<DataType>::RBTree() {
  nil = new RBTreeNode<DataType>();  
  nil->setColor(BLACK);              
  nil->setLeft(nil);
  nil->setRight(nil);
  nil->setParent(nil);
  root = nil;                        
}


template <typename DataType>
RBTreeNode<DataType>* RBTree<DataType>::getRoot() const {
  return this->root;
}

template <typename DataType>
RBTreeNode<DataType>* RBTree<DataType>::getNil() const {
  return this->nil;
}

template <typename DataType>
RBTreeNode<DataType>* RBTree<DataType>::search(
    const RBTreeNode<DataType>* rootOfSubtree, const DataType &value) const {
      while (rootOfSubtree && value != rootOfSubtree->getKey()) {
        if (value < rootOfSubtree->getKey()) {
          rootOfSubtree = rootOfSubtree->getLeft();
        } else {
          rootOfSubtree = rootOfSubtree->getRight();
        }
      }
      return const_cast<RBTreeNode<DataType>*>(rootOfSubtree);
    }

template <typename DataType>
RBTreeNode<DataType>* RBTree<DataType>::getMinimum(
    const RBTreeNode<DataType>* rootOfSubTree) const {
      while (rootOfSubTree && rootOfSubTree->getLeft()) {
        rootOfSubTree = rootOfSubTree->getLeft()
      }
      return const_cast<RBTreeNode<DataType>*>(rootOfSubTree);
    }

template <typename DataType>

RBTreeNode<DataType>* RBTree<DataType>::getMaximum(
  const RBTreeNode<DataType>* rootOfSubTree) const {
    while (rootOfSubTree && rootOfSubTree->getRight()) {
      rootOfSubTree = rootOfSubTree->getRight()
    }
    return const_cast<RBTreeNode<DataType>*>(rootOfSubTree);
  }

template <typename DataType>
RBTreeNode<DataType>* RBTree<DataType>::getSuccessor(
    const RBTreeNode<DataType>* node) const {
      if (node->getRight()) {
        return getMinimum(node->getRight());
      }
      RBTreeNode<DataType>* parent = node->getParent();
      while (parent && node == parent->getRight()) {
        node = parent;
        parent = parent->getParent();
      }
      return parent;
    }

template <typename DataType>
void RBTree<DataType>::insert(const DataType &value) {
  RBTreeNode<DataType>* z = new RBTreeNode<DataType>(value, nil, nil, nil, RED);


  RBTreeNode<DataType>* y = nil;  
  RBTreeNode<DataType>* x = root; 

  while (x != nil) {
    y = x;
    if (z->getKey() < x->getKey()) {
      x = x->getLeft();
    } else {
      x = x->getRight();
    }
  }

  z->setParent(y);

  if (y == nil) {
    root = z; 
  } else if (z->getKey() < y->getKey()) {
    y->setLeft(z);
  } else {
    y->setRight(z);
  }

  z->setLeft(nil);
  z->setRight(nil);
  z->setColor(RED);

  insertFixup(z);
}

template <typename DataType>
void RBTree<DataType>::insertFixup(RBTreeNode<DataType>* z) {
  while (z->getParent()->color == RED) {

    if (z->getParent() == z->getParent()->getParent()->getLeft()) {
      RBTreeNode<DataType>* y = z->getParent()->getParent()->getRight(); // tío

      if (y->color == RED) {
        z->getParent()->setColor(BLACK);
        y->setColor(BLACK);
        z->getParent()->getParent()->setColor(RED);
        z = z->getParent()->getParent();
      } else {
        if (z == z->getParent()->getRight()) {
          z = z->getParent();
          leftRotate(z);
        }
        z->getParent()->setColor(BLACK);
        z->getParent()->getParent()->setColor(RED);
        rightRotate(z->getParent()->getParent());
      }
    }

    else {
      RBTreeNode<DataType>* y = z->getParent()->getParent()->getLeft();

      if (y->color == RED) {
        z->getParent()->setColor(BLACK);
        y->setColor(BLACK);
        z->getParent()->getParent()->setColor(RED);
        z = z->getParent()->getParent();
      } else {
        if (z == z->getParent()->getLeft()) {
          z = z->getParent();
          rightRotate(z);
        }
        z->getParent()->setColor(BLACK);
        z->getParent()->getParent()->setColor(RED);
        leftRotate(z->getParent()->getParent());
      }
    }
  }
  root->setColor(BLACK);
}

template <typename DataType>
void RBTree<DataType>::leftRotate(RBTreeNode<DataType>* x) {
  RBTreeNode<DataType>* y = x->getRight();
  x->setRight(y->getLeft());
  if (y->getLeft() != nil)
    y->getLeft()->setParent(x);

  y->setParent(x->getParent());

  if (x->getParent() == nil)
    root = y;
  else if (x == x->getParent()->getLeft())
    x->getParent()->setLeft(y);
  else
    x->getParent()->setRight(y);

  y->setLeft(x);
  x->setParent(y);
}
    
template <typename DataType>
void RBTree<DataType>::rightRotate(RBTreeNode<DataType>* y) {
  RBTreeNode<DataType>* x = y->getLeft();
  y->setLeft(x->getRight());
  if (x->getRight() != nil)
    x->getRight()->setParent(y);

  x->setParent(y->getParent());

  if (y->getParent() == nil)
    root = x;
  else if (y == y->getParent()->getRight())
    y->getParent()->setRight(x);
  else
    y->getParent()->setLeft(x);

  x->setRight(y);
  y->setParent(x);
}


template <typename DataType>
void RBTree<DataType>::transplant(RBTreeNode<DataType>* u, RBTreeNode<DataType>* v) {
    if (u->getParent() == nil) {
        root = v;
    } else if (u == u->getParent()->getLeft()) {
        u->getParent()->setLeft(v);
    } else {
        u->getParent()->setRight(v);
    }
    v->setParent(u->getParent());
}

template <typename DataType>
void RBTree<DataType>::remove(const DataType &value) {
    RBTreeNode<DataType>* z = search(root, value);
    if (z == nil) return;

    RBTreeNode<DataType>* y = z;
    enum colors yOriginalColor = y->color;
    RBTreeNode<DataType>* x = nullptr;

    if (z->getLeft() == nil) {
        x = z->getRight();
        transplant(z, z->getRight());
    } else if (z->getRight() == nil) {
        x = z->getLeft();
        transplant(z, z->getLeft());
    } else {
        y = getMinimum(z->getRight());
        yOriginalColor = y->color;
        x = y->getRight();
        if (y->getParent() != z) {
            transplant(y, y->getRight());
            y->setRight(z->getRight());
            y->getRight()->setParent(y);
        } else {
            x->setParent(y);
        }
        transplant(z, y);
        y->setLeft(z->getLeft());
        y->getLeft()->setParent(y);
        y->setColor(z->color);
    }

    if (yOriginalColor == BLACK) {
        deleteFixup(x);
    }

    delete z;
}

template <typename DataType>
void RBTree<DataType>::deleteFixup(RBTreeNode<DataType>* x) {
    while (x != root && x->color == BLACK) {
        if (x == x->getParent()->getLeft()) {
            RBTreeNode<DataType>* w = x->getParent()->getRight();            
            if (w->color == RED) {
                w->setColor(BLACK);
                x->getParent()->setColor(RED);
                leftRotate(x->getParent());
                w = x->getParent()->getRight();
            }            
            if (w->getLeft()->color == BLACK && w->getRight()->color == BLACK) {
                w->setColor(RED);
                x = x->getParent();
            } else {                
                if (w->getRight()->color == BLACK) {
                    w->getLeft()->setColor(BLACK);
                    w->setColor(RED);
                    rightRotate(w);
                    w = x->getParent()->getRight();
                }               
                w->setColor(x->getParent()->color);
                x->getParent()->setColor(BLACK);
                w->getRight()->setColor(BLACK);
                leftRotate(x->getParent());
                x = root;
            }
        } else { 
            RBTreeNode<DataType>* w = x->getParent()->getLeft();            
            if (w->color == RED) {
                w->setColor(BLACK);
                x->getParent()->setColor(RED);
                rightRotate(x->getParent());
                w = x->getParent()->getLeft();
            }            
            if (w->getRight()->color == BLACK && w->getLeft()->color == BLACK) {
                w->setColor(RED);
                x = x->getParent();
            } else {                
                if (w->getLeft()->color == BLACK) {
                    w->getRight()->setColor(BLACK);
                    w->setColor(RED);
                    leftRotate(w);
                    w = x->getParent()->getLeft();
                }                
                w->setColor(x->getParent()->color);
                x->getParent()->setColor(BLACK);
                w->getLeft()->setColor(BLACK);
                rightRotate(x->getParent());
                x = root;
            }
        }
    }
    x->setColor(BLACK);
}
