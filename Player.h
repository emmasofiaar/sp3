//Emma Sofia Aparicio Rodríguez A01666223
//Eleanor Alarcón Neri A01665593
//Situación Problema TC1031

#ifndef PLAYER_H
#define PLAYER_H
#include "Monster.h"
#include "Dice.h"
#include <string>
#include <vector>
using namespace std;

class Player {
    public:
        Player();
        Player(string name, string raza, int hp, int lp);
        ~Player();

        void setName(string name);
        void setRaza(string raza);
        void sethp(int hp);
        void setlp(int lp);
        void setDerrotados(vector<Monster>& derrotados);
        string getName();
        string getRaza();
        int gethp();
        int getlp();
        vector<Monster>& getDerrotados();

        //Methods
        void heal(Dice& dice);
        void addDerrotado(Monster& monster);

    private:
        string name;
        string raza;
        int hp;
        int lp;
        vector<Monster> derrotados;
};

#endif //PLAYER_H
