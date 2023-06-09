#include <iostream>
#include "BinarySearchTree.hpp"
#include "AVL.hpp"

int main() {
    BinarySearchTree<int> tree(
        [](int value) -> void {
            std::cout << value << "\n";
        },
        [](int a, int b) -> bool {
            return a > b;
        },
        [](int a, int b) -> bool {
            return a == b;
        }
    );
    tree.insert(5);
    tree.insert(3);
    tree.insert(2);
    tree.insert(4);
    tree.insert(1);
    tree.insert(9);
    tree.insert(8);
    tree.insert(14);
    tree.insert(10);
    tree.insert(16);
    try {
        std::cout << "En sucesor de 4 es " << tree.findSuccessor(4) << "\n";
        std::cout << "En sucesor de 9 es " << tree.findSuccessor(9) << "\n";
        std::cout << "El antecesor de 4 es " << tree.findPreviousNode(4) << "\n";
        std::cout << "El antecesor de 10 es " << tree.findPreviousNode(10) << "\n";
        std::cout << "El antecesor de 15 es " << tree.findPreviousNode(15) << "\n";
    }catch(const char* message) {
        std::cout << "\nERROR: " << message << "\n";
    }
    return 0;
}