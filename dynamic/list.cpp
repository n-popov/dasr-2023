#include <iostream>

template <typename T> struct Node {
    T value;
    Node* next;
    Node* prev;

    Node(T value) {
        this->value = value;
        this->next = nullptr;
        this->prev = nullptr;
    }
};

template<typename T>
Node<T>* push_after(T value, Node<T>* node = nullptr) {
    Node<T>* new_node = new Node<T>(value);

    if (node) {
        if (node->next) {
            new_node->next = (node->next);
            (node->next)->prev = new_node;
        }

        new_node->prev = node;
        node->next = new_node;
    }


    return new_node;
}

template <typename T>
Node<T>* push_before(T value, Node<T>* node) {
    Node<T>* new_node = new Node<T>(value);

    if (node->prev) {
        new_node->prev = node->prev;
        node->prev->next = new_node;
    }

    new_node->next = node;
    node->prev = new_node;

    return new_node;
}

template <typename T>
void remove(Node<T>* node) {
    Node<T>* prev = node->prev;
    Node<T>* next = node->next;

    if (prev) {
        prev->next = next;
    }

    if (next) {
        next->prev = prev;
    }

    delete node;
}

template <typename T>
Node<T>* find(Node<T>* first, T value) {
    for(Node<T>* current = first; current; current = current->next) {
        if (current->value == value) {
            return current;
        }
    }
    return nullptr;
}

int main() {
    std::cout << "Input elements" << std::endl;
    // Adding first element
    int value;
    std::cin >> value;
    auto first = push_after(value);
    // compiler understands by value that push_after is push_after<int>
    // then return value is Node<int>* so that first has type Node<int>

    // adding 4 elements more before first
    for (int i = 0; i < 4; i++) {
        std::cin >> value;
        first = push_before(value, first);
    }

    for (auto c = first; c; c = c->next) {
        std::cout << c->value << ' ';
    }
    std::cout << std::endl;

    // will look for value
    std::cout << "input value to look for:" << std::endl;
    std::cin >> value;

    Node<int>* found = find(first, value);
    if (found) {
        std::cout << "Found element!" << std::endl;
    } else {
        std::cout << "Not found element!" << std::endl;
    }

    for(Node<int>* current = first; current;) {
        Node<int>* to_delete = current;
        current = current->next;
        remove(to_delete);
    }


}

