//Emma Sofia Aparicio Rodríguez A01666223
//Eleanor Alarcón Neri A01665593
//Situación Problema TC1031
#include "Dice.h"
#include "Graph.h"
#include "Monster.h"
#include "Manager.h"
#include "Spell.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void Manager::chooseSpell(Spell& spellList) {
    // Load spells from file
    spellList.loadFromFile("spells.csv");
    vector<Spell*> randomSpells = spellList.getRandomSpells();

    if (!randomSpells.empty()) {
        // Show the list of spells to choose from
        cout << "Randomly selected spells:" << endl;
        for (int i = 0; i < randomSpells.size(); ++i) {
            cout << i + 1 << ". " << randomSpells[i]->getName() << endl;
        }

        // Ask the player to pick a spell
        int choice = -1;
        while (choice < 1 || choice > randomSpells.size()) {
            cout << "Please select a spell by entering the number (1 to " << randomSpells.size() << "): ";
            cin >> choice;

            // Ensure the input is valid
            if (choice < 1 || choice > randomSpells.size()) {
                cout << "Invalid choice. Please choose a number between 1 and " << randomSpells.size() << "." << endl;
            }
        }

        // Now that the player has chosen, show the details of the chosen spell
        Spell* chosenSpell = randomSpells[choice - 1];  // Get the selected spell
        cout << "\nYou have selected the following spell: " << chosenSpell->getName() << endl;
        cout << "Description: " << chosenSpell->getInfo() << endl;
        cout << "Power: " << chosenSpell->getType() << endl;

        // Optionally, remove the spell from the list if you no longer need it
        randomSpells.erase(randomSpells.begin() + (choice - 1)); // Remove from vector if needed

        // You can now store the selected spell or use it for further actions
        // For example, you could add it to the player's spell inventory or use it in combat
    } else {
        cout << "No spells were selected." << endl;
    }
}

