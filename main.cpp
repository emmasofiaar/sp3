//Emma Sofia Aparicio Rodríguez A01666223
//Eleanor Alarcón Neri A01665593
//Situación Problema TC1031

#include <iostream>
#include <vector>
#include "Monster.h"
#include "Spell.h"
#include "Player.h"
#include "Manager.h"
#include "Graph.h"

using namespace std;

ostream operator<<(const ostream &lhs, double(*rhs)());

int main() {
    Monster monsters;
    monsters.loadFromFile("monsters_patched.csv");

    cout << "Monsters:" << endl;
    monsters.display();

    Spell spells;
    spells.loadFromFile("spells.csv");

    cout << "Spells:" << endl;
    spells.display();

    Player player;
    Monster monsterList;

    // Cargar monstruos desde el archivo
    monsterList.loadFromFile("monsters_patched.csv");

    // Obtener 20 monstruos aleatorios (o menos si hay menos de 20)
    vector<Monster*> randomMonsters = monsterList.getRandomMonsters();

    // Verificar si se obtuvieron monstruos aleatorios
    if (!randomMonsters.empty()) {
        cout << "Randomly selected monsters:" << endl;
        for (Monster* m : randomMonsters) {
            cout << m->getName() << endl;  // Imprimir el nombre de cada monstruo
        }
    } else {
        cout << "No monsters were selected." << endl;
    }

    Spell spellList;
    spellList.loadFromFile("spells.csv");
    vector<Spell*> randomSpells = spellList.getRandomSpells();
    if (!randomSpells.empty()) {
        cout << "Randomly selected spells:" << endl;
        for (Spell* s : randomSpells) {
            cout << s->getName() << endl;  // Imprimir el nombre de cada hechizo
        }
    } else {
        cout << "No spells were selected." << endl;
    }

    Graph dungeons(21);

    // Añadir bordes al gráfico (dungeon map)
    dungeons.addEdge(0, 1, 5);
    dungeons.addEdge(1, 2, 10);
    dungeons.addEdge(2, 3, 3);
    dungeons.addEdge(3, 4, 2);
    dungeons.addEdge(4, 5, 6);
    dungeons.addEdge(5, 6, 4);
    dungeons.addEdge(6, 7, 1);
    dungeons.addEdge(7, 8, 8);
    dungeons.addEdge(8, 9, 9);
    dungeons.addEdge(9, 10, 2);
    dungeons.addEdge(10, 11, 7);
    dungeons.addEdge(11, 12, 5);
    dungeons.addEdge(12, 13, 4);
    dungeons.addEdge(13, 14, 6);
    dungeons.addEdge(14, 15, 1);
    dungeons.addEdge(15, 16, 3);
    dungeons.addEdge(16, 17, 8);
    dungeons.addEdge(17, 18, 2);
    dungeons.addEdge(18, 19, 7);
    dungeons.addEdge(19, 20, 1);

    // Asignar monstruos a los dungeons
    vector<Monster*> dungeonMonsters(20);

    for (int i = 0; i < 20; i++) {
        dungeonMonsters[i] = randomMonsters[i]; // Asignar el monstruo i al dungeon i
    }

    // Mostrar el mapa con los monstruos asignados
    cout << "Mapa de Dungeons y Monstruos asignados:" << endl;
    for (int i = 0; i < 20; i++) {
        cout << "Dungeon " << i + 1 << ": "
             << dungeonMonsters[i]->getName() // Correcto
             << " (CR: " << dungeonMonsters[i]->getCr() << ")" << endl; // Correcto
    }

    // Mostrar la matriz de adyacencia
    dungeons.displayMatrix();

    Dice dice;
    dice.getDice20();

    Manager manager;
    manager.game(player, dungeonMonsters, dungeons);

    return 0;
}
