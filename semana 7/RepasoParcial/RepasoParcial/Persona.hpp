#pragma once
#include<string>

class Persona {
public:
	Persona(std::string nombre, std::string codigoReculta): 
		_nombre(nombre), _codigoRecluta(codigoReculta) {}
private:
	std::string _nombre;
	std::string _codigoRecluta;
};