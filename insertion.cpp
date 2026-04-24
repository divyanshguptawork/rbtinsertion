#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

// Node color enumeration
enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node *left, *right, *parent;

    Node(int val) : data(val), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;

    // Standard Left Rotation: Moves nodes to maintain balance while preserving BST order
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

    // Standard Right Rotation: Essential for fixing "Line" cases in RB-Trees
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

    // This function enforces the 5 Red-Black Tree rules after an insertion
    void fixInsert(Node* k) {
        while (k != root && k->parent->color == RED) {
            if (k->parent == k->parent->parent->left) {
                Node* u = k->parent->parent->right; // The Uncle node
                
                // Case 1: Uncle is Red (Recolor only)
                if (u != nullptr && u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    // Case 2: Uncle is Black (Triangle shape) -> Convert to Line
                    if (k == k->parent->right) {
                        k = k->parent;
                        rotateLeft(k);
                    }
                    // Case 3: Uncle is Black (Line shape) -> Rotate & Recolor
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rotateRight(k->parent->parent);
                }
            } else {
                Node* u = k->parent->parent->left; // The Uncle node
                
                // Case 1: Uncle is Red
                if (u != nullptr && u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    // Case 2: Uncle is Black (Triangle shape)
                    if (k == k->parent->left) {
                        k = k->parent;
                        rotateRight(k);
                    }
                    // Case 3: Uncle is Black (Line shape)
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rotateLeft(k->parent->parent);
                }
            }
        }
        root->color = BLACK; // Rule: Root must always be Black
    }

    // Recursive helper for visual printing
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

        // Perform standard BST insertion
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
    RedBlackTree rbt;
    int choice;
    
    while (true) {
        cout << "\nmenu" << endl;
        cout << "1. Add Single Number\n2. Read Numbers from File\n3. Print Tree\n4. Exit" << endl;
        cout << "Choice: ";
        
        if (!(cin >> choice)) break;
        
        if (choice == 1) {
            int val;
            cout << "enter number (1-999): ";
            cin >> val;
            rbt.insert(val);
        } else if (choice == 2) {
            string filename;
            cout << "enter filename (e.g., input.txt): ";
            cin >> filename;
            ifstream file(filename);
            if (!file) {
                cout << "error: could not open file." << endl;
                continue;
            }
            int val;
            while (file >> val) rbt.insert(val);
            cout << "File data processed successfully." << endl;
        } else if (choice == 3) {
            cout << "\ntree" << endl;
            rbt.display();
        } else if (choice == 4) {
            cout << "exiting program..." << endl;
            break;
        } else {
            cout << "try again, incorrect option" << endl;
        }
    }
    return 0;
}
