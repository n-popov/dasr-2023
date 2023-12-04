#include <iostream>

struct Node {
    int value;
    Node* left = nullptr;
    Node* right = nullptr;
    int height = 1;

    Node(int value) {
        this->value = value;
    }
};

Node* find(Node* root, int value) {
    if (!root) {
        return nullptr;
    }
    if (value == root->value) {
        return root;
    } else if (value < root->value) {
        return find(root->left, value);
    } else {
        return find(root->right, value);
    }
}

Node* _insert(Node* elem, int value) {
    if (!elem) {
        elem = new Node(value);
    } else if (value < elem->value) {
        elem->left = _insert(elem->left, value);
    } else if (value > elem->value) {
        elem->right = _insert(elem->right, value);
    }

    int left_height = (elem->left) ? elem->left->height : 0;
    int right_height = (elem->right) ? elem->right->height : 0;
    elem->height = 1 +
        (left_height > right_height ? left_height : right_height);
    return elem;
}

int height(Node* elem) {
    return elem ? elem->height : 0;
}

int balanceFactor(Node* elem) {
    return height(elem->left) - height(elem->right);
}

Node* right_turn(Node* elem) {
    Node* left_child = elem->left;
    elem->left = left_child->right;
    left_child->right = elem;
    return left_child;
}

Node* left_turn(Node* elem) {
    Node* right_child = elem->right;
    elem->right = right_child->left;
    right_child->left = elem;
    return right_child;
}

Node* right_big_turn(Node* elem) {
    Node* new_left_child = left_turn(elem->left);
    elem->left = new_left_child;

    return right_turn(elem);
}

Node* left_big_turn(Node* elem) {
    elem->right = right_turn(elem->right);
    return left_turn(elem);
}

Node* _balance(Node* root) {
    int bf = balanceFactor(root);
    std::cout << "BF is " << bf << std::endl;
    if (bf < -1) {
        int right_bf = balanceFactor(root->right);
        if (right_bf < 0) {
            std::cout << "LT" << std::endl;
            return left_turn(root);
        } else {
            std::cout << "LBT" << std::endl;
            return left_big_turn(root);
        }
    } else if (bf > 1) {
        if (balanceFactor(root->left) > 0) {
            std::cout << "RT" << std::endl;
            return right_turn(root);
        } else {
            std::cout << "RBT" << std::endl;
            return right_big_turn(root);
        }
    }

    return root;
}

Node* insert(Node* root, int value) {
    root = _insert(root, value);
    return _balance(root);
}

void traverse(Node* root, bool debug = false) {
    if (!root) return;
    if (debug) std::cout << "reached elem " << root->value << std::endl;
    traverse(root->left, debug);
    std::cout << root->value << ' ';
    traverse(root->right, debug);
}

int main() {
    int N;
    std::cin >> N;
    int value;
    Node* root = nullptr;

    for(int i = 0; i < N; i++) {
        std::cin >> value;
        root = insert(root, value);
        traverse(root);
        std::cout << std::endl;
    }
    traverse(root, true);
}

