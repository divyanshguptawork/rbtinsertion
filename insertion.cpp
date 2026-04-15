#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

//forgot to do using namespace std

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    // Helper: Recursive insertion
    Node* insert(Node* node, int val) {
        if (node == nullptr) {
            return new Node(val);
        }
        if (val < node->data) {
            node->left = insert(node->left, val);
        } else if (val > node->data) {
            node->right = insert(node->right, val);
        }
        return node;
    }

    // Helper: Recursive search
    bool search(Node* node, int val) {
        if (node == nullptr) return false;
        if (node->data == val) return true;
        
        if (val < node->data) return search(node->left, val);
        return search(node->right, val);
    }

    // Helper: Find the smallest node in a subtree (In-order Successor)
    Node* findMin(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // Helper: Recursive removal with 3 cases
    Node* remove(Node* node, int val) {
        if (node == nullptr) return nullptr;

        if (val < node->data) {
            node->left = remove(node->left, val);
        } else if (val > node->data) {
            node->right = remove(node->right, val);
        } else {
            // Case 1 & 2: No child or only one child
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Case 3: Two children
            // Get the in-order successor (smallest in the right subtree)
            Node* temp = findMin(node->right);
            node->data = temp->data;
            // Delete the successor
            node->right = remove(node->right, temp->data);
        }
        return node;
    }

    // Helper: Visual representation (Rotated 90 degrees)
    void printTree(Node* root, int indent) {
        if (root == nullptr) return;

        indent += 8;
        // Print Right first (appears at top)
        printTree(root->right, indent);

        std::cout << std::endl;
        std::cout << std::setw(indent) << root->data << std::endl;

        // Print Left (appears at bottom)
        printTree(root->left, indent);
    }

public:
    BST() : root(nullptr) {}

    void add(int val) {
        root = insert(root, val);
    }

    void remove(int val) {
        root = remove(root, val);
    }

    bool contains(int val) {
        return search(root, val);
    }

    void display() {
        if (root == nullptr) {
            std::cout << "The tree is currently empty." << std::endl;
        } else {
            printTree(root, 0);
        }
    }
};

int main() {
    BST tree;
    std::string input;
    int choice, val;

    std::cout << "Binary Search Tree Manager" << std::endl;
    std::cout << "Enter initial numbers (1-999) separated by spaces:" << std::endl;
    std::getline(std::cin, input);

    std::stringstream ss(input);
    int temp;
    while (ss >> temp) {
        if (temp >= 1 && temp <= 999) tree.add(temp);
    }

    do {
        std::cout << "\n[1] Add [2] Remove [3] Search [4] Visual Print [5] Exit" << std::endl;
        std::cout << "Selection: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Value to add: ";
                std::cin >> val;
                tree.add(val);
                break;
            case 2:
                std::cout << "Value to remove: ";
                std::cin >> val;
                tree.remove(val);
                break;
            case 3:
                std::cout << "Value to search: ";
                std::cin >> val;
                if (tree.contains(val)) std::cout << "Found!" << std::endl;
                else std::cout << "Not in tree." << std::endl;
                break;
            case 4:
                std::cout << "\n Tree Layout";
                tree.display();
                break;
            case 5:
                std::cout << "Closing program..." << std::endl;
                break;
            default:
                std::cout << "Invalid option." << std::endl;
        }
    } while (choice != 5);

    return 0;
}
