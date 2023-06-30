#include <iostream>
#include <functional>

using std::function;

template<class T>
class FourChildsBinarySearchTree {
public:
    FourChildsBinarySearchTree(function<bool(T,T)> equals, function<bool(T,T)> lowerThan, function<bool(T,T)> higherThan)
    : _root(nullptr), _equals(equals), _lowerThan(lowerThan), _higherThan(higherThan) {}
    void insert(T value) {
        _insert(_root, value);
    }
    void inOrder(void (*show)(T)) {
        _inOrder(_root, show);
    }
private:
    class Node {
    public:
        Node* leftMost;
        Node* left;
        Node* right;
        Node* rightMost;
        T value;
    };
    Node* _root;
    size_t _size;
    function<bool(T,T)> _equals;
    function<bool(T,T)> _lowerThan;
    function<bool(T,T)> _higherThan;
private:
    void _insert(Node*& node, T value) {
        if(node == nullptr) {
            node = new Node{nullptr, nullptr, nullptr, nullptr, value};
            ++_size;
            return;
        }
        if(_equals(node->value, value)) {
            std::cout << "\n This value already exists";
            return;
        }
        bool isLower = false, isHigher = false; 
        // value < node->value
        if(_lowerThan(value, node->value)) {
            isLower = true;
        }else {
            isHigher = true;
        }
        if(isLower && node->left == nullptr) {
            _insert(node->left,value);
            return;
        }
        if(isLower && node->leftMost == nullptr) {
            if(_lowerThan(value,node->left->value))
                _insert(node->leftMost, value);
            else {
                node->leftMost = node->left;
                node->left = nullptr;
                _insert(node->left, value);
            }
            return;
        }
        if(isHigher && node->right == nullptr) {
            _insert(node->right, value);
            return;
        }
        if(isHigher && node->rightMost == nullptr) {
            if(_higherThan(value, node->right->value))
                _insert(node->rightMost, value);
            else {
                node->rightMost = node->right;
                node->right = nullptr;
                _insert(node->right, value);
            }
            return;
        }
        if(isLower) {
            bool toLeft = _higherThan(value, node->leftMost->value) && _lowerThan(value,node->value);
            if(toLeft) _insert(node->left,value);
            else _insert(node->leftMost, value);
            return;
        } 
        if(isHigher) {
            bool toRight = _higherThan(value, node->value) && _lowerThan(value, node->rightMost->value);
            if(toRight) _insert(node->right, value);
            else _insert(node->rightMost, value);
        }
    }
    void _inOrder(Node* node, void (*show)(T)) {
        if(node == nullptr) return;
        // L - N - R : Antes
        // LM - L - N - R - RM :  Ahora
        _inOrder(node->leftMost, show);
        _inOrder(node->left, show);
        show(node->value);
        _inOrder(node->right, show);
        _inOrder(node->rightMost, show);
    }
};

int main() {
    FourChildsBinarySearchTree<int> tree(
        [](int a, int b) -> bool { return a == b; },
        [](int a, int b) -> bool { return a < b; },
        [](int a, int b) -> bool { return a > b; }
    );
    tree.insert(5);
    tree.insert(3);
    tree.insert(4);
    tree.insert(8);
    tree.insert(6);
    tree.insert(10);
    tree.insert(2);
    tree.inOrder([](int a) -> void { std::cout << a << "\n"; });
    tree.insert(7);
    std::cout << "\n-------------------------------------------\n";
    tree.inOrder([](int a) -> void { std::cout << a << "\n"; });
    return 0;
}