void Manager::game(Player& player, vector<Monster*>& dungeonMonsters, Graph& graph) {

    vector<Monster*> defeatedMonsters; // Lista de monstruos derrotados
    int conqueredDungeons = 0;         // Contador de calabozos conquistados
    int currentDungeon = 0;            // Índice del calabozo actual

    Dice dice; // Instancia del dado

    // El jugador empieza en un calabozo aleatorio basado en el dado de 20 caras
    currentDungeon = dice.getDice20() - 1;

    if (currentDungeon >= dungeonMonsters.size()) {
        currentDungeon = dungeonMonsters.size() - 1;
    }

    cout << "¡Comienza la aventura!" << endl;

    // Fase inicial: Primer combate sin usar Dijkstra
    Monster* currentMonster = dungeonMonsters[currentDungeon];
    cout << "\nLlegaste al calabozo " << currentDungeon + 1 << " con el monstruo " << currentMonster->getName() << endl;

    // Si el monstruo ya está derrotado, busca otro calabozo
    if (currentMonster->getHp() <= 0) {
        cout << "El monstruo " << currentMonster->getName() << " ya está derrotado. Buscando otro calabozo..." << endl;
        conqueredDungeons++;
    }

    // Combatir hasta que el jugador o el monstruo sean derrotados
    while (player.gethp() > 0 && currentMonster->getHp() > 0) {
        // Ataque del monstruo
        int monsterDamage = dice.getDice10();  // Ejemplo de daño adicional generado por el dado
        float realDamage = monsterDamage * 0.10;
        int totalDamage = realDamage * currentMonster->getHp();
        int vida = player.getlp() - totalDamage;// Multiplicamos el daño base por la vida del monstruo
        player.setlp(vida);
        cout << currentMonster->getName() << " te ataca y hace " << totalDamage << " de dano. HP restante: " << player.gethp() << endl;

        if (player.getlp() <= 0) {
            cout << "¡Has sido derrotado por " << currentMonster->getName() << "!" << endl;
            break;
        }

        // Ataque del jugador
        int playerDamage = dice.getDice10();  // Ejemplo de daño adicional generado por el dado
        float realDamagee = playerDamage * 0.10;
        int totalDamagee = realDamagee * player.gethp();  // Multiplicamos el daño base por la vida del monstruo
        currentMonster->setHp(currentMonster->getHp() - totalDamagee);
        cout << "Atacas a " << currentMonster->getName() << " y haces " << playerDamage << " de daño. HP restante del monstruo: " << currentMonster->getHp() << endl;

        if (currentMonster->getHp() <= 0) {
            cout << "¡Has derrotado a " << currentMonster->getName() << "!" << endl;
            defeatedMonsters.push_back(currentMonster); // Registrar monstruo derrotado
            conqueredDungeons++;
            break;
        }
    }


    // Después del primer combate, usar DFS para encontrar el camino más corto
    while (player.gethp() > 0 && conqueredDungeons < dungeonMonsters.size()) {
        if (conqueredDungeons > 0) {  // Solo aplica DFS después de conquistar al menos un calabozo
            graph.DFS(currentDungeon);  // Realizar DFS desde el calabozo actual
        }

        // Aquí no necesitamos un "path" como con Dijkstra, ya que DFS no necesariamente da el camino más corto.
        // El calabozo siguiente se determinará de alguna manera (puede ser el siguiente vecino en el DFS).
        currentDungeon = (currentDungeon + 1) % dungeonMonsters.size();  // Ejemplo simple de avanzar al siguiente calabozo

        currentMonster = dungeonMonsters[currentDungeon];
        cout << "\nLlegaste al calabozo " << currentDungeon + 1 << " con el monstruo " << currentMonster->getName() << endl;

        // Si el monstruo ya está derrotado, avanzar al siguiente calabozo
        if (currentMonster->getHp() <= 0) {
            cout << "El monstruo " << currentMonster->getName() << " ya está derrotado. Buscando otro calabozo..." << endl;
            conqueredDungeons++;
            continue;
        }

        // Combate del jugador con el monstruo
        while (player.gethp() > 0 && currentMonster->getHp() > 0) {
            int monsterDamage = dice.getDice10();  // Ejemplo de daño adicional generado por el dado
            float realDamage = monsterDamage * 0.10;
            int totalDamage = realDamage * currentMonster->getHp();  // Multiplicamos el daño base por la vida del monstruo
            player.setlp(player.getlp() - totalDamage);
            cout << currentMonster->getName() << " te ataca y hace " << totalDamage << " de daño. HP restante: " << player.gethp() << endl;

            if (player.gethp() <= 0) {
                cout << "¡Has sido derrotado por " << currentMonster->getName() << "!" << endl;
                break;
            }

            int playerDamage = dice.getDice10();  // Ejemplo de daño adicional generado por el dado
            float realDamagee = playerDamage * 0.10;
            int totalDamagee = realDamagee * player.gethp();  // Multiplicamos el daño base por la vida del monstruo
            currentMonster->setHp(currentMonster->getHp() - totalDamagee);
            cout << "Atacas a " << currentMonster->getName() << " y haces " << playerDamage << " de daño. HP restante del monstruo: " << currentMonster->getHp() << endl;

            if (currentMonster->getHp() <= 0) {
                cout << "¡Has derrotado a " << currentMonster->getName() << "!" << endl;
                defeatedMonsters.push_back(currentMonster); // Registrar monstruo derrotado
                // Recuperación de vida
                if (player.getlp() > 0) {
                    player.heal(dice);
                }
                conqueredDungeons++;
                break;
            }
        }


    }

    // Fin del juego
    cout << "\n¡El juego ha terminado!" << endl;
    cout << "Monstruos derrotados: " << defeatedMonsters.size() << endl;
    cout << "Calabozos conquistados: " << conqueredDungeons << endl;

    // Ordenar los monstruos derrotados por nombre
    sort(defeatedMonsters.begin(), defeatedMonsters.end(),
         [](Monster* a, Monster* b) { return a->getName() < b->getName(); });

    cout << "\nLista de monstruos derrotados (ordenados por nombre):" << endl;
    for (Monster* monster : defeatedMonsters) {
        cout << monster->getName() << " (CR: " << monster->getCr() << ", HP restante: " << monster->getHp() << ")" << endl;
    }
}

void Manager::healPlayer() {
    Dice dice;  // Crear una instancia de Dice
    player.heal(dice);
}

void Manager::printDefeatedMonsters() {
    vector<Monster>& defeatedMonsters = player.getDerrotados();
    sort(defeatedMonsters.begin(), defeatedMonsters.end(), []( Monster& m1, Monster& m2) {
        return m1.getName() < m2.getName();  // Sort alphabetically by monster name
    });

    cout << "List of defeated monsters:" << endl;
    for (Monster& monster : defeatedMonsters) {
        cout << "Monster: " << monster.getName() << ", Type: " << monster.getType() << ", HP: " << monster.getHp() << endl;
    }
}

void Manager::showDefeatedMonsters() {
    printDefeatedMonsters();
}
