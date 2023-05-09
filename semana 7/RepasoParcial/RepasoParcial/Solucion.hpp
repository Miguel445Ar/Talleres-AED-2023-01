#pragma once
#include "ListaDoble.hpp"
#include "Persona.hpp"
#include "Utilidades.hpp"
class Solucion {
public:
	Solucion() {
		this->_lista = new DoublyLinkedList<Persona>([](Persona p) -> void {});
		Utilidades::generarPersonasAleatorias(
			[this](Persona p) -> void {
				this->_lista->pushBack(p);
			},
			1420
		);
	}
	~Solucion() {
		delete this->_lista;
	}
private:
	DoublyLinkedList<Persona>* _lista;
};