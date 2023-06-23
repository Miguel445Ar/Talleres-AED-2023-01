#include <iostream>
#include <list>
#include <vector>
#include <string>
#include "HashTable.hpp"

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
};

enum Gender {
    MALE,
    FEMALE
};

class Person {
public:
    std::string name;
    int age;
    Gender gender;
};

int main() {
    UndirectedGraph<> graph = UndirectedGraph<>();
    graph.add(0,1);
    graph.add(0,2);
    graph.add(1,2);
    graph.print();

    HashTable<Person> ht(20);
    Person p1 = {"Miguel", 20, Gender::MALE};
    ht.insert(p1.name,p1);
    Person p2 = {"Ely", 20, Gender::MALE};
    ht.insert(p2.name, p2);

    std::cout << "\n\n----------------------------------------------------------\n\n";

    ht.display([](Person p) -> void {
        std::cout << "(nombre: " << p.name << ", edad: " << p.age << ", genero: " << p.gender << ")";
    });
    return 0;
}