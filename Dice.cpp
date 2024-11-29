//Eleanor Alarcón Neri A01665593
// Emma Sofia Aparicio Rodriguez A01666223
//Situación Problema TC1031

#include "Dice.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

// constructor
Dice :: Dice() : dicelp(1), dicehp(1), dicecb(1) {srand(time(0));}

// constructor parametrizado
Dice::Dice(int dicelp, int dicehp, int dicecb) : dicelp(dicelp), dicehp(dicehp), dicecb(dicecb){
    cout << "Parameterized constructor for dice executed" << endl;
}

Dice :: ~Dice(){}

//Setters and getters
void Dice::setDice8(int dicelp) {
    this->dicelp = dicelp;
}

void Dice::setDice10(int dicehp) {
    this->dicehp = dicehp;
}

void Dice::setDice20(int dicecb) {
    this->dicecb = dicecb;
}

int Dice::getDice8(void) {
    return rand() % 8 + 1;
}

int Dice::getDice10(void) {
    return rand() % 10 + 1;
}

int Dice::getDice20(void) {
    return  rand() % 20 + 1;
}



