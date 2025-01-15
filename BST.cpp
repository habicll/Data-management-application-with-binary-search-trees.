#include "BST.h"
#include <iostream>

// Returns the height of a given node, or 0 if the node is nullptr
int BST::getHeight(const std::unique_ptr<Node>& node) const {
    return node ? node->height : 0;
}

// Computes the balance factor for a node to determine if rotations are needed
int BST::getBalanceFactor(const std::unique_ptr<Node>& node) const {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// Performs a right rotation to balance the tree
std::unique_ptr<Node> BST::rotateRight(std::unique_ptr<Node> y) {
    auto x = std::move(y->left);
    y->left = std::move(x->right);
    x->right = std::move(y);
    x->right->height = std::max(getHeight(x->right->left), getHeight(x->right->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

// Performs a left rotation to balance the tree
std::unique_ptr<Node> BST::rotateLeft(std::unique_ptr<Node> x) {
    auto y = std::move(x->right);
    x->right = std::move(y->left);
    y->left = std::move(x);
    y->left->height = std::max(getHeight(y->left->left), getHeight(y->left->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

// Inserts a student into the tree, maintaining BST and AVL properties
std::unique_ptr<Node> BST::insert(std::unique_ptr<Node> node, const Student& student) {
    if (!node) return std::make_unique<Node>(student); // Base case: Insert new node
    if (student.id < node->student.id) {
        node->left = insert(std::move(node->left), student); // Recursive insert into left subtree
    } else if (student.id > node->student.id) {
        node->right = insert(std::move(node->right), student); // Recursive insert into right subtree
    } else {
        std::cerr << "Duplicate ID found: " << student.id << std::endl; // Handle duplicate IDs
        return node;
    }

    // Update height and check balance
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    int balance = getBalanceFactor(node);

    // Apply rotations if tree is unbalanced
    if (balance > 1 && student.id < node->left->student.id) return rotateRight(std::move(node));  // Left Left Case
    if (balance < -1 && student.id > node->right->student.id) return rotateLeft(std::move(node));  // Right Right Case
    if (balance > 1 && student.id > node->left->student.id) {                                     // Left Right Case
        node->left = rotateLeft(std::move(node->left));
        return rotateRight(std::move(node));
    }
    if (balance < -1 && student.id < node->right->student.id) {                                   // Right Left Case
        node->right = rotateRight(std::move(node->right));
        return rotateLeft(std::move(node));
    }
    return node;
}

// Public wrapper function for inserting a student
void BST::insert(const Student& student) {
    root = insert(std::move(root), student);
}

// Recursive helper function for searching by student ID
Node* BST::search(const std::unique_ptr<Node>& node, int id) const {
    if (!node || node->student.id == id) return node.get(); // Base case: ID found or tree is empty
    if (id < node->student.id) return search(node->left, id); // Search left subtree
    return search(node->right, id);                           // Search right subtree
}

// Public function to search for a student and print the result
void BST::search(int id) const {
    Node* result = search(root, id);
    if (result) {
        std::cout << "Student Found: " << result->student.name << std::endl;
    } else {
        std::cout << "Student Not Found!" << std::endl;
    }
}

// Display the tree structure using in-order traversal
void BST::display() const {
    std::function<void(const std::unique_ptr<Node>&, int)> inorder = [&](const std::unique_ptr<Node>& node, int depth) {
        if (node) {
            inorder(node->left, depth + 1); // Visit left subtree
            std::cout << std::string(depth * 4, ' ') << "ID: " << node->student.id << ", Name: " << node->student.name << std::endl;
            inorder(node->right, depth + 1); // Visit right subtree
        }
    };
    inorder(root, 0);
}

// Removes a student by ID, maintaining tree balance
std::unique_ptr<Node> BST::remove(std::unique_ptr<Node> node, int id) {
    if (!node) return nullptr;
    if (id < node->student.id) {
        node->left = remove(std::move(node->left), id); // Recursive remove from left subtree
    } else if (id > node->student.id) {
        node->right = remove(std::move(node->right), id); // Recursive remove from right subtree
    } else {
        if (!node->left) return std::move(node->right);   // Node with only right child or no child
        if (!node->right) return std::move(node->left);   // Node with only left child
        Node* minNode = node->right.get();                // Find minimum node in right subtree
        while (minNode->left) minNode = minNode->left.get();
        node->student = minNode->student;                 // Copy data of minNode to current node
        node->right = remove(std::move(node->right), minNode->student.id); // Remove minNode
    }
    return node;
}

// Public function to remove a student by ID
void BST::remove(int id) {
    root = remove(std::move(root), id);
}
