#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <list>

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

template<class T = int>
class UndirectedGraph {
public:
    UndirectedGraph() {}
    void add(int v, int u) {
        if(v < 0 || u < 0) throw new std::runtime_error("One or both nodes indexes are invalid");
        if(v >= _graph.size() || u >= _graph.size()) resize(std::max<int>(v,u) + 1);
        // v -> u
        // v <- u
        Vertex* nV = _graph[v];
        Vertex* nU = _graph[u];
        // Confirmar si u no existe en la lista de adyacencia de v
        if(vertexExistInAdjList(v,u) == false) {
            // v -> u
            nV->adjList.push_back(nU->index);
        }
        // Confirmar si v no existe en la lista de adyacencia de u
        if(vertexExistInAdjList(u,v) == false) {
            // v <- u
            nU->adjList.push_back(nV->index);
        }
    }
    void print() {
        for(Vertex* v: _graph) {
            std::cout << "\n" << v->index << ": ";
            std::cout << "[";
            for(int u: v->adjList) {
                std::cout << u << ",";
            }
            std::cout << "]\n";
        }
    }
    void dfs(int verticeInicio) {
        std::vector<bool> visitados(this->_graph.size(), false);
        std::vector<int> paths(this->_graph.size(), -1);
        _dfs(-1,verticeInicio,visitados,paths);
        for(int i = 0; i < paths.size(); ++i) {
            std::cout << i << " -> " << paths[i] << "\n";
        }
    }
private:
    class Vertex {
    public:
        int index;
        T value;
        std::list<int> adjList;
    };
    std::vector<Vertex*> _graph;
    void resize(int size) {
        int oldSize = _graph.size();
        _graph.resize(size);
        for(int i = oldSize; i < _graph.size(); ++i)
            _graph[i] = new Vertex{i,T(), std::list<int>()};
    }
    bool vertexExistInAdjList(int v, int u) {
        auto it = _graph[v]->adjList.begin();
        for(it; it != _graph[v]->adjList.end(); ++it) {
            if(*it == u) return true;
        }
        return false;
    }
    void _dfs(int verticeAntecesor, int verticeActual, std::vector<bool>& visitados, std::vector<int>& paths) {
        if(visitados[verticeActual]) return;
        visitados[verticeActual] = true;
        paths[verticeActual] = verticeAntecesor;
        for(int verticeAdyacente: this->_graph[verticeActual]->adjList){
            _dfs(verticeActual, verticeAdyacente, visitados, paths);
        }
    }
};

int main() {
    /*FileManager fm;
    std::vector<Person> personas = fm.leerEstudiantes();
    for(Person p: personas) {
        std::cout << p << "\n";
    }*/
    UndirectedGraph<> graph = UndirectedGraph<>();
    graph.add(0,1);
    graph.add(0,2);
    graph.add(1,2);
    graph.print();
    graph.dfs(0);
    return 0;
}