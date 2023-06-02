#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
#include <sstream>
#include "BinarySearchTree.hpp"
#include "HashTable.hpp"
#include "SortingAlgorithms.hpp"
#include "Heap.hpp"

using namespace std;

class Registro {
    string iso_code, contiente, location;
    unsigned int total_cases, total_deaths, 
    total_cases_per_million, total_deaths_per_million;
public:
    Registro(string iso_code, string contiente, string location, unsigned int total_cases, unsigned int total_deaths, 
    unsigned int total_cases_per_million, unsigned int total_deaths_per_million):
    iso_code(iso_code), contiente(contiente), location(location),
    total_cases(total_cases), total_deaths(total_deaths),
    total_cases_per_million(total_cases_per_million), total_deaths_per_million(total_deaths_per_million)
    {

    }
    Registro() {}
    friend ostream& operator<<(ostream& os, Registro r) {
        os << "(" << r.iso_code << "|" << r.contiente << " | " << r.total_cases << ")";
        return os;
    }
    bool operator>(Registro r) {
        return this->total_cases > r.total_cases;
    }
    bool operator==(Registro r) {
        return this->total_cases == r.total_cases;
    }
    unsigned int getTotalCases() {
        return this->total_cases;
    }
    string getLocation() {
        return this->location;
    }
    unsigned int getTotalCasesPerMillion() {
        return this->total_cases_per_million;
    }
};

class Diagnostico {
    BinarySearchTree<Registro>* arbol;
    Heap<Registro>* colaPrioridad;
    HashTable<Registro>* hashTable;
public:
    Diagnostico() {
        arbol = new BinarySearchTree<Registro>(
            [](Registro r) -> void { cout << r << "\n"; },
            [](Registro a, Registro b) -> bool {
                return a > b;
            },
            [](Registro a, Registro b) -> bool {
                return a == b;
            }
        );
        colaPrioridad = new Heap<Registro>(
            [](Registro a, Registro b) {
                return a.getTotalCasesPerMillion() < b.getTotalCasesPerMillion();
            }
        );
        hashTable = new HashTable<Registro>(100);
    }
    void leer() {
        ifstream archivo("data.txt");
        if(archivo.is_open() == false) {
            cout << "\nEl archivo data.txt no existe\n";
            return;
        }

        string line;
        while(getline(archivo, line)) {
            stringstream s(line);
            string iso_code, contiente, location;
            unsigned int total_cases, total_deaths, 
            total_cases_per_million, total_deaths_per_million;
            string aux;
            getline(s,aux, ',');
            iso_code = aux;
            getline(s,aux, ',');
            contiente = aux;
            getline(s,aux, ',');
            location = aux;
            getline(s,aux, ',');
            total_cases = stoi(aux);
            getline(s,aux, ',');
            total_deaths = stoi(aux);
            getline(s,aux,',');
            total_cases_per_million = stoi(aux);
            getline(s,aux, ',');
            total_deaths_per_million = stoi(aux);
            Registro r = Registro(iso_code, contiente, location, total_cases, total_deaths, total_cases_per_million, total_deaths_per_million);
            // cout << r << "\n";
            this->arbol->insert(r);
            this->colaPrioridad->push(r);
            this->hashTable->insert(iso_code + location, r);
        }
        this->arbol->preOrder();
        Registro rMax = this->arbol->max();
        Registro rMin = this->arbol->min();
        cout << "\nPais con mayor cantidad de casos: " << rMax.getLocation() << " y tiene " <<rMax.getTotalCases() << " casos" << "\n";
        cout << "\nPais con menor cantidad de casos: " << rMin.getLocation() << " y tiene " <<rMin.getTotalCases() << " casos" << "\n";
        cout << "\n5 países que tienen la menor cantidad de casos por millón de habitantes. \n";
        for(unsigned short i = 0; i < 5; ++i) {
            Registro registro = this->colaPrioridad->pop();
            cout << i + 1 << ": " << registro.getLocation() << "\n";
        }
        this->hashTable->display([](Registro r) -> void {
            cout << r << "\n";
        });
        archivo.close();

    }
};

int main() {
    Diagnostico d;
    d.leer();
    return 0;
}