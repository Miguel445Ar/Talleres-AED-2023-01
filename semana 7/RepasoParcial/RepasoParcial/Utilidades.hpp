#pragma once
#include "Persona.hpp"
#include <functional>
#include <ctime>
namespace Utilidades {
	Persona generarPersonaAleatoria() {
		std::string nombre = "";
		const int inicio = static_cast<int>('A'); // A -> 65 , Z -> 90
		const int final = static_cast<int>('Z');
		for (unsigned int i = 0; i < 10; ++i) {
			const char letra = static_cast<char>(inicio + rand() % (final - inicio + 1));
			nombre.push_back(letra);
		}
		std::string codigoRecluta = std::to_string(100000 + rand() % (999999 - 100000 + 1));
		return Persona(nombre, codigoRecluta);
	}
	void generarPersonasAleatorias(std::function<void(Persona)> insertarEnLista, long cantidad = 1000 + rand() % (7500 - 1000 + 1)) {
		for (unsigned int i = 0; i < cantidad; ++i)
			insertarEnLista(generarPersonaAleatoria());
	}
};