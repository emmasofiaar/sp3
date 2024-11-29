//Emma Sofia Aparicio Rodríguez A01666223
//Eleanor Alarcón Neri A01665593
//Situación Problema TC1031

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>
#include <random>
#include "Spell.h"

using namespace std;


// se inicia la lista
Spell::Spell() : head(nullptr) {}

// constructor para spell
Spell::Spell(string name, string type, string info)
    : name(name), type(type), info(info) {
    cout << "Parametrized constructor for Spell executed" << endl;
}

// destructor para spell
Spell::~Spell() {
    Spell* current = head;
    while (current != nullptr) {
        Spell* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
    cout << "Destructor for Spell executed" << endl;
}

// setters y getters
void Spell::setName(string name) {
    this->name = name;
}

void Spell::setType(string type) {
    this->type = type;
}

void Spell::setInfo(string info) {
    this->info = info;
}

void Spell::setSpell(Spell* nextSpell) {
    this->next = nextSpell;
}

string Spell::getName(void) {
    return name;
}

string Spell::getType(void) {
    return type;
}

string Spell::getInfo(void) {
    return info;
}

Spell* Spell::getNext(void) {
    return next;
}

//Methods

void Spell::insert(Spell* newSpell) {
    newSpell->next = head;
    head = newSpell;
}

void Spell::display() {
    Spell* current=head;
    while(current!= nullptr) {
        cout << "Name: " << current-> name << " Type: " << current-> type << endl;
        cout << "Info: " << current -> info << endl;
        current= current->next;
    }
}

void Spell::loadFromFile(const std::string& filename) {
    // Imprimir el directorio de trabajo actual
    cout << "Current working directory: " << filesystem::current_path() << endl;

    // Intentar abrir el archivo
    ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Failed to open the file." << std::endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string name, type, info;

        // Leer las tres columnas separadas por comas
        getline(ss, name, ',');  // Name
        getline(ss, type, ',');  // Type
        getline(ss, info, ',');  // Info

        // Crear un nuevo hechizo y agregarlo a la lista
        Spell* newSpell = new Spell(name, type, info);
        insert(newSpell);
    }
}

// se almacenan todos los spells en un vector y luego se hace su selección aleatoria
vector<Spell*> Spell::getRandomSpells() {
    vector<Spell*> Spells;  // vector que guarda los hechizos

    // se agregan hechizos a la lista
    int count = 0;
    Spell* current = head;
    while (current != nullptr) {
        Spells.push_back(current);
        current = current->next;
    }

    // si no hay hechizos en la lisa regresa el vector vacio
    if (Spells.empty()) {
        cout << "No spells in the list :( " << endl;
        return Spells;
    }

    vector<Spell*> randomSpells;
    shuffle(Spells.begin(), Spells.end(), default_random_engine(rand())); // utilizamos la libreria de random, esto como que "barajea" los hechizos
    for (int i = 0; i < min(15, (int)Spells.size()); ++i) {
        randomSpells.push_back(Spells[i]);
    }
    return randomSpells;
}
