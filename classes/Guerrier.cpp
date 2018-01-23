#include "Guerrier.h"
#include <iostream>


using namespace std;

//Constructeur
Guerrier::Guerrier(string nom) : Personnage(nom){};

//Méthodes de magicien virtuelles ici
void Guerrier::soigner(Personnage& cible, int points){}
void Guerrier::bouleDeFeu(Personnage &cible, int duree, int coutMana){}
void Guerrier::gel(Personnage &cible, int coutMana){}

//getter
string Guerrier::getClasse() const //renvoie la classe
{
    return "Guerrier";
}

//Destructeur
Guerrier::~Guerrier(){}
