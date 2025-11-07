//Esta es una clase para imprimir todos los elementos de las estructuras de datos especificas y no tenerlo todo 
//en el main

#include "ChainedHashTable.hpp"
#include "OpenAddressHashTable.hpp"
#include <iostream>
#include <random>
#include <chrono>

template <typename DataType>
class Printer {
    public:
        void printSinglyLinkedListData();
        void printBinarySearchTreeData();
        void printRedBlackTreeData();
        void printChainedHashTableData();
        void printOpenAddressHashTableData();
};

// Implementación de los métodos de impresión
template <typename DataType>
void Printer<DataType>::printSinglyLinkedListData() {
    std::cout << "=============== Singly Linked List ===============" << std::endl;
    // const int n = 1000000; //Si se quiere probar con el tamaño original, descomentar estas líneas
    // const int e = 10000;
    const int n = 100000; //Voy a dejar estos para que en caso de prueba, no tarde tanto
    const int e = 1000;

    SLList<int> list;
    
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 10*n - 1);

    auto t0 = std::chrono::steady_clock::now();

    //Inserción aleatoria 
    for(int i = 0; i < n; ++i) {
        list.insert(dist(rng));
        // list.insert(i);   
    }

    auto t1 = std::chrono::steady_clock::now();
    std::cout << "Inserción aleatoria: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count()
              << " ms" << std::endl;

    //Búsquedas aleatorias 
    int found = 0;
    t0 = std::chrono::steady_clock::now();

    for (int i = 0; i < e; ++i) {
        auto node = list.search(dist(rng));
        if (node != nullptr)
            ++found;
    }
   
    t1 = std::chrono::steady_clock::now();
    std::cout << "Elementos encontrados: " << found << std::endl;
    std::cout << "Búsqueda: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count()
              << " ms" << std::endl;

    //Eliminaciones aleatorias
    t0 = std::chrono::steady_clock::now();
    for(int i = 0; i < e; ++i) {
        list.remove(dist(rng));
    }
    t1 = std::chrono::steady_clock::now();
    std::cout << "Eliminación: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count()
              << " ms" << std::endl;


    std::cout << "===============================================================" << std::endl;
    std::cout << std::endl;
}

template <typename DataType>
void Printer<DataType>::printBinarySearchTreeData() {
    std::cout << "=============== Binary Search Tree ===============" << std::endl;
    const int n = 1000000;
    const int e = 10000;

    BSTree<int> bst;
    
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 10*n - 1);

    auto t0 = std::chrono::steady_clock::now();

    //Inserción aleatoria
    for(int i = 0; i < n; ++i) {
        bst.insert(dist(rng));   
    }

    // bst.fastInsert(n); // Inserción rápida de n elementos ordenados

    auto t1 = std::chrono::steady_clock::now();
    std::cout << "Inserción aleatoria: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count()
              << " ms" << std::endl;

    //Búsquedas aleatorias
    int found = 0;
    t0 = std::chrono::steady_clock::now();
    for(int i = 0; i < e; ++i) {
        auto node = bst.search(bst.getRoot(), dist(rng));
        if (node != nullptr) {
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
              << " ms" << std::endl;

    std::cout << "===============================================================" << std::endl;
    std::cout << std::endl;

}

template <typename DataType>
void Printer<DataType>::printRedBlackTreeData() {
    std::cout << "=============== Red-Black Tree ===============" << std::endl;
    const int n = 1000000;
    const int e = 10000;

    RBTree<int> rbt;
    
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 10*n - 1);

    auto t0 = std::chrono::steady_clock::now();

    //Inserción aleatoria
    for(int i = 0; i < n; ++i) {
        rbt.insert(dist(rng));   
        // rbt.insert(i);
    }

    auto t1 = std::chrono::steady_clock::now();
    std::cout << "Inserción aleatoria: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count()
              << " ms" << std::endl;

    //Búsquedas aleatorias 
    int found = 0;
    t0 = std::chrono::steady_clock::now();
    for(int i = 0; i < e; ++i) {
        auto node = rbt.search(rbt.getRoot(), dist(rng));
        if (node != rbt.getNil()) {
            ++found;
        }
    }
   
    t1 = std::chrono::steady_clock::now();
    std::cout << "Elementos encontrados: " << found << std::endl;
    std::cout << "Búsqueda: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count()
              << " ms" << std::endl;

    //Eliminaciones aleatorias 
    t0 = std::chrono::steady_clock::now();
    for(int i = 0; i < e; ++i) {
        rbt.remove(dist(rng));
    }
    t1 = std::chrono::steady_clock::now();
    std::cout << "Eliminación: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count()
              << " ms" << std::endl;


    std::cout << "===============================================================" << std::endl;
    std::cout << std::endl;
}

