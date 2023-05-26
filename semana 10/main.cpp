#include <iostream>
#include <string>
#include <cmath>

template<class T>
class HashTable {
public:
    HashTable(size_t capacity) : _capacity(capacity) {
        _size = 0;
        _hashTable = new Element * [capacity];
        for (int i = 0; i < capacity; ++i) _hashTable[i] = nullptr;
    }
    void insert(std::string key, T value) {
        if (_size == _capacity) throw "Hash table is full";
        int index = _hashFunction(key);
        if (this->_hashTable[index] != nullptr) // Si es que esta posici�n est� ocupada
            index = _cuadraticProbing(index);
        this->_hashTable[index] = new Element{ key, value };
        ++_size;
    }
    T& operator[](std::string key) {
        int index = _hashFunction(key);
        if (this->_hashTable[index] != nullptr) // Si es que esta posici�n est� ocupada
            index = _cuadraticProbing(index);
        this->_hashTable[index] = new Element{ key, T() };
        return this->_hashTable[index]->value;
    }
    T getCopy(std::string key) {
        int index = _hashFunction(key);
        return this->_hashTable[_cuadraticProbingForReturnValues(index, key)]->value;
    }
    void display(void (*show)(T)) {
        for (unsigned int i = 0; i < _capacity; ++i) {
            std::cout << "\nPos: " << i << ": ";
            if (_hashTable[i] == nullptr) {
                std::cout << "nullptr";
                continue;
            }
            show(_hashTable[i]->value);
        }
    }
    // Para eliminar:
    // Obtener el elemento en su posici�n adecuada (get)
    // Eliminar elemento delete _hashTable[pos];
    // Asignar como disponible _hashTable[pos] = nullptr;
    // Decrementar el _size --_size
private:
    struct Element {
        std::string key;
        T value;
    };
    Element** _hashTable;
    size_t _size;
    size_t _capacity;
private:
    int _hashFunction(std::string key) {
        int res = 0;
        for (unsigned int i = 0; i < key.length(); ++i)
            res += std::pow(static_cast<int>(key[i]), i + 1);
        return res % _capacity;
    }
    int _cuadraticProbing(int colisionIndex) {
        int jump = 1;
        int newIndex = colisionIndex;
        while (_hashTable[newIndex] != nullptr) {
            newIndex = colisionIndex;
            newIndex += pow(jump, 2);
            if (newIndex >= _capacity) newIndex %= _capacity;
            ++jump;
        }
        return newIndex;
    }
    int _cuadraticProbingForReturnValues(int index, std::string key) {
        int jump = 1;
        int newIndex = index;
        while (_hashTable[newIndex]->key != key) {
            newIndex = index;
            newIndex += pow(jump, 2);
            if (newIndex >= _capacity) newIndex %= _capacity;
            ++jump;
        }
        return newIndex;
    }
};


template<class T>
class ABB {
public:
    ABB() {
        raiz = nullptr;
        cantidad = 0;
    }
    void insert(T value) {
        _insert(raiz, value);
    }
    void recorrer() {
        _preOrden(raiz);
    }
private:
    struct Node {
        Node* hijoIzquierdo;
        Node* hijoDerecho;
        T valor;
    };
    Node* raiz;
    size_t cantidad;
private:
    void _insert(Node*& nodo, T valor) {
        if(nodo == nullptr) {
            nodo = new Node{nullptr, nullptr, valor};
            ++cantidad;
            return;
        }
        if(valor < nodo->valor ) {
            _insert(nodo->hijoIzquierdo, valor);
            return;
        }
        
        _insert(nodo->hijoDerecho, valor);
    }
    void _preOrden(Node* n) {
        if(n == nullptr) return;
        std::cout << n->valor << "\n";
        _preOrden(n->hijoIzquierdo);
        _preOrden(n->hijoDerecho);
    }
};

int main() {
    ABB<int> abb;
    abb.insert(5);
    abb.insert(4);
    abb.insert(8);
    abb.insert(10);
    abb.recorrer();
    return 0;
}