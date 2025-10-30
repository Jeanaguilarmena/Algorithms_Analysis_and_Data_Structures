#include "SinglyLinkedList.hpp"
#include "BinarySearchTree.hpp"
#include <iostream>
#include <random>
#include <chrono>

int main() {
    SLList<int> list;
    BSTree<int> bst;
    const int n = 1000000;
    const int e = 10000;

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 10*n - 1);


    auto t0 = std::chrono::steady_clock::now();

    // --- Inserción aleatoria ---
    for(int i = 0; i < n; ++i) {
        bst.insert(dist(rng));
        
    }
    auto t1 = std::chrono::steady_clock::now();
    std::cout << "Inserción aleatoria: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count()
              << " ms" << std::endl;

    // --- Búsquedas aleatorias ---
    int found = 0;
    t0 = std::chrono::steady_clock::now();
    for(int i = 0; i < e; ++i) {
        auto node = bst.search(bst.getRoot(), dist(rng));
        if (node) {
            ++found;
        }
    }
   
    t1 = std::chrono::steady_clock::now();
    std::cout << "Elementos encontrados: " << found << std::endl;
    std::cout << "Búsqueda: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count()
              << " ms" << std::endl;

    // --- Eliminaciones aleatorias ---
    t0 = std::chrono::steady_clock::now();
    for(int i = 0; i < e; ++i) {
        bst.remove(dist(rng));
    }
    t1 = std::chrono::steady_clock::now();
    std::cout << "Eliminación: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count()
              << " ms\n";

    // list.printList();
    return 0;
}
