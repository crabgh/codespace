#include <iostream>

template <class K, class V>
class AVLMap {
private:
    typedef struct Node {
        K first;
        V second;
        int height = 1;
        Node* left;
        Node* right;
    } Node;

    Node* root;
    
    int getHeight(Node* node) {
        if(!node) return 0;
        return node->height;
    }

    int getBalance(Node* node) {
        if(!node) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }
    
    Node* rotateLeft(Node* a) {
        Node* b = a->right;
        Node* c = b->left;

        b->left = a;
        a->right = c;

        a->height = 1 + std::max(getHeight(a->left), getHeight(a->right));
        b->height = 1 + std::max(getHeight(b->left), getHeight(b->right));

        return b;
    }

    Node* rotateRight(Node* a) {
        Node* b = a->left;
        Node* c = b->right;

        b->right = a;
        a->left = c;

        a->height = 1 + std::max(getHeight(a->left), getHeight(a->right));
        b->height = 1 + std::max(getHeight(b->left), getHeight(b->right));

        return b;
    }

    /*Node* insert(K key, Node* node) {
        if(!node) return new Node{key};

        if(key < node->first) {
            node->left = insert(key, node->left);
        } else if(key > node->first) {
            node->right = insert(key, node->right);
        }
        
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        if(balance > 1 && getBalance(node->left) >= 0) return rotateRight(node);
        if(balance > 1 && getBalance(node->left) < 0) return rotateRight(rotateLeft(node));
        if(balance < -1 && getBalance(node->right) <= 0) return rotateLeft(node);
        if(balance < -1 && getBalance(node->right) > 0) return rotateLeft(rotateRight(node));

        return node;
    }*/

    std::pair<Node*, Node*> insert(K key, Node* node) {
        if(!node) {
            Node* n = new Node{key};
            return {n, n};
        }

        Node* n;
        if(key < node->first) {
            std::pair<Node*, Node*> a = insert(key, node->left);
            node->left = a.first;
            n = a.second;
        } else if(key > node->first) {
            std::pair<Node*, Node*> a = insert(key, node->right);
            node->right = a.first;
            n = a.second;
        }
        
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        if(balance > 1 && getBalance(node->left) >= 0) node = rotateRight(node);
        if(balance > 1 && getBalance(node->left) < 0) node = rotateRight(rotateLeft(node));
        if(balance < -1 && getBalance(node->right) <= 0) node = rotateLeft(node);
        if(balance < -1 && getBalance(node->right) > 0) node = rotateLeft(rotateRight(node));

        return {node, n};
    }

    void inOrderTraversal(Node* node) {
        if(!node) return;

        inOrderTraversal(node->left);
        std::cout << node->first << ": " << node->second << "\n";
        inOrderTraversal(node->right);
    }

    Node* minNode(Node* node) {
        if(node->left) return minNode(node->left);
        return node;
    }

    Node* erase(K key, Node* node) {
        if(!node) return nullptr;

        if(key < node->first) {
            node->left = erase(key, node->left);
        } else if(key > node->first) {
            node->right = erase(key, node->right);
        } else {
            if(!node->left) {
                Node* a = node->right;
                node = nullptr;
                return a;
            } else if(!node->right) {
                Node* a = node->left;
                node = nullptr;
                return a;
            }

            node->first = minNode(node->right)->first;
            node->right = erase(node->first, node->right);
        }
        
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        if(balance > 1 && getBalance(node->left) >= 0) return rotateRight(node);
        if(balance > 1 && getBalance(node->left) < 0) return rotateRight(rotateLeft(node));
        if(balance < -1 && getBalance(node->right) <= 0) return rotateLeft(node);
        if(balance < -1 && getBalance(node->right) > 0) return rotateLeft(rotateRight(node));

        return node;
    }

    Node* get(K key, Node* node) {
        if(!node) return nullptr;

        if(key == node->key) return node;
        if(key < node->key) return get(key, node->left);
        if(key > node->key) return get(key, node->right);

        return nullptr;
    }

public:
    AVLMap<K, V>(K key, V value) {
        root = new Node{key, value, 1};
    }

    void inOrderTraversal() {
        inOrderTraversal(root);
    }

    V erase(K key) {
        Node* a = erase(key, root);
        if(a) return a->second;
        return NULL;
    }

    V& operator[](K key) {
        std::pair<Node*, Node*> a = insert(key, root);
        root = a.first;
        return a.second->second;
    };

    const V operator[](K key) const {
        Node* a = get(key, root);
        if(a) return a->value;
        return NULL;
    }
};