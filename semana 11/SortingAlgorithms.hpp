#ifndef ___SORTING_ALGORITHMS__
#define ___SORTING_ALGORITHMS__

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
    template<typename T>
     static void quickSelect(std::vector<T>& arr,bool(*compare1)(T,T), bool(*compare2)(T,T), int i, int& p, int f) {
        while(i < f) {
            //      a  <  b 
            while(compare1(arr[i],arr[p])) ++i;
            //     a > b 
            while(compare2(arr[f],arr[p])) --f;
            swap(arr[i],arr[f]);
            if(p == i) {
                p = f;
                ++i;
            }else if (p == f) {
                p = i;
                --f;
            }else{
                ++i; --f;
            }
        }
    }
    template<typename T>
    static void quickSort(std::vector<T>& arr, bool(*compare1)(T,T), bool(*compare2)(T,T), int i, int f) {
        if(i >= f) return;
        int p = (i + f) / 2;
        quickSelect(arr,compare1,compare2,i,p,f);
        quickSort(arr,compare1,compare2,i,p - 1);
        quickSort(arr,compare1,compare2,p + 1, f);
    }
};
#endif