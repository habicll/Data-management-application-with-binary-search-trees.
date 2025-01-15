#ifndef BST_H
#define BST_H

#include "student.h"
#include <memory>

// Node class representing elements in the BST
class Node {
public:
    Student student;
    int height;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
    Node(const Student& student) : student(student), height(1), left(nullptr), right(nullptr) {}
};

// Binary Search Tree (BST) with AVL balancing
class BST {
public:
    void insert(const Student& student);
    void remove(int id);
    void search(int id) const;
    void display() const;

private:
    std::unique_ptr<Node> root;

    int getHeight(const std::unique_ptr<Node>& node) const;
    int getBalanceFactor(const std::unique_ptr<Node>& node) const;
    std::unique_ptr<Node> insert(std::unique_ptr<Node> node, const Student& student);
    std::unique_ptr<Node> remove(std::unique_ptr<Node> node, int id);
    Node* search(const std::unique_ptr<Node>& node, int id) const;
    std::unique_ptr<Node> rotateRight(std::unique_ptr<Node> y);
    std::unique_ptr<Node> rotateLeft(std::unique_ptr<Node> x);
};

#endif // BST_H
