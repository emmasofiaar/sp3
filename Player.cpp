//Emma Sofia Aparicio Rodríguez A01666223
//Eleanor Alarcón Neri A01665593
//Situación Problema TC1031

#include <iostream>
#include "Player.h"
using namespace std;

// constructor
Player :: Player() {
    cout << "\t HELLO, LET'S CREATE YOUR CHARACTER!" << endl;
    cout << "Enter your nickname: " << endl;
    cin >> name;
    cout << "Enter your species: " << endl;
    cin >> raza;
    hp = 10;
    lp = 100;
    cout << "Ok. This is you: " << endl;
    cout << "Name: " << name << " Raza: " << raza << " HP: " << hp << " LP: " << lp << endl;
}

// constructor parametrizado
Player :: Player(string name, string raza, int hp, int lp)
    : name(name), raza(raza), hp(hp), lp(lp){
    cout << "Parametrized constructor for Player executed" << endl;
}

// destructor
Player :: ~Player(){
 cout << "Destructor for Player executed" << endl;
}

//Setters and getters
void Player::setName(string name){
    this->name = name;
}

void Player::setRaza(string raza){
    this->raza = raza;
}

void Player::sethp(int hp){
    this->hp = hp;
}

void Player::setlp(int lp){
    this->lp = lp;
}

void Player::setDerrotados(vector<Monster>& derrotados) {
    this->derrotados = derrotados;
}

string Player::getName() {
    return name;
}

string Player::getRaza() {
    return raza;
}

int Player::getlp() {
    return lp;
}

int Player :: gethp() {
    return hp;
}

void Player::addDerrotado(Monster& monster) {
    derrotados.push_back(monster);
}

vector<Monster>& Player::getDerrotados()  {
    return derrotados;
}

void Player::heal(Dice& dice) {
     if(lp < 999) {
        int dado = dice.getDice8();
        float healingFactor = dado * 0.10;

        int temp = lp;
        int totalHeal = temp * healingFactor;
        lp += totalHeal;

        if (lp > 999) {
            lp = 999;  // maximo lp es 999
        }

        cout << "-- Player " << name << " healed for " << totalHeal << " life points" << endl;
        cout << "-- Player " << name << " now has " << lp << " life points" << endl;
    }
}


