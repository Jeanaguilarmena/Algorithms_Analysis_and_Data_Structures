#include <iostream>
#include <random>
#include <chrono>
#include "printer.hpp"
#include "Student.hpp"

int main() {
    Printer<int> printer;
    printer.printSinglyLinkedListData();
    printer.printBinarySearchTreeData();
    printer.printRedBlackTreeData();
    printer.printChainedHashTableData();
    printer.printOpenAddressHashTableData();
    std::string student = imprimirDatosDeTarea();
    std::cout << student << std::endl;

    return 0;
}








