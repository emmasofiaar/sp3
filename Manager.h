//Emma Sofia Aparicio Rodríguez A01666223
//Eleanor Alarcón Neri A01665593
//Situación Problema TC1031

#ifndef MANAGER_H
#define MANAGER_H
#include <vector>
#include <fstream>
#include "Player.h"
#include "Spell.h"
#include "Graph.h"
#include "Monster.h"  // Asegúrate de incluir el encabezado de Monster si no lo has hecho

using namespace std;

class Manager {
public:
    void chooseSpell(Spell& spellList);
    void dijkstra(Graph& graph, int startIndex);
    void game(Player& player, vector<Monster*>& dungeonMonsters, Graph& graph);
    void healPlayer();
    void printDefeatedMonsters();
    void showDefeatedMonsters();

private:
    Player player;
    vector<Monster*> defeatedMonsters;  // Usamos punteros para almacenar los monstruos derrotados
    vector<Spell> spells;
    vector<string> dungeons;
};

#endif //MANAGER_H