template <typename DataType>
void Printer<DataType>::printChainedHashTableData() {
    std::cout << "=============== Chained Hash Table ===============" << std::endl;
    const int n = 1000000;  // número de llaves a insertar
    const int e = 10000;    // número de búsquedas/eliminaciones
    const size_t m = 1048575; // tamaño de la tabla (2^20 - 1)

    ChainedHashTable<int> hashTable(m);

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 10 * n - 1);

    //INSERCIÓN ALEATORIA 
    auto t0 = std::chrono::steady_clock::now();

    for (int i = 0; i < n; ++i) {
        hashTable.insert(dist(rng));
        // hashTable.insert(i);
    }

    auto t1 = std::chrono::steady_clock::now();
    std::cout << "Inserción aleatoria: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count()
              << " ms" << std::endl;

    std::cout << "Colisiones en inserción: " << hashTable.getCollisionCount() << std::endl << std::endl;

    //BÚSQUEDAS ALEATORIAS
    hashTable.resetCollisionCount(); // resetear antes de medir las búsquedas
    int found = 0;

    t0 = std::chrono::steady_clock::now();
    for (int i = 0; i < e; ++i) {
        auto pos = hashTable.search(dist(rng));
        if (pos != nullptr) ++found; 
    }         
    t1 = std::chrono::steady_clock::now();

    std::cout << "Elementos encontrados: " << found << std::endl;
    std::cout << "Búsqueda: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count()
              << " ms" << std::endl;
    std::cout << "Colisiones en búsqueda: " << hashTable.getCollisionCount() << std::endl << std::endl;

    //ELIMINACIONES ALEATORIAS
    hashTable.resetCollisionCount(); // resetear antes de medir eliminaciones
    t0 = std::chrono::steady_clock::now();

    for (int i = 0; i < e; ++i) {
        hashTable.remove(dist(rng));
    }

    t1 = std::chrono::steady_clock::now();
    std::cout << "Eliminación: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count()
              << " ms" << std::endl;
    std::cout << "Colisiones en eliminación: " << hashTable.getCollisionCount() << std::endl;


    std::cout << "===============================================================" << std::endl;
    std::cout << std::endl;
}



template <typename DataType>
void Printer<DataType>::printOpenAddressHashTableData() {
    std::cout << "=============== Open Address Hash Table ===============" << std::endl;
    const int n = 1000000;  // número de llaves a insertar
    const int e = 10000;    // número de búsquedas/eliminaciones
    const size_t m = 1048575; // tamaño de la tabla (2^20 - 1)

    OpenAddressHashTable<int> oaHashTable(m);

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 10 * n - 1);

    //INSERCIÓN ALEATORIA
    auto t0 = std::chrono::steady_clock::now();

    for (int i = 0; i < n; ++i) {
        oaHashTable.insert(dist(rng));
        // oaHashTable.insert(i);
    }

    auto t1 = std::chrono::steady_clock::now();
    std::cout << "Inserción aleatoria: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count()
              << " ms" << std::endl;

    std::cout << "Colisiones en inserción: " << oaHashTable.getCollisionCount() << std::endl << std::endl;

    //BÚSQUEDAS ALEATORIAS 
    oaHashTable.resetCollisionCount(); // resetear antes de medir las búsquedas
    int found = 0;

    t0 = std::chrono::steady_clock::now();
    for (int i = 0; i < e; ++i) {
        auto pos = oaHashTable.search(dist(rng));
        constexpr size_t NOT_FOUND = static_cast<size_t>(-1);
        if (pos != NOT_FOUND) ++found; 
    }         
    t1 = std::chrono::steady_clock::now();

    std::cout << "Elementos encontrados: " << found << std::endl;
    std::cout << "Búsqueda: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count()
              << " ms" << std::endl;
    std::cout << "Colisiones en búsqueda: " << oaHashTable.getCollisionCount() << std::endl << std::endl;

    //ELIMINACIONES ALEATORIAS 
    oaHashTable.resetCollisionCount(); // resetear antes de medir eliminaciones
    t0 = std::chrono::steady_clock::now();

    for (int i = 0; i < e; ++i) {
        oaHashTable.remove(dist(rng));
    }

    t1 = std::chrono::steady_clock::now();
    std::cout << "Eliminación: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count()
              << " ms" << std::endl;
    std::cout << "Colisiones en eliminación: " << oaHashTable.getCollisionCount() << std::endl;

    std::cout << "===============================================================" << std::endl;
    std::cout << std::endl;
}
