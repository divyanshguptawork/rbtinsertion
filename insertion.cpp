#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

enum Color {RED, BLACK};

struct Node {
    int data;
  Color color;
  Node *left, *right, *parent;

  Node(int val) : data(val), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;

  // Inside private:
void rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != nullptr) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rotateRight(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != nullptr) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr) root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
}

  void fixInsert(Node* k) {
    while (k != root && k->parent->color == RED) {
        if (k->parent == k->parent->parent->left) {
            Node* u = k->parent->parent->right; 
            if (u != nullptr && u->color == RED) {
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
                    k = k->parent;
                    rotateLeft(k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rotateRight(k->parent->parent);
            }
        } else {
            Node* u = k->parent->parent->left; 
            if (u != nullptr && u->color == RED) {
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rotateRight(k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rotateLeft(k->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

  // Update public add method
void add(int data) {
    Node* node = new Node(data);
    Node* y = nullptr;
    Node* x = root;
    while (x != nullptr) {
        y = x;
        if (node->data < x->data) x = x->left;
        else x = x->right;
    }
    node->parent = y;
    if (y == nullptr) root = node;
    else if (node->data < y->data) y->left = node;
    else y->right = node;

    if (node->parent == nullptr) {
        node->color = BLACK;
        return;
    }
    if (node->parent->parent == nullptr) return;
    fixInsert(node);
}

// Update printHelper inside private
void printHelper(Node* n, int space) {
    if (n == nullptr) return;
    space += 10;
    printHelper(n->right, space);
    cout << endl << setw(space) << n->data 
         << (n->color == RED ? "[R]" : "[B]") 
         << " (P:" << (n->parent ? to_string(n->parent->data) : "N") << ")" << endl;
    printHelper(n->left, space);
}

public:
    RedBlackTree() : root(nullptr) {}

    void insert(int data) {
      Node* node = new Node(data);
      Node* y = nullptr;
      Node* x = root;

      //perform standard bst insertion
              while (x != nullptr) {
            y = x;
            if (node->data < x->data) x = x->left;
            else x = x->right;
        }

        node->parent = y;
        if (y == nullptr) root = node;
        else if (node->data < y->data) y->left = node;
        else y->right = node;

        // If the new node is root, color it black and return
        if (node->parent == nullptr) {
            node->color = BLACK;
            return;
        }
        
        // If grandparent doesn't exist, no need to fix properties
        if (node->parent->parent == nullptr) return;

        // Fix the tree to maintain RB properties
        fixInsert(node);
    }

    void display() {
        if (root == nullptr) cout << "The tree is currently empty." << endl;
        else printHelper(root, 0);
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
