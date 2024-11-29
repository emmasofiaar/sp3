//Emma Sofia Aparicio Rodríguez A01666223
//Eleanor Alarcón Neri A01665593
//Situación Problema TC1031

#ifndef SPELL_H
#define SPELL_H
#include <string>
using namespace std;

class Spell {
    public:
        Spell();
        Spell(string name, string type, string info);
        ~Spell();
        //Setters and Getters
        void setName(string name);
        void setType(string type);
        void setInfo(string info);
        void setSpell(Spell* nextSpell);
        string getName(void);
        string getType(void);
        string getInfo(void);
        Spell* getNext(void);
        //Methods
        void insert(Spell* newSpell);
        void display();
        void loadFromFile(const string& filename);
        vector<Spell*> getRandomSpells();
    private:
        string name;
        string type;
        string info;
        Spell* next;
        Spell* head;
};

#endif //SPELL_H
