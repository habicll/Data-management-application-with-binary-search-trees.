#include "BST.h"
#include <iostream>

void displayMenu() {
    std::cout << "\nMenu:\n";
    std::cout << "1. Insert Student\n";
    std::cout << "2. Search for Student by ID\n";
    std::cout << "3. Remove Student by ID\n";
    std::cout << "4. Display Tree Structure\n";
    std::cout << "5. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    BST tree;
    int choice;
    while (true) {
        displayMenu();
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();  // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore invalid input
            std::cout << "Invalid input! Please enter a number between 1 and 5.\n";
            continue;
        }

        switch (choice) {
        case 1: {
            int id, year;
            std::string name;
            float gpa;
            std::cout << "Enter Student ID: ";
            std::cin >> id;
            std::cout << "Enter Student Name: ";
            std::cin.ignore();  // Ignore newline character left in buffer
            std::getline(std::cin, name);
            std::cout << "Enter Year of Enrollment: ";
            std::cin >> year;
            std::cout << "Enter GPA: ";
            std::cin >> gpa;
            tree.insert(Student(id, name, year, gpa));
            break;
        }
        case 2: {
            int id;
            std::cout << "Enter Student ID to search: ";
            std::cin >> id;
            tree.search(id);
            break;
        }
        case 3: {
            int id;
            std::cout << "Enter Student ID to remove: ";
            std::cin >> id;
            tree.remove(id);
            break;
        }
        case 4:
            tree.display();
            break;
        case 5:
            std::cout << "Exiting program.\n";
            return 0;
        default:
            std::cout << "Invalid choice! Please enter a number between 1 and 5.\n";
        }
    }
}
