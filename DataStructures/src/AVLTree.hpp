#include <iostream>

template <class T>
class AVLTree {
private:
    typedef struct Node {
        T value;
        int height;
        Node* left;
        Node* right;
    } Node;

    Node* head;

    Node* rotateLeft(Node* a) {
        auto b = a->right;
        auto c = b->left;

        b->left = a;
        a->right = c;

        a->height = 1 + std::max(getHeight(a->left), getHeight(a->right));
        b->height = 1 + std::max(getHeight(b->left), getHeight(b->right));

        return b;
    }

    Node* rotateRight(Node* a) {
        auto b = a->left;
        auto c = b->right;

        b->right = a;
        a->left = c;

        a->height = 1 + std::max(getHeight(a->left), getHeight(a->right));
        b->height = 1 + std::max(getHeight(b->left), getHeight(b->right));

        return b;
    }

    Node* insert(T value, Node* node) {
        if(!node) return new Node{value, 1};

        if(value < node->value) {
            node->left = insert(value, node->left);
        } else if(value > node->value) {
            node->right = insert(value, node->right);
        }

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        if(balance > 1 && getBalance(node->left) >= 0) return rotateRight(node);
        if(balance > 1 && getBalance(node->left) < 0) return rotateRight(rotateLeft(node));
        if(balance < -1 && getBalance(node->right) <= 0) return rotateLeft(node);
        if(balance < -1 && getBalance(node->right) > 0) return rotateLeft(rotateRight(node));

        return node;
    }

    void inOrderTraversal(Node* node) {
        if(!node) return;

        inOrderTraversal(node->left);
        std::cout << node->value << " -- " << node->height << "\n";
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
        
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        if(balance > 1 && getBalance(node->left) >= 0) return rotateRight(node);
        if(balance > 1 && getBalance(node->left) < 0) return rotateRight(rotateLeft(node));
        if(balance < -1 && getBalance(node->right) <= 0) return rotateLeft(node);
        if(balance < -1 && getBalance(node->right) > 0) return rotateLeft(rotateRight(node));


        return node;
    }
public:
    AVLTree<T>(T value) {
        head = new Node{value, 1};
    }

    int getHeight(Node* node) {
        if(!node) return 0;
        return node->height;
    }

    int getBalance(Node* node) {
        if(!node) return 0;
        return getHeight(node->left) - getHeight(node->right);
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