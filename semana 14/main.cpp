#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

class Person {
    int id, edad;
    std::string nombre, apellido, carrera;
public:
    Person(int id, int edad, std::string nombre, std::string apellido, std::string carrera)
        :id(id), edad(edad), nombre(nombre), apellido(apellido), carrera(carrera)
     {}
    friend std::ostream& operator<<(std::ostream& os, Person p) {
        os << "(" << p.id << ", " << p.nombre << ", " << p.edad << ", " << p.apellido << ", " << p.carrera << ")";
        return os;
    }
};

class FileManager {
public:
    std::vector<Person> leerEstudiantes() {
        std::ifstream arch("data-estudiantes.csv");
        if(arch.is_open() == false) {
            throw "El archivo no existe";
        }
        std::string fila;
        std::vector<Person> arreglo;
        while(std::getline(arch,fila,'\n')) {
            std::stringstream ss(fila);
            int id, edad;
            std::string nombre, apellido, carrera;
            std::string aux;
            std::getline(ss,aux,',');
            id = std::stoi(aux);
            std::getline(ss,nombre,',');
            std::getline(ss,apellido,',');
            std::getline(ss,aux,',');
            edad = std::stoi(aux);
            std::getline(ss,carrera,',');
            Person p(id,edad,nombre,apellido,carrera);
            arreglo.push_back(p);
        }
        return arreglo;
    }
};

int main() {
    FileManager fm;
    std::vector<Person> personas = fm.leerEstudiantes();
    for(Person p: personas) {
        std::cout << p << "\n";
    }
    return 0;
}