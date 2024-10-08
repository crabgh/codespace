#include <iostream>

template <class T>
class BinaryTree {
private:
    typedef struct Node {
        T value;
        Node* left;
        Node* right;
    } Node;

    Node* head;

    Node* insert(T value, Node* node) {
        if(!node) return new Node{value};

        if(value < node->value) {
            node->left = insert(value, node->left);
        } else if(value > node->value) {
            node->right = insert(value, node->right);
        }

        return node;
    }

    void inOrderTraversal(Node* node) {
        if(!node) return;

        inOrderTraversal(node->left);
        std::cout << node->value << "\n";
        inOrderTraversal(node->right);
    }

    Node* minNode(Node* node) {
        if(node->left) return minNode(node->left);
        return node;
    }

    Node* remove(T value, Node* node) {
        if(!node) return nullptr;

        if(value < node->value) {
            node->left = remove(value, node->left);
        } else if(value > node->value) {
            node->right = remove(value, node->right);
        } else {
            if(!node->left) {
                auto a = node->right;
                node = nullptr;
                return a;
            } else if(!node->right) {
                auto a = node->left;
                node = nullptr;
                return a;
            }

            node->value = minNode(node->right)->value;
            node->right = remove(node->data, node->right);
        }

        return node;
    }
public:
    BinaryTree<T>(T value) {
        head = new Node{value};
    }

    void insert(T value) {
        head = insert(value, head);
    }

    void inOrderTraversal() {
        inOrderTraversal(head);
    }

    Node* minNode() {
        return minNode(head);
    }

    Node* remove(T value) {
        return remove(value, head);
    }
};