//Emma Sofia Aparicio Rodríguez A01666223
//Eleanor Alarcón Neri A01665593
//Situación Problema TC1031

#ifndef MONSTER_H
#define MONSTER_H
#include <string>
#include <vector>

using namespace std;

class Monster {
    public:
        Monster();
        Monster(string name,double cr,string type,string size,int ac,int hp,string align);
        ~Monster();
        //Setters and Getters
        void setName(string name);
        void setCr(double cr);
        void setType(string type);
        void setSize(string size);
        void setAc(int ac);
        void setHp(int hp);
        void setAlign(string align);
        void setNext(Monster* nextMonster);
        string getName(void);
        string getType(void);
        string getAlign(void);
        string getSize(void);
        int getAc(void);
        int getHp(void);
        double getCr(void);
        Monster* getNext(void);
        //Methods
        void insert(Monster* newMonster);
        void display();
        void loadFromFile(const string& filename);
        vector<Monster*> getRandomMonsters();
    private:
        string name;
        double cr;
        string type;
        string size;
        int ac;
        int hp;
        string align;
        Monster* next;
        Monster* head;
};

#endif //MONSTER_H

