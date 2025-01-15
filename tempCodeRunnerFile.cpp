#include "BST.h"
#include <iostream>

int main() {
    BST tree;
    tree.insert(Student(1, "Alice", 2023, 3.8));
    tree.insert(Student(2, "Bob", 2022, 3.5));
    tree.insert(Student(3, "Charlie", 2021, 3.9));
    tree.insert(Student(4, "samiro", 2022, 3.3));
    std::cout << "Current Tree Structure:\n";
    tree.display();
    std::cout << "\nSearching for Student with ID 2:\n";
    tree.search(2);
    std::cout << "\nRemoving Student with ID 2...\n";
    tree.remove(2);
    std::cout << "\nCurrent Tree Structure:\n";
    tree.display();
    return 0;
}