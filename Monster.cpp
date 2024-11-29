//Emma Sofia Aparicio Rodríguez A01666223
//Eleanor Alarcón Neri A01665593
//Situación Problema TC1031

#include "Graph.h"
#include "Monster.h"
#include "Manager.h"
#include "Spell.h"
#include <iostream>
#include <vector>

using namespace std;

void Manager::chooseSpell(Spell& spellList) {
    // Load spells from file
    spellList.loadFromFile("spells.csv");
    vector<Spell*> randomSpells = spellList.getRandomSpells();

    if (!randomSpells.empty()) {
        cout << "Randomly selected spells:" << endl;
        for (int i = 0; i < randomSpells.size(); ++i) {
            cout << i + 1 << ". " << randomSpells[i]->getName() << endl;
        }

        int choice = -1;
        while (choice < 1 || choice > randomSpells.size()) {
            cout << "Please select a spell by entering the number (1 to " << randomSpells.size() << "): ";
            cin >> choice;

            if (choice < 1 || choice > randomSpells.size()) {
                cout << "Invalid choice. Please choose a number between 1 and " << randomSpells.size() << "." << endl;
            }
        }

        Spell* chosenSpell = randomSpells[choice - 1];
        cout << "\nYou have selected the spell: " << chosenSpell->getName() << endl;
        cout << "Description: " << chosenSpell->getInfo() << endl;
        cout << "Power: " << chosenSpell->getType() << endl;

        // Optionally, remove the spell from the list if needed
        randomSpells.erase(randomSpells.begin() + (choice - 1));
    } else {
        cout << "No spells were selected." << endl;
    }
}

void Manager::game(Player& player, vector<Monster*>& dungeonMonsters, Graph& graph) {
    int conqueredDungeons = 0;
    Dice dice;
    int currentDungeon = dice.getDice20() - 1;

    // Ensure valid dungeon index
    if (currentDungeon >= dungeonMonsters.size()) {
        currentDungeon = dungeonMonsters.size() - 1;
    }

    cout << "The adventure begins!" << endl;
    Monster* currentMonster = dungeonMonsters[currentDungeon];
    cout << "\nYou entered dungeon " << currentDungeon + 1 << " and face " << currentMonster->getName() << endl;

    // Combat phase
    while (player.gethp() > 0 && currentMonster->getHp() > 0) {
        int monsterDamage = dice.getDice10();
        int totalMonsterDamage = monsterDamage;
        player.setlp(player.getlp() - totalMonsterDamage);

        cout << currentMonster->getName() << " attacks and does " << totalMonsterDamage << " damage. HP remaining: " << player.gethp() << endl;

        if (player.gethp() <= 0) {
            cout << "You were defeated by " << currentMonster->getName() << "!" << endl;
            break;
        }

        int playerDamage = dice.getDice10();
        currentMonster->setHp(currentMonster->getHp() - playerDamage);

        cout << "You attack " << currentMonster->getName() << " and do " << playerDamage << " damage. Monster HP: " << currentMonster->getHp() << endl;

        if (currentMonster->getHp() <= 0) {
            cout << "You defeated " << currentMonster->getName() << "!" << endl;
            defeatedMonsters.push_back(currentMonster);
            conqueredDungeons++;
            break;
        }
    }

    // Dungeon exploration after first combat
    while (player.gethp() > 0 && conqueredDungeons < dungeonMonsters.size()) {
        currentDungeon = (currentDungeon + 1) % dungeonMonsters.size();
        currentMonster = dungeonMonsters[currentDungeon];

        cout << "\nYou entered dungeon " << currentDungeon + 1 << " and face " << currentMonster->getName() << endl;

        if (currentMonster->getHp() <= 0) {
            cout << "Monster " << currentMonster->getName() << " is already defeated. Searching for another dungeon..." << endl;
            conqueredDungeons++;
            continue;
        }

        // Repeat combat logic
        while (player.gethp() > 0 && currentMonster->getHp() > 0) {
            int monsterDamage = dice.getDice10();
            int totalMonsterDamage = monsterDamage;
            player.setlp(player.getlp() - totalMonsterDamage);

            cout << currentMonster->getName() << " attacks and does " << totalMonsterDamage << " damage. HP remaining: " << player.gethp() << endl;

            if (player.gethp() <= 0) {
                cout << "You were defeated by " << currentMonster->getName() << "!" << endl;
                break;
            }

            int playerDamage = dice.getDice10();
            currentMonster->setHp(currentMonster->getHp() - playerDamage);

            cout << "You attack " << currentMonster->getName() << " and do " << playerDamage << " damage. Monster HP: " << currentMonster->getHp() << endl;

            if (currentMonster->getHp() <= 0) {
                cout << "You defeated " << currentMonster->getName() << "!" << endl;
                defeatedMonsters.push_back(currentMonster);
                conqueredDungeons++;
                break;
            }
        }
    }

    // End of game
    cout << "\nThe game has ended!" << endl;
    cout << "Monsters defeated: " << defeatedMonsters.size() << endl;
    cout << "Dungeons conquered: " << conqueredDungeons << endl;

    // Manual sorting (bubble sort)
    for (size_t i = 0; i < defeatedMonsters.size(); ++i) {
        for (size_t j = 0; j < defeatedMonsters.size() - i - 1; ++j) {
            if (defeatedMonsters[j]->getName() > defeatedMonsters[j + 1]->getName()) {
                swap(defeatedMonsters[j], defeatedMonsters[j + 1]);
            }
        }
    }

    cout << "\nDefeated monsters (sorted by name):" << endl;
    for (const auto& monster : defeatedMonsters) {
        cout << monster->getName() << " (CR: " << monster->getCr() << ", HP remaining: " << monster->getHp() << ")" << endl;
    }
}

void Manager::healPlayer() {
    Dice dice;
    player.heal(dice);
}

void Manager::printDefeatedMonsters() const {
    // Manual sorting (bubble sort)
    vector<Monster*> sortedMonsters = defeatedMonsters;
    for (size_t i = 0; i < sortedMonsters.size(); ++i) {
        for (size_t j = 0; j < sortedMonsters.size() - i - 1; ++j) {
            if (sortedMonsters[j]->getName() > sortedMonsters[j + 1]->getName()) {
                swap(sortedMonsters[j], sortedMonsters[j + 1]);
            }
        }
    }

    cout << "List of defeated monsters:" << endl;
    for (const auto& monster : sortedMonsters) {
        cout << "Monster: " << monster->getName() << ", Type: " << monster->getType() << ", HP: " << monster->getHp() << endl;
    }
}

void Manager::showDefeatedMonsters() const {
    printDefeatedMonsters();
}


