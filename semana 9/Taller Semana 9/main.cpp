#include <iostream>
#include <vector>

typedef unsigned int ui;

namespace Algorithms {
	template<class T>
	void swap(T& a, T& b) {
		T c = a;
		a = b;
		b = c;
	}
	template<typename T>
	static void heapify(std::vector<T>& arr) {
		const int nodoRaiz = 0;
		for (int i = 0; i < arr.size(); ++i) {
			int nodoPadre = (i - 1) / 2;
			int nodo = i;
			if (!(arr[nodo] > arr[nodoPadre])) continue;
			int nodoActual = nodo;
			while (arr[nodo] > arr[nodoPadre]) {
				nodoPadre = (i - 1) / 2;
				swap<T>(arr[nodo], arr[nodoPadre]);
				nodoActual = nodoPadre;
			}
		}
	}
	template<typename T>
	static void heapifyParOrdenar(std::vector<T>& arr, int n, int i) {
		int nodo = i;
		int hijoIzquierdo = 2 * i + 1;
		int hijoDerecho = 2 * i + 2;
		
		int mayor = nodo;
		if (hijoDerecho > n && hijoIzquierdo > n) return;
		if (hijoIzquierdo >= n && hijoDerecho < n) { // Tengo hijo derecho
			mayor = (arr[hijoDerecho] > arr[nodo]) ? hijoDerecho : nodo;
		}
		else if (hijoDerecho >= n && hijoIzquierdo < n) { // Tengo hijo izquirdo
			mayor = (arr[hijoIzquierdo] > arr[nodo]) ? hijoIzquierdo : nodo;
		}
		else {
			int hijoMayor = (arr[hijoIzquierdo] > arr[hijoDerecho]) ? hijoIzquierdo : hijoDerecho;
			mayor = (arr[hijoMayor] > arr[nodo]) ? hijoMayor : nodo;
		}
		if (mayor == nodo) return;
		swap(arr[nodo], arr[mayor]);
		heapifyParOrdenar<T>(arr, n, mayor);
			
	}
	template<typename T>
	static void heapsort(std::vector<T>& arr) {
		heapify(arr);
		for (int i = arr.size() - 1; i >= 1; --i) {
			swap<T>(arr[0], arr[i]);
			heapifyParOrdenar<T>(arr, i, 0);
		}
	}
};

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
        if (this->_hashTable[index] != nullptr) // Si es que esta posición está ocupada
            index = _cuadraticProbing(index);
        this->_hashTable[index] = new Element{ key, value };
        ++_size;
    }
    T& operator[](std::string key) {
        int index = _hashFunction(key);
        if (this->_hashTable[index] != nullptr) // Si es que esta posición está ocupada
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
    // Obtener el elemento en su posición adecuada (get)
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
            res += pow(static_cast<int>(key[i]), i + 1);
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


int main() {
	std::vector<int> arr = { 5,6,8,1,2,4,10,7 };
	Algorithms::heapsort<int>(arr);
	for (int num : arr) {
		std::cout << num << " ";
	}
	std::cout << "\n";
	return 0;
